#pragma once
#include <string>
#include <vector>
#include "frame.h"

class widget
{
public:
	widget(frame* parent);
	int set_allignment(std::string allignment);
	int set_position(int row, int column);
	int set_output(const std::string& text);
	int set_spacing(int top, int bottom, int right, int left);
private:
	frame *parent_frame;
	int widget_id;
};