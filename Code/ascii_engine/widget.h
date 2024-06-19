#pragma once
#include <string>
#include <vector>
#include "frame.h"

class menu;

class widget
{
public:
	widget(frame* parent, int row, int column);
	int set_allignment(std::string allignment);
	int set_output(const std::string& text);
	int set_spacing(int top, int bottom, int right, int left);
	int set_widget_type(int type);
	int set_vertical_border(char border);
	int set_horizontal_border(char border);
	int set_corner_border(char border);
	int add_border();
	void refresh();
	operator int() { return widget_id; }
private:
	frame *parent_frame;
	int widget_id;
};