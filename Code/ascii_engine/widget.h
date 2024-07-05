#pragma once
#include <string>
#include <vector>
#include "frame.h"

class widget
{
public:
	widget(frame* parent, std::string special_operation="none");
	void set_alignment(std::string alignment);
	void set_spacing(int top, int bottom, int right, int left);
	void set_widget_type(int type);
	void set_vertical_border(char border);
	void set_horizontal_border(char border);
	void set_corner_border(char border);
	void add_border();
	void refresh();
	unsigned int get_width(bool include_spacing=false);
	unsigned int get_height(bool include_spacing = false);
	int get_x_origin();
	int get_y_origin();
	std::string get_output();
	std::string get_alignment();
	operator int() { return widget_id; }
protected:
	void set_output_to_frame(const std::string& text);
private:
	frame *parent_frame;
	int widget_id;
};