#include "widget.h"

widget::widget(frame* parent)
{
	parent_frame = parent;
	widget_id = parent->add_widget();
}

int widget::set_allignment(std::string allignment)
{
	int status = parent_frame->set_allignment(widget_id, allignment);
	return status;
}

int widget::set_position(int row, int column)
{
	int status = parent_frame->set_position(widget_id, row, column);
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