#pragma once
#include <string>
#include "frame.h"
#include "widget.h"
#include "format_tools.h"

#ifdef _WIN32
#ifdef LABEL_EXPORTS
#define LABEL_API __declspec(dllexport)
#else
#define LABEL_API __declspec(dllimport)
#endif
#elif __linux__
#define LABEL_API
#endif

class label : public widget
{
public:
	LABEL_API label(frame* parent, std::string special_operation = "none", bool start_logging=false, std::string logging_file_path="label.log");
	LABEL_API void set_output(const std::string& output);
	LABEL_API void set_colors(const std::vector<format_tools::index_format>& colors);
	LABEL_API std::vector<format_tools::index_format> get_colors();
};