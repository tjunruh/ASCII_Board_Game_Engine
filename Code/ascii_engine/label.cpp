#include "../ascii_engine_dll_files/pch.h"
#include "label.h"
#include "widget_types.h"
#include "error_codes.h"

label::label(frame* parent, const std::string& special_operation, int lines_count, bool start_logging, const std::string& logging_file_path) : widget(parent, special_operation)
{
	if (start_logging)
	{
		int logger_status = log.start_widget_logging(logging_file_path, LABEL);
		if (logger_status != 0)
		{
			ascii_io::clear();
			ascii_io::print("label initialization: Invalid logger path.\nPress any button to continue.");
			ascii_io::getchar();
		}
	}
	set_widget_type(LABEL);
	unselectable();
	if (lines_count != 0)
	{
		if (lines_count > 0)
		{
			set_line_subtraction_from_terminal_height(0);
			set_displayed_lines(lines_count);
		}
		else if (lines_count < 0)
		{
			set_line_subtraction_from_terminal_height(lines_count * -1);
		}

		set_line_constraint(true);
	}
}

void label::set_output(std::string output)
{
	std::vector<format_tools::index_format> colors = format_tools::convert_color_tags(output);
	if (colors.size() == 0)
	{
		colors = get_index_colors();
		if (colors.size() > 0)
		{
			int color_elements = (int)colors.size() - 1;
			for (int i = color_elements; i >= 0; i--)
			{
				if ((unsigned int)colors[i].index >= output.length())
				{
					colors.erase(colors.begin() + i);
				}
				else if (output[colors[i].index] == '\n')
				{
					if (((unsigned int)colors[i].index + 1) < output.length())
					{
						colors[i].index = colors[i].index + 1;
					}
					else if ((colors[i].index - 1) >= 0)
					{
						colors[i].index = colors[i].index - 1;
					}
					else
					{
						colors.erase(colors.begin() + i);
					}
				}
			}
			set_index_colors(colors);
		}
	}
	else
	{
		set_index_colors(colors);
	}

	set_output_to_frame(output);
}

void label::set_colors(std::vector<format_tools::index_format> colors)
{
	std::string output = get_output();
	if (colors.size() > 0)
	{
		int color_elements = (int)colors.size() - 1;
		for (int i = color_elements; i >= 0; i--)
		{
			if ((colors[i].index < 0) || ((unsigned int)colors[i].index >= output.length()))
			{
				log.log_status(INVALID_INDEX, "label::set_colors");
				return;
			}
			else if (output[colors[i].index] == '\n')
			{
				if (((unsigned int)colors[i].index + 1) < output.length())
				{
					colors[i].index = colors[i].index + 1;
				}
				else if (colors[i].index - 1 >= 0)
				{
					colors[i].index = colors[i].index - 1;
				}
				else
				{
					colors.erase(colors.begin() + i);
				}
			}
		}
	}


	log.log_status(SUCCESS, "label::set_colors");
	set_index_colors(colors);
}

std::vector<format_tools::index_format> label::get_colors()
{
	return get_index_colors();
}

std::vector<format_tools::index_format> label::get_displayed_colors()
{
	return get_displayed_index_colors();
}

void label::display()
{
	std::vector<std::string> displayed_output;
	std::vector<format_tools::index_format> colors;
	get_displayed_output(displayed_output, colors);
	widget_display(displayed_output, true, true, colors);
}

void label::scroll()
{
	int input = ascii_io::undefined;
	do
	{
		input = ascii_io::getchar();
		if (input == _up)
		{
			scroll_up();
		}
		else if (input == _down)
		{
			scroll_down();
		}

	} while (input != _quit);
}

void label::scroll_up(unsigned int amount, bool render)
{
	unsigned int top_line = get_top_line();
	if (amount >= top_line)
	{
		top_line = 0;
	}
	else
	{
		top_line = top_line - amount;
	}
	set_top_line(top_line);
	if (render)
	{
		display();
	}
}

void label::scroll_down(unsigned int amount, bool render)
{
	unsigned int top_line = get_top_line();
	unsigned int displayed_lines = get_displayed_lines();
	unsigned int total_lines = get_lines_count(false);
	unsigned int bottom_line = 0;
	if (displayed_lines < total_lines)
	{
		bottom_line = total_lines - displayed_lines;
	}

	if ((top_line + amount) > bottom_line)
	{
		top_line = bottom_line;
	}
	else
	{
		top_line = top_line + amount;
	}
	set_top_line(top_line);
	if (render)
	{
		display();
	}
}

void label::set_controls(int up, int down, int quit)
{
	_up = up;
	_down = down;
	_quit = quit;
}

void label::get_controls(int& up, int& down, int& quit)
{
	up = _up;
	down = _down;
	quit = _quit;
}

void label::set_lines_count(int lines_count)
{
	if (lines_count == 0)
	{
		set_line_constraint(false);
		set_top_line(0);
	}
	else if (lines_count > 0)
	{
		set_line_subtraction_from_terminal_height(0);
		set_displayed_lines(lines_count);
		set_line_constraint(true);
		bound_top_line();
	}
	else if (lines_count < 0)
	{
		set_line_subtraction_from_terminal_height(lines_count * -1);
		dynamically_adjust_displayed_lines();
		set_line_constraint(true);
	}
}