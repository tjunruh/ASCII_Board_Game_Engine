#include "../ascii_engine_dll_files/pch.h"
#include "frame.h"
#include "error_codes.h"
#include <cmath>
#include <algorithm>


frame::frame(bool start_logger, const std::string& logging_file_path)
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

	ascii_io::get_terminal_size(terminal_x, terminal_y);
}

frame::~frame()
{
	widgets.clear();
}

void frame::display()
{
	std::string output = generate_frame_output();
#ifdef WIN32
	if ((terminal_x != previous_x) || (terminal_y != previous_y))
	{
		ascii_io::clear();
	}
	else
	{
		std::vector<format_tools::index_format> index_regions;
		std::vector<int> ignore_flags;
		ascii_io::move_cursor_to_position(0, 0);
	}
#elif __linux__
	ascii_io::clear();
#endif
	if (_dec_enabled || _color_enabled)
	{
		std::vector<format_tools::index_format> index_regions;
		if (_color_enabled)
		{
			index_regions = format_tools::convert(color_regions, format_tools::get_first_line_length(output));
		}

		if (_dec_enabled)
		{
			std::vector<format_tools::index_format> dec_regions = dec.format(output);
			if (index_regions.size() > 0)
			{
				index_regions = format_tools::combine(index_regions, dec_regions);
			}
			else
			{
				index_regions = dec_regions;
			}
		}

		std::vector<format_tools::content_format> regions = format_tools::convert(index_regions, output);
		for (unsigned int i = 0; i < regions.size(); i++)
		{
			int foreground_color = default_foreground_color;
			int background_color = default_background_color;
			if (std::count(format_tools::colors.begin(), format_tools::colors.end(), regions[i].format.foreground_format) != 0)
			{
				foreground_color = regions[i].format.foreground_format;
			}

			if (std::count(format_tools::colors.begin(), format_tools::colors.end(), regions[i].format.background_format) != 0)
			{
				background_color = regions[i].format.background_format;
			}

			ascii_io::set_color(foreground_color, background_color, regions[i].format.bold);

			if (regions[i].format.dec)
			{
#ifdef _WIN32
				ascii_io::enable_dec();
				ascii_io::print(regions[i].content);
#elif __linux__
				dec.print_dec_string(regions[i].content);
#endif
			}
			else
			{
#ifdef _WIN32
				ascii_io::disable_dec();
#endif
				ascii_io::print(regions[i].content);
			}
		}
#ifdef _WIN32
		ascii_io::disable_dec();
#endif
	}
	else
	{
		ascii_io::print(output);
	}

	previous_x = terminal_x;
	previous_y = terminal_y;
	display_stale = false;
}

bool frame::stale()
{
	if (!display_stale)
	{
		int x = 0;
		int y = 0;
		if (!_use_fake_console_dimensions)
		{
			ascii_io::get_terminal_size(x, y);
		}
		else
		{
			x = _fake_console_width;
			y = _fake_console_height;
		}

		if ((x != previous_x) || (y != previous_y))
		{
			display_stale = true;
		}
	}
	return display_stale;
}

void frame::set_controls(int select, int quit, int up, int down, int left, int right)
{
	_select = select;
	_quit = quit;
	_up = up;
	_down = down;
	_right = right;
	_left = left;
}

void frame::get_controls(int& select, int& quit, int& up, int& down, int& left, int& right)
{
	select = _select;
	quit = _quit;
	up = _up;
	down = _down;
	left = _left;
	right = _right;
}

int frame::get_selection()
{
	int input = 0;
	int selected_id = -1;
	log.log_begin("frame::get_selection");
	if (!initialize_selection(selected_row, selected_column, selected_level))
	{
		log.log_comment("No selectable widget found.");
		return -1;
	}

	log.log_comment("Start row: " + std::to_string(selected_row) + " Start column: " + std::to_string(selected_column) + " Start level: " + std::to_string(selected_level));

	do
	{
		if (stale())
		{
			display();
		}
		unhighlight(last_selected_row, last_selected_column, last_selected_level);
		highlight(selected_row, selected_column, selected_level);
		last_selected_row = selected_row;
		last_selected_column = selected_column;
		last_selected_level = selected_level;
		input = ascii_io::getchar();
		if (input == _select)
		{
			log.log_comment("select action");
			widget_info* item = get_widget(selected_row, selected_column, selected_level);
			if (item->selectable)
			{
				selected_id = item->id;
				log.log_comment("Selected row: " + std::to_string(selected_row) + " Selected column: " + std::to_string(selected_column) + " Selected level: " + std::to_string(selected_level));
				log.log_comment("Selected ID: " + std::to_string(item->id));
				break;
			}
		}
		else if (input == _up)
		{
			log.log_comment("up action");
			up_handle(selected_row, selected_column, selected_level);
		}
		else if (input == _down)
		{
			log.log_comment("down action");
			down_handle(selected_row, selected_column, selected_level);
		}
		else if (input == _right)
		{
			log.log_comment("right action");
			right_handle(selected_row, selected_column, selected_level);
		}
		else if (input == _left)
		{
			log.log_comment("left action");
			left_handle(selected_row, selected_column, selected_level);
		}
		log.log_comment("Current row: " + std::to_string(selected_row) + " Current column: " + std::to_string(selected_column) + " Current level: " + std::to_string(selected_level));
	} while (input != _quit);

	log.log_end("frame::get_selection");
	return selected_id;
}

void frame::enable_dec(bool enable)
{
	_dec_enabled = enable;
}

bool frame::dec_enabled()
{
	return _dec_enabled;
}

void frame::enable_color(bool enable)
{
	_color_enabled = enable;
}

bool frame::color_enabled()
{
	return _color_enabled;
}

void frame::set_dec_format_characters(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char)
{
	if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), horizontal_char) != 0)
	{
		log.log_status(INVALID_VALUE, "frame::set_dec_format_characters");
	}
	else if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), vertical_char) != 0)
	{
		log.log_status(INVALID_VALUE, "frame::set_dec_format_characters");
	}
	else if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), intersection_char) != 0)
	{
		log.log_status(INVALID_VALUE, "frame::set_dec_format_characters");
	}
	else if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), endpoint_char) != 0)
	{
		log.log_status(INVALID_VALUE, "frame::set_dec_format_characters");
	}
	else
	{
		dec.set_format_chars(horizontal_char, vertical_char, intersection_char, endpoint_char);
		log.log_status(SUCCESS, "frame::set_dec_format_characters");
	}
}

void frame::get_dec_format_characters(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char)
{
	dec.get_format_chars(horizontal_char, vertical_char, intersection_char, endpoint_char);
}

void frame::set_default_background_color(int color)
{
	if (std::count(format_tools::colors.begin(), format_tools::colors.end(), color) == 0)
	{
		log.log_status(INVALID_VALUE, "frame::set_default_background_color");
	}
	else
	{
		default_background_color = color;
		log.log_status(SUCCESS, "frame::set_default_background_color");
	}
}

void frame::set_default_foreground_color(int color)
{
	if (std::count(format_tools::colors.begin(), format_tools::colors.end(), color) == 0)
	{
		log.log_status(INVALID_VALUE, "frame::set_default_foreground_color");
	}
	else
	{
		default_foreground_color = color;
		log.log_status(SUCCESS, "frame::set_default_foreground_color");
	}
}

int frame::get_default_background_color()
{
	return default_background_color;
}

int frame::get_default_foreground_color()
{
	return default_foreground_color;
}

void frame::use_fake_console_dimensions(bool use)
{
	_use_fake_console_dimensions = use;
}

void frame::set_fake_console_width(int width)
{
	if (width >= 0)
	{
		_fake_console_width = width;
	}
	else
	{
		log.log_status(INVALID_VALUE, "frame::set_fake_console_width");
	}
}

void frame::set_fake_console_height(int height)
{
	if (height >= 0)
	{
		_fake_console_height = height;
	}
	else
	{
		log.log_status(INVALID_VALUE, "frame::set_fake_console_height");
	}
}

std::string frame::get_frame_output()
{
	return generate_frame_output();
}

int frame::start_logging(const std::string& file_path)
{
	int status = log.start_widget_logging(file_path, FRAME);
	return status;
}

void frame::stop_logging()
{
	log.stop_widget_logging();
}

int frame::reset_logging(const std::string& file_path)
{
	int status = log.log_reset(file_path, FRAME);
	return status;
}

void frame::add_widget(widget_info* item)
{
	int id = generate_widget_id();
	item->id = id;
	widgets.push_back(item);
}

int frame::append(int id, const std::string& special_operation)
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
		if (widgets[i]->id == id)
		{
			widgets[i]->row = row;
			widgets[i]->column = column;
			widgets[i]->level = level;
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
		if ((widgets[i]->row == row) && (widgets[i]->column == column) && (widgets[i]->level == level))
		{
			unsigned int width = get_widget_width(widgets[i], false);
			unsigned int height = get_widget_height(widgets[i], false);

			int x = widgets[i]->x_origin - 2 - widgets[i]->left_border_spacing;
			int y = widgets[i]->y_origin - 1 - widgets[i]->top_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			ascii_io::print(std::string(1, widgets[i]->highlight_character));

			x = widgets[i]->x_origin + (int)width + 1 + widgets[i]->right_border_spacing;
			y = widgets[i]->y_origin - 1 - widgets[i]->top_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			ascii_io::print(std::string(1, widgets[i]->highlight_character));

			x = widgets[i]->x_origin - 2 - widgets[i]->left_border_spacing;
			y = widgets[i]->y_origin + (int)height  + widgets[i]->bottom_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			ascii_io::print(std::string(1, widgets[i]->highlight_character));

			x = widgets[i]->x_origin + (int)width + 1 + widgets[i]->left_border_spacing;
			y = widgets[i]->y_origin + (int)height + widgets[i]->bottom_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			ascii_io::print(std::string(1, widgets[i]->highlight_character));
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
		if ((widgets[i]->row == row) && (widgets[i]->column == column) && (widgets[i]->level == level))
		{
			char corner_character = ' ';
			if (widgets[i]->add_border)
			{
				corner_character = widgets[i]->corner_border;
			}

			unsigned int width = get_widget_width(widgets[i], false);
			unsigned int height = get_widget_height(widgets[i], false);

			int x = widgets[i]->x_origin - 2 - widgets[i]->left_border_spacing;
			int y = widgets[i]->y_origin - 1 - widgets[i]->top_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			if (_dec_enabled && widgets[i]->add_border && (widgets[i]->corner_border == dec.get_endpoint_char()))
			{
#ifdef _WIN32
				ascii_io::enable_dec();
				ascii_io::print(std::string(1, dec.top_left_corner));
#elif __linux__
				dec.print_dec_string(std::string(1, dec.top_left_corner));
#endif
			}
			else
			{
				ascii_io::print(std::string(1, corner_character));
			}

			x = widgets[i]->x_origin + (int)width + 1 + widgets[i]->right_border_spacing;
			y = widgets[i]->y_origin - 1 - widgets[i]->top_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			if (_dec_enabled && widgets[i]->add_border && (widgets[i]->corner_border == dec.get_endpoint_char()))
			{
#ifdef _WIN32
				ascii_io::print(std::string(1, dec.top_right_corner));
#elif __linux__
				dec.print_dec_string(std::string(1, dec.top_right_corner));
#endif
			}
			else
			{
				ascii_io::print(std::string(1, corner_character));
			}

			x = widgets[i]->x_origin - 2 - widgets[i]->left_border_spacing;
			y = widgets[i]->y_origin + (int)height  + widgets[i]->bottom_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			if (_dec_enabled && widgets[i]->add_border && (widgets[i]->corner_border == dec.get_endpoint_char()))
			{
#ifdef _WIN32
				ascii_io::print(std::string(1, dec.bottom_left_corner));
#elif __linux__
				dec.print_dec_string(std::string(1, dec.bottom_left_corner));
#endif
			}
			else
			{
				ascii_io::print(std::string(1, corner_character));
			}

			x = widgets[i]->x_origin + (int)width + 1 + widgets[i]->left_border_spacing;
			y = widgets[i]->y_origin + (int)height + widgets[i]->bottom_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			if (_dec_enabled && widgets[i]->add_border && (widgets[i]->corner_border == dec.get_endpoint_char()))
			{
#ifdef _WIN32
				ascii_io::print(std::string(1, dec.bottom_right_corner));
#elif __linux__
				dec.print_dec_string(std::string(1, dec.bottom_right_corner));
#endif
			}
			else
			{
				ascii_io::print(std::string(1, corner_character));
			}
#ifdef _WIN32
			if (_dec_enabled)
			{
				ascii_io::disable_dec();
			}
#endif
			status = SUCCESS;
			break;
		}
	}
	log.log_status(status, "frame::unhighlight");
}

void frame::keep_point_in_console_bounds(int& x, int& y)
{
	if (x < 0)
	{
		x = 0;
	}
	else if (x >= terminal_x)
	{
		x = terminal_x - 1;
	}

	if (y < 0)
	{
		y = 0;
	}
	else if (y >= terminal_y)
	{
		y = terminal_y - 1;
	}
}

int frame::get_levels(int row, int column)
{
	int count = 0;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i]->row == row) && (widgets[i]->column == column))
		{
			count++;
		}
	}
	return count;
}

float frame::get_greatest_width_multiplier_at_coordinate(int row, int column)
{
	float greatest_width_multiplier = 0.0;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i]->row == row) && (widgets[i]->column == column))
		{
			float multiplier = 0.0;
			if (widgets[i]->use_spacing_width_multipliers)
			{
				multiplier = widgets[i]->width_multiplier + widgets[i]->right_width_multiplier + widgets[i]->left_width_multiplier;
			}
			else
			{
				multiplier = widgets[i]->width_multiplier;
			}

			if (multiplier > greatest_width_multiplier)
			{
				greatest_width_multiplier = multiplier;
			}
		}
	}
	return greatest_width_multiplier;
}

float frame::get_width_weight(const widget_info* const item, float multiplier)
{
	float total_width_multiplier = 0.0;
	std::vector<int> columns_completed;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i]->row == item->row) && (std::count(columns_completed.begin(), columns_completed.end(), widgets[i]->column) == 0))
		{
			total_width_multiplier = total_width_multiplier + get_greatest_width_multiplier_at_coordinate(widgets[i]->row, widgets[i]->column);
			columns_completed.push_back(widgets[i]->column);
		}
	}

	return (multiplier / total_width_multiplier);
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
		if (widgets[i]->row == row)
		{
			ids.push_back(widgets[i]->id);
		}
	}
	return ids;
}

std::vector<std::vector<int>> frame::sort_row_ids(std::vector<int> ids)
{
	std::vector<widget_info*> widgets_vec;
	for (unsigned int i = 0; i < ids.size(); i++)
	{
		widgets_vec.push_back(get_widget(ids[i]));
	}

	unsigned int widgets_vec_length = widgets_vec.size();
	std::vector<widget_info*> sorted_widgets;
	for (unsigned int i = 0; i < widgets_vec_length; i++)
	{
		int index = get_min_column_index(widgets_vec);
		sorted_widgets.push_back(widgets_vec[index]);
		widgets_vec.erase(widgets_vec.begin() + index);
	}
	
	std::vector<std::vector<int>> sorted_ids;
	while(sorted_widgets.size() > 0)
	{
		std::vector<widget_info*> level_group;
		level_group.push_back(sorted_widgets[0]);
		sorted_widgets.erase(sorted_widgets.begin());
		for (unsigned int i = 0; i < sorted_widgets.size(); i++)
		{
			if ((level_group[0]->row == sorted_widgets[i]->row) && (level_group[0]->column == sorted_widgets[i]->column))
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
				sorted_id_group.push_back(level_group[index]->id);
				level_group.erase(level_group.begin() + index);
			}
		}
		else
		{
			sorted_id_group.push_back(level_group[0]->id);
		}
		sorted_ids.push_back(sorted_id_group);
	}
	return sorted_ids;
}

int frame::get_min_column_index(const std::vector<widget_info*> widget_vec)
{
	int min_index = 0;
	int min_column = 0;
	if (widget_vec.size() > 0)
	{
		min_index = 0;
		min_column = widget_vec[min_index]->column;
		for (unsigned int i = 1; i < widget_vec.size(); i++)
		{
			if (widget_vec[i]->column < min_column)
			{
				min_index = i;
				min_column = widget_vec[min_index]->column;
			}
		}
	}
	return min_index;
}

int frame::get_min_level_index(const std::vector<widget_info*> widget_vec)
{
	int min_index = 0;
	int min_level = 0;
	if (widget_vec.size() > 0)
	{
		min_index = 0;
		min_level = widget_vec[min_index]->level;
		for (unsigned int i = 1; i < widget_vec.size(); i++)
		{
			if (widget_vec[i]->level < min_level)
			{
				min_index = i;
				min_level = widget_vec[min_index]->level;
			}
		}
	}
	return min_index;
}

frame::widget_info* frame::get_widget(int id)
{
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i]->id == id)
		{
			return widgets[i];
		}
	}

	return nullptr;
}

frame::widget_info* frame::get_widget(int row, int column, int level)
{
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i]->row == row) && (widgets[i]->column == column) && (widgets[i]->level == level))
		{
			return widgets[i];
		}
	}
	return nullptr;
}

unsigned int frame::get_widget_width(const widget_info* const item, bool include_spacing)
{	
	int raw_width = 0;
	raw_width = int(terminal_x * get_width_weight(item, item->width_multiplier));
	
	if(!include_spacing)
	{
		if(!item->use_spacing_width_multipliers)
		{
			raw_width = raw_width - item->left_spacing - item->right_spacing;
		}
		
		if (item->add_border)
		{
			raw_width = raw_width - 4;
		}
	}
	else if (item->use_spacing_width_multipliers)
	{
		raw_width = raw_width + int(terminal_x * get_width_weight(item, item->left_width_multiplier)) + int(terminal_x * get_width_weight(item, item->right_width_multiplier));
	}

	unsigned int width = 0;
	if (raw_width >= 0)
	{
		width = (unsigned int)raw_width;
	}
	else
	{
		log.log_begin("frame::get_widget_width");
		log.log_comment("Widget id: " + std::to_string(item->id) + " has zero width.");
		log.log_end("frame::get_widget_width");
	}
	return width;
}

unsigned int frame::get_greatest_widget_width_at_coordinate(const widget_info* const item, bool include_spacing)
{
	unsigned int greatest_widget_width = 0;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i]->row == item->row) && (widgets[i]->column == item->column))
		{
			unsigned int widget_width = get_widget_width(widgets[i], include_spacing);
			if (widget_width > greatest_widget_width)
			{
				greatest_widget_width = widget_width;
			}
		}
	}
	return greatest_widget_width;
}

unsigned int frame::get_widget_width(int id, bool include_spacing)
{
	return get_widget_width(get_widget(id), include_spacing);
}

unsigned int frame::get_widget_height(const widget_info* const item, bool include_spacing)
{
	unsigned int height = 0;
	if (item->line_constraint)
	{
		height = item->displayed_lines_count;
	}
	else
	{
		height = item->lines.size();
	}

	if (include_spacing)
	{
		height = height + item->top_spacing + item->bottom_spacing;
		if (item->add_border)
		{
			height = height + 2;
		}
	}

	return height;
}

unsigned int frame::get_widget_height(int id, bool include_spacing)
{
	return get_widget_height(get_widget(id), include_spacing);
}

void frame::constrain_lines(const widget_info* const item, std::vector<std::string>& widget_lines)
{
	if (item->line_constraint)
	{
		unsigned int stop_line = 0;
		std::string empty_line = format_tools::get_spacing(get_widget_width(item, false), ' ');
		if (widget_lines.size() < (item->displayed_lines_count + item->top_line))
		{
			stop_line = widget_lines.size();
		}
		else
		{
			stop_line = item->displayed_lines_count + item->top_line;
		}

		int last_widget_line = widget_lines.size() - 1;
		for (int i = last_widget_line; i >= 0; i--)
		{
			if ((unsigned int)i >= stop_line || (unsigned int)i < item->top_line)
			{
				widget_lines.erase(widget_lines.begin() + i);
			}
		}

		for (unsigned int i = widget_lines.size(); i < item->displayed_lines_count; i++)
		{
			widget_lines.push_back(empty_line);
		}
	}

	if (item->column_constraint)
	{
		unsigned int width = get_widget_width(item, false);
		for (unsigned int i = 0; i < widget_lines.size(); i++)
		{
			if (widget_lines[i].length() > (item->left_column + width))
			{
				widget_lines[i].erase(item->left_column + width, widget_lines[i].length() - (item->left_column + width));
			}
			widget_lines[i].erase(0, item->left_column);
		}
	}
}

void frame::constrain_colors(const widget_info* const item, std::vector<format_tools::coordinate_format>& colors)
{
	if (item->coordinate_colors.size() > 0)
	{
		colors = item->coordinate_colors;
		if (item->line_constraint)
		{
			unsigned int stop_line = 0;
			if (item->lines.size() < (item->displayed_lines_count + item->top_line))
			{
				stop_line = item->lines.size();
			}
			else
			{
				stop_line = item->displayed_lines_count + item->top_line;
			}

			int number_of_coordinate_colors = item->coordinate_colors.size() - 1;
			for (int i = number_of_coordinate_colors; i >= 0; i--)
			{
				if (item->coordinate_colors[i].y_position < (int)item->top_line || item->coordinate_colors[i].y_position >= (int)stop_line)
				{
					colors.erase(colors.begin() + i);
				}
			}

			for (unsigned int i = 0; i < colors.size(); i++)
			{
				colors[i].y_position = colors[i].y_position - item->top_line;
			}
		}

		if (item->column_constraint)
		{
			int number_of_coordinate_colors = colors.size() - 1;
			unsigned int width = get_widget_width(item, false);
			for (int i = number_of_coordinate_colors; i >= 0; i--)
			{
				if (colors[i].x_position < (int)item->left_column || colors[i].x_position >= ((int)item->left_column + (int)width))
				{
					colors.erase(colors.begin() + i);
				}
			}

			for (unsigned int i = 0; i < colors.size(); i++)
			{
				colors[i].x_position = colors[i].x_position - item->left_column;
			}

			format_tools::coordinate_format color;
			color.x_position = width;
			for (unsigned int i = 0; i < item->displayed_lines_count; i++)
			{
				color.y_position = i;
				colors.push_back(color);
			}
		}

		std::sort(colors.begin(), colors.end(), format_tools::coordinate_format_sorting_functor());
		if ((colors.size() > 0) && format_tools::format_empty(colors[0].format))
		{
			colors.erase(colors.begin());
		}
	}
}

void frame::update_widget_output_from_lines(widget_info* item)
{
	unsigned int output_index = 0;
	for (unsigned int i = 0; i < item->lines.size(); i++)
	{
		for (unsigned int j = 0; j < item->lines[i].length(); j++)
		{
			while (output_index < item->output.length() && item->output[output_index] == '\n')
			{
				output_index++;
			}

			if (output_index < item->output.length())
			{
				item->output[output_index] = (item->lines[i])[j];
				output_index++;
			}
			else
			{
				return;
			}
		}
	}
}

std::vector<std::string> frame::build_core_widget_lines(widget_info* item)
{
	std::vector<std::string> widget_lines;
	unsigned int width = get_widget_width(item, false);

	std::vector<int> ignore_flags;

	std::string output_copy = item->output;
	if (output_copy == "")
	{
		output_copy = " ";
	}

	if (_color_enabled)
	{
		ignore_flags = format_tools::set_flags(item->index_colors, output_copy, '*');
	}

	std::vector<std::string> user_lines = format_tools::split_string(output_copy, '\n');
	std::string line = "";

	if (!item->column_constraint)
	{
		for (unsigned int i = 0; i < user_lines.size(); i++)
		{
			if (user_lines[i] == "\n")
			{
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
						if (item->widget_type == LABEL)
						{
							second_section.insert(0, "-");
						}
						words.insert(words.begin() + (j + 1), second_section);
					}
					else
					{
						if (item->widget_type == TEXTBOX)
						{
							if (words[j] == " ")
							{
								line = line + words[j];
								widget_lines.push_back(line);
								line = "";
							}
							else
							{
								widget_lines.push_back(line);
								line = words[j];
							}
						}
						else
						{
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
		}
	}
	else
	{
		for (unsigned int i = 0; i < user_lines.size(); i++)
		{
			if (user_lines[i] != "\n")
			{
				widget_lines.push_back(user_lines[i]);
			}
		}
	}

	if (line != "")
	{
		widget_lines.push_back(line);
		line = "";
	}

	if (user_lines.size() > 0 && user_lines.back() == "\n")
	{
		widget_lines.push_back(format_tools::get_spacing(width, ' '));
	}

	if (std::count(widget_types::line_constraint_widgets.begin(), widget_types::line_constraint_widgets.end(), item->widget_type) != 0)
	{
		item->lines = format_tools::remove_flags(item->index_colors, ignore_flags, widget_lines, '*');
	}

	if (!item->column_constraint)
	{
		widget_lines = format_tools::fill_lines(widget_lines, width, item->alignment);
	}
	else
	{
		unsigned int longest_line_length = width;
		for (unsigned int i = 0; i < widget_lines.size(); i++)
		{
			if (widget_lines[i].length() > longest_line_length)
			{
				longest_line_length = widget_lines[i].length();
			}
		}
		widget_lines = format_tools::fill_lines(widget_lines, longest_line_length, item->alignment);
	}

	if (_color_enabled)
	{
		convert_flags(item->coordinate_colors, item->index_colors, ignore_flags, widget_lines, '*');
		if (item->widget_type == LABEL)
		{
			item->coordinate_colors = format_tools::bound_colors(item->coordinate_colors, widget_lines);
		}
	}

	if (std::count(widget_types::line_constraint_widgets.begin(), widget_types::line_constraint_widgets.end(), item->widget_type) != 0)
	{
		if (item->line_constraint || item->column_constraint)
		{
			if (item->line_constraint)
			{
				if (item->line_subtraction_from_terminal_height != 0)
				{
					dynamically_adjust_displayed_lines(item);
				}
				else if (item->top_line >= widget_lines.size())
				{
					if (widget_lines.size() > 0)
					{
						item->top_line = widget_lines.size() - 1;
					}
					else
					{
						item->top_line = 0;
					}
				}
			}

			constrain_lines(item, widget_lines);
		}
	}

	if (item->widget_type == TEXTBOX)
	{
		for (unsigned int i = 0; i < widget_lines.size(); i++)
		{
			if (widget_lines[i].length() > width)
			{
				widget_lines[i].erase(widget_lines[i].begin() + widget_lines[i].length() - 1);
			}
		}
	}

	return widget_lines;
}

std::vector<std::string> frame::build_widget_lines(widget_info* item)
{
	std::vector<std::string> widget_lines;
	if (item->line_edited)
	{
		update_widget_output_from_lines(item);
		item->line_edited = false;
	}

	int left_spacing = 0;
	int right_spacing = 0;
	if (item->use_spacing_width_multipliers)
	{
		left_spacing = int(terminal_x * get_width_weight(item, item->left_width_multiplier));
		right_spacing = int(terminal_x * get_width_weight(item, item->right_width_multiplier));
	}
	else
	{
		left_spacing = item->left_spacing;
		right_spacing = item->right_spacing;
	}
	std::string left_spacing_string = format_tools::get_spacing(left_spacing, ' ');
	std::string right_spacing_string = format_tools::get_spacing(right_spacing, ' ');
	unsigned int width = get_widget_width(item, false);
	std::string active_spacing = format_tools::get_spacing(width, ' ');

	widget_lines = build_core_widget_lines(item);

	for (int i = 0; i < item->top_spacing; i++)
	{
		widget_lines.insert(widget_lines.begin(), active_spacing);
	}

	for (int i = 0; i < item->bottom_spacing; i++)
	{
		widget_lines.push_back(active_spacing);
	}

	for (unsigned int i = 0; i < widget_lines.size(); i++)
	{
		widget_lines[i].insert(0, left_spacing_string);
		widget_lines[i] = widget_lines[i] + right_spacing_string;
	}

	return widget_lines;
}

std::vector<std::string> frame::get_displayed_output(int id)
{
	widget_info* item = get_widget(id);
	std::vector<std::string> displayed_output = item->lines;
	constrain_lines(item, displayed_output);
	return displayed_output;
}

std::vector<format_tools::index_format> frame::get_displayed_colors(int id)
{
	widget_info* item = get_widget(id);
	std::vector<format_tools::index_format> colors;
	if (_color_enabled)
	{
		std::vector<format_tools::coordinate_format> colors_container;
		constrain_colors(item, colors_container);
		colors = format_tools::convert(colors_container, get_widget_width(item, false));
	}
	return colors;
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
		if (!element_exists(rows, widgets[i]->row))
		{
			rows.push_back(widgets[i]->row);
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
		const widget_info* const item = get_widget(row_ids[i]);
		if (!element_exists(columns, item->column))
		{
			columns.push_back(item->column);
		}
	}
	return columns.size();
}

std::string frame::generate_frame_output()
{
	if (!_use_fake_console_dimensions)
	{
		ascii_io::get_terminal_size(terminal_x, terminal_y);
	}
	else
	{
		terminal_x = _fake_console_width;
		terminal_y = _fake_console_height;
	}

	std::string frame_output = "";
	int total_rows = get_total_rows();
	row_heights.clear();
	format_tools::text_column column_data;
	for (int i = 0; i < total_rows; i++)
	{
		std::vector<std::vector<int>> row_ids = sort_row_ids(get_row_ids(i));
		widget_info* item = nullptr;
		for (unsigned int j = 0; j < row_ids.size(); j++)
		{
			std::vector<std::string> accumulated_widget_lines;
			for (unsigned int m = 0; m < row_ids[j].size(); m++)
			{
				std::vector<std::string> widget_lines;
				item = get_widget((row_ids[j])[m]);
				widget_lines = build_widget_lines(item);

				if (item->add_border)
				{
					generate_border(item, widget_lines);
				}

				if (!only_widget_at_coordinate(item))
				{
					widget_lines = format_tools::fill_lines(widget_lines, get_greatest_widget_width_at_coordinate(item, true), format_tools::left_alignment_keyword);
				}

				accumulated_widget_lines.insert(accumulated_widget_lines.end(), widget_lines.begin(), widget_lines.end());
			}
			column_data.text.push_back(accumulated_widget_lines);
			column_data.width.push_back(get_greatest_widget_width_at_coordinate(item, true));
		}
		unsigned int row_lines = 0;
		frame_output = frame_output + format_tools::fuse_columns_into_row(column_data, row_lines);
		row_heights.push_back(row_lines);
		column_data.text.clear();
		column_data.width.clear();
	}
	std::vector<std::string> frame_lines = format_tools::get_lines(frame_output);
	frame_lines = format_tools::remove_newline_characters(frame_lines);
	frame_lines = format_tools::fill_lines(frame_lines, terminal_x, format_tools::left_alignment_keyword);
	if (frame_lines.size() < (unsigned int)terminal_y)
	{
		frame_lines = format_tools::add_lines(frame_lines, terminal_y - frame_lines.size(), terminal_x);
	}
	frame_lines = format_tools::add_newline_characters(frame_lines);
	frame_output = format_tools::get_string(frame_lines);
	if ((frame_output.back() == '\n') && (frame_output.length() > 0))
	{
		frame_output.erase((frame_output.length() - 1), 1);
	}
	set_widget_origins();
	if (_color_enabled)
	{
		translate_coordinate_colors_to_frame();
	}
	return frame_output;
}

void frame::set_widget_origins()
{
	int column = 0;
	int level = 0;
	unsigned int x = 0;
	unsigned int y = 0;
	widget_info* item;
	for(unsigned int row = 0; row < row_heights.size(); row++)
	{
		x = 0;
		column = 0;
		item = get_widget(row, column, level);
		while (item != nullptr)
		{
			unsigned int y_origin = y;
			int greatest_widget_width_at_coordinate = get_greatest_widget_width_at_coordinate(item, true);
			do
			{
				int left_spacing = 0;
				if (item->use_spacing_width_multipliers)
				{
					left_spacing = int(terminal_x * get_width_weight(item, item->left_width_multiplier));
				}
				else
				{
					left_spacing = item->left_spacing;
				}
				unsigned int x_origin = x + left_spacing;
				y_origin = y_origin + item->top_spacing;
				if (item->add_border)
				{
					x_origin = x_origin + 2;
					y_origin = y_origin + 1;
				}
				item->x_origin = x_origin;
				item->y_origin = y_origin;
				if (item->add_border)
				{
					y_origin = y_origin - 1;
				}
				y_origin = y_origin - item->top_spacing;
				y_origin = y_origin + get_widget_height(item, true);
				level++;
				item = get_widget(row, column, level);
			} while (item != nullptr);
			level = 0;
			column++;
			x = x + greatest_widget_width_at_coordinate;
			item = get_widget(row, column, level);
		}
		y = y + row_heights[row];
	}
}

void frame::translate_coordinate_colors_to_frame()
{
	color_regions.clear();
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (!widgets[i]->line_constraint && !widgets[i]->column_constraint)
		{
			for (unsigned int j = 0; j < widgets[i]->coordinate_colors.size(); j++)
			{
				format_tools::coordinate_format color_region;
				color_region.x_position = widgets[i]->coordinate_colors[j].x_position + widgets[i]->x_origin;
				color_region.y_position = widgets[i]->coordinate_colors[j].y_position + widgets[i]->y_origin;
				color_region.format = widgets[i]->coordinate_colors[j].format;
				color_regions.push_back(color_region);
			}
		}
		else if (widgets[i]->line_constraint && !widgets[i]->column_constraint)
		{
			for (unsigned int j = 0; j < widgets[i]->coordinate_colors.size(); j++)
			{
				if (widgets[i]->coordinate_colors[j].y_position >= (int)widgets[i]->top_line && widgets[i]->coordinate_colors[j].y_position < ((int)widgets[i]->top_line + (int)widgets[i]->displayed_lines_count))
				{
					format_tools::coordinate_format color_region;
					color_region.x_position = widgets[i]->coordinate_colors[j].x_position + widgets[i]->x_origin;
					color_region.y_position = widgets[i]->coordinate_colors[j].y_position - widgets[i]->top_line + widgets[i]->y_origin;
					color_region.format = widgets[i]->coordinate_colors[j].format;
					color_regions.push_back(color_region);
				}
			}
		}
		else if (!widgets[i]->line_constraint && widgets[i]->column_constraint)
		{
			unsigned int width = get_widget_width(widgets[i], false);
			for (unsigned int j = 0; j < widgets[i]->coordinate_colors.size(); j++)
			{
				if (widgets[i]->coordinate_colors[j].x_position >= (int)widgets[i]->left_column && widgets[i]->coordinate_colors[j].x_position < ((int)widgets[i]->left_column + (int)width))
				{
					format_tools::coordinate_format color_region;
					color_region.x_position = widgets[i]->coordinate_colors[j].x_position - widgets[i]->left_column + widgets[i]->x_origin;
					color_region.y_position = widgets[i]->coordinate_colors[j].y_position + widgets[i]->y_origin;
					color_region.format = widgets[i]->coordinate_colors[j].format;
					color_regions.push_back(color_region);
				}
			}

			format_tools::coordinate_format color_region;
			for (unsigned int j = 0; j < widgets[i]->displayed_lines_count; j++)
			{
				color_region.x_position = widgets[i]->x_origin + width;
				color_region.y_position = widgets[i]->y_origin + j;
				color_regions.push_back(color_region);
			}
		}
		else
		{
			unsigned int width = get_widget_width(widgets[i], false);
			for (unsigned int j = 0; j < widgets[i]->coordinate_colors.size(); j++)
			{
				bool in_line_bound = widgets[i]->coordinate_colors[j].y_position >= (int)widgets[i]->top_line && widgets[i]->coordinate_colors[j].y_position < ((int)widgets[i]->top_line + (int)widgets[i]->displayed_lines_count);
				bool in_column_bound = widgets[i]->coordinate_colors[j].x_position >= (int)widgets[i]->left_column && widgets[i]->coordinate_colors[j].x_position < ((int)widgets[i]->left_column + (int)width);
				if (in_line_bound && in_column_bound)
				{
					format_tools::coordinate_format color_region;
					color_region.x_position = widgets[i]->coordinate_colors[j].x_position - widgets[i]->left_column + widgets[i]->x_origin;
					color_region.y_position = widgets[i]->coordinate_colors[j].y_position - widgets[i]->top_line + widgets[i]->y_origin;
					color_region.format = widgets[i]->coordinate_colors[j].format;
					color_regions.push_back(color_region);
				}
			}

			format_tools::coordinate_format color_region;
			for (unsigned int j = 0; j < widgets[i]->displayed_lines_count; j++)
			{
				color_region.x_position = widgets[i]->x_origin + width;
				color_region.y_position = widgets[i]->y_origin + j;
				color_regions.push_back(color_region);
			}
		}
	}
}

bool frame::is_selectable(int row, int column, int level)
{
	bool selectable = false;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i]->row == row) && (widgets[i]->column == column) && (widgets[i]->level == level))
		{
			if (widgets[i]->selectable)
			{
				selectable = true;
				break;
			}
		}
	}
	return selectable;
}

bool frame::initialize_selection(int& row, int& column, int& level)
{
	while (true)
	{
		if (is_selectable(row, column, level))
		{
			return true;
		}

		level++;
		if (level >= get_levels(row, column))
		{
			column++;
			level = 0;
		}

		if (column >= (int)get_columns_in_row(row))
		{
			row++;
			column = 0;
			level = 0;
		}

		if (row >= (int)get_total_rows())
		{
			return false;
		}
	}
}

bool frame::get_nearest_selectable_in_row(int& row, int& column, int& level, const widget_info* const item, int search_row)
{
	int original_row = row;
	int original_column = column;
	int original_level = level;
	row = search_row;
	std::vector<int> row_ids = get_row_ids(row);
	if (row_ids.size() == 0)
	{
		return false;
	}
	float distance = 0.0;
	float min_distance = 0.0;
	int min_id = 0;
	bool widget_found = false;
	for (unsigned int i = 0; i < row_ids.size(); i++)
	{
		widget_info* other_item = get_widget(row_ids[i]);
		if (item->selectable)
		{
			distance = (float)pow(pow(abs(other_item->x_origin - item->x_origin), 2) + pow(abs(other_item->y_origin - item->y_origin), 2), 0.5);
			if ((distance < min_distance) || min_distance == 0)
			{
				min_distance = distance;
				min_id = row_ids[i];
				widget_found = true;
			}
		}
	}

	if (!widget_found)
	{
		row = original_row;
		column = original_column;
		level = original_level;
	}
	else
	{
		widget_info* item = get_widget(min_id);
		row = item->row;
		column = item->column;
		level = item->level;
	}
	return widget_found;
}

void frame::up_handle(int& selected_row, int& selected_column, int& selected_level)
{
	int last_selected_row = selected_row;
	int last_selected_column = selected_column;
	int last_selected_level = selected_level;
	widget_info* item = get_widget(selected_row, selected_column, selected_level);
	if (item != nullptr)
	{
		do
		{
			if ((selected_level - 1) >= 0)
			{
				selected_level--;
			}
			else if ((selected_row - 1) >= 0)
			{

				if (!get_nearest_selectable_in_row(selected_row, selected_column, selected_level, item, selected_row - 1))
				{
					selected_row--;
					selected_level = 0;
				}
			}
			else
			{
				selected_row = last_selected_row;
				selected_column = last_selected_column;
				selected_level = last_selected_level;
				break;
			}

		} while (!is_selectable(selected_row, selected_column, selected_level));
	}
}

void frame::down_handle(int& selected_row, int& selected_column, int& selected_level)
{
	int last_selected_row = selected_row;
	int last_selected_column = selected_column;
	int last_selected_level = selected_level;
	widget_info* item = get_widget(selected_row, selected_column, selected_level);
	if (item != nullptr)
	{
		do
		{
			if ((selected_level + 1) < get_levels(selected_row, selected_column))
			{
				selected_level++;
			}
			else if ((selected_row + 1) < (int)get_total_rows())
			{
				if (!get_nearest_selectable_in_row(selected_row, selected_column, selected_level, item, selected_row + 1))
				{
					selected_row++;
					selected_level = 0;
				}
			}
			else
			{
				selected_row = last_selected_row;
				selected_column = last_selected_column;
				selected_level = last_selected_level;
				break;
			}

		} while (!is_selectable(selected_row, selected_column, selected_level));
	}
}

void frame::right_handle(int& selected_row, int& selected_column, int& selected_level)
{
	int last_selected_row = selected_row;
	int last_selected_column = selected_column;
	int last_selected_level = selected_level;
	do
	{
		if ((selected_column + 1) < (int)get_columns_in_row(selected_row))
		{
			selected_column++;
			int total_levels = get_levels(selected_row, selected_column);
			if (selected_level >= total_levels)
			{
				selected_level = total_levels - 1;
			}
			for (int i = 0, j = selected_level; i < total_levels; ++i, j = (j + 1) % total_levels)
			{
				selected_level = j;
				if (is_selectable(selected_row, selected_column, selected_level))
				{
					break;
				}
			}
		}
		else
		{
			selected_row = last_selected_row;
			selected_column = last_selected_column;
			selected_level = last_selected_level;
			break;
		}

	} while (!is_selectable(selected_row, selected_column, selected_level));
}

void frame::left_handle(int& selected_row, int& selected_column, int& selected_level)
{
	int last_selected_row = selected_row;
	int last_selected_column = selected_column;
	int last_selected_level = selected_level;
	do
	{
		if ((selected_column - 1) >= 0)
		{
			selected_column--;
			int total_levels = get_levels(selected_row, selected_column);
			if (selected_level >= total_levels)
			{
				selected_level = total_levels - 1;
			}
			for (int i = 0, j = selected_level; i < total_levels; ++i, j = (j + 1) % total_levels)
			{
				selected_level = j;
				if (is_selectable(selected_row, selected_column, selected_level))
				{
					break;
				}
			}
		}
		else
		{
			selected_row = last_selected_row;
			selected_column = last_selected_column;
			selected_level = last_selected_level;
			break;
		}

	} while (!is_selectable(selected_row, selected_column, selected_level));
}

void frame::generate_border(const widget_info* const item, std::vector<std::string>& lines)
{
	int top_spacing = item->top_spacing - item->top_border_spacing;
	int bottom_spacing = item->bottom_spacing - item->bottom_border_spacing;
	int left_spacing = 0;
	int right_spacing = 0;
	int left_border_spacing = 0;
	int right_border_spacing = 0;

	if (item->use_spacing_width_multipliers)
	{
		left_border_spacing = int(terminal_x * get_width_weight(item, item->left_border_width_multiplier));
		right_border_spacing = int(terminal_x * get_width_weight(item, item->right_border_width_multiplier));
		left_spacing = int(terminal_x * get_width_weight(item, item->left_width_multiplier)) - left_border_spacing;
		right_spacing = int(terminal_x * get_width_weight(item, item->right_width_multiplier)) - right_border_spacing;
	}
	else
	{
		left_border_spacing = item->left_border_spacing;
		right_border_spacing = item->right_border_spacing;
		left_spacing = item->left_spacing - item->left_border_spacing;
		right_spacing = item->right_spacing - item->right_border_spacing;
	}

	int middle_spacing = get_widget_width(item, false) + 2 + left_border_spacing + right_border_spacing;

	for (unsigned int k = 0; k < lines.size(); k++)
	{
		if (k < (unsigned int)(top_spacing) || (k > (lines.size() - bottom_spacing - 1)))
		{
			lines[k].insert(left_spacing, "  ");
			lines[k].insert(lines[k].length() - right_spacing, "  ");
		}
		else
		{
			lines[k].insert(left_spacing, std::string(1, item->vertical_border) + " ");
			lines[k].insert(lines[k].length() - right_spacing, " " + std::string(1, item->vertical_border));
		}
	}
	lines.insert(lines.begin() + top_spacing, format_tools::get_spacing(left_spacing, ' ') + std::string(1, item->corner_border) + format_tools::get_spacing(middle_spacing, item->horizontal_border) + std::string(1, item->corner_border) + format_tools::get_spacing(right_spacing, ' '));
	lines.insert(lines.end() - bottom_spacing, format_tools::get_spacing(left_spacing, ' ') + std::string(1, item->corner_border) + format_tools::get_spacing(middle_spacing, item->horizontal_border) + std::string(1, item->corner_border) + format_tools::get_spacing(right_spacing, ' '));
}

bool frame::only_widget_at_coordinate(const widget_info* const item)
{
	unsigned int widgets_at_coordinate = 0;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i]->row == item->row) && (widgets[i]->column == item->column))
		{
			widgets_at_coordinate = widgets_at_coordinate + 1;
		}
	}

	if (widgets_at_coordinate == 1)
	{
		return true;
	}

	return false;
}

std::vector<format_tools::index_format> frame::dec_format(std::string& format_content, unsigned int line_length)
{
	return dec.format(format_content, line_length);
}

void frame::bound_top_line(widget_info* item)
{
	if (item->widget_type == MENU)
	{
		unsigned int top_line_remainder = 0;
		unsigned int top_item = format_tools::compress(item->top_line, item->line_compression_amount, top_line_remainder);
		unsigned int displayed_lines_remainder = 0;
		unsigned int displayed_items = format_tools::compress(item->displayed_lines_count, item->line_compression_amount, displayed_lines_remainder);
		unsigned int line_count_remainder = 0;
		unsigned int item_count = format_tools::compress(item->lines.size(), item->line_compression_amount, line_count_remainder);
		if ((int)top_item > ((int)item_count - (int)displayed_items))
		{
			if (((int)item_count - (int)displayed_items) >= 0)
			{
				top_item = item_count - displayed_items;
				item->top_line = format_tools::expand(top_item, item->line_compression_amount, top_line_remainder);
			}
			else
			{
				top_item = 0;
				item->top_line = format_tools::expand(top_item, item->line_compression_amount, top_line_remainder);
			}
		}
	}
	else if ((item->widget_type == BOARD) || (item->widget_type == TEXTBOX) || (item->widget_type == LABEL))
	{
		if ((int)item->top_line > ((int)item->lines.size() - (int)item->displayed_lines_count))
		{
			if (((int)item->lines.size() - (int)item->displayed_lines_count) >= 0)
			{
				item->top_line = item->lines.size() - item->displayed_lines_count;
			}
			else
			{
				item->top_line = 0;
			}
		}
	}
}

void frame::dynamically_adjust_displayed_lines(widget_info* item)
{
	if (terminal_y > (int)item->line_subtraction_from_terminal_height)
	{
		item->displayed_lines_count = (unsigned int)(terminal_y - item->line_subtraction_from_terminal_height);
		bound_top_line(item);
	}
	else
	{
		item->displayed_lines_count = 1;
		bound_top_line(item);
	}
}

#ifdef __linux__
void frame::dec_print(const std::string& input)
{
	dec.print_dec_string(input);
}
#endif
