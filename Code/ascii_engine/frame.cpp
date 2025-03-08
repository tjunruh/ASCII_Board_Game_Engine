#include "../ascii_engine_dll_files/pch.h"
#include "frame.h"
#include "error_codes.h"
#include <cmath>

#ifdef __linux__
#include <algorithm>
#endif

frame::frame(bool start_logger, const std::string& logging_file_path)
{
	if (start_logger)
	{
		int logger_status = log.start_widget_logging(logging_file_path, FRAME);
		if (logger_status != 0)
		{
			ascii_io::clear();
			ascii_io::print("frame initialization: Invalid logger path.\nPress any button to continue.");
			ascii_io::getchar();
		}
	}

	ascii_io::get_terminal_size(terminal_x, terminal_y);
}

void frame::display()
{
	std::string output = generate_frame_output();
#ifdef WIN32
	if ((terminal_x != previous_x) || (terminal_y != previous_y))
	{
		ascii_io::clear();
	}
	else
	{
		std::vector<format_tools::index_format> index_regions;
		std::vector<int> ignore_flags;
		ascii_io::move_cursor_to_position(0, 0);
		unsigned int width = 0;
		if (_color_enabled)
		{
			index_regions = format_tools::convert(color_regions, format_tools::get_first_line_length(output));
			ignore_flags = format_tools::set_flags(index_regions, output, '*');
		}
		format_tools::mask_string(output, previous_output);
		if (_color_enabled)
		{
			std::vector<std::string> lines = format_tools::get_lines(output);
			convert_flags(color_regions, index_regions, ignore_flags, lines, '*');
			output = format_tools::get_string(lines);
		}
	}
	previous_output = output;
#elif __linux__
	ascii_io::clear();
#endif
	if (_dec_enabled || _color_enabled)
	{
		std::vector<format_tools::index_format> index_regions;
		if (_color_enabled)
		{
			index_regions = format_tools::convert(color_regions, format_tools::get_first_line_length(output));
		}

		if (_dec_enabled)
		{
			std::vector<format_tools::index_format> dec_regions = dec.format(output);
			if (index_regions.size() > 0)
			{
				index_regions = format_tools::combine(index_regions, dec_regions);
			}
			else
			{
				index_regions = dec_regions;
			}
		}

		std::vector<format_tools::content_format> regions = format_tools::convert(index_regions, output);
		for (unsigned int i = 0; i < regions.size(); i++)
		{
			int foreground_color = default_foreground_color;
			int background_color = default_background_color;
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
				dec.print_dec_string(regions[i].content);
#endif
			}
			else
			{
#ifdef _WIN32
				ascii_io::disable_dec();
#endif
				ascii_io::print(regions[i].content);
			}
		}
#ifdef _WIN32
		ascii_io::disable_dec();
#endif
	}
	else
	{
		ascii_io::print(output);
	}

	previous_x = terminal_x;
	previous_y = terminal_y;
	display_stale = false;
}

bool frame::stale()
{
	if (!display_stale)
	{
		int x = 0;
		int y = 0;
		ascii_io::get_terminal_size(x, y);
		if ((x != previous_x) || (y != previous_y))
		{
			display_stale = true;
		}
	}
	return display_stale;
}

void frame::set_controls(int select, int quit, int up, int down, int left, int right)
{
	_select = select;
	_quit = quit;
	_up = up;
	_down = down;
	_right = right;
	_left = left;
}

void frame::get_controls(int& select, int& quit, int& up, int& down, int& left, int& right)
{
	select = _select;
	quit = _quit;
	up = _up;
	down = _down;
	left = _left;
	right = _right;
}

int frame::get_selection()
{
	int input = 0;
	int selected_row = 0;
	int last_selected_row = 0;
	int selected_column = 0;
	int last_selected_column = 0;
	int selected_level = 0;
	int last_selected_level = 0;
	int selected_id = -1;
	log.log_begin("frame::get_selection");
	if (!initialize_selection(selected_row, selected_column, selected_level))
	{
		log.log_comment("No selectable widget found.");
		return -1;
	}

	log.log_comment("Start row: " + std::to_string(selected_row) + " Start column: " + std::to_string(selected_column) + " Start level: " + std::to_string(selected_level));

	do
	{
		if (stale())
		{
			display();
		}
		unhighlight(last_selected_row, last_selected_column, last_selected_level);
		highlight(selected_row, selected_column, selected_level);
		last_selected_row = selected_row;
		last_selected_column = selected_column;
		last_selected_level = selected_level;
		input = ascii_io::getchar();
		if (input == _select)
		{
			log.log_comment("select action");
			widget_info item;
			get_widget(selected_row, selected_column, selected_level, item);
			if (item.selectable)
			{
				selected_id = item.id;
				log.log_comment("Selected row: " + std::to_string(selected_row) + " Selected column: " + std::to_string(selected_column) + " Selected level: " + std::to_string(selected_level));
				log.log_comment("Selected ID: " + std::to_string(item.id));
				break;
			}
		}
		else if (input == _up)
		{
			log.log_comment("up action");
			up_handle(selected_row, selected_column, selected_level);
		}
		else if (input == _down)
		{
			log.log_comment("down action");
			down_handle(selected_row, selected_column, selected_level);
		}
		else if (input == _right)
		{
			log.log_comment("right action");
			right_handle(selected_row, selected_column, selected_level);
		}
		else if (input == _left)
		{
			log.log_comment("left action");
			left_handle(selected_row, selected_column, selected_level);
		}
		log.log_comment("Current row: " + std::to_string(selected_row) + " Current column: " + std::to_string(selected_column) + " Current level: " + std::to_string(selected_level));
	} while (input != _quit);

	log.log_end("frame::get_selection");
	return selected_id;
}

void frame::set_spacer_character(char character)
{
	if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), character) != 0)
	{
		log.log_status(INVALID_VALUE, "frame::set_spacer_character");
		return;
	}

	spacer_character = character;
	log.log_status(SUCCESS, "frame::set_spacer_character");
}

char frame::get_spacer_character()
{
	return spacer_character;
}

void frame::enable_dec(bool enable)
{
	_dec_enabled = enable;
}

bool frame::dec_enabled()
{
	return _dec_enabled;
}

void frame::enable_color(bool enable)
{
	_color_enabled = enable;
}

bool frame::color_enabled()
{
	return _color_enabled;
}

void frame::set_dec_format_characters(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char)
{
	if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), horizontal_char) != 0)
	{
		log.log_status(INVALID_VALUE, "frame::set_dec_format_characters");
	}
	else if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), vertical_char) != 0)
	{
		log.log_status(INVALID_VALUE, "frame::set_dec_format_characters");
	}
	else if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), intersection_char) != 0)
	{
		log.log_status(INVALID_VALUE, "frame::set_dec_format_characters");
	}
	else if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), endpoint_char) != 0)
	{
		log.log_status(INVALID_VALUE, "frame::set_dec_format_characters");
	}
	else
	{
		dec.set_format_chars(horizontal_char, vertical_char, intersection_char, endpoint_char);
		log.log_status(SUCCESS, "frame::set_dec_format_characters");
	}
}

void frame::get_dec_format_characters(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char)
{
	dec.get_format_chars(horizontal_char, vertical_char, intersection_char, endpoint_char);
}

void frame::set_default_background_color(int color)
{
	if (std::count(format_tools::colors.begin(), format_tools::colors.end(), color) == 0)
	{
		log.log_status(INVALID_VALUE, "frame::set_default_background_color");
	}
	else
	{
		default_background_color = color;
		log.log_status(SUCCESS, "frame::set_default_background_color");
	}
}

void frame::set_default_foreground_color(int color)
{
	if (std::count(format_tools::colors.begin(), format_tools::colors.end(), color) == 0)
	{
		log.log_status(INVALID_VALUE, "frame::set_default_foreground_color");
	}
	else
	{
		default_foreground_color = color;
		log.log_status(SUCCESS, "frame::set_default_foreground_color");
	}
}

int frame::get_default_background_color()
{
	return default_background_color;
}

int frame::get_default_foreground_color()
{
	return default_foreground_color;
}

void frame::use_fake_console_dimensions()
{
	_use_fake_console_dimensions = true;
}

void frame::use_true_console_dimensions()
{
	_use_fake_console_dimensions = false;
}

void frame::set_fake_console_width(int width)
{
	if (width >= 0)
	{
		_fake_console_width = width;
	}
	else
	{
		log.log_status(INVALID_VALUE, "frame::set_fake_console_width");
	}
}

void frame::set_fake_console_height(int height)
{
	if (height >= 0)
	{
		_fake_console_height = height;
	}
	else
	{
		log.log_status(INVALID_VALUE, "frame::set_fake_console_height");
	}
}

std::string frame::get_frame_output()
{
	return generate_frame_output();
}

int frame::start_logging(const std::string& file_path)
{
	int status = log.start_widget_logging(file_path, FRAME);
	return status;
}

void frame::stop_logging()
{
	log.stop_widget_logging();
}

int frame::reset_logging(const std::string& file_path)
{
	int status = log.log_reset(file_path, FRAME);
	return status;
}

int frame::add_widget()
{
	int id = generate_widget_id();
	widget_info new_widget;
	new_widget.id = id;
	widgets.push_back(new_widget);
	return id;
}

int frame::append(int id, const std::string& special_operation)
{
	if (special_operation == special_operation_new_line)
	{
		append_row++;
		append_column = 0;
		append_level = 0;
	}
	else if (special_operation == special_operation_none)
	{
		append_column++;
		append_level = 0;
	}
	else if (special_operation != special_operation_merge)
	{
		throw std::string("Unrecognized operation");
	}

	if (append_column < 0)
	{
		append_column = 0;
	}

	int status = set_position(id, append_row, append_column, append_level);
	append_level++;
	return status;
}

int frame::set_position(int id, int row, int column, int level)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].row = row;
			widgets[i].column = column;
			widgets[i].level = level;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_output(int id, const std::string& output)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].output = output;
			display_stale = true;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_alignment(int id, const std::string& alignment)
{
	if ((alignment != format_tools::right_alignment_keyword) && (alignment != format_tools::left_alignment_keyword) && (alignment != format_tools::center_alignment_keyword) && (alignment != format_tools::center_block_alignment_keyword))
	{
		return INVALID_VALUE;
	}

	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			if (widgets[i].widget_type == TEXTBOX)
			{
				status = OPERATION_NOT_SUPPORTED;
			}
			else
			{
				widgets[i].alignment = alignment;
				display_stale = true;
				status = SUCCESS;
			}
			break;
		}
	}
	return status;
}

int frame::set_spacing(int id, int top, int bottom, int left, int right)
{
	if ((top < 0) || (bottom < 0) || (right < 0) || (left < 0))
	{
		return INVALID_VALUE;
	}

	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].top_spacing = top;
			widgets[i].bottom_spacing = bottom;
			widgets[i].right_spacing = right;
			widgets[i].left_spacing = left;
			if (widgets[i].top_border_spacing > top)
			{
				widgets[i].top_border_spacing = top;
			}

			if (widgets[i].bottom_border_spacing > bottom)
			{
				widgets[i].bottom_border_spacing = bottom;
			}

			if (widgets[i].left_border_spacing > left)
			{
				widgets[i].left_border_spacing = left;
			}

			if (widgets[i].right_border_spacing > right)
			{
				widgets[i].right_border_spacing = right;
			}
			display_stale = true;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_border_spacing(int id, int top, int bottom, int right, int left)
{
	if ((top < 0) || (bottom < 0) || (right < 0) || (left < 0))
	{
		return INVALID_VALUE;
	}

	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			if ((widgets[i].top_spacing >= top) && (widgets[i].bottom_spacing >= bottom) && (widgets[i].right_spacing >= right) && (widgets[i].left_spacing >= left))
			{
				widgets[i].top_border_spacing = top;
				widgets[i].bottom_border_spacing = bottom;
				widgets[i].right_border_spacing = right;
				widgets[i].left_border_spacing = left;
				display_stale = true;
				status = SUCCESS;
			}
			else
			{
				status = INVALID_VALUE;
			}
			break;
		}
	}
	return status;
}

int frame::set_widget_type(int id, int type)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].widget_type = type;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_vertical_border(int id, char border)
{
	if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), border) != 0)
	{
		return INVALID_VALUE;
	}

	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].vertical_border = border;
			display_stale = true;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_horizontal_border(int id, char border)
{
	if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), border) != 0)
	{
		return INVALID_VALUE;
	}

	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].horizontal_border = border;
			display_stale = true;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_corner_border(int id, char border)
{
	if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), border) != 0)
	{
		return INVALID_VALUE;
	}

	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].corner_border = border;
			display_stale = true;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_highlight_character(int id, char character)
{
	if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), character) != 0)
	{
		return INVALID_VALUE;
	}

	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].highlight_character = character;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_x_origin(int id, int x_origin)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].x_origin = x_origin;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_y_origin(int id, int y_origin)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].y_origin = y_origin;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::add_border(int id, bool border)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].add_border = border;
			display_stale = true;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::use_spacing_width_multipliers(int id, bool use)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].use_spacing_width_multipliers = use;
			display_stale = true;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

void frame::highlight(int row, int column, int level)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column) && (widgets[i].level == level))
		{
			int x_origin = 0;
			int y_origin = 0;
			get_x_origin(widgets[i].id, x_origin);
			get_y_origin(widgets[i].id, y_origin);
			unsigned int width = get_widget_width(widgets[i], false);
			unsigned int height = get_widget_height(widgets[i], false);
			
			int x = x_origin - 2 - widgets[i].left_border_spacing;
			int y = y_origin - 1 - widgets[i].top_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			ascii_io::print(std::string(1, widgets[i].highlight_character));

			x = x_origin + (int)width + 1 + widgets[i].right_border_spacing;
			y = y_origin - 1 - widgets[i].top_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			ascii_io::print(std::string(1, widgets[i].highlight_character));

			x = x_origin - 2 - widgets[i].left_border_spacing;
			y = y_origin + (int)height  + widgets[i].bottom_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			ascii_io::print(std::string(1, widgets[i].highlight_character));

			x = x_origin + (int)width + 1 + widgets[i].left_border_spacing;
			y = y_origin + (int)height + widgets[i].bottom_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			ascii_io::print(std::string(1, widgets[i].highlight_character));
			status = SUCCESS;
			break;
		}
	}
	log.log_status(status, "frame::highlight");
}

void frame::unhighlight(int row, int column, int level)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column) && (widgets[i].level == level))
		{
			char corner_character = ' ';
			if (widgets[i].add_border)
			{
				corner_character = widgets[i].corner_border;
			}
			int x_origin = 0;
			int y_origin = 0;
			get_x_origin(widgets[i].id, x_origin);
			get_y_origin(widgets[i].id, y_origin);
			unsigned int width = get_widget_width(widgets[i], false);
			unsigned int height = get_widget_height(widgets[i], false);

			int x = x_origin - 2 - widgets[i].left_border_spacing;
			int y = y_origin - 1 - widgets[i].top_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			if (_dec_enabled && widgets[i].add_border && (widgets[i].corner_border == dec.get_endpoint_char()))
			{
#ifdef _WIN32
				ascii_io::enable_dec();
				ascii_io::print(std::string(1, dec.top_left_corner));
#elif __linux__
				dec.print_dec_string(std::string(1, dec.top_left_corner));
#endif
			}
			else
			{
				ascii_io::print(std::string(1, corner_character));
			}

			x = x_origin + (int)width + 1 + widgets[i].right_border_spacing;
			y = y_origin - 1 - widgets[i].top_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			if (_dec_enabled && widgets[i].add_border && (widgets[i].corner_border == dec.get_endpoint_char()))
			{
#ifdef _WIN32
				ascii_io::print(std::string(1, dec.top_right_corner));
#elif __linux__
				dec.print_dec_string(std::string(1, dec.top_right_corner));
#endif
			}
			else
			{
				ascii_io::print(std::string(1, corner_character));
			}

			x = x_origin - 2 - widgets[i].left_border_spacing;
			y = y_origin + (int)height  + widgets[i].bottom_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			if (_dec_enabled && widgets[i].add_border && (widgets[i].corner_border == dec.get_endpoint_char()))
			{
#ifdef _WIN32
				ascii_io::print(std::string(1, dec.bottom_left_corner));
#elif __linux__
				dec.print_dec_string(std::string(1, dec.bottom_left_corner));
#endif
			}
			else
			{
				ascii_io::print(std::string(1, corner_character));
			}

			x = x_origin + (int)width + 1 + widgets[i].left_border_spacing;
			y = y_origin + (int)height + widgets[i].bottom_border_spacing;
			keep_point_in_console_bounds(x, y);
			ascii_io::move_cursor_to_position(x, y);
			if (_dec_enabled && widgets[i].add_border && (widgets[i].corner_border == dec.get_endpoint_char()))
			{
#ifdef _WIN32
				ascii_io::print(std::string(1, dec.bottom_right_corner));
#elif __linux__
				dec.print_dec_string(std::string(1, dec.bottom_right_corner));
#endif
			}
			else
			{
				ascii_io::print(std::string(1, corner_character));
			}
#ifdef _WIN32
			if (_dec_enabled)
			{
				ascii_io::disable_dec();
			}
#endif
			status = SUCCESS;
			break;
		}
	}
	log.log_status(status, "frame::unhighlight");
}

void frame::keep_point_in_console_bounds(int& x, int& y)
{
	if (x < 0)
	{
		x = 0;
	}
	else if (x >= terminal_x)
	{
		x = terminal_x - 1;
	}

	if (y < 0)
	{
		y = 0;
	}
	else if (y >= terminal_y)
	{
		y = terminal_y - 1;
	}
}

bool frame::widget_exists(int id)
{
	bool exists = false;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			exists = true;
			break;
		}
	}
	return exists;
}

bool frame::widget_exists(int row, int column)
{
	bool exists = false;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column))
		{
			exists = true;
			break;
		}
	}
	return exists;
}

int frame::get_levels(int row, int column)
{
	int count = 0;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column))
		{
			count++;
		}
	}
	return count;
}

int frame::get_lines_count(int id, unsigned int& lines_count, bool only_displayed)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			if (!widgets[i].line_constraint)
			{
				lines_count = widgets[i].lines_count;
			}
			else if (only_displayed)
			{
				lines_count = widgets[i].displayed_lines;
			}
			else
			{
				lines_count = widgets[i].lines.size();
			}

			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_x_origin(int id, int& x_origin)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			if (widgets[i].x_origin == -1)
			{
				status = UNDEFINED;
			}
			else
			{
				x_origin = widgets[i].x_origin;
				status = SUCCESS;
			}
			break;
		}
	}
	return status;
}

int frame::get_y_origin(int id, int& y_origin)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			if (widgets[i].y_origin == -1)
			{
				status = UNDEFINED;
			}
			else
			{
				y_origin = widgets[i].y_origin;
				status = SUCCESS;
			}
			break;
		}
	}
	return status;
}

int frame::get_alignment(int id, std::string& alignment)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			alignment = widgets[i].alignment;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_spacing(int id, int& top, int& bottom, int& left, int& right)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			top = widgets[i].top_spacing;
			bottom = widgets[i].bottom_spacing;
			left = widgets[i].left_spacing;
			right = widgets[i].right_spacing;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_border_spacing(int id, int& top, int& bottom, int& left, int& right)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			top = widgets[i].top_border_spacing;
			bottom = widgets[i].bottom_border_spacing;
			left = widgets[i].left_border_spacing;
			right = widgets[i].right_border_spacing;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_vertical_border(int id, char& border)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			border = widgets[i].vertical_border;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_horizontal_border(int id, char& border)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			border = widgets[i].horizontal_border;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_corner_border(int id, char& border)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			border = widgets[i].corner_border;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_width_multiplier(int id, float& multiplier)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			multiplier = widgets[i].width_multiplier;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_spacing_width_multipliers(int id, float& left_multiplier, float& right_multiplier)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			left_multiplier = widgets[i].left_width_multiplier;
			right_multiplier = widgets[i].right_width_multiplier;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_border_spacing_width_multipliers(int id, float& left_multiplier, float& right_multiplier)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			left_multiplier = widgets[i].left_border_width_multiplier;
			right_multiplier = widgets[i].right_border_width_multiplier;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_highlight_character(int id, char& highlight_character)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			highlight_character = widgets[i].highlight_character;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_selectability(int id, bool& selectable)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			selectable = widgets[i].selectable;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_top_line(int id, unsigned int& top_line)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			top_line = widgets[i].top_line;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_displayed_lines(int id, unsigned int& displayed_lines)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			displayed_lines = widgets[i].displayed_lines;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

float frame::get_greatest_width_multiplier_at_coordinate(int row, int column)
{
	float greatest_width_multiplier = 0.0;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column))
		{
			float multiplier = 0.0;
			if (widgets[i].use_spacing_width_multipliers)
			{
				multiplier = widgets[i].width_multiplier + widgets[i].right_width_multiplier + widgets[i].left_width_multiplier;
			}
			else
			{
				multiplier = widgets[i].width_multiplier;
			}

			if (multiplier > greatest_width_multiplier)
			{
				greatest_width_multiplier = multiplier;
			}
		}
	}
	return greatest_width_multiplier;
}

float frame::get_width_weight(const widget_info& item, float multiplier)
{
	float total_width_multiplier = 0.0;
	std::vector<int> columns_completed;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].row == item.row && (std::count(columns_completed.begin(), columns_completed.end(), widgets[i].column) == 0))
		{
			total_width_multiplier = total_width_multiplier + get_greatest_width_multiplier_at_coordinate(widgets[i].row, widgets[i].column);
			columns_completed.push_back(widgets[i].column);
		}
	}

	return (multiplier / total_width_multiplier);
}

int frame::get_index_colors(int id, std::vector<format_tools::index_format>& index_colors)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			index_colors = widgets[i].index_colors;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_line_constraint(int id, bool& line_constraint)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			line_constraint = widgets[i].line_constraint;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_lines_count(int id, unsigned int lines_count)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].lines_count = lines_count;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_width_multiplier(int id, float multiplier)
{
	if (multiplier <= 0)
	{
		return INVALID_VALUE;
	}

	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].width_multiplier = multiplier;
			display_stale = true;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_spacing_width_multipliers(int id, float left_multiplier, float right_multiplier)
{
	if ((left_multiplier < 0) || (right_multiplier < 0))
	{
		return INVALID_VALUE;
	}

	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].left_width_multiplier = left_multiplier;
			widgets[i].right_width_multiplier = right_multiplier;
			if (widgets[i].left_border_width_multiplier > left_multiplier)
			{
				widgets[i].left_border_width_multiplier = left_multiplier;
			}

			if (widgets[i].right_border_width_multiplier > right_multiplier)
			{
				widgets[i].right_border_width_multiplier = right_multiplier;
			}
			display_stale = true;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_border_spacing_width_multipliers(int id, float left_multiplier, float right_multiplier)
{
	if ((left_multiplier < 0) || (right_multiplier < 0))
	{
		return INVALID_VALUE;
	}

	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			if ((widgets[i].right_width_multiplier >= right_multiplier) && (widgets[i].left_width_multiplier >= left_multiplier))
			{
				widgets[i].left_border_width_multiplier = left_multiplier;
				widgets[i].right_border_width_multiplier = right_multiplier;
				display_stale = true;
				status = SUCCESS;
			}
			else
			{
				status = INVALID_VALUE;
			}
			break;
		}
	}
	return status;
}

int frame::set_selectable(int id, bool selectable)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].selectable = selectable;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_coordinate_colors(int id, std::vector<format_tools::coordinate_format> coordinate_colors)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].coordinate_colors = coordinate_colors;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_index_colors(int id, std::vector<format_tools::index_format> index_colors)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].index_colors = index_colors;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_line_constraint(int id, bool line_constraint)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].line_constraint = line_constraint;
			status = SUCCESS;
			display_stale = true;
			break;
		}
	}
	return status;
}

int frame::set_top_line(int id, unsigned int top_line)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].top_line = top_line;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_displayed_lines(int id, unsigned int displayed_lines)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].displayed_lines = displayed_lines;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_lines(int id, const std::vector <std::string>& lines)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].lines = lines;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::set_line_character(int id, char character, unsigned int line, unsigned int character_index)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			if (line < widgets[i].lines.size())
			{
				if (character_index < widgets[i].lines[line].length())
				{
					(widgets[i].lines[line])[character_index] = character;
					widgets[i].line_edited = true;
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
			break;
		}
	}
	return status;
}

int frame::set_line_edited(int id, bool line_edited)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			widgets[i].line_edited = line_edited;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::generate_widget_id()
{
	int id = widgets.size();
	return id;
}

std::vector<int> frame::get_row_ids(int row)
{
	std::vector<int> ids;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].row == row)
		{
			ids.push_back(widgets[i].id);
		}
	}
	return ids;
}

std::vector<std::vector<int>> frame::sort_row_ids(std::vector<int> ids)
{
	std::vector<widget_info> widgets_vec;
	for (unsigned int i = 0; i < ids.size(); i++)
	{
		widget_info item;
		get_widget(ids[i], item);
		widgets_vec.push_back(item);
	}

	unsigned int widgets_vec_length = widgets_vec.size();
	std::vector<widget_info> sorted_widgets;
	for (unsigned int i = 0; i < widgets_vec_length; i++)
	{
		int index = get_min_column_index(widgets_vec);
		sorted_widgets.push_back(widgets_vec[index]);
		widgets_vec.erase(widgets_vec.begin() + index);
	}
	
	std::vector<std::vector<int>> sorted_ids;
	while(sorted_widgets.size() > 0)
	{
		std::vector<widget_info> level_group;
		level_group.push_back(sorted_widgets[0]);
		sorted_widgets.erase(sorted_widgets.begin());
		for (unsigned int i = 0; i < sorted_widgets.size(); i++)
		{
			if ((level_group[0].row == sorted_widgets[i].row) && (level_group[0].column == sorted_widgets[i].column))
			{
				level_group.push_back(sorted_widgets[i]);
				sorted_widgets.erase(sorted_widgets.begin() + i);
				i--;
			}
		}

		std::vector<int> sorted_id_group;
		if (level_group.size() > 1)
		{
			unsigned int id_group_length = level_group.size();
			for (unsigned int k = 0; k < id_group_length; k++)
			{
				int index = get_min_level_index(level_group);
				sorted_id_group.push_back(level_group[index].id);
				level_group.erase(level_group.begin() + index);
			}
		}
		else
		{
			sorted_id_group.push_back(level_group[0].id);
		}
		sorted_ids.push_back(sorted_id_group);
	}
	return sorted_ids;
}

int frame::get_min_column_index(const std::vector<widget_info>& widget_vec)
{
	int min_index = 0;
	int min_column = 0;
	if (widget_vec.size() > 0)
	{
		min_index = 0;
		min_column = widget_vec[min_index].column;
		for (unsigned int i = 1; i < widget_vec.size(); i++)
		{
			if (widget_vec[i].column < min_column)
			{
				min_index = i;
				min_column = widget_vec[min_index].column;
			}
		}
	}
	return min_index;
}

int frame::get_min_level_index(const std::vector<widget_info>& widget_vec)
{
	int min_index = 0;
	int min_level = 0;
	if (widget_vec.size() > 0)
	{
		min_index = 0;
		min_level = widget_vec[min_index].level;
		for (unsigned int i = 1; i < widget_vec.size(); i++)
		{
			if (widget_vec[i].level < min_level)
			{
				min_index = i;
				min_level = widget_vec[min_index].level;
			}
		}
	}
	return min_index;
}

bool frame::in_range(int value, int begin, int end)
{
	bool in = false;
	if ((value >= begin) || (value < end))
	{
		in = true;
	}
	return in;
}

int frame::get_output(int id, std::string& output)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			output = widgets[i].output;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_widget(int id, widget_info& return_value)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			return_value = widgets[i];
			status = SUCCESS;
			break;
		}
	}
	return status;
}

int frame::get_widget(int row, int column, int level, widget_info& return_value)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column) && (widgets[i].level == level))
		{
			return_value = widgets[i];
			status = SUCCESS;
			break;
		}
	}
	return status;
}

unsigned int frame::get_widget_width(const widget_info& item, bool include_spacing)
{	
	int raw_width = 0;
	raw_width = int(terminal_x * get_width_weight(item, item.width_multiplier));
	
	if(!include_spacing)
	{
		if(!item.use_spacing_width_multipliers)
		{
			raw_width = raw_width - item.left_spacing - item.right_spacing;
		}
		
		if (item.add_border)
		{
			raw_width = raw_width - 4;
		}
	}
	else if (item.use_spacing_width_multipliers)
	{
		raw_width = raw_width + int(terminal_x * get_width_weight(item, item.left_width_multiplier)) + int(terminal_x * get_width_weight(item, item.right_width_multiplier));
	}

	unsigned int width = 0;
	if (raw_width >= 0)
	{
		width = (unsigned int)raw_width;
	}
	else
	{
		log.log_begin("frame::get_widget_width");
		log.log_comment("Widget id: " + std::to_string(item.id) + " has zero width.");
		log.log_end("frame::get_widget_width");
	}
	return width;
}

unsigned int frame::get_greatest_widget_width_at_coordinate(const widget_info& item, bool include_spacing)
{
	unsigned int greatest_widget_width = 0;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == item.row) && (widgets[i].column == item.column))
		{
			unsigned int widget_width = get_widget_width(widgets[i], include_spacing);
			if (widget_width > greatest_widget_width)
			{
				greatest_widget_width = widget_width;
			}
		}
	}
	return greatest_widget_width;
}

int frame::get_widget_width(int id, unsigned int& width, bool include_spacing)
{
	int status = ELEMENT_NOT_FOUND;
	widget_info item;
	status = get_widget(id, item);
	if (status == SUCCESS)
	{
		width = get_widget_width(item, include_spacing);
	}
	return status;
}

unsigned int frame::get_widget_height(const widget_info& item, bool include_spacing)
{
	unsigned int height = 0;
	get_lines_count(item.id, height);
	if (include_spacing)
	{
		height = height + item.top_spacing + item.bottom_spacing;
		if (item.add_border)
		{
			height = height + 2;
		}
	}

	return height;
}

int frame::get_widget_height(int id, unsigned int& height, bool include_spacing)
{
	int status = ELEMENT_NOT_FOUND;
	widget_info item;
	status = get_widget(id, item);
	if (status == SUCCESS)
	{
		height = get_widget_height(item, include_spacing);
	}
	return status;
}

void frame::constrain_lines(const widget_info& item, std::vector<std::string>& widget_lines)
{
	unsigned int stop_line = 0;
	std::string empty_line = format_tools::get_spacing(get_widget_width(item, false), ' ');
	if (!item.line_constraint || widget_lines.size() < (item.displayed_lines + item.top_line))
	{
		stop_line = widget_lines.size();
	}
	else
	{
		stop_line = item.displayed_lines + item.top_line;
	}

	int last_widget_line = widget_lines.size() - 1;
	for (int i = last_widget_line; i >= 0; i--)
	{
		if ((unsigned int)i >= stop_line || (unsigned int)i < item.top_line)
		{
			widget_lines.erase(widget_lines.begin() + i);
		}
	}

	for (unsigned int i = widget_lines.size(); i < item.displayed_lines; i++)
	{
		widget_lines.push_back(empty_line);
	}
}

void frame::constrain_colors(const widget_info& item, std::vector<format_tools::coordinate_format>& colors)
{
	if (item.coordinate_colors.size() > 0)
	{
		unsigned int stop_line = 0;
		if (!item.line_constraint || item.lines.size() < (item.displayed_lines + item.top_line))
		{
			stop_line = item.lines.size();
		}
		else
		{
			stop_line = item.displayed_lines + item.top_line;
		}

		int number_of_coordinate_colors = item.coordinate_colors.size() - 1;
		for (int i = number_of_coordinate_colors; i >= 0; i--)
		{
			if (item.coordinate_colors[i].y_position < (int)item.top_line || item.coordinate_colors[i].y_position >= (int)stop_line)
			{
				colors.erase(item.coordinate_colors.begin() + i);
			}
		}

		for (unsigned int i = 0; i < colors.size(); i++)
		{
			colors[i].y_position = colors[i].y_position - item.top_line;
		}
	}
}

void frame::update_widget_output_from_lines(widget_info& item)
{
	unsigned int output_index = 0;
	for (unsigned int i = 0; i < item.lines.size(); i++)
	{
		for (unsigned int j = 0; j < item.lines[i].length(); j++)
		{
			while (output_index < item.output.length() && item.output[output_index] == '\n')
			{
				output_index++;
			}

			if (output_index < item.output.length())
			{
				item.output[output_index] = (item.lines[i])[j];
				output_index++;
			}
			else
			{
				return;
			}
		}
	}
}

std::vector<std::string> frame::get_widget_lines(int id)
{
	widget_info item;
	get_widget(id, item);

	if (item.line_edited)
	{
		update_widget_output_from_lines(item);
		set_line_edited(id, false);
		widgets[id].output = item.output;
	}

	if (item.output == "")
	{
		item.output = " ";
	}
	int left_spacing = 0;
	int right_spacing = 0;
	if (item.use_spacing_width_multipliers)
	{
		left_spacing = int(terminal_x * get_width_weight(item, item.left_width_multiplier));
		right_spacing = int(terminal_x * get_width_weight(item, item.right_width_multiplier));
	}
	else
	{
		left_spacing = item.left_spacing;
		right_spacing = item.right_spacing;
	}
	std::string left_spacing_string = format_tools::get_spacing(left_spacing, ' ');
	std::string right_spacing_string = format_tools::get_spacing(right_spacing, ' ');
	unsigned int width = get_widget_width(item, false);
	std::string active_spacing = format_tools::get_spacing(width, ' ');
	std::vector<std::string> widget_lines;
	std::vector<int> ignore_flags;

	if (_color_enabled)
	{
		ignore_flags = format_tools::set_flags(item.index_colors, item.output, '*');
	}

	std::vector<std::string> user_lines = format_tools::split_string(item.output, '\n');
	std::string line = "";

	for (unsigned int i = 0; i < user_lines.size(); i++)
	{
		if (user_lines[i] == "\n")
		{
			widget_lines.push_back(line);
			line = "";
		}
		else
		{
			std::vector<std::string> words = format_tools::split_string(user_lines[i], ' ');
			for (unsigned int j = 0; j < words.size(); j++)
			{
				if ((((line + words[j]).length())) <= width)
				{
					line = line + words[j];
				}
				else if (words[j].length() >= width)
				{
					std::string first_section = "";
					std::string second_section = "";
					format_tools::cut_word(words[j], width - line.length(), first_section, second_section);
					line = line + first_section;
					widget_lines.push_back(line);
					line = "";
					if (item.widget_type == LABEL)
					{
						second_section.insert(0, "-");
					}
					words.insert(words.begin() + (j + 1), second_section);
				}
				else
				{
					widget_lines.push_back(line);
					if (words[j] != " ")
					{
						line = words[j];
					}
					else
					{
						line = "";
					}
				}
			}
		}
	}

	if (line != "")
	{
		widget_lines.push_back(line);
		line = "";
	}

	if (user_lines.back() == "\n")
	{
		widget_lines.push_back(active_spacing);
	}

	if (std::count(widget_types::lince_constraint_widgets.begin(), widget_types::lince_constraint_widgets.end(), item.widget_type) != 0)
	{
		set_lines(item.id, format_tools::remove_flags(item.index_colors, ignore_flags, widget_lines, '*'));
	}

	widget_lines = format_tools::fill_lines(widget_lines, width, item.alignment);

	if (_color_enabled)
	{
		convert_flags(item.coordinate_colors, item.index_colors, ignore_flags, widget_lines, '*');
		if (item.widget_type == LABEL)
		{
			item.coordinate_colors = format_tools::bound_colors(item.coordinate_colors, widget_lines);
		}
		set_coordinate_colors(item.id, item.coordinate_colors);
	}

	if (std::count(widget_types::lince_constraint_widgets.begin(), widget_types::lince_constraint_widgets.end(), item.widget_type) != 0)
	{
		if (item.line_constraint)
		{
			constrain_lines(item, widget_lines);
		}
	}

	set_lines_count(item.id, widget_lines.size());

	for (int i = 0; i < item.top_spacing; i++)
	{
		widget_lines.insert(widget_lines.begin(), active_spacing);
	}

	for (int i = 0; i < item.bottom_spacing; i++)
	{
		widget_lines.push_back(active_spacing);
	}

	for (unsigned int i = 0; i < widget_lines.size(); i++)
	{
		widget_lines[i].insert(0, left_spacing_string);
		widget_lines[i] = widget_lines[i] + right_spacing_string;
	}
	return widget_lines;
}

int frame::get_displayed_output(int id, std::vector<std::string>& displayed_output)
{
	widget_info item;
	int status = get_widget(id, item);
	if (status == SUCCESS)
	{
		constrain_lines(item, item.lines);
		displayed_output = item.lines;
	}
	return status;
}

int frame::get_displayed_colors(int id, std::vector<format_tools::index_format>& colors)
{
	widget_info item;
	int status = get_widget(id, item);
	if (_color_enabled && (status == SUCCESS))
	{
		constrain_colors(item, item.coordinate_colors);
		colors = format_tools::convert(item.coordinate_colors, get_widget_width(item, false));
	}
	return status;
}

bool frame::element_exists(const std::vector<int>& storage, int element)
{
	bool exists = false;
	for (unsigned int i = 0; i < storage.size(); i++)
	{
		if (storage[i] == element)
		{
			exists = true;
			break;
		}
	}
	return exists;
}

unsigned int frame::get_total_rows()
{
	std::vector<int> rows;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (!element_exists(rows, widgets[i].row))
		{
			rows.push_back(widgets[i].row);
		}
	}
	return rows.size();
}

unsigned int frame::get_columns_in_row(int row)
{
	std::vector<int> row_ids = get_row_ids(row);
	std::vector<int> columns;
	for (unsigned int i = 0; i < row_ids.size(); i++)
	{
		widget_info item;
		get_widget(row_ids[i], item);
		if (!element_exists(columns, item.column))
		{
			columns.push_back(item.column);
		}
	}
	return columns.size();
}

std::string frame::generate_frame_output()
{
	if (!_use_fake_console_dimensions)
	{
		ascii_io::get_terminal_size(terminal_x, terminal_y);
	}
	else
	{
		terminal_x = _fake_console_width;
		terminal_y = _fake_console_height;
	}

	std::string frame_output = "";
	int total_rows = get_total_rows();
	row_heights.clear();
	format_tools::text_column column_data;
	for (int i = 0; i < total_rows; i++)
	{
		std::vector<std::vector<int>> row_ids = sort_row_ids(get_row_ids(i));
		widget_info item;
		for (unsigned int j = 0; j < row_ids.size(); j++)
		{
			std::vector<std::string> accumulated_widget_lines;
			for (unsigned int m = 0; m < row_ids[j].size(); m++)
			{
				std::vector<std::string> widget_lines;
				widget_lines = get_widget_lines((row_ids[j])[m]);
				get_widget((row_ids[j])[m], item);

				if (item.add_border)
				{
					generate_border(item, widget_lines);
				}

				if (!only_widget_at_coordinate(item))
				{
					widget_lines = format_tools::fill_lines(widget_lines, get_greatest_widget_width_at_coordinate(item, true), format_tools::left_alignment_keyword);
				}

				accumulated_widget_lines.insert(accumulated_widget_lines.end(), widget_lines.begin(), widget_lines.end());
			}
			column_data.text.push_back(accumulated_widget_lines);
			column_data.width.push_back(get_widget_width(item, true));
		}
		unsigned int row_lines = 0;
		frame_output = frame_output + format_tools::fuse_columns_into_row(column_data, row_lines);
		row_heights.push_back(row_lines);
		column_data.text.clear();
		column_data.width.clear();
	}
	std::vector<std::string> frame_lines = format_tools::get_lines(frame_output);
	frame_lines = format_tools::remove_newline_characters(frame_lines);
	frame_lines = format_tools::fill_lines(frame_lines, terminal_x, format_tools::left_alignment_keyword);
	if (frame_lines.size() < (unsigned int)terminal_y)
	{
		frame_lines = format_tools::add_lines(frame_lines, terminal_y - frame_lines.size(), terminal_x);
	}
	frame_lines = format_tools::add_newline_characters(frame_lines);
	frame_output = format_tools::get_string(frame_lines);
	if ((frame_output.back() == '\n') && (frame_output.length() > 0))
	{
		frame_output.erase((frame_output.length() - 1), 1);
	}
	set_widget_origins();
	if (_color_enabled)
	{
		translate_coordinate_colors_to_frame();
	}
	return frame_output;
}

void frame::set_widget_origins()
{
	int column = 0;
	int level = 0;
	unsigned int x = 0;
	unsigned int y = 0;
	widget_info item;
	for(unsigned int row = 0; row < row_heights.size(); row++)
	{
		x = 0;
		column = 0;
		while (get_widget(row, column, level, item) != ELEMENT_NOT_FOUND)
		{
			unsigned int y_origin = y;
			do
			{
				int left_spacing = 0;
				if (item.use_spacing_width_multipliers)
				{
					left_spacing = int(terminal_x * get_width_weight(item, item.left_width_multiplier));
				}
				else
				{
					left_spacing = item.left_spacing;
				}
				unsigned int x_origin = x + left_spacing;
				y_origin = y_origin + item.top_spacing;
				if (item.add_border)
				{
					x_origin = x_origin + 2;
					y_origin = y_origin + 1;
				}
				set_x_origin(item.id, x_origin);
				set_y_origin(item.id, y_origin);
				if (item.add_border)
				{
					y_origin = y_origin - 1;
				}
				y_origin = y_origin - item.top_spacing;
				y_origin = y_origin + get_widget_height(item, true);
				level++;
			} while (get_widget(row, column, level, item) != ELEMENT_NOT_FOUND);
			level = 0;
			column++;
			x = x + get_greatest_widget_width_at_coordinate(item, true);
		}
		y = y + row_heights[row];
	}
}

void frame::translate_coordinate_colors_to_frame()
{
	color_regions.clear();
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		for (unsigned int j = 0; j < widgets[i].coordinate_colors.size(); j++)
		{
			if (!widgets[i].line_constraint)
			{
				format_tools::coordinate_format color_region;
				color_region.x_position = widgets[i].coordinate_colors[j].x_position + widgets[i].x_origin;
				color_region.y_position = widgets[i].coordinate_colors[j].y_position + widgets[i].y_origin;
				color_region.format = widgets[i].coordinate_colors[j].format;
				color_regions.push_back(color_region);
			}
			else if (widgets[i].coordinate_colors[j].y_position >= (int)widgets[i].top_line && widgets[i].coordinate_colors[j].y_position < ((int)widgets[i].top_line + (int)widgets[i].displayed_lines))
			{
				format_tools::coordinate_format color_region;
				color_region.x_position = widgets[i].coordinate_colors[j].x_position + widgets[i].x_origin;
				color_region.y_position = widgets[i].coordinate_colors[j].y_position - widgets[i].top_line + widgets[i].y_origin;
				color_region.format = widgets[i].coordinate_colors[j].format;
				color_regions.push_back(color_region);
			}
		}
	}
}

bool frame::is_selectable(int row, int column, int level)
{
	bool selectable = false;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == row) && (widgets[i].column == column) && (widgets[i].level == level))
		{
			if (widgets[i].selectable)
			{
				selectable = true;
				break;
			}
		}
	}
	return selectable;
}

bool frame::is_selectable(int id)
{
	bool selectable = false;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if (widgets[i].id == id)
		{
			selectable = widgets[i].selectable;
			break;
		}
	}
	return selectable;
}

bool frame::initialize_selection(int& row, int& column, int& level)
{
	while (true)
	{
		if (is_selectable(row, column, level))
		{
			return true;
		}

		level++;
		if (level >= get_levels(row, column))
		{
			column++;
			level = 0;
		}

		if (column >= (int)get_columns_in_row(row))
		{
			row++;
			column = 0;
			level = 0;
		}

		if (row >= (int)get_total_rows())
		{
			return false;
		}
	}
}

bool frame::get_nearest_selectable_in_row(int& row, int& column, int& level, widget_info item, int search_row)
{
	int original_row = row;
	int original_column = column;
	int original_level = level;
	row = search_row;
	std::vector<int> row_ids = get_row_ids(row);
	if (row_ids.size() == 0)
	{
		return false;
	}
	float distance = 0.0;
	int original_x = item.x_origin;
	int original_y = item.y_origin;
	int x = 0;
	int y = 0;
	float min_distance = 0.0;
	int min_id = 0;
	bool widget_found = false;
	for (unsigned int i = 0; i < row_ids.size(); i++)
	{
		if (is_selectable(row_ids[i]))
		{
			get_x_origin(row_ids[i], x);
			get_y_origin(row_ids[i], y);
			distance = (float)pow(pow(abs(x - original_x), 2) + pow(abs(y - original_y), 2), 0.5);
			if ((distance < min_distance) || min_distance == 0)
			{
				min_distance = distance;
				min_id = row_ids[i];
				widget_found = true;
			}
		}
	}

	if (!widget_found)
	{
		row = original_row;
		column = original_column;
		level = original_level;
	}
	else
	{
		get_widget(min_id, item);
		row = item.row;
		column = item.column;
		level = item.level;
	}
	return widget_found;
}

void frame::up_handle(int& selected_row, int& selected_column, int& selected_level)
{
	int last_selected_row = selected_row;
	int last_selected_column = selected_column;
	int last_selected_level = selected_level;
	widget_info item;
	get_widget(selected_row, selected_column, selected_level, item);
	do
	{
		if ((selected_level - 1) >= 0)
		{
			selected_level--;
		}
		else if ((selected_row - 1) >= 0)
		{

			if (!get_nearest_selectable_in_row(selected_row, selected_column, selected_level, item, selected_row - 1))
			{
				selected_row--;
				selected_level = 0;
			}
		}
		else
		{
			selected_row = last_selected_row;
			selected_column = last_selected_column;
			selected_level = last_selected_level;
			break;
		}

	} while (!is_selectable(selected_row, selected_column, selected_level));
}

void frame::down_handle(int& selected_row, int& selected_column, int& selected_level)
{
	int last_selected_row = selected_row;
	int last_selected_column = selected_column;
	int last_selected_level = selected_level;
	widget_info item;
	get_widget(selected_row, selected_column, selected_level, item);
	do
	{
		if ((selected_level + 1) < get_levels(selected_row, selected_column))
		{
			selected_level++;
		}
		else if ((selected_row + 1) < (int)get_total_rows())
		{
			if (!get_nearest_selectable_in_row(selected_row, selected_column, selected_level, item, selected_row + 1))
			{
				selected_row++;
				selected_level = 0;
			}
		}
		else
		{
			selected_row = last_selected_row;
			selected_column = last_selected_column;
			selected_level = last_selected_level;
			break;
		}

	} while (!is_selectable(selected_row, selected_column, selected_level));
}

void frame::right_handle(int& selected_row, int& selected_column, int& selected_level)
{
	int last_selected_row = selected_row;
	int last_selected_column = selected_column;
	int last_selected_level = selected_level;
	do
	{
		if ((selected_column + 1) < (int)get_columns_in_row(selected_row))
		{
			selected_column++;
			int total_levels = get_levels(selected_row, selected_column);
			if (selected_level >= total_levels)
			{
				selected_level = total_levels - 1;
			}
			for (int i = 0, j = selected_level; i < total_levels; ++i, j = (j + 1) % total_levels)
			{
				selected_level = j;
				if (is_selectable(selected_row, selected_column, selected_level))
				{
					break;
				}
			}
		}
		else
		{
			selected_row = last_selected_row;
			selected_column = last_selected_column;
			selected_level = last_selected_level;
			break;
		}

	} while (!is_selectable(selected_row, selected_column, selected_level));
}

void frame::left_handle(int& selected_row, int& selected_column, int& selected_level)
{
	int last_selected_row = selected_row;
	int last_selected_column = selected_column;
	int last_selected_level = selected_level;
	do
	{
		if ((selected_column - 1) >= 0)
		{
			selected_column--;
			int total_levels = get_levels(selected_row, selected_column);
			if (selected_level >= total_levels)
			{
				selected_level = total_levels - 1;
			}
			for (int i = 0, j = selected_level; i < total_levels; ++i, j = (j + 1) % total_levels)
			{
				selected_level = j;
				if (is_selectable(selected_row, selected_column, selected_level))
				{
					break;
				}
			}
		}
		else
		{
			selected_row = last_selected_row;
			selected_column = last_selected_column;
			selected_level = last_selected_level;
			break;
		}

	} while (!is_selectable(selected_row, selected_column, selected_level));
}

void frame::generate_border(const widget_info& item, std::vector<std::string>& lines)
{
	int top_spacing = item.top_spacing - item.top_border_spacing;
	int bottom_spacing = item.bottom_spacing - item.bottom_border_spacing;
	int left_spacing = 0;
	int right_spacing = 0;
	int left_border_spacing = 0;
	int right_border_spacing = 0;

	if (item.use_spacing_width_multipliers)
	{
		left_border_spacing = int(terminal_x * get_width_weight(item, item.left_border_width_multiplier));
		right_border_spacing = int(terminal_x * get_width_weight(item, item.right_border_width_multiplier));
		left_spacing = int(terminal_x * get_width_weight(item, item.left_width_multiplier)) - left_border_spacing;
		right_spacing = int(terminal_x * get_width_weight(item, item.right_width_multiplier)) - right_border_spacing;
	}
	else
	{
		left_border_spacing = item.left_border_spacing;
		right_border_spacing = item.right_border_spacing;
		left_spacing = item.left_spacing - item.left_border_spacing;
		right_spacing = item.right_spacing - item.right_border_spacing;
	}

	int middle_spacing = get_widget_width(item, false) + 2 + left_border_spacing + right_border_spacing;

	for (unsigned int k = 0; k < lines.size(); k++)
	{
		if (k < (unsigned int)(top_spacing) || (k > (lines.size() - bottom_spacing - 1)))
		{
			lines[k].insert(left_spacing, "  ");
			lines[k].insert(lines[k].length() - right_spacing, "  ");
		}
		else
		{
			lines[k].insert(left_spacing, std::string(1, item.vertical_border) + " ");
			lines[k].insert(lines[k].length() - right_spacing, " " + std::string(1, item.vertical_border));
		}
	}
	lines.insert(lines.begin() + top_spacing, format_tools::get_spacing(left_spacing, ' ') + std::string(1, item.corner_border) + format_tools::get_spacing(middle_spacing, item.horizontal_border) + std::string(1, item.corner_border) + format_tools::get_spacing(right_spacing, ' '));
	lines.insert(lines.end() - bottom_spacing, format_tools::get_spacing(left_spacing, ' ') + std::string(1, item.corner_border) + format_tools::get_spacing(middle_spacing, item.horizontal_border) + std::string(1, item.corner_border) + format_tools::get_spacing(right_spacing, ' '));
}

bool frame::only_widget_at_coordinate(const widget_info& item)
{
	unsigned int widgets_at_coordinate = 0;
	for (unsigned int i = 0; i < widgets.size(); i++)
	{
		if ((widgets[i].row == item.row) && (widgets[i].column == item.column))
		{
			widgets_at_coordinate = widgets_at_coordinate + 1;
		}
	}

	if (widgets_at_coordinate == 1)
	{
		return true;
	}

	return false;
}

std::vector<format_tools::index_format> frame::dec_format(std::string& format_content, unsigned int line_length)
{
	return dec.format(format_content, line_length);
}

void frame::mark_as_stale()
{
	display_stale = true;
}

#ifdef __linux__
void frame::dec_print(const std::string& input)
{
	dec.print_dec_string(input);
}
#endif
