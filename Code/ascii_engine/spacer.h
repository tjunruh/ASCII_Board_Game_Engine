#pragma once
#include <string>
#include "frame.h"
#include "logger.h"

#ifdef _WIN32
#ifdef SPACER_EXPORTS
#define SPACER_API __declspec(dllexport)
#else
#define SPACER_API __declspec(dllimport)
#endif
#elif __linux__
#define SPACER_API
#endif
class spacer
{
public:
	SPACER_API spacer(frame* parent, const std::string& special_operation = "none", bool start_logging = false, const std::string& logging_file_path = "spacer.log");
	SPACER_API void set_width_multiplier(float multiplier);
	SPACER_API float get_width_multiplier();
private:
	logger log;
	frame* parent_frame;
	int widget_id;
};
