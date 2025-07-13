#include "../ascii_engine_dll_files/pch.h"
#include "widget.h"
#include "error_codes.h"

#ifdef __linux__
#include <algorithm>
#endif

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

void widget::set_output_to_frame(const std::string& text, bool mark_stale)
{
	int status = parent_frame->set_output(widget_id, text, mark_stale);
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

void widget::display_entire_frame()
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

std::string widget::get_displayed_output()
{
	std::vector<std::string> output_lines;
	std::string output = "";
	int status = parent_frame->get_displayed_output(widget_id, output_lines);
	output_lines = format_tools::add_newline_characters(output_lines);
	if (output_lines.size() > 0 && output_lines[output_lines.size() - 1].length() > 0)
	{
		output_lines[output_lines.size() - 1].erase(output_lines[output_lines.size() - 1].length() - 1, 1);
	}
	output = format_tools::get_string(output_lines);
	log.log_status(status, "widget::get_displayed_output");
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

void widget::mark_frame_as_stale()
{
	parent_frame->mark_as_stale();
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

std::vector<format_tools::index_format> widget::get_displayed_index_colors()
{
	std::vector<format_tools::index_format> index_colors;
	int status = parent_frame->get_displayed_colors(widget_id, index_colors);
	log.log_status(status, "widget::get_displayed_index_colors");
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

void widget::widget_display(std::vector<std::string> output_lines, bool can_use_dec, bool can_use_color, const std::vector<format_tools::index_format>& colors)
{
	unsigned int width = get_width();
	int x_origin = get_x_origin();
	int y_origin = get_y_origin();
	int cursor_x = 0;
	int cursor_y = 0;
	ascii_io::get_cursor_position(cursor_x, cursor_y);
	if (frame_stale())
	{
		frame_display();
	}
	else if ((can_use_dec && dec_enabled()) || (can_use_color && color_enabled()))
	{
		std::vector<format_tools::index_format> index_regions;
		if (can_use_color && color_enabled())
		{
			index_regions = colors;
		}

		output_lines = format_tools::fill_lines(output_lines, width, get_alignment());

		std::string adjusted_output = format_tools::get_string(output_lines);

		if (can_use_dec && dec_enabled())
		{
			std::vector<format_tools::index_format> dec_regions = dec_format(adjusted_output, get_width());
			if (index_regions.size() > 0)
			{
				index_regions = format_tools::combine(index_regions, dec_regions);
			}
			else
			{
				index_regions = dec_regions;
			}
		}

		int line = 0;
		unsigned int line_length = 0;
		ascii_io::move_cursor_to_position(x_origin, y_origin);
		std::vector<format_tools::content_format> regions = format_tools::convert(index_regions, adjusted_output);
		regions = format_tools::fit_to_width(regions, width);
		for (unsigned int i = 0; i < regions.size(); i++)
		{
			int foreground_color = get_default_foreground_color();
			int background_color = get_default_background_color();
			if (std::count(format_tools::colors.begin(), format_tools::colors.end(), regions[i].format.foreground_format) != 0)
			{
				foreground_color = regions[i].format.foreground_format;
			}

			if (std::count(format_tools::colors.begin(), format_tools::colors.end(), regions[i].format.background_format) != 0)
			{
				background_color = regions[i].format.background_format;
			}

			ascii_io::set_color(foreground_color, background_color, regions[i].format.bold);

			if (regions[i].format.dec)
			{
#ifdef _WIN32
				ascii_io::enable_dec();
				ascii_io::print(regions[i].content);
#elif __linux__
				dec_print(regions[i].content);
#endif
			}
			else
			{
#ifdef _WIN32
				ascii_io::disable_dec();
#endif
				ascii_io::print(regions[i].content);
			}
			line_length = line_length + regions[i].content.length();
			if (line_length >= width)
			{
				line++;
				line_length = 0;
				ascii_io::move_cursor_to_position(x_origin, y_origin + line);
			}
		}
		ascii_io::set_color(get_default_foreground_color(), get_default_background_color());
#ifdef _WIN32
		ascii_io::disable_dec();
#endif
	}
	else
	{
		output_lines = format_tools::fill_lines(output_lines, width, get_alignment());
		for (unsigned int i = 0; i < output_lines.size(); i++)
		{
			ascii_io::move_cursor_to_position(x_origin, y_origin + i);
			ascii_io::print(output_lines[i]);
		}
	}
	ascii_io::move_cursor_to_position(cursor_x, cursor_y);
}

void widget::set_line_constraint(bool line_constraint)
{
	int status = parent_frame->set_line_constraint(widget_id, line_constraint);
	log.log_status(status, "widget::set_line_constraint");
}

void widget::set_column_constraint(bool column_constraint)
{
	int status = parent_frame->set_column_constraint(widget_id, column_constraint);
	log.log_status(status, "widget::set_column_constraint");
}

void widget::set_displayed_lines(unsigned int displayed_lines)
{
	int status = parent_frame->set_displayed_lines(widget_id, displayed_lines);
	log.log_status(status, "widget::set_displayed_lines");
}

void widget::set_line_subtraction_from_terminal_height(unsigned int line_subtraction_from_terminal_height)
{
	int status = parent_frame->set_line_subtraction_from_terminal_height(widget_id, line_subtraction_from_terminal_height);
	log.log_status(status, "widget::set_line_subtraction_from_terminal_height");
}

void widget::set_line_compression_amount(unsigned int line_compression_amount)
{
	int status = parent_frame->set_line_compression_amount(widget_id, line_compression_amount);
	log.log_status(status, "widget::set_line_compression_amount");
}

void widget::set_top_line(unsigned int top_line)
{
	int status = parent_frame->set_top_line(widget_id, top_line);
	log.log_status(status, "widget::set_top_line");
}

void widget::set_left_column(unsigned int left_column)
{
	int status = parent_frame->set_left_column(widget_id, left_column);
	log.log_status(status, "widget::set_left_column");
}

void widget::get_displayed_output(std::vector<std::string>& displayed_output)
{
	int status = parent_frame->get_displayed_output(widget_id, displayed_output);
	log.log_status(status, "widget::get_displayed_output");
}

void widget::get_displayed_output(std::vector<std::string>& displayed_output, std::vector<format_tools::index_format>& colors)
{
	int status = parent_frame->get_displayed_output(widget_id, displayed_output);
	log.log_status(status, "widget::get_displayed_output");
	status = parent_frame->get_displayed_colors(widget_id, colors);
	log.log_status(status, "widget::get_displayed_output");
}

bool widget::get_line_constraint()
{
	bool line_constraint = false;
	int status = parent_frame->get_line_constraint(widget_id, line_constraint);
	log.log_status(status, "widget::get_line_constraint");
	return line_constraint;
}

bool widget::get_column_constraint()
{
	bool column_constraint = false;
	int status = parent_frame->get_column_constraint(widget_id, column_constraint);
	log.log_status(status, "widget::get_column_constraint");
	return column_constraint;
}

unsigned int widget::get_displayed_lines()
{
	unsigned int displayed_lines = 0;
	int status = parent_frame->get_displayed_lines(widget_id, displayed_lines);
	log.log_status(status, "widget::get_displayed_lines");
	return displayed_lines;
}

unsigned int widget::get_line_subtraction_from_terminal_height()
{
	unsigned int line_subtraction_from_terminal_height = 0;
	int status = parent_frame->get_line_subtraction_from_terminal_height(widget_id, line_subtraction_from_terminal_height);
	log.log_status(status, "widget::get_line_subtraction_from_terminal_height");
	return line_subtraction_from_terminal_height;
}

unsigned int widget::get_line_compression_amount()
{
	unsigned int line_compression_amount = 0;
	int status = parent_frame->get_line_compression_amount(widget_id, line_compression_amount);
	log.log_status(status, "widget::get_line_compression_amount");
	return line_compression_amount;
}

unsigned int widget::get_top_line()
{
	unsigned int top_line = 0;
	int status = parent_frame->get_top_line(widget_id, top_line);
	log.log_status(status, "widget::get_top_line");
	return top_line;
}

unsigned int widget::get_left_column()
{
	unsigned int left_column = 0;
	int status = parent_frame->get_left_column(widget_id, left_column);
	log.log_status(status, "widget::get_left_column");
	return left_column;
}

unsigned int widget::get_lines_count(bool only_displayed)
{
	unsigned int lines_count = 0;
	int status = parent_frame->get_lines_count(widget_id, lines_count, only_displayed);
	log.log_status(status, "widget::get_lines_count");
	return lines_count;
}

unsigned int widget::get_columns_count()
{
	unsigned int columns_count = 0;
	int status = parent_frame->get_columns_count(widget_id, columns_count);
	log.log_status(status, "widget::get_columns_count");
	return columns_count;
}

void widget::set_line_character(char character, unsigned int line, unsigned int character_index)
{
	int status = parent_frame->set_line_character(widget_id, character, line, character_index);
	log.log_status(status, "widget::set_line_character");
}

void widget::update_lines()
{
	frame::widget_info* item = parent_frame->get_widget(widget_id);
	if (item != nullptr)
	{
		parent_frame->build_core_widget_lines(item);
		log.log_status(SUCCESS, "widget::update_lines");
	}
	else
	{
		log.log_status(ELEMENT_NOT_FOUND, "widget::update_lines");
	}
}

unsigned int widget::get_line_length(unsigned int line)
{
	unsigned int length = 0;
	int status = parent_frame->get_line_length(widget_id, line, length);
	log.log_status(status, "widget::get_line_length");
	return length;
}

void widget::insert_character_in_output(unsigned int index, char character)
{
	int status = parent_frame->insert_character_in_output(widget_id, index, character);
	log.log_status(status, "widget::insert_line_in_output");
}

void widget::erase_character_in_output(unsigned int index)
{
	int status = parent_frame->erase_character_in_output(widget_id, index);
	log.log_status(status, "widget::erase_character_in_output");
}

unsigned int widget::get_output_length()
{
	unsigned int length = 0;
	int status = parent_frame->get_output_length(widget_id, length);
	log.log_status(status, "widget::get_output_length");
	return length;
}

void widget::dynamically_adjust_displayed_lines()
{
	frame::widget_info* item = parent_frame->get_widget(widget_id);
	if (item != nullptr)
	{
		parent_frame->dynamically_adjust_displayed_lines(item);
	}
}

void widget::bound_top_line()
{
	frame::widget_info* item = parent_frame->get_widget(widget_id);
	if (item != nullptr)
	{
		parent_frame->bound_top_line(item);
	}
}

#ifdef __linux__
void widget::dec_print(const std::string& input)
{
	parent_frame->dec_print(input);
}
#endif