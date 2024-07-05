#include "widget.h"
#include "error_codes.h"

widget::widget(frame* parent, std::string special_operation)
{
	parent_frame = parent;
	widget_id = parent_frame->add_widget();
	parent_frame->append(widget_id, special_operation);
}

void widget::set_alignment(std::string alignment)
{
	int status = parent_frame->set_alignment(widget_id, alignment);
}

void widget::set_output_to_frame(const std::string& text)
{
	int status = parent_frame->set_output(widget_id, text);
}

void widget::set_spacing(int top, int bottom, int right, int left)
{
	int status = parent_frame->set_spacing(widget_id, top, bottom, right, left);
}

void widget::set_widget_type(int type)
{
	int status = parent_frame->set_widget_type(widget_id, type);
}

void widget::set_vertical_border(char border)
{
	int status = parent_frame->set_vertical_border(widget_id, border);
}

void widget::set_horizontal_border(char border)
{
	int status = parent_frame->set_horizontal_border(widget_id, border);
}

void widget::set_corner_border(char border)
{
	int status = parent_frame->set_corner_border(widget_id, border);
}

void widget::add_border()
{
	int status = parent_frame->add_border(widget_id);
}

void widget::refresh()
{
	parent_frame->display();
}

unsigned int widget::get_width(bool include_spacing)
{
	unsigned int width = 0;
	int status = parent_frame->get_widget_width(widget_id, width, include_spacing);
	return width;
}

unsigned int widget::get_height(bool include_spacing)
{
	unsigned int height = 0;
	int status = parent_frame->get_widget_height(widget_id, height, include_spacing);
	return height;
}

int widget::get_x_origin()
{
	int x_origin = 0;
	int status = parent_frame->get_x_origin(widget_id, x_origin);
	return x_origin;
}

int widget::get_y_origin()
{
	int y_origin = 0;
	int status = parent_frame->get_y_origin(widget_id, y_origin);
	return y_origin;
}

std::string widget::get_output()
{
	std::string output = "";
	int status = parent_frame->get_output(widget_id, output);
	return output;
}

std::string widget::get_alignment()
{
	std::string alignment = "";
	int status = parent_frame->get_alignment(widget_id, alignment);
	return alignment;
}