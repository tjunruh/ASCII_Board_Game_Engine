#pragma once
#include <string>
#include <vector>
#include "frame.h"
#include "widget.h"
#include "format_tools.h"

class text_box : public widget
{
public:
	text_box(frame* parent, std::string special_operation="none", unsigned int lines_count=1);
	void write();
private:
	bool curser_on_top_border();
	bool curser_on_bottom_border();
	void update_lines();
	void display();
	unsigned int get_linear_curser_position();
	void get_two_dimensional_curser_position(unsigned int linear_position, int& x, int& y);
	unsigned int get_curser_line();
	unsigned int get_curser_column();
	unsigned int get_line_of_position(unsigned int position);
	void move_curser_to_linear_position(unsigned int position);
	void fit_curser_to_line();
	unsigned int top_line = 0;
	unsigned int displayed_lines = 0;
	std::string editable_content = "";
	std::vector<std::string> editable_lines;
	int x_origin = 0;
	int y_origin = 0;
	int width = 0;
	int height = 0;
};

