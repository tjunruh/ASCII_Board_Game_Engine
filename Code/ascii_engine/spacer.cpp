#include "spacer.h"
#include "logger.h"
#include "error_codes.h"

void spacer(frame* parent, float multiplier, std::string special_operation, bool start_logging, std::string logging_file_path)
{
	int id = parent->add_widget();
	logger log;
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

	if (special_operation != parent->special_operation_none && special_operation != parent->special_operation_new_line)
	{
		log.log_status(INVALID_VALUE, "spacer");
		return;
	}

	int status = parent->append(id, special_operation);
	log.log_status(status, "spacer");

	status = parent->set_widget_type(id, SPACER);
	log.log_status(status, "spacer");

	status = parent->set_selectable(id, false);
	log.log_status(status, "spacer");

	status = parent->set_output(id, "\n");
	log.log_status(status, "spacer");

	status = parent->set_width_multiplier(id, multiplier);
	log.log_status(status, "spacer");
	log.stop_widget_logging();
}