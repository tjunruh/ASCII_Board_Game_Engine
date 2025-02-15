#include "../ascii_engine_dll_files/pch.h"
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

void widget::set_width_multiplier(float multiplier)
{
	int status = parent_frame->set_width_multiplier(widget_id, multiplier);
	log.log_status(status, "widget::set_width_multiplier");
}

void widget::set_spacing_width_multipliers(float left_multiplier, float right_multiplier)
{
	int status = parent_frame->set_spacing_width_multipliers(widget_id, left_multiplier, right_multiplier);
	log.log_status(status, "widget::set_spacing_width_multipliers");
}

void widget::set_border_spacing_width_multipliers(float left_multiplier, float right_multiplier)
{
	int status = parent_frame->set_border_spacing_width_multipliers(widget_id, left_multiplier, right_multiplier);
	log.log_status(status, "widget::set_border_spacing_width_multipliers");
}

void widget::add_border(bool border)
{
	int status = parent_frame->add_border(widget_id, border);
	log.log_status(status, "widget::add_border");
}

void widget::use_spacing_width_multipliers(bool use)
{
	int status = parent_frame->use_spacing_width_multipliers(widget_id, use);
	log.log_status(status, "widget::use_spacing_width_multipliers");
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

bool widget::is_selectable()
{
	bool selectable = false;
	int status = parent_frame->get_selectability(widget_id, selectable);
	log.log_status(status, "widget::is_selectable");
	return selectable;
}

void widget::get_spacing(int& top, int& bottom, int& left, int& right)
{
	int status = parent_frame->get_spacing(widget_id, top, bottom, left, right);
	log.log_status(status, "widget::get_spacing");
}

void widget::get_border_spacing(int& top, int& bottom, int& left, int& right)
{
	int status = parent_frame->get_border_spacing(widget_id, top, bottom, left, right);
	log.log_status(status, "widget::get_border_spacing");
}

char widget::get_vertical_border()
{
	char border = ' ';
	int status = parent_frame->get_vertical_border(widget_id, border);
	log.log_status(status, "widget::get_vertical_border");
	return border;
}

char widget::get_horizontal_border()
{
	char border = ' ';
	int status = parent_frame->get_horizontal_border(widget_id, border);
	log.log_status(status, "widget::get_horizontal_border");
	return border;
}

char widget::get_corner_border()
{
	char border = ' ';
	int status = parent_frame->get_corner_border(widget_id, border);
	log.log_status(status, "widget::get_corner_border");
	return border;
}

char widget::get_highlight_character()
{
	char highlight_character = ' ';
	int status = parent_frame->get_highlight_character(widget_id, highlight_character);
	log.log_status(status, "widget::get_highlight_character");
	return highlight_character;
}

float widget::get_width_multiplier()
{
	float multiplier = 0.0;
	int status = parent_frame->get_width_multiplier(widget_id, multiplier);
	log.log_status(status, "widget::get_width_multiplier");
	return multiplier;
}

void widget::get_spacing_width_multipliers(float& left_multiplier, float& right_multiplier)
{
	int status = parent_frame->get_spacing_width_multipliers(widget_id, left_multiplier, right_multiplier);
	log.log_status(status, "widget::get_spacing_width_multipliers");
}

void widget::get_border_spacing_width_multipliers(float& left_multiplier, float& right_multiplier)
{
	int status = parent_frame->get_border_spacing_width_multipliers(widget_id, left_multiplier, right_multiplier);
	log.log_status(status, "widget::get_border_spacing_width_multipliers");
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

bool widget::color_enabled()
{
	return parent_frame->color_enabled();
}

void widget::set_index_colors(const std::vector<format_tools::index_format>& index_colors)
{
	int status = parent_frame->set_index_colors(widget_id, index_colors);
	log.log_status(status, "widget::set_index_colors");
}

std::vector<format_tools::index_format> widget::get_index_colors()
{
	std::vector<format_tools::index_format> index_colors;
	int status = parent_frame->get_index_colors(widget_id, index_colors);
	log.log_status(status, "widget::get_index_colors");
	return index_colors;
}

std::vector<format_tools::index_format> widget::dec_format(std::string& format_content, unsigned int line_length)
{
	return parent_frame->dec_format(format_content, line_length);
}

int widget::get_default_foreground_color()
{
	return parent_frame->get_default_foreground_color();
}

int widget::get_default_background_color()
{
	return parent_frame->get_default_background_color();
}

int widget::start_logging(const std::string& file_path)
{
	int status = log.start_widget_logging(file_path, widget_type);
	return status;
}

void widget::stop_logging()
{
	log.stop_widget_logging();
}

int widget::reset_logging(const std::string& file_path)
{
	int status = log.log_reset(file_path, widget_type);
	return status;
}

#ifdef __linux__
void widget::dec_print(const std::string& input)
{
	parent_frame->dec_print(input);
}
#endif