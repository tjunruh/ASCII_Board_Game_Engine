#include "../ascii_engine_dll_files/pch.h"
#include "label.h"
#include "widget_types.h"
#include "error_codes.h"

label::label(frame* parent, std::string special_operation, bool start_logging, std::string logging_file_path) : widget(parent, special_operation)
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
}

void label::set_output(const std::string& output)
{
	std::vector<format_tools::index_format> colors = get_index_colors();
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