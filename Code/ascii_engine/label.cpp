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
	set_output_to_frame(output);
}

void label::set_colors(const std::vector<format_tools::index_format>& colors)
{
	std::string output = get_output();
	for (unsigned int i = 0; i < colors.size(); i++)
	{
		if ((colors[i].index < 0) || ((unsigned int)colors[i].index >= output.length()))
		{
			log.log_status(INVALID_INDEX, "label::set_colors");
			return;
		}
	}

	log.log_status(SUCCESS, "label::set_colors");
	set_index_colors(colors);
}

std::vector<format_tools::index_format> label::get_colors()
{
	return get_index_colors();
}