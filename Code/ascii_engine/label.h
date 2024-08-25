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
#endif

class label : public widget
{
public:
	label(frame* parent, std::string special_operation = "none", bool start_logging=false, std::string logging_file_path="label.log");
	void set_output(const std::string& output);
	int start_logging(const std::string& file_path);
	void stop_logging();
};