#include "../ascii_engine_dll_files/pch.h"
#include "text_box.h"
#include "widget_types.h"

text_box::text_box(frame* parent, std::string special_operation, int lines_count, bool start_logging, std::string logging_file_path) : widget(parent, special_operation)
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
	set_selectable(true);
	set_line_constraint(true);
	if (lines_count > 0)
	{
		set_displayed_lines_count(lines_count);
		set_line_subtraction_from_terminal_height(0);
	}
	else if (lines_count < 0)
	{
		set_line_subtraction_from_terminal_height(lines_count * -1);
	}
	else
	{
		set_displayed_lines_count(1);
		set_line_subtraction_from_terminal_height(0);
	}
}

unsigned int text_box::write()
{
	x_origin = get_x_origin();
	y_origin = get_y_origin();

	if (get_output_length() == 0)
	{
		ascii_io::move_cursor_to_position(x_origin, y_origin);
	}
	else if (!first_key_stroke_initialized)
	{
		move_cursor_to_linear_position(saved_cursor_linear_position);
	}
	else
	{
		ascii_io::move_cursor_to_position(mouse_x_position, mouse_y_position);
	}

	if (get_line_of_position(saved_cursor_linear_position) >= (get_displayed_lines_count() + get_top_line()))
	{
		int x = 0;
		int y = 0;
		ascii_io::get_cursor_position(x, y);
		y = y_origin - 1 + get_displayed_lines_count();
		ascii_io::move_cursor_to_position(x, y);
		fit_cursor_to_line();
	}

	update_lines();
	ascii_io::show_cursor();
	int input = ascii_io::undefined;

	do
	{
		saved_cursor_linear_position = get_linear_cursor_position();
		input = ascii_io::getchar(mouse_x_position, mouse_y_position);
		if (frame_stale())
		{
			display_entire_frame();

			x_origin = get_x_origin();
			y_origin = get_y_origin();

			move_cursor_to_linear_position(saved_cursor_linear_position);

			if (get_line_of_position(saved_cursor_linear_position) >= (get_displayed_lines_count() + get_top_line()))
			{
				int x = 0;
				int y = 0;
				ascii_io::get_cursor_position(x, y);
				y = y_origin - 1 + get_displayed_lines_count();
				ascii_io::move_cursor_to_position(x, y);
				fit_cursor_to_line();
			}
		}

		unsigned int top_line = get_top_line();
		unsigned int displayed_lines = get_displayed_lines_count();

		if (input == ascii_io::up || input == ascii_io::scroll_up)
		{
			if (input == ascii_io::scroll_up && !inside_widget_space(mouse_x_position, mouse_y_position))
			{
				break;
			}
			else if (cursor_on_top_border())
			{
				if (top_line > 0)
				{
					top_line--;
					set_top_line(top_line);
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
		else if (input == ascii_io::down || input == ascii_io::scroll_down)
		{
			if (input == ascii_io::scroll_down && !inside_widget_space(mouse_x_position, mouse_y_position))
			{
				break;
			}
			else if (cursor_on_bottom_border())
			{
				if ((get_cursor_line() + 1) < get_total_lines_count())
				{
					top_line++;
					set_top_line(top_line);
					display();
					fit_cursor_to_line();
				}
			}
			else if((get_cursor_line() + 1) < get_total_lines_count())
			{
				ascii_io::move_cursor_down();
				fit_cursor_to_line();
			}
		}
		else if (input == ascii_io::right)
		{
			unsigned int position = get_linear_cursor_position();
			if ((position + 1) <= get_output_length())
			{
				if (get_line_of_position(position + 1) >= (top_line + displayed_lines))
				{
					top_line++;
					set_top_line(top_line);
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
					set_top_line(top_line);
				}
				move_cursor_to_linear_position(position - 1);
				display();
			}
		}
		else if (input == ascii_io::mouse_left_pressed)
		{
			if (inside_widget_space(mouse_x_position, mouse_y_position))
			{
				if (get_output_length() != 0)
				{
					unsigned int total_lines_count = get_total_lines_count();
					if (mouse_y_position - get_y_origin() + get_top_line() > total_lines_count)
					{
						mouse_y_position = get_y_origin() + total_lines_count - get_top_line();
					}
					ascii_io::move_cursor_to_position(mouse_x_position, mouse_y_position);
					fit_cursor_to_line();
				}
				else
				{
					ascii_io::move_cursor_to_position(x_origin, y_origin);
				}
			}
			else
			{
				break;
			}
		}
		else if (input == ascii_io::backspace && (get_linear_cursor_position() != 0))
		{
			unsigned int position = get_linear_cursor_position();
			erase_character_in_output(get_linear_cursor_position() - 1);
			update_lines();
			
			if (get_line_of_position(position - 1) < top_line)
			{
				top_line--;
				set_top_line(top_line);
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
		else if ((input != ascii_io::backspace) && (input != ascii_io::mouse_left_released) && (input != ascii_io::mouse_right_released) && (input != ascii_io::mouse_middle) && (input != ascii_io::mouse_right_pressed) && (input != ascii_io::unknown_mouse) && ((max_characters < 0) || (int(get_output_length()) < max_characters)))
		{
			unsigned int position = get_linear_cursor_position();
			log.log_comment(std::to_string(input));
			insert_character_in_output(position, (char)input);
			update_lines();

			if (get_line_of_position(position + 1) >= (top_line + displayed_lines))
			{
				top_line++;
				set_top_line(top_line);
			}
			move_cursor_to_linear_position(position + 1);
			display();
		}

	} while (true);
	
	saved_cursor_linear_position = get_linear_cursor_position();
	ascii_io::hide_cursor();
	return input;
}

void text_box::set_max_characters(int characters)
{
	max_characters = characters;
}

void text_box::clear()
{
	set_top_line(0);
	saved_cursor_linear_position = 0;
	set_output_to_frame("");
}

std::string text_box::get_text()
{
	return get_output();
}

void text_box::set_lines_count(int lines_count)
{
	if (lines_count > 0)
	{
		set_displayed_lines_count(lines_count);
		set_line_subtraction_from_terminal_height(0);
	}
	else if (lines_count < 0)
	{
		set_line_subtraction_from_terminal_height(lines_count * -1);
		dynamically_adjust_displayed_lines();
	}
	else
	{
		set_displayed_lines_count(1);
		set_line_subtraction_from_terminal_height(0);
	}

	mark_frame_as_stale();
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
	if ((unsigned int)y == ((unsigned int)y_origin + get_height() - 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void text_box::display()
{
	ascii_io::hide_cursor();
	std::vector<std::string> displayed_output;
	get_displayed_output(displayed_output);
	widget_display(displayed_output);
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
	unsigned int total_lines = get_total_lines_count();
	for (unsigned int i = 0; i < total_lines; i++)
	{
		if (((int)i - (int)get_top_line()) == y)
		{
			break;
		}
		position = position + get_line_length(i);
	}

	position = position + (unsigned int)x;
	return position;
}

void text_box::get_two_dimensional_cursor_position(unsigned int linear_position, int& x, int& y)
{
	x = x_origin;
	y = y_origin;
	unsigned int current_linear_position = 0;
	unsigned int total_lines = get_total_lines_count();
	for (unsigned int i = 0; i < total_lines; i++)
	{
		unsigned int line_length = get_line_length(i);
		if (i >= get_top_line())
		{
			for (unsigned int j = 0; j < line_length; j++)
			{
				if (current_linear_position >= linear_position)
				{
					return;
				}
				x++;
				current_linear_position++;
			}

			if (i != (total_lines - 1))
			{
				x = x_origin;
				y++;
			}
		}
		else
		{
			current_linear_position = current_linear_position + line_length;
		}
		
	}
}

unsigned int text_box::get_cursor_line()
{
	int x = 0;
	int y = 0;
	ascii_io::get_cursor_position(x, y);
	unsigned int line = (unsigned int)y - (unsigned int)y_origin + get_top_line();
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
	unsigned int total_lines = get_total_lines_count();
	for (unsigned int i = 0; i < total_lines; i++)
	{
		unsigned int line_length = get_line_length(i);
		for (unsigned int j = 0; j < line_length; j++)
		{
			if (current_linear_position >= position)
			{
				return line;
			}
			current_linear_position++;
		}

		if (i != (total_lines - 1))
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
	int line_length = (int)get_line_length(line);
	if (x > line_length)
	{
		x = line_length;
		ascii_io::move_cursor_to_position(x + x_origin, y + y_origin);
	}
}

void text_box::scroll_up()
{
	unsigned int top_line = get_top_line();
	if (1 >= top_line)
	{
		top_line = 0;
	}
	else
	{
		top_line--;
	}
	set_top_line(top_line);
	display();
}

void text_box::scroll_down()
{
	unsigned int top_line = get_top_line();
	unsigned int displayed_lines_count = get_displayed_lines_count();
	unsigned int total_lines = get_total_lines_count();
	unsigned int bottom_line = 0;
	if (displayed_lines_count < total_lines)
	{
		bottom_line = total_lines - displayed_lines_count;
	}

	if ((top_line + 1) > bottom_line)
	{
		top_line = bottom_line;
	}
	else
	{
		top_line = top_line + 1;
	}
	set_top_line(top_line);
	display();
}