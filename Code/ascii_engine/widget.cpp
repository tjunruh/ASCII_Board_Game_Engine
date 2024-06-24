#include "widget.h"
#include "error_codes.h"

widget::widget(frame* parent, std::string special_operation)
{
	parent_frame = parent;
	widget_id = parent_frame->add_widget();
	parent_frame->append(widget_id, special_operation);
}

int widget::set_allignment(std::string allignment)
{
	int status = parent_frame->set_allignment(widget_id, allignment);
	return status;
}

int widget::set_output(const std::string& text)
{
	int status = parent_frame->set_output(widget_id, text);
	return status;
}

int widget::set_spacing(int top, int bottom, int right, int left)
{
	int status = parent_frame->set_spacing(widget_id, top, bottom, right, left);
	return status;
}

int widget::set_widget_type(int type)
{
	int status = parent_frame->set_widget_type(widget_id, type);
	return status;
}

int widget::set_vertical_border(char border)
{
	int status = parent_frame->set_vertical_border(widget_id, border);
	return status;
}

int widget::set_horizontal_border(char border)
{
	int status = parent_frame->set_horizontal_border(widget_id, border);
	return status;
}

int widget::set_corner_border(char border)
{
	int status = parent_frame->set_corner_border(widget_id, border);
	return status;
}

int widget::add_border()
{
	int status = parent_frame->add_border(widget_id);
	return status;
}

void widget::refresh()
{
	parent_frame->display();
}