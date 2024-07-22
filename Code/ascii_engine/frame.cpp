#include "frame.h"
#include "error_codes.h"

#ifdef __linux__
#include <algorithm>
#endif

frame::frame(bool start_logger, std::string logging_file_path)
{
	if (start_logger)
	{
		int logger_status = log.start_widget_logging(logging_file_path, FRAME);
		if (logger_status != 0)
		{
			ascii_io::clear();
			ascii_io::print("frame initialization: Invalid logger path.\nPress any button to continue.");
			ascii_io::getchar();
		}
	}
}

void frame::display()
{
	std::string output = get_frame_output();
#ifdef WIN32
	int x = 0;
	int y = 0;
	ascii_io::get_terminal_size(x, y);
	if ((x != previous_x) || (y != previous_y))
	{
		ascii_io::clear();
	}
	else
	{
		ascii_io::reset();
		format_tools::mask_string(output, previous_output);
	}
	ascii_io::print(output);
	previous_output = output;
	previous_x = x;
	previous_y = y;
#elif __linux__
	ascii_io::clear();
	ascii_io::print(output);
#endif
}

void frame::set_controls(int select, int quit, int up, int down, int right, int left)
{
	_select = select;
	_quit = quit;
	_up = up;
	_down = down;
	_right = right;
	_left = left;
}

int frame::get_selection()
{
	int input = 0;
	int selected_row = 0;
	int last_selected_row = 0;
	int selected_column = 0;
	int last_selected_column = 0;
	int selected_level = 0;
	int last_selected_level = 0;
	int selected_id = -1;
	int x = 0;
	int y = 0;
	int last_x = 0;
	int last_y = 0;
	do
	{
		if (selected_column >= (int)get_columns_in_row(selected_row))
		{
			selected_column = (int)get_columns_in_row(selected_row) - 1;
		}
		
		ascii_io::get_terminal_size(x, y);
		if (x != last_x || y != last_y)
		{
			display();
		}
		last_x = x;
		last_y = y;
		unhighlight(last_selected_row, last_selected_column, last_selected_level);
		highlight(selected_row, selected_column, selected_level);
		last_selected_row = selected_row;
		last_selected_column = selected_column;
		last_selected_level = selected_level;
		input = ascii_io::getchar();
		if (input == _select)
		{
			widget_info item;
			get_widget(selected_row, selected_column, selected_level, item);
			if (std::count(selectable_widgets.begin(), selectable_widgets.end(), item.widget_type) != 0)
			{
				selected_id = item.id;
				break;
			}
		}
		else if (input == _up)
		{
			if (((selected_level - 1) >= 0) && (get_levels(selected_row, selected_column) > 1))
			{
				selected_level--;
			}
			else if ((selected_row - 1) >= 0)
			{
				selected_row--;
				selected_level = get_levels(selected_row, selected_column) - 1;
			}
		}
		else if (input == _down)
		{
			if (((selected_level + 1) < get_levels(selected_row, selected_column)) && (get_levels(selected_row, selected_column) > 1))
			{
				selected_level++;
			}
			else if ((selected_row + 1) < (int)get_total_rows())
			{
				selected_row++;
				selected_level = 0;
			}
		}
		else if (input == _right)
		{
			if ((selected_column + 1) < (int)get_columns_in_row(selected_row))
			{
				selected_column++;
				if (selected_level >= get_levels(selected_row, selected_column))
				{
					selected_level = get_levels(selected_row, selected_column) - 1;
				}
			}
		}
		else if (input == _left)
		{
			if ((selected_column - 1) >= 0)
			{
				selected_column--;
				if (selected_level >= get_levels(selected_row, selected_column))
				{
					selected_level = get_levels(selected_row, selected_column) - 1;
				}
			}
		}
	} while (input != _quit);
	return selected_id;
}

void frame::set_row_width_weight(float weight, unsigned int row)
{
	if ((weight < 0) || (weight > 1.0))
	{
		log.log_status(INVALID_VALUE, "frame::set_row_width_weight");
		return;
	}

	if (row_width_weights.find(row) != row_width_weights.end())
	{
		row_width_weights.erase(row);
	}

	row_width_weights.insert({ row, weight });
	log.log_status(SUCCESS, "frame::set_row_width_weight");
}

void frame::set_coordinate_width_multiplier(float multiplier, int row, int column)
{
	if ((multiplier < 0) || (row < 0) || (column < 0))
	{
		log.log_status(INVALID_VALUE, "frame::set_coordinate_width_multiplier");
		return;
	}

	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column))
		{
			widgets[i].width_multiplier = multiplier;
		}
		status = SUCCESS;
	}
	log.log_status(status, "frame::set_coordinate_width_multiplier");
}

int frame::add_widget()
{
	int id = generate_widget_id();
	widget_info new_widget;
	new_widget.id = id;
	widgets.push_back(new_widget);
	return id;
}

int frame::append(int id, std::string special_operation)
{
	if (special_operation == special_operation_new_line)
	{
		append_row++;
		append_column = 0;
		append_level = 0;
	}
	else if (special_operation == special_operation_none)
	{
		append_column++;
		append_level = 0;
	}
	else if (special_operation != special_operation_merge)
	{
		throw std::string("Unrecognized operation");
	}

	if (append_column < 0)
	{
		append_column = 0;
	}

	int status = set_position(id, append_row, append_column, append_level);
	append_level++;
	return status;
}

int frame::set_position(int id, int row, int column, int level)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].row = row;
			widgets[i].column = column;
			widgets[i].level = level;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_output(int id, const std::string& output)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].output = output;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_alignment(int id, std::string alignment)
{
	int status = ELEMENT_NOT_FOUND;
	if ((alignment == format_tools::right_alignment_keyword) || (alignment == format_tools::left_alignment_keyword) || (alignment == format_tools::center_alignment_keyword))
	{
		for (unsigned int i = 0; i < widgets.size(); i++)
		{
			if (widgets[i].id == id)
			{
				widgets[i].alignment = alignment;
				status = SUCCESS;
				break;
			}
		}
	}
	return status;
}

int frame::set_spacing(int id, int top, int bottom, int left, int right)
{
	if ((top < 0) || (bottom < 0) || (right < 0) || (left < 0))
	{
		return INVALID_VALUE;
	}

	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].top_spacing = top;
			widgets[i].bottom_spacing = bottom;
			widgets[i].right_spacing = right;
			widgets[i].left_spacing = left;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_border_spacing(int id, int top, int bottom, int right, int left)
{
	if ((top < 0) || (bottom < 0) || (right < 0) || (left < 0))
	{
		return INVALID_VALUE;
	}

	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			if ((widgets[i].top_spacing >= top) && (widgets[i].bottom_spacing >= bottom) && (widgets[i].right_spacing >= right) && (widgets[i].left_spacing >= left))
			{
				widgets[i].top_border_spacing = top;
				widgets[i].bottom_border_spacing = bottom;
				widgets[i].right_border_spacing = right;
				widgets[i].left_border_spacing = left;
				status = SUCCESS;
			}
			else
			{
				status = INVALID_VALUE;
			}
			break;
		}
	}
	return status;
}

int frame::set_widget_type(int id, int type)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].widget_type = type;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_vertical_border(int id, char border)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].vertical_border = border;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_horizontal_border(int id, char border)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].horizontal_border = border;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_corner_border(int id, char border)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].corner_border = border;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_highlight_character(int id, char character)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].highlight_character = character;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_x_origin(int id, int x_origin)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].x_origin = x_origin;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_y_origin(int id, int y_origin)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].y_origin = y_origin;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::add_border(int id)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].add_border = true;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

void frame::highlight(int row, int column, int level)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column) && (widgets[i].level == level))
		{
			int x_origin = 0;
			int y_origin = 0;
			get_x_origin(widgets[i].id, x_origin);
			get_y_origin(widgets[i].id, y_origin);
			unsigned int width = get_widget_width(widgets[i], false);
			unsigned int height = get_widget_height(widgets[i], false);
			
			int x = x_origin - 2 - widgets[i].left_border_spacing;
			int y = y_origin - 1 - widgets[i].top_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_curser_to_position(x, y);
			ascii_io::print(std::string(1, widgets[i].highlight_character));

			x = x_origin + (int)width + 1 + widgets[i].right_border_spacing;
			y = y_origin - 1 - widgets[i].top_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_curser_to_position(x, y);
			ascii_io::print(std::string(1, widgets[i].highlight_character));

			x = x_origin - 2 - widgets[i].left_border_spacing;
			y = y_origin + (int)height  + widgets[i].bottom_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_curser_to_position(x, y);
			ascii_io::print(std::string(1, widgets[i].highlight_character));

			x = x_origin + (int)width + 1 + widgets[i].left_border_spacing;
			y = y_origin + (int)height + widgets[i].bottom_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_curser_to_position(x, y);
			ascii_io::print(std::string(1, widgets[i].highlight_character));
			status = SUCCESS;
			break;
		}
	}
	log.log_status(status, "frame::highlight");
}

void frame::unhighlight(int row, int column, int level)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column) && (widgets[i].level == level))
		{
			char corner_character = ' ';
			if (widgets[i].add_border)
			{
				corner_character = widgets[i].corner_border;
			}
			int x_origin = 0;
			int y_origin = 0;
			get_x_origin(widgets[i].id, x_origin);
			get_y_origin(widgets[i].id, y_origin);
			unsigned int width = get_widget_width(widgets[i], false);
			unsigned int height = get_widget_height(widgets[i], false);

			int x = x_origin - 2 - widgets[i].left_border_spacing;
			int y = y_origin - 1 - widgets[i].top_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_curser_to_position(x, y);
			ascii_io::print(std::string(1, corner_character));

			x = x_origin + (int)width + 1 + widgets[i].right_border_spacing;
			y = y_origin - 1 - widgets[i].top_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_curser_to_position(x, y);
			ascii_io::print(std::string(1, corner_character));

			x = x_origin - 2 - widgets[i].left_border_spacing;
			y = y_origin + (int)height  + widgets[i].bottom_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_curser_to_position(x, y);
			ascii_io::print(std::string(1, corner_character));

			x = x_origin + (int)width + 1 + widgets[i].left_border_spacing;
			y = y_origin + (int)height + widgets[i].bottom_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_curser_to_position(x, y);
			ascii_io::print(std::string(1, corner_character));
			status = SUCCESS;
			break;
		}
	}
	log.log_status(status, "frame::unhighlight");
}

void frame::keep_point_in_console_bounds(int& x, int& y)
{
	int max_x = 0;
	int max_y = 0;
	ascii_io::get_terminal_size(max_x, max_y);
	if (x < 0)
	{
		x = 0;
	}
	else if (x >= max_x)
	{
		x = max_x - 1;
	}

	if (y < 0)
	{
		y = 0;
	}
	else if (y >= max_y)
	{
		y = max_y - 1;
	}
}

bool frame::widget_exists(int id)
{
	bool exists = false;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			exists = true;
			break;
		}
	}
	return exists;
}

bool frame::widget_exists(int row, int column)
{
	bool exists = false;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column))
		{
			exists = true;
			break;
		}
	}
	return exists;
}

int frame::get_levels(int row, int column)
{
	int count = 0;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column))
		{
			count++;
		}
	}
	return count;
}

int frame::get_lines_count(int id, int& lines_count)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			lines_count = widgets[i].lines_count;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_x_origin(int id, int& x_origin)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			if (widgets[i].x_origin == -1)
			{
				status = UNDEFINED;
			}
			else
			{
				x_origin = widgets[i].x_origin;
				status = SUCCESS;
			}
			break;
		}
	}
	return status;
}

int frame::get_y_origin(int id, int& y_origin)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			if (widgets[i].y_origin == -1)
			{
				status = UNDEFINED;
			}
			else
			{
				y_origin = widgets[i].y_origin;
				status = SUCCESS;
			}
			break;
		}
	}
	return status;
}

int frame::get_alignment(int id, std::string& alignment)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			alignment = widgets[i].alignment;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

float frame::get_width_weight(widget_info item)
{
	float total_width_multiplier = item.width_multiplier;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == item.row) && (widgets[i].level == 0) && (widgets[i].column != item.column))
		{
			total_width_multiplier = total_width_multiplier + widgets[i].width_multiplier;
		}
	}

	return (item.width_multiplier / total_width_multiplier);
}

int frame::set_lines_count(int id, int lines_count)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].lines_count = lines_count;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::generate_widget_id()
{
	int id = widgets.size();
	return id;
}

std::vector<int> frame::get_row_ids(int row)
{
	std::vector<int> ids;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].row == row)
		{
			ids.push_back(widgets[i].id);
		}
	}
	return ids;
}

std::vector<std::vector<int>> frame::sort_row_ids(std::vector<int> ids)
{
	std::vector<widget_info> widgets_vec;
	for (unsigned int i = 0; i < ids.size(); i++)
	{
		widget_info item;
		get_widget(ids[i], item);
		widgets_vec.push_back(item);
	}

	unsigned int widgets_vec_length = widgets_vec.size();
	std::vector<widget_info> sorted_widgets;
	for (unsigned int i = 0; i < widgets_vec_length; i++)
	{
		int index = get_min_column_index(widgets_vec);
		sorted_widgets.push_back(widgets_vec[index]);
		widgets_vec.erase(widgets_vec.begin() + index);
	}
	
	std::vector<std::vector<int>> sorted_ids;
	while(sorted_widgets.size() > 0)
	{
		std::vector<widget_info> level_group;
		level_group.push_back(sorted_widgets[0]);
		sorted_widgets.erase(sorted_widgets.begin());
		for (unsigned int i = 0; i < sorted_widgets.size(); i++)
		{
			if ((level_group[0].row == sorted_widgets[i].row) && (level_group[0].column == sorted_widgets[i].column))
			{
				level_group.push_back(sorted_widgets[i]);
				sorted_widgets.erase(sorted_widgets.begin() + i);
				i--;
			}
		}

		std::vector<int> sorted_id_group;
		if (level_group.size() > 1)
		{
			unsigned int id_group_length = level_group.size();
			for (unsigned int k = 0; k < id_group_length; k++)
			{
				int index = get_min_level_index(level_group);
				sorted_id_group.push_back(level_group[index].id);
				level_group.erase(level_group.begin() + index);
			}
		}
		else
		{
			sorted_id_group.push_back(level_group[0].id);
		}
		sorted_ids.push_back(sorted_id_group);
	}
	return sorted_ids;
}

int frame::get_min_column_index(const std::vector<widget_info>& widget_vec)
{
	int min_index = 0;
	int min_column = 0;
	if (widget_vec.size() > 0)
	{
		min_index = 0;
		min_column = widget_vec[min_index].column;
		for (unsigned int i = 1; i < widget_vec.size(); i++)
		{
			if (widget_vec[i].column < min_column)
			{
				min_index = i;
				min_column = widget_vec[min_index].column;
			}
		}
	}
	return min_index;
}

int frame::get_min_level_index(const std::vector<widget_info>& widget_vec)
{
	int min_index = 0;
	int min_level = 0;
	if (widget_vec.size() > 0)
	{
		min_index = 0;
		min_level = widget_vec[min_index].level;
		for (unsigned int i = 1; i < widget_vec.size(); i++)
		{
			if (widget_vec[i].level < min_level)
			{
				min_index = i;
				min_level = widget_vec[min_index].level;
			}
		}
	}
	return min_index;
}

bool frame::in_range(int value, int begin, int end)
{
	bool in = false;
	if ((value >= begin) || (value < end))
	{
		in = true;
	}
	return in;
}

int frame::get_output(int id, std::string& output)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			output = widgets[i].output;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_widget(int id, widget_info& return_value)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			return_value = widgets[i];
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_widget(int row, int column, int level, widget_info& return_value)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column) && (widgets[i].level == level))
		{
			return_value = widgets[i];
			status = SUCCESS;
			break;
		}
	}
	return status;
}

unsigned int frame::get_widget_width(const widget_info& item, bool include_spacing)
{
	int x = 0;
	int y = 0;
	ascii_io::get_terminal_size(x, y);
	float row_multiplier = 1.0;
	auto updated_row_multiplier = row_width_weights.find(item.row);
	if (updated_row_multiplier != row_width_weights.end())
	{
		row_multiplier = updated_row_multiplier->second;
	}
	int raw_width = int(x * get_width_weight(item) * row_multiplier);
	if(!include_spacing)
	{
		raw_width = raw_width - item.left_spacing - item.right_spacing;
		if (item.add_border)
		{
			raw_width = raw_width - 4;
		}
	}
	unsigned int width = 0;
	if (raw_width >= 0)
	{
		width = (unsigned int)raw_width;
	}
	else
	{
		log.log_begin("frame::get_widget_width");
		log.log_comment("Widget id: " + std::to_string(item.id) + " has zero width.");
		log.log_end("frame::get_widget_width");
	}
	return width;
}

int frame::get_widget_width(int id, unsigned int& width, bool include_spacing)
{
	int status = ELEMENT_NOT_FOUND;
	widget_info item;
	status = get_widget(id, item);
	if (status == SUCCESS)
	{
		width = get_widget_width(item, include_spacing);
	}
	return status;
}

unsigned int frame::get_widget_height(const widget_info& item, bool include_spacing)
{
	int raw_height = 0;
	if (!include_spacing)
	{
		raw_height = item.lines_count - item.top_spacing - item.bottom_spacing;
		if (item.add_border)
		{
			raw_height = raw_height - 2;
		}
	}
	else
	{
		raw_height = item.lines_count;
	}

	unsigned int height = 0;
	if (raw_height >= 0)
	{
		height = (unsigned int)raw_height;
	}
	else
	{
		log.log_begin("frame::get_widget_height");
		log.log_comment("Widget id: " + std::to_string(item.id) + " has zero height.");
		log.log_end("frame::get_widget_height");
	}
	return height;
}

int frame::get_widget_height(int id, unsigned int& height, bool include_spacing)
{
	int status = ELEMENT_NOT_FOUND;
	widget_info item;
	status = get_widget(id, item);
	if (status == SUCCESS)
	{
		height = get_widget_height(item, include_spacing);
	}
	return status;
}

std::vector<std::string> frame::get_widget_lines(int id)
{
	widget_info item;
	get_widget(id, item);
	std::string left_spacing = format_tools::get_spacing(item.left_spacing, ' ');
	std::string right_spacing = format_tools::get_spacing(item.right_spacing, ' ');
	unsigned int width = get_widget_width(item, false);
	std::string active_spacing = format_tools::get_spacing(width, ' ');
	std::vector<std::string> widget_lines;
	std::vector<std::string> user_lines = format_tools::split_string(item.output, '\n');
	std::string line = "";
	for (int i = 0; i < item.top_spacing; i++)
	{
		widget_lines.push_back(active_spacing);
	}

	for (unsigned int i = 0; i < user_lines.size(); i++)
	{
		if (user_lines[i] == "\n")
		{
			line = format_tools::fill_line(line, width, item.alignment);
			widget_lines.push_back(line);
			line = "";
		}
		else
		{
			std::vector<std::string> words = format_tools::split_string(user_lines[i], ' ');
			for (unsigned int j = 0; j < words.size(); j++)
			{
				if ((((line + words[j]).length())) <= width)
				{
					line = line + words[j];
				}
				else if (words[j].length() >= width)
				{
					std::string first_section = "";
					std::string second_section = "";
					format_tools::cut_word(words[j], width - line.length(), first_section, second_section);
					line = line + first_section;
					widget_lines.push_back(line);
					line = "";
					if (item.widget_type == LABEL)
					{
						second_section.insert(0, "-");
					}
					words.insert(words.begin() + (j + 1), second_section);
				}
				else
				{
					line = format_tools::fill_line(line, width, item.alignment);
					widget_lines.push_back(line);
					if (words[j] != " ")
					{
						line = words[j];
					}
					else
					{
						line = "";
					}
					
				}
			}
		}
	}
	if (line != "")
	{
		line = format_tools::fill_line(line, width, item.alignment);
		widget_lines.push_back(line);
		line = "";
	}

	for (int i = 0; i < item.bottom_spacing; i++)
	{
		widget_lines.push_back(active_spacing);
	}

	for (unsigned int i = 0; i < widget_lines.size(); i++)
	{
		widget_lines[i].insert(0, left_spacing);
		widget_lines[i] = widget_lines[i] + right_spacing;
	}
	return widget_lines;
}

bool frame::element_exists(const std::vector<int>& storage, int element)
{
	bool exists = false;
	for (unsigned int i = 0; i < storage.size(); i++)
	{
		if (storage[i] == element)
		{
			exists = true;
			break;
		}
	}
	return exists;
}

unsigned int frame::get_total_rows()
{
	std::vector<int> rows;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (!element_exists(rows, widgets[i].row))
		{
			rows.push_back(widgets[i].row);
		}
	}
	return rows.size();
}

unsigned int frame::get_columns_in_row(int row)
{
	std::vector<int> row_ids = get_row_ids(row);
	std::vector<int> columns;
	for (unsigned int i = 0; i < row_ids.size(); i++)
	{
		widget_info item;
		get_widget(row_ids[i], item);
		if (!element_exists(columns, item.column))
		{
			columns.push_back(item.column);
		}
	}
	return columns.size();
}

std::string frame::get_frame_output()
{
	std::string frame_output = "";
	int total_rows = get_total_rows();
	row_heights.clear();
	format_tools::text_column column_data;
	for (int i = 0; i < total_rows; i++)
	{
		std::vector<std::vector<int>> row_ids = sort_row_ids(get_row_ids(i));
		widget_info item;
		for (unsigned int j = 0; j < row_ids.size(); j++)
		{
			std::vector<std::string> accumulated_widget_lines;
			for (unsigned int m = 0; m < row_ids[j].size(); m++)
			{
				std::vector<std::string> widget_lines;
				widget_lines = get_widget_lines((row_ids[j])[m]);
				get_widget((row_ids[j])[m], item);
				if (item.add_border)
				{
					int top_spacing = item.top_spacing - item.top_border_spacing;
					int left_spacing = item.left_spacing - item.left_border_spacing;
					int middle_spacing = get_widget_width(item, false) + 2 + item.left_border_spacing + item.right_border_spacing;
					int right_spacing = item.right_spacing - item.right_border_spacing;
					int bottom_spacing = item.bottom_spacing - item.bottom_border_spacing;
					for (unsigned int k = 0; k < widget_lines.size(); k++)
					{
						if (k < (unsigned int)(top_spacing) || (k > (widget_lines.size() - bottom_spacing - 1)))
						{
							widget_lines[k].insert(left_spacing, "  ");
							widget_lines[k].insert(widget_lines[k].length() - right_spacing, "  ");
						}
						else
						{
							widget_lines[k].insert(left_spacing, std::string(1, item.vertical_border) + " ");
							widget_lines[k].insert(widget_lines[k].length() - right_spacing, " " + std::string(1, item.vertical_border));
						}
					}
					widget_lines.insert(widget_lines.begin() + top_spacing, format_tools::get_spacing(left_spacing, ' ') + std::string(1, item.corner_border) + format_tools::get_spacing(middle_spacing, item.horizontal_border) + std::string(1, item.corner_border) + format_tools::get_spacing(right_spacing, ' '));
					widget_lines.insert(widget_lines.end() - bottom_spacing, format_tools::get_spacing(left_spacing, ' ') + std::string(1, item.corner_border) + format_tools::get_spacing(middle_spacing, item.horizontal_border) + std::string(1, item.corner_border) + format_tools::get_spacing(right_spacing, ' '));
				}
				set_lines_count(item.id, widget_lines.size());
				accumulated_widget_lines.insert(accumulated_widget_lines.end(), widget_lines.begin(), widget_lines.end());
			}
			column_data.text.push_back(accumulated_widget_lines);
			column_data.width.push_back(get_widget_width(item, true));
		}
		unsigned int row_lines = 0;
		frame_output = frame_output + format_tools::fuse_columns_into_row(column_data, row_lines);
		row_heights.push_back(row_lines);
		column_data.text.clear();
		column_data.width.clear();
	}
	set_widget_origins();
	return frame_output;
}

void frame::set_widget_origins()
{
	int column = 0;
	int level = 0;
	unsigned int x = 0;
	unsigned int y = 0;
	widget_info item;
	for(unsigned int row = 0; row < row_heights.size(); row++)
	{
		x = 0;
		column = 0;
		while (get_widget(row, column, level, item) != ELEMENT_NOT_FOUND)
		{
			unsigned int y_origin = y;
			do
			{
				unsigned int x_origin = x + item.left_spacing;
				y_origin = y_origin + item.top_spacing;
				if (item.add_border)
				{
					x_origin = x_origin + 2;
					y_origin = y_origin + 1;
				}
				set_x_origin(item.id, x_origin);
				set_y_origin(item.id, y_origin);
				if (item.add_border)
				{
					y_origin = y_origin - 1;
				}
				y_origin = y_origin - item.top_spacing;
				y_origin = y_origin + get_widget_height(item, true);
				level++;
			} while (get_widget(row, column, level, item) != ELEMENT_NOT_FOUND);
			level = 0;
			column++;
			x = x + get_widget_width(item, true);
		}
		y = y + row_heights[row];
	}
}