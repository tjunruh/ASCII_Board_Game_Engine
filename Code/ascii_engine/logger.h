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
	LOGGER_API int start_widget_logging(const std::string& file_path, int widget_type);
	LOGGER_API void stop_widget_logging();
	LOGGER_API std::string get_file_path();
	LOGGER_API bool is_logging();
	LOGGER_API void log_status(int status, const std::string& function_name);
	LOGGER_API void log_comment(const std::string& comment);
	LOGGER_API void log_begin(const std::string& function_name);
	LOGGER_API void log_end(const std::string& function_name);
	LOGGER_API int log_reset(const std::string& file_path, int widget_type);
private:
	bool log = false;
	std::string _file_path = "";
};