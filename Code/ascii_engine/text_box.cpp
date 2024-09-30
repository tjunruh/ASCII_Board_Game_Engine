#include "../ascii_engine_dll_files/pch.h"
#include "text_box.h"
#include "widget_types.h"

text_box::text_box(frame* parent, std::string special_operation, unsigned int lines_count, bool start_logging, std::string logging_file_path) : widget(parent, special_operation)
{
	if (start_logging)
	{
		int logger_status = log.start_widget_logging(logging_file_path, LABEL);
		if (logger_status != 0)
		{
			ascii_io::clear();
			ascii_io::print("text_box initialization: Invalid logger path.\nPress any button to continue.");
			ascii_io::getchar();
		}
	}
	set_widget_type(TEXTBOX);
	selectable();
	displayed_lines = lines_count;
	std::string lines = "";
	for (unsigned int i = 0; i < lines_count; i++)
	{
		lines = lines + "\n";
	}
	set_output_to_frame(lines);
}

unsigned int text_box::write()
{
	x_origin = get_x_origin();
	y_origin = get_y_origin();
	width = get_width();
	height = get_height();
	if ((saved_cursor_x > 0) && (saved_cursor_y > 0))
	{
		ascii_io::move_cursor_to_position(saved_cursor_x, saved_cursor_y);
	}
	else
	{
		ascii_io::move_cursor_to_position(x_origin, y_origin);
	}
	ascii_io::show_cursor();
	int input = ascii_io::undefined;
	do
	{
		input = ascii_io::getchar();
		if (input == ascii_io::up)
		{
			if (cursor_on_top_border())
			{
				if (top_line > 0)
				{
					top_line--;
					display();
					fit_cursor_to_line();
				}
			}
			else
			{
				ascii_io::move_cursor_up();
				fit_cursor_to_line();
			}
		}
		else if (input == ascii_io::down)
		{
			if (cursor_on_bottom_border())
			{
				if ((get_cursor_line() + 1) < editable_lines.size())
				{
					top_line++;
					display();
					fit_cursor_to_line();
				}
			}
			else if((get_cursor_line() + 1) < editable_lines.size())
			{
				ascii_io::move_cursor_down();
				fit_cursor_to_line();
			}
		}
		else if (input == ascii_io::right)
		{
			unsigned int position = get_linear_cursor_position();
			if ((position + 1) <= editable_content.length())
			{
				if (get_line_of_position(position + 1) >= (top_line + displayed_lines))
				{
					top_line++;
				}
				move_cursor_to_linear_position(position + 1);
				display();
			}
		}
		else if (input == ascii_io::left)
		{
			unsigned int position = get_linear_cursor_position();
			if (position > 0)
			{
				if (get_line_of_position(position - 1) < top_line)
				{
					top_line--;
				}
				move_cursor_to_linear_position(position - 1);
				display();
			}
		}
		else if (input == ascii_io::backspace && (get_linear_cursor_position() != 0))
		{
			unsigned int position = get_linear_cursor_position();
			editable_content.erase(editable_content.begin() + get_linear_cursor_position() - 1);
			update_lines();
			
			if (get_line_of_position(position - 1) < top_line)
			{
				top_line--;
			}
			move_cursor_to_linear_position(position - 1);
			display();
		}
		else if (input == ascii_io::enter)
		{
			break;
		}
		else if (input == ascii_io::DEL)
		{
			break;
		}
		else if (input == ascii_io::ESC)
		{
			break;
		}
		else if ((input != ascii_io::backspace) && ((max_characters < 0) || (int(editable_content.length()) < max_characters)))
		{
			unsigned int position = get_linear_cursor_position();
			editable_content.insert(get_linear_cursor_position(), std::string(1, (char)input));
			update_lines();

			if (get_line_of_position(position + 1) >= (top_line + displayed_lines))
			{
				top_line++;
			}
			move_cursor_to_linear_position(position + 1);
			display();
		}

	} while (true);
	
	set_output();
	ascii_io::get_cursor_position(saved_cursor_x, saved_cursor_y);
	return input;
}

void text_box::set_max_characters(int characters)
{
	max_characters = characters;
}

void text_box::clear()
{
	top_line = 0;
	editable_content = "";
	editable_lines.clear();
	saved_cursor_x = -1;
	saved_cursor_y = -1;
	set_output();
}

std::string text_box::get_text()
{
	return editable_content;
}

bool text_box::cursor_on_top_border()
{
	int x = 0;
	int y = 0;
	ascii_io::get_cursor_position(x, y);
	if (y == y_origin)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool text_box::cursor_on_bottom_border()
{
	int x = 0;
	int y = 0;
	ascii_io::get_cursor_position(x, y);
	if (y == (y_origin + height - 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void text_box::update_lines()
{
	std::string line = "";
	editable_lines.clear();
	std::vector<std::string> words = format_tools::split_string(editable_content, ' ');
	for (unsigned int j = 0; j < words.size(); j++)
	{
		if ((((line + words[j]).length())) <= (unsigned int)width)
		{
			line = line + words[j];
		}
		else if (words[j].length() >= (unsigned int)width)
		{
			std::string first_section = "";
			std::string second_section = "";
			format_tools::cut_word(words[j], width - line.length(), first_section, second_section);
			line = line + first_section;
			editable_lines.push_back(line);
			line = "";
			words.insert(words.begin() + (j + 1), second_section);
		}
		else
		{
			if (words[j] == " ")
			{
				line = line + words[j];
				editable_lines.push_back(line);
				line = "";
			}
			else
			{
				editable_lines.push_back(line);
				line = words[j];
			}
		}
	}
	if (line != "")
	{
		editable_lines.push_back(line);
	}
}

void text_box::display()
{
	unsigned int stop_line = 0;
	int cursor_x = 0;
	int cursor_y = 0;
	ascii_io::get_cursor_position(cursor_x, cursor_y);
	if (editable_lines.size() < (displayed_lines + top_line))
	{
		stop_line = editable_lines.size();
	}
	else
	{
		stop_line = displayed_lines + top_line;
	}

	ascii_io::hide_cursor();
	ascii_io::move_cursor_to_position(x_origin, y_origin);
	std::string line = "";
	for (unsigned int i = top_line; i < stop_line; i++)
	{
		line = editable_lines[i];
		ascii_io::print(format_tools::fill_line(line, width, "left"));
		ascii_io::move_cursor_to_position(x_origin, y_origin + i - top_line + 1);
	}
	if (stop_line != (displayed_lines + top_line))
	{
		ascii_io::print(format_tools::get_spacing(width, ' '));
	}
	ascii_io::move_cursor_to_position(cursor_x, cursor_y);
	ascii_io::show_cursor();
}

unsigned int text_box::get_linear_cursor_position()
{
	int x = 0;
	int y = 0;
	ascii_io::get_cursor_position(x, y);
	x = x - x_origin;
	y = y - y_origin;
	unsigned int position = 0;
	for (unsigned int i = 0; i < editable_lines.size(); i++)
	{
		if (((int)i - (int)top_line) == y)
		{
			break;
		}
		position = position + editable_lines[i].length();
	}

	position = position + (unsigned int)x;
	return position;
}

void text_box::get_two_dimensional_cursor_position(unsigned int linear_position, int& x, int& y)
{
	x = x_origin;
	y = y_origin;
	unsigned int current_linear_position = 0;
	for (unsigned int i = 0; i < editable_lines.size(); i++)
	{
		if (i >= top_line)
		{
			for (unsigned int j = 0; j < editable_lines[i].length(); j++)
			{
				if (current_linear_position >= linear_position)
				{
					return;
				}
				x++;
				current_linear_position++;
			}

			if (i != (editable_lines.size() - 1))
			{
				x = x_origin;
				y++;
			}
		}
		else
		{
			current_linear_position = current_linear_position + editable_lines[i].length();
		}
		
	}
}

unsigned int text_box::get_cursor_line()
{
	int x = 0;
	int y = 0;
	ascii_io::get_cursor_position(x, y);
	unsigned int line = (unsigned int)y - (unsigned int)y_origin + top_line;
	return line;
}

unsigned int text_box::get_cursor_column()
{
	int x = 0;
	int y = 0;
	ascii_io::get_cursor_position(x, y);
	unsigned int column = (unsigned int)x - (unsigned int)x_origin;
	return column;
}

unsigned int text_box::get_line_of_position(unsigned int position)
{
	unsigned int line = 0;
	unsigned int current_linear_position = 0;
	for (unsigned int i = 0; i < editable_lines.size(); i++)
	{
		for (unsigned int j = 0; j < editable_lines[i].length(); j++)
		{
			if (current_linear_position >= position)
			{
				return line;
			}
			current_linear_position++;
		}

		if (i != (editable_lines.size() - 1))
		{
			line++;
		}
	}
	return line;
}

void text_box::move_cursor_to_linear_position(unsigned int position)
{
	int x = 0;
	int y = 0;
	get_two_dimensional_cursor_position(position, x, y);
	ascii_io::move_cursor_to_position(x, y);
}

void text_box::fit_cursor_to_line()
{
	int x = 0;
	int y = 0;
	ascii_io::get_cursor_position(x, y);
	x = x - x_origin;
	y = y - y_origin;
	unsigned int line = get_cursor_line();
	if (x > int(editable_lines[line].length()))
	{
		x = editable_lines[line].length();
		ascii_io::move_cursor_to_position(x + x_origin, y + y_origin);
	}
}

void text_box::set_output()
{
	unsigned int stop_line = 0;
	std::string output = "";
	if (editable_lines.size() < (displayed_lines + top_line))
	{
		stop_line = editable_lines.size();
	}
	else
	{
		stop_line = displayed_lines + top_line;
	}

	for (unsigned int i = top_line; i < stop_line; i++)
	{
		output = output + editable_lines[i];
	}

	if (output != "")
	{
		output = output + "\n";
	}
	
	for (unsigned int i = (stop_line - top_line); i < displayed_lines; i++)
	{
		output = output + "\n";
	}

	set_output_to_frame(output);
}