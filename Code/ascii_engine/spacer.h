#pragma once
#include <string>
#include "frame.h"

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
	SPACER_API spacer(frame* parent, float multiplier, const std::string& special_operation = "none", bool start_logging = false, const std::string& logging_file_path = "spacer.log");
};
