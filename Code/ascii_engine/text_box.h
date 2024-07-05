#pragma once
#include <string>
#include "frame.h"
#include "widget.h"

class text_box : public widget
{
public:
	text_box(frame* parent, std::string special_operation="none");
};

