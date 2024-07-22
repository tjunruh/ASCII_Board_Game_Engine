#include "logger.h"
#include "error_codes.h"
#include "../file_manager/file_manager.h"

int logger::start_widget_logging(const std::string& file_path, int widget_type)
{
	int status = file_manager::write_file(file_path, "Log for type " + std::to_string(widget_type) + " widget.");
	if (status == 1)
	{
		return INVALID_PATH;
	}
	else
	{
		log = true;
		_file_path = file_path;
		return SUCCESS;
	}
}

void logger::stop_widget_logging()
{
	log = false;
}

std::string logger::get_file_path()
{
	return _file_path;
}

bool logger::is_logging()
{
	return log;
}

void logger::log_status(int status, const std::string& function_name)
{
	if (log)
	{
		std::string log_line = function_name + " status: " + std::to_string(status);
		file_manager::append_to_file(_file_path, log_line);
	}
}

void logger::log_comment(const std::string& comment)
{
	if (log)
	{
		file_manager::append_to_file(_file_path, comment);
	}
}

void logger::log_begin(const std::string& function_name)
{
	if (log)
	{
		file_manager::append_to_file(_file_path, "=== " + function_name + " begin ===");
	}
}

void logger::log_end(const std::string& function_name)
{
	if (log)
	{
		file_manager::append_to_file(_file_path, "=== " + function_name + " end ===");
	}
}