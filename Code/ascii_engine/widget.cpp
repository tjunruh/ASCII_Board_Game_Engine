#include "widget.h"
#include "error_codes.h"

widget::widget(frame* parent, int row, int column)
{
	parent_frame = parent;
	widget_id = parent->add_widget();
	int status = parent_frame->set_position(widget_id, row, column);
	if (status == INVALID_INDEX)
	{
		throw std::string("invalid index");
	}
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

void widget::refresh()
{
	parent_frame->display();
}