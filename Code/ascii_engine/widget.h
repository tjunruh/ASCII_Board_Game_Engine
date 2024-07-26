#pragma once
#include <string>
#include <vector>
#include "frame.h"
#include "logger.h"

class widget
{
public:
	widget(frame* parent, std::string special_operation="none");
	void set_alignment(std::string alignment);
	void set_spacing(int top, int bottom, int left, int right);
	void set_border_spacing(int top, int bottom, int left, int right);
	void set_vertical_border(char border);
	void set_horizontal_border(char border);
	void set_corner_border(char border);
	void set_highlight_character(char character);
	void add_border();
	void refresh();
	void selectable();
	void unselectable();
	unsigned int get_width(bool include_spacing=false);
	unsigned int get_height(bool include_spacing=false);
	int get_x_origin();
	int get_y_origin();
	int get_widget_type();
	std::string get_output();
	std::string get_alignment();
	operator int() { return widget_id; }
protected:
	void set_output_to_frame(const std::string& text);
	void set_widget_type(int type);
	logger log;
private:
	frame *parent_frame;
	int widget_id;
	int widget_type = WIDGET;
};