#include "../ascii_engine_dll_files/pch.h"
#include "widget.h"
#include "error_codes.h"

#ifdef __linux__
#include <algorithm>
#endif

widget::widget(frame* parent, std::string special_operation)
{
	parent_frame = parent;
	parent_frame->add_widget(&item);
	int status = parent_frame->append(item.id, special_operation);
	log.log_status(status, "widget::widget");
}

void widget::set_alignment(std::string alignment)
{
	int status = UNDEFINED;
	if ((alignment != format_tools::right_alignment_keyword) && (alignment != format_tools::left_alignment_keyword) && (alignment != format_tools::center_alignment_keyword) && (alignment != format_tools::center_block_alignment_keyword))
	{
		status = INVALID_VALUE;
	}
	else if (item.widget_type == TEXTBOX)
	{
		status = OPERATION_NOT_SUPPORTED;
	}
	else
	{
		item.alignment = alignment;
		parent_frame->display_stale = true;
		status = SUCCESS;
	}

	log.log_status(status, "widget::set_alignment");
}

void widget::set_output_to_frame(const std::string& text, bool mark_stale)
{
	item.output = text;
	parent_frame->display_stale = mark_stale;
	item.line_edited = false;
}

void widget::set_spacing(int top, int bottom, int left, int right)
{
	int status = UNDEFINED;
	if ((top < 0) || (bottom < 0) || (right < 0) || (left < 0))
	{
		status = INVALID_VALUE;
	}
	else
	{
		item.top_spacing = top;
		item.bottom_spacing = bottom;
		item.right_spacing = right;
		item.left_spacing = left;
		if (item.top_border_spacing > top)
		{
			item.top_border_spacing = top;
		}

		if (item.bottom_border_spacing > bottom)
		{
			item.bottom_border_spacing = bottom;
		}

		if (item.left_border_spacing > left)
		{
			item.left_border_spacing = left;
		}

		if (item.right_border_spacing > right)
		{
			item.right_border_spacing = right;
		}

		parent_frame->display_stale = true;
		status = SUCCESS;
	}

	log.log_status(status, "widget::set_spacing");
}

void widget::set_border_spacing(int top, int bottom, int right, int left)
{
	int status = UNDEFINED;
	if ((top < 0) || (bottom < 0) || (right < 0) || (left < 0))
	{
		status = INVALID_VALUE;
	}
	else if ((item.top_spacing >= top) && (item.bottom_spacing >= bottom) && (item.right_spacing >= right) && (item.left_spacing >= left))
	{
		item.top_border_spacing = top;
		item.bottom_border_spacing = bottom;
		item.right_border_spacing = right;
		item.left_border_spacing = left;
		parent_frame->display_stale = true;
		status = SUCCESS;
	}
	else
	{
		status = INVALID_VALUE;
	}

	log.log_status(status, "widget::set_border_spacing");
}

void widget::set_widget_type(int type)
{
	item.widget_type = type;
}

void widget::set_vertical_border(char border)
{
	int status = UNDEFINED;
	if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), border) != 0)
	{
		status = INVALID_VALUE;
	}
	else
	{
		item.vertical_border = border;
		parent_frame->display_stale = true;
		status = SUCCESS;
	}

	log.log_status(status, "widget::set_vertical_border");
}

void widget::set_horizontal_border(char border)
{
	int status = UNDEFINED;
	if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), border) != 0)
	{
		status = INVALID_VALUE;
	}
	else
	{
		item.horizontal_border = border;
		parent_frame->display_stale = true;
		status = SUCCESS;
	}

	log.log_status(status, "widget::set_horizontal_border");
}

void widget::set_corner_border(char border)
{
	int status = UNDEFINED;
	if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), border) != 0)
	{
		status = INVALID_VALUE;
	}
	else
	{
		item.corner_border = border;
		parent_frame->display_stale = true;
		status = SUCCESS;
	}

	log.log_status(status, "widget::set_corner_border");
}

void widget::set_highlight_character(char character)
{
	int status = UNDEFINED;
	if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), character) != 0)
	{
		status = INVALID_VALUE;
	}
	else
	{
		item.highlight_character = character;
		status = SUCCESS;
	}

	log.log_status(status, "widget::set_highlight_character");
}

void widget::set_width_multiplier(float multiplier)
{
	int status = UNDEFINED;
	if (multiplier <= 0)
	{
		status = INVALID_VALUE;
	}
	else
	{
		item.width_multiplier = multiplier;
		parent_frame->display_stale = true;
		status = SUCCESS;
	}

	log.log_status(status, "widget::set_width_multiplier");
}

void widget::set_spacing_width_multipliers(float left_multiplier, float right_multiplier)
{
	int status = UNDEFINED;
	if ((left_multiplier < 0) || (right_multiplier < 0))
	{
		status = INVALID_VALUE;
	}
	else
	{
		item.left_width_multiplier = left_multiplier;
		item.right_width_multiplier = right_multiplier;
		if (item.left_border_width_multiplier > left_multiplier)
		{
			item.left_border_width_multiplier = left_multiplier;
		}

		if (item.right_border_width_multiplier > right_multiplier)
		{
			item.right_border_width_multiplier = right_multiplier;
		}
		parent_frame->display_stale = true;
		status = SUCCESS;
	}

	log.log_status(status, "widget::set_spacing_width_multipliers");
}

void widget::set_border_spacing_width_multipliers(float left_multiplier, float right_multiplier)
{
	int status = UNDEFINED;
	if ((left_multiplier < 0) || (right_multiplier < 0))
	{
		status = INVALID_VALUE;
	}
	else if ((item.right_width_multiplier >= right_multiplier) && (item.left_width_multiplier >= left_multiplier))
	{
		item.left_border_width_multiplier = left_multiplier;
		item.right_border_width_multiplier = right_multiplier;
		parent_frame->display_stale = true;
		status = SUCCESS;
	}
	else
	{
		status = INVALID_VALUE;
	}

	log.log_status(status, "widget::set_border_spacing_width_multipliers");
}

void widget::set_title(const std::string& title)
{
	int status = SUCCESS;
	for (unsigned int i = 0; i < title.size(); i++)
	{
		if (title[i] == '\n')
		{
			status = INVALID_VALUE;
			break;
		}
	}

	if (status == SUCCESS)
	{
		item.title = title;
	}

	log.log_status(status, "widget::set_title");
}

void widget::add_border(bool border)
{
	item.add_border = border;
	parent_frame->display_stale = true;
}

void widget::use_spacing_width_multipliers(bool use)
{
	item.use_spacing_width_multipliers = use;
	parent_frame->display_stale = true;
}

void widget::display_entire_frame()
{
	parent_frame->display();
}

void widget::set_selectable(bool selectable)
{
	item.selectable = selectable;
}

bool widget::is_selectable()
{
	return item.selectable;
}

void widget::get_spacing(int& top, int& bottom, int& left, int& right)
{
	top = item.top_spacing;
	bottom = item.bottom_spacing;
	left = item.left_spacing;
	right = item.right_spacing;
}

void widget::get_border_spacing(int& top, int& bottom, int& left, int& right)
{
	top = item.top_border_spacing;
	bottom = item.bottom_border_spacing;
	left = item.left_border_spacing;
	right = item.right_border_spacing;
}

char widget::get_vertical_border()
{
	return item.vertical_border;
}

char widget::get_horizontal_border()
{
	return item.horizontal_border;
}

char widget::get_corner_border()
{
	return item.corner_border;
}

char widget::get_highlight_character()
{
	return item.highlight_character;
}

float widget::get_width_multiplier()
{
	return item.width_multiplier;
}

void widget::get_spacing_width_multipliers(float& left_multiplier, float& right_multiplier)
{
	left_multiplier = item.left_width_multiplier;
	right_multiplier = item.right_width_multiplier;
}

void widget::get_border_spacing_width_multipliers(float& left_multiplier, float& right_multiplier)
{
	left_multiplier = item.left_border_width_multiplier;
	right_multiplier = item.right_border_width_multiplier;
}

std::string widget::get_title()
{
	return item.title;
}

unsigned int widget::get_width(bool include_spacing)
{
	return parent_frame->get_widget_width(item.id, include_spacing);
}

unsigned int widget::get_height(bool include_spacing)
{
	return parent_frame->get_widget_height(item.id, include_spacing);
}

int widget::get_x_origin()
{
	int status = UNDEFINED;
	int x_origin = 0;
	if (item.x_origin != -1)
	{
		x_origin = item.x_origin;
		status = SUCCESS;
	}

	log.log_status(status, "widget::get_x_origin");
	return x_origin;
}

int widget::get_y_origin()
{
	int status = UNDEFINED;
	int y_origin = 0;
	if (item.y_origin != -1)
	{
		y_origin = item.y_origin;
		status = SUCCESS;
	}

	log.log_status(status, "widget::get_y_origin");
	return y_origin;
}

int widget::get_widget_type()
{
	return item.widget_type;
}

std::string widget::get_output()
{
	return item.output;
}

std::string widget::get_displayed_output()
{
	std::string output = "";
	std::vector<std::string> output_lines = parent_frame->get_displayed_output(item.id);
	output_lines = format_tools::add_newline_characters(output_lines);
	if (output_lines.size() > 0 && output_lines[output_lines.size() - 1].length() > 0)
	{
		output_lines[output_lines.size() - 1].erase(output_lines[output_lines.size() - 1].length() - 1, 1);
	}
	output = format_tools::get_string(output_lines);
	return output;
}

std::string widget::get_alignment()
{
	return item.alignment;
}

bool widget::frame_stale()
{
	return parent_frame->stale();
}

void widget::mark_frame_as_stale()
{
	parent_frame->display_stale = true;
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
	item.index_colors = index_colors;
}

std::vector<format_tools::index_format> widget::get_index_colors()
{
	return item.index_colors;
}

std::vector<format_tools::index_format> widget::get_displayed_index_colors()
{
	return parent_frame->get_displayed_colors(item.id);
}

std::vector<format_tools::index_format> widget::dec_format(std::string& format_content, unsigned int line_length)
{
	return parent_frame->dec_format(format_content, line_length);
}

int widget::start_logging(const std::string& file_path)
{
	int status = log.start_widget_logging(file_path, item.widget_type);
	return status;
}

void widget::stop_logging()
{
	log.stop_widget_logging();
}

int widget::reset_logging(const std::string& file_path)
{
	int status = log.log_reset(file_path, item.widget_type);
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
		parent_frame->display();
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
			int foreground_color = parent_frame->get_default_foreground_color();
			int background_color = parent_frame->get_default_background_color();
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
		ascii_io::set_color(parent_frame->get_default_foreground_color(), parent_frame->get_default_background_color());
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
	item.line_constraint = line_constraint;
	parent_frame->display_stale = true;
}

void widget::set_column_constraint(bool column_constraint)
{
	item.column_constraint = column_constraint;
	parent_frame->display_stale = true;
}

void widget::set_displayed_lines_count(unsigned int displayed_lines_count)
{
	item.displayed_lines_count = displayed_lines_count;
}

void widget::set_line_subtraction_from_terminal_height(unsigned int line_subtraction_from_terminal_height)
{
	item.line_subtraction_from_terminal_height = line_subtraction_from_terminal_height;
}

void widget::set_line_compression_amount(unsigned int line_compression_amount)
{
	item.line_compression_amount = line_compression_amount;
}

void widget::set_top_line(unsigned int top_line)
{
	item.top_line = top_line;
}

void widget::set_left_column(unsigned int left_column)
{
	item.left_column = left_column;
}

void widget::get_displayed_output(std::vector<std::string>& displayed_output)
{
	displayed_output = parent_frame->get_displayed_output(item.id);
}

void widget::get_displayed_output(std::vector<std::string>& displayed_output, std::vector<format_tools::index_format>& colors)
{
	displayed_output = parent_frame->get_displayed_output(item.id);
	colors = parent_frame->get_displayed_colors(item.id);
}

bool widget::get_line_constraint()
{
	return item.line_constraint;
}

bool widget::get_column_constraint()
{
	return item.column_constraint;
}

unsigned int widget::get_total_lines_count()
{
	return item.lines.size();
}

unsigned int widget::get_displayed_lines_count()
{
	return item.displayed_lines_count;
}

unsigned int widget::get_line_subtraction_from_terminal_height()
{
	return item.line_subtraction_from_terminal_height;
}

unsigned int widget::get_line_compression_amount()
{
	return item.line_compression_amount;
}

unsigned int widget::get_top_line()
{
	return item.top_line;
}

unsigned int widget::get_left_column()
{
	return item.left_column;
}

unsigned int widget::get_total_columns_count()
{
	unsigned int total_columns_count = 0;
	for (unsigned int i = 0; i < item.lines.size(); i++)
	{
		unsigned int line_length = item.lines[i].length();
		if (line_length > total_columns_count)
		{
			total_columns_count = line_length;
		}
	}

	return total_columns_count;
}

unsigned int widget::get_displayed_columns_count()
{
	return get_width();
}

void widget::set_line_character(char character, unsigned int line, unsigned int character_index)
{
	int status = UNDEFINED;
	if (line < item.lines.size())
	{
		if (character_index < item.lines[line].length())
		{
			(item.lines[line])[character_index] = character;
			item.line_edited = true;
			status = SUCCESS;
		}
		else
		{
			status = INVALID_INDEX;
		}
	}
	else
	{
		status = INVALID_INDEX;
	}

	log.log_status(status, "widget::set_line_character");
}

void widget::update_lines()
{
	parent_frame->build_core_widget_lines(&item);
}

unsigned int widget::get_line_length(unsigned int line)
{
	int status = UNDEFINED;
	unsigned int length = 0;
	if (item.lines.size() > line)
	{
		length = item.lines[line].length();
		status = SUCCESS;
	}
	else
	{
		status = INVALID_INDEX;
	}

	log.log_status(status, "widget::get_line_length");
	return length;
}

void widget::insert_character_in_output(unsigned int index, char character)
{
	int status = UNDEFINED;
	if (item.output.length() >= index)
	{
		item.output.insert(index, std::string(1, character));
		status = SUCCESS;
	}
	else
	{
		status = INVALID_INDEX;
	}

	log.log_status(status, "widget::insert_character_in_output");
}

void widget::erase_character_in_output(unsigned int index)
{
	int status = UNDEFINED;
	if (item.output.length() > index)
	{
		item.output.erase(item.output.begin() + index);
		status = SUCCESS;
	}
	else
	{
		status = INVALID_INDEX;
	}

	log.log_status(status, "widget::erase_character_in_output");
}

unsigned int widget::get_output_length()
{
	return item.output.length();
}

void widget::dynamically_adjust_displayed_lines()
{
	parent_frame->dynamically_adjust_displayed_lines(&item);
}

void widget::bound_top_line()
{
		parent_frame->bound_top_line(&item);
}

#ifdef __linux__
void widget::dec_print(const std::string& input)
{
	parent_frame->dec_print(input);
}
#endif