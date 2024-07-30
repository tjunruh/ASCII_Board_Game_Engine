#include "widget.h"

widget::widget(frame* parent, std::string special_operation)
{
	parent_frame = parent;
	widget_id = parent_frame->add_widget();
	int status = parent_frame->append(widget_id, special_operation);
	log.log_status(status, "widget::widget");
}

void widget::set_alignment(std::string alignment)
{
	int status = parent_frame->set_alignment(widget_id, alignment);
	log.log_status(status, "widget::set_alignment");
}

void widget::set_output_to_frame(const std::string& text)
{
	int status = parent_frame->set_output(widget_id, text);
	log.log_status(status, "widget::set_output_to_frame");
}

void widget::set_spacing(int top, int bottom, int left, int right)
{
	int status = parent_frame->set_spacing(widget_id, top, bottom, left, right);
	log.log_status(status, "widget::set_spacing");
}

void widget::set_border_spacing(int top, int bottom, int right, int left)
{
	int status = parent_frame->set_border_spacing(widget_id, top, bottom, right, left);
	log.log_status(status, "widget::set_border_spacing");
}

void widget::set_widget_type(int type)
{
	widget_type = type;
	int status = parent_frame->set_widget_type(widget_id, widget_type);
	log.log_status(status, "widget::set_widget_type");
}

void widget::set_vertical_border(char border)
{
	int status = parent_frame->set_vertical_border(widget_id, border);
	log.log_status(status, "widget::set_vertical_border");
}

void widget::set_horizontal_border(char border)
{
	int status = parent_frame->set_horizontal_border(widget_id, border);
	log.log_status(status, "widget::set_horizontal_border");
}

void widget::set_corner_border(char border)
{
	int status = parent_frame->set_corner_border(widget_id, border);
	log.log_status(status, "widget::set_corner_border");
}

void widget::set_highlight_character(char character)
{
	int status = parent_frame->set_highlight_character(widget_id, character);
	log.log_status(status, "widget::set_highlight_character");
}

void widget::add_border()
{
	int status = parent_frame->add_border(widget_id);
	log.log_status(status, "widget::add_border");
}

void widget::refresh()
{
	parent_frame->display();
}

void widget::selectable()
{
	int status = parent_frame->set_selectable(widget_id, true);
	log.log_status(status, "widget::selectable");
}

void widget::unselectable()
{
	int status = parent_frame->set_selectable(widget_id, false);
	log.log_status(status, "widget::unselectable");
}

unsigned int widget::get_width(bool include_spacing)
{
	unsigned int width = 0;
	int status = parent_frame->get_widget_width(widget_id, width, include_spacing);
	log.log_status(status, "widget::get_width");
	return width;
}

unsigned int widget::get_height(bool include_spacing)
{
	unsigned int height = 0;
	int status = parent_frame->get_widget_height(widget_id, height, include_spacing);
	log.log_status(status, "widget::get_height");
	return height;
}

int widget::get_x_origin()
{
	int x_origin = 0;
	int status = parent_frame->get_x_origin(widget_id, x_origin);
	log.log_status(status, "widget::get_x_origin");
	return x_origin;
}

int widget::get_y_origin()
{
	int y_origin = 0;
	int status = parent_frame->get_y_origin(widget_id, y_origin);
	log.log_status(status, "widget::get_y_origin");
	return y_origin;
}

int widget::get_widget_type()
{
	return widget_type;
}

std::string widget::get_output()
{
	std::string output = "";
	int status = parent_frame->get_output(widget_id, output);
	log.log_status(status, "widget::get_output");
	return output;
}

std::string widget::get_alignment()
{
	std::string alignment = "";
	int status = parent_frame->get_alignment(widget_id, alignment);
	log.log_status(status, "widget::get_alignment");
	return alignment;
}

bool widget::frame_stale()
{
	return parent_frame->stale();
}

void widget::frame_display()
{
	parent_frame->display();
}

bool widget::dec_enabled()
{
	return parent_frame->dec_enabled();
}

std::vector<dec_region> widget::dec_format(const std::string& format_content)
{
	return parent_frame->dec_format(format_content);
}

#ifdef __linux__
void widget::dec_print(const std::string& input)
{
	parent_frame->dec_print(input);
}
#endif