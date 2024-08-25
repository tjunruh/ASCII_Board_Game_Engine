#include "pch.h"
#include "label.h"
#include "widget_types.h"

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

int label::start_logging(const std::string& file_path)
{
	int status = log.start_widget_logging(file_path, get_widget_type());
	return status;
}

void label::stop_logging()
{
	log.stop_widget_logging();
}