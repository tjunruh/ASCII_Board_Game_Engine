#include "../ascii_engine_dll_files/pch.h"
#include "spacer.h"
#include "error_codes.h"

spacer::spacer(frame* parent, const std::string& special_operation, bool start_logging, const std::string& logging_file_path)
{
	parent_frame = parent;
	widget_id = parent_frame->add_widget();
	if (start_logging)
	{
		int logger_status = log.start_widget_logging(logging_file_path, SPACER);
		if (logger_status != 0)
		{
			ascii_io::clear();
			ascii_io::print("spacer initialization: Invalid logger path.\nPress any button to continue.");
			ascii_io::getchar();
		}
	}

	if (special_operation != parent_frame->special_operation_none && special_operation != parent_frame->special_operation_new_line)
	{
		log.log_status(INVALID_VALUE, "spacer");
		return;
	}

	int status = parent_frame->append(widget_id, special_operation);
	log.log_status(status, "spacer");

	status = parent_frame->set_widget_type(widget_id, SPACER);
	log.log_status(status, "spacer");

	status = parent_frame->set_selectable(widget_id, false);
	log.log_status(status, "spacer");

	status = parent_frame->set_output(widget_id, "\n");
	log.log_status(status, "spacer");

	
	log.stop_widget_logging();
}

void spacer::set_width_multiplier(float multiplier)
{
	int status = parent_frame->set_width_multiplier(widget_id, multiplier);
	log.log_status(status, "spacer::set_width_multiplier");
}

float spacer::get_width_multiplier()
{
	float multiplier = 0.0;
	int status = parent_frame->get_width_multiplier(widget_id, multiplier);
	log.log_status(status, "spacer::get_width_multiplier");
	return multiplier;
}