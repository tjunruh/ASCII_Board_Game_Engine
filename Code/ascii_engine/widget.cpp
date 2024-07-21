#include "widget.h"
#include "error_codes.h"
#include "../file_manager/file_manager.h"

widget::widget(frame* parent, std::string special_operation)
{
	parent_frame = parent;
	widget_id = parent_frame->add_widget();
	parent_frame->append(widget_id, special_operation);
}

void widget::set_alignment(std::string alignment)
{
	int status = parent_frame->set_alignment(widget_id, alignment);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "set_alignment status: " + std::to_string(status));
	}
}

void widget::set_output_to_frame(const std::string& text)
{
	int status = parent_frame->set_output(widget_id, text);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "set_output_to_frame status: " + std::to_string(status));
	}
}

void widget::set_spacing(int top, int bottom, int left, int right)
{
	int status = parent_frame->set_spacing(widget_id, top, bottom, left, right);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "set_spacing status: " + std::to_string(status));
	}
}

void widget::set_border_spacing(int top, int bottom, int right, int left)
{
	int status = parent_frame->set_border_spacing(widget_id, top, bottom, right, left);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "set_border_spacing status: " + std::to_string(status));
	}
}

void widget::set_widget_type(int type)
{
	int status = parent_frame->set_widget_type(widget_id, type);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "set_widget_type status: " + std::to_string(status));
	}
}

void widget::set_vertical_border(char border)
{
	int status = parent_frame->set_vertical_border(widget_id, border);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "set_vertical_border status: " + std::to_string(status));
	}
}

void widget::set_horizontal_border(char border)
{
	int status = parent_frame->set_horizontal_border(widget_id, border);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "set_horizontal_border status: " + std::to_string(status));
	}
}

void widget::set_corner_border(char border)
{
	int status = parent_frame->set_corner_border(widget_id, border);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "set_corner_border status: " + std::to_string(status));
	}
}

void widget::add_border()
{
	int status = parent_frame->add_border(widget_id);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "add_border status: " + std::to_string(status));
	}
}

void widget::refresh()
{
	parent_frame->display();
}

unsigned int widget::get_width(bool include_spacing)
{
	unsigned int width = 0;
	int status = parent_frame->get_widget_width(widget_id, width, include_spacing);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "get_width status: " + std::to_string(status));
	}
	return width;
}

unsigned int widget::get_height(bool include_spacing)
{
	unsigned int height = 0;
	int status = parent_frame->get_widget_height(widget_id, height, include_spacing);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "get_height status: " + std::to_string(status));
	}
	return height;
}

int widget::get_x_origin()
{
	int x_origin = 0;
	int status = parent_frame->get_x_origin(widget_id, x_origin);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "get_x_origin status: " + std::to_string(status));
	}
	return x_origin;
}

int widget::get_y_origin()
{
	int y_origin = 0;
	int status = parent_frame->get_y_origin(widget_id, y_origin);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "get_y_origin status: " + std::to_string(status));
	}
	return y_origin;
}

std::string widget::get_output()
{
	std::string output = "";
	int status = parent_frame->get_output(widget_id, output);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "get_output status: " + std::to_string(status));
	}
	return output;
}

std::string widget::get_alignment()
{
	std::string alignment = "";
	int status = parent_frame->get_alignment(widget_id, alignment);
	if (log)
	{
		file_manager::append_to_file(log_file_path, "get_alignment status: " + std::to_string(status));
	}
	return alignment;
}

int widget::start_logging(std::string file_path)
{
	int status = UNDEFINED;
	int type = WIDGET;
	status = parent_frame->get_widget_type(widget_id, type);
	if (status != SUCCESS)
	{
		return status;
	}
	status = file_manager::write_file(file_path, "Log for type " + std::to_string(type) + " widget.");
	if (status == 1)
	{
		return INVALID_PATH;
	}
	else
	{
		log = true;
		log_file_path = file_path;
		return SUCCESS;
	}
}

void widget::stop_logging()
{
	log = false;
}