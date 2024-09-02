#pragma once
#include <string>
#include "frame.h"
#include "widget.h"

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
};