#include "frame.h"
#include "error_codes.h"

frame::frame()
{
	
}

void frame::display()
{
	ascii_io::clear();
	ascii_io::print(get_frame_output());
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
	int selected_column = 0;
	int selected_level = 0;
	int selected_id = -1;
	do
	{
		if (selected_column >= (int)get_columns_in_row(selected_row))
		{
			selected_column = (int)get_columns_in_row(selected_row) - 1;
		}

		highlight(selected_row, selected_column, selected_level);
		display();
		input = ascii_io::getchar();
		if (input == _select)
		{
			widget_info item;
			get_widget(selected_row, selected_column, selected_level, item);
			if (item.widget_type == MENU)
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
			}
		}
		else if (input == _left)
		{
			if ((selected_column - 1) >= 0)
			{
				selected_column--;
			}
		}
	} while (input != _quit);
	return selected_id;
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

int frame::set_allignment(int id, std::string allignment)
{
	int status = ELEMENT_NOT_FOUND;
	if ((allignment == right_allignment_keyword) || (allignment == left_allignment_keyword) || (allignment == center_allignment_keyword))
	{
		for (unsigned int i = 0; i < widgets.size(); i++)
		{
			if (widgets[i].id == id)
			{
				widgets[i].allignment = allignment;
				status = SUCCESS;
				break;
			}
		}
	}
	return status;
}

int frame::set_spacing(int id, int top, int bottom, int right, int left)
{
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

int frame::highlight(int row, int column, int level)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column) && (widgets[i].level == level))
		{
			widgets[i].highlight = true;
			status = SUCCESS;
		}
		else if(widgets[i].highlight)
		{
			widgets[i].highlight = false;
		}
	}
	return status;
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

std::string frame::get_output(int id)
{
	std::string output = "";
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			output = widgets[i].output;
		}
	}
	return output;
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
	int raw_width = (x / (int)get_columns_in_row(item.row));
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
	return width;
}

std::vector<std::string> frame::get_widget_lines(int id)
{
	widget_info item;
	get_widget(id, item);
	std::string left_spacing = get_spacing(item.left_spacing, ' ');
	std::string right_spacing = get_spacing(item.right_spacing, ' ');
	unsigned int width = get_widget_width(item, false);
	std::string active_spacing = get_spacing(width, ' ');
	std::vector<std::string> widget_lines;
	std::vector<std::string> user_lines = split_string(item.output, '\n');
	std::string line = "";
	for (int i = 0; i < item.top_spacing; i++)
	{
		widget_lines.push_back(active_spacing);
	}

	for (unsigned int i = 0; i < user_lines.size(); i++)
	{
		if (user_lines[i] == "\n")
		{
			line = fill_line(line, width, item.allignment);
			widget_lines.push_back(line);
			line = "";
		}
		else
		{
			std::vector<std::string> words = split_string(user_lines[i], ' ');
			for (unsigned int j = 0; j < words.size(); j++)
			{
				if ((((line + words[j]).length())) < width)
				{
					line = line + words[j];
				}
				else if (words[j].length() > width)
				{
					std::string first_section = "";
					std::string second_section = "";
					cut_word(words[j], width - line.length(), first_section, second_section);
					line = line + first_section;
					widget_lines.push_back(line);
					line = "";
					second_section.insert(0, "-");
					words.insert(words.begin() + (j + 1), second_section);
				}
				else
				{
					line = fill_line(line, width, item.allignment);
					widget_lines.push_back(line);
					if ((words[j] != " ") && item.widget_type == TEXTBOX)
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
		line = fill_line(line, width, item.allignment);
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

std::vector<std::string> frame::split_string(std::string str, char split_character)
{
	std::string section = "";
	std::vector<std::string> sections;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == split_character)
		{
			sections.push_back(section);
			if (section != std::string(1, split_character))
			{
				sections.push_back(std::string(1, split_character));
			}
			section = "";
		}
		else
		{
			section = section + str[i];
		}
	}

	if (section != "")
	{
		sections.push_back(section);
	}

	return sections;
}

std::string frame::get_spacing(unsigned int length, char space_char)
{
	std::string spacing = "";
	for (unsigned int i = 0; i < length; i++)
	{
		spacing = spacing + space_char;
	}
	return spacing;
}

std::string frame::fill_line(std::string input, unsigned int length, std::string allignment)
{
	if (allignment == left_allignment_keyword)
	{
		while (input.length() < length)
		{
			input = input + " ";
		}
	}
	else if (allignment == center_allignment_keyword)
	{
		bool begin = true;
		while (input.length() < length)
		{
			if (begin)
			{
				input.insert(0, " ");
				begin = false;
			}
			else
			{
				input = input + " ";
				begin = true;
			}
		}
	}
	else if (allignment == right_allignment_keyword)
	{
		while (input.length() < length)
		{
			input.insert(0, " ");
		}
	}
	return input;
}

std::vector<std::string> frame::add_lines(std::vector<std::string> lines, unsigned int number_of_added_lines, unsigned int line_length)
{
	std::string line = get_spacing(line_length, ' ');
	for (unsigned int i = 0; i < number_of_added_lines; i++)
	{
		lines.push_back(line);
	}
	return lines;
}

std::string frame::fuse_columns_into_row(std::vector<std::vector<std::string>> columns_content, unsigned int widget_width_with_spacing)
{
	std::string row = "";
	unsigned int max_length = 0;
	for (unsigned int column = 0; column < columns_content.size(); column++)
	{
		if (columns_content[column].size() > max_length)
		{
			max_length = columns_content[column].size();
		}
	}

	for (unsigned int column = 0; column < columns_content.size(); column++)
	{
		columns_content[column] = add_lines(columns_content[column], max_length - columns_content[column].size(), widget_width_with_spacing);
	}

	for (unsigned int line = 0; line < max_length; line++)
	{
		for (unsigned int column = 0; column < columns_content.size(); column++)
		{
			row = row + (columns_content[column])[line];
		}
		row = row + "\n";
	}
	return row;
}

void frame::cut_word(const std::string& word, unsigned int length, std::string& first_section, std::string& second_section)
{
	first_section = "";
	second_section = "";
	if (length > word.length())
	{
		length = word.length();
	}

	for (unsigned int i = 0; i < length; i++)
	{
		first_section = first_section + word[i];
	}

	for (unsigned int i = length; i < word.length(); i++)
	{
		second_section = second_section + word[i];
	}
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
	std::vector<std::vector<std::string>> columns_output;
	int total_rows = get_total_rows();
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
					widget_lines.insert(widget_lines.begin(), get_spacing(item.left_spacing, ' ') + std::string(1, item.corner_border) + get_spacing(get_widget_width(item, false) + 2, item.horizontal_border) + std::string(1, item.corner_border) + get_spacing(item.right_spacing, ' '));
					for (unsigned int k = 1; k < widget_lines.size(); k++)
					{
						widget_lines[k].insert(item.left_spacing, std::string(1, item.vertical_border) + " ");
						widget_lines[k].insert(widget_lines[k].length() - item.right_spacing, " " + std::string(1, item.vertical_border));
					}
					widget_lines.push_back(get_spacing(item.left_spacing, ' ') + std::string(1, item.corner_border) + get_spacing(get_widget_width(item, false) + 2, item.horizontal_border) + std::string(1, item.corner_border) + get_spacing(item.right_spacing, ' '));
				}

				if (item.highlight)
				{
					(widget_lines[0])[item.left_spacing] = item.highlight_character;
					(widget_lines[0])[widget_lines[0].length() - 1 - item.right_spacing] = item.highlight_character;
					(widget_lines[widget_lines.size() - 1])[item.left_spacing] = item.highlight_character;
					(widget_lines[widget_lines.size() - 1])[widget_lines[widget_lines.size() - 1].length() - 1 - item.right_spacing] = item.highlight_character;
				}
				accumulated_widget_lines.insert(accumulated_widget_lines.end(), widget_lines.begin(), widget_lines.end());
			}
			columns_output.push_back(accumulated_widget_lines);
		}
		frame_output = frame_output + fuse_columns_into_row(columns_output, get_widget_width(item, true));
		columns_output.clear();
	}
	return frame_output;
}