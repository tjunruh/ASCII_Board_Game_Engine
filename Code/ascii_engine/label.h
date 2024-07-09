#pragma once
#include <string>
#include "frame.h"
#include "widget.h"

class label : public widget
{
public:
	label(frame* parent, std::string special_operation = "none");
	void set_output(const std::string& output);
};