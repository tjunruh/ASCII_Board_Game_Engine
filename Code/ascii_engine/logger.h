#pragma once
#include <string>

#ifdef _WIN32
#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif
#elif __linux__
#define LOGGER_API
#endif

class logger
{
public:
	int start_widget_logging(const std::string& file_path, int widget_type);
	void stop_widget_logging();
	std::string get_file_path();
	bool is_logging();
	void log_status(int status, const std::string& function_name);
	void log_comment(const std::string& comment);
	void log_begin(const std::string& function_name);
	void log_end(const std::string& function_name);
private:
	bool log = false;
	std::string _file_path = "";
};