#include "../ascii_engine_dll_files/pch.h"
#include "menu.h"
#include "widget_types.h"
#include "error_codes.h"
#include "format_tools.h"

#ifdef __linux__
#include <algorithm>
#endif

menu::menu(frame* parent, std::string special_operation, unsigned int lines_count, bool start_logging, std::string logging_file_path) : widget(parent, special_operation)
{
	if (start_logging)
	{
		int logger_status = log.start_widget_logging(logging_file_path, MENU);
		if (logger_status != 0)
		{
			ascii_io::clear();
			ascii_io::print("menu initialization: Invalid logger path.\nPress any button to continue.");
			ascii_io::getchar();
		}
	}
	set_widget_type(MENU);
	selectable();
	if (lines_count != 0)
	{
		displayed_lines = lines_count;
	}
	else
	{
		no_lines_constraint = true;
	}

}

int menu::append_item(std::string item)
{
	int status = DUPLICATE_ELEMENT;
	if (!item_exists(item))
	{
		item_structure item_initialization;
		item_initialization.name_id = item;
		menu_items.push_back(item_initialization);
		status = SUCCESS;
		if (no_lines_constraint)
		{
			displayed_lines++;
		}
	}
	log.log_status(status, "menu::append_item");
	return status;
}

int menu::remove_item(std::string item)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < menu_items.size(); i++)
	{
		if (menu_items[i].name_id == item)
		{
			menu_items.erase(menu_items.begin() + i);
			status = SUCCESS;
			break;
		}
	}
	log.log_status(status, "menu::remove_item");
	return status;
}

void menu::remove_all_items()
{
	menu_items.clear();
}

int menu::set_item_label(std::string item, const std::string& label)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < menu_items.size(); i++)
	{
		if (menu_items[i].name_id == item)
		{
			menu_items[i].label = label;
			status = SUCCESS;
		}
	}
	log.log_status(status, "menu::set_item_label");
	return status;
}

void menu::set_cursor(char cursor)
{
	int status = UNDEFINED;
	if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), cursor) != 0)
	{
		status = INVALID_VALUE;
	}
	else
	{
		_cursor = cursor;
		status = SUCCESS;
	}
	log.log_status(status, "menu::set_cursor");
}

char menu::get_cursor()
{
	return _cursor;
}

bool menu::item_exists(std::string item)
{
	bool exists = false;
	for (unsigned int i = 0; i < menu_items.size(); i++)
	{
		if (menu_items[i].name_id == item)
		{
			exists = true;
			break;
		}
	}
	return exists;
}

std::string menu::build_output()
{
	std::string item_output = "";
	std::string label_output = "";
	unsigned int stop_line = 0;
	bool build_label = label_exists();
	unsigned int item_width = get_longest_item_length() + 2;
	unsigned int label_width = get_longest_label_length() + 3;

	if (_separate_items)
	{
		item_output = format_tools::get_spacing(item_width, _horizontal_char) + "\n";
		if (build_label)
		{
			label_output = std::string(1, _horizontal_char) + std::string(1, _endpoint_char) + format_tools::get_spacing(label_width - 2, _horizontal_char) + "\n";
		}
	}

	if (menu_items.size() < (displayed_lines + top_line))
	{
		stop_line = menu_items.size();
	}
	else
	{
		stop_line = displayed_lines + top_line;
	}

	std::string separation_string = "   ";
	if (_separate_items)
	{
		separation_string = " " + std::string(1, _vertical_char) + " ";
	}

	for (unsigned int i = top_line; i < stop_line; i++)
	{
		if (cursor_line == i)
		{
			item_output = item_output + _cursor + " ";
		}
		else
		{
			item_output = item_output + "  ";
		}
		
		item_output = item_output + menu_items[i].name_id + "\n";
		if (_separate_items && ((i + 1) != stop_line))
		{
			item_output = item_output + format_tools::get_spacing(item_width, _horizontal_char) + "\n";
		}

		if (build_label)
		{
			label_output = label_output + separation_string + menu_items[i].label + "\n";
			if (_separate_items && ((i + 1) != stop_line))
			{
				label_output = label_output + std::string(1, _horizontal_char) + std::string(1, _intersection_char) + format_tools::get_spacing(label_width - 2, _horizontal_char) + "\n";
			}
		}
	}

	if (_separate_items)
	{
		item_output = item_output + format_tools::get_spacing(item_width, _horizontal_char) + "\n";
		if (build_label)
		{
			label_output = label_output + std::string(1, _horizontal_char) + std::string(1, _endpoint_char) + format_tools::get_spacing(label_width - 2, _horizontal_char) + "\n";
		}
	}

	std::string output = "";
	std::vector<std::string> item_lines = format_tools::get_lines(item_output);
	item_lines = format_tools::remove_newline_characters(item_lines);
	item_lines = format_tools::fill_lines(item_lines, item_width, format_tools::left_alignment_keyword);
	
	if (build_label)
	{
		std::vector<std::string> label_lines = format_tools::get_lines(label_output);
		label_lines = format_tools::remove_newline_characters(label_lines);
		label_lines = format_tools::fill_lines(label_lines, label_width, format_tools::left_alignment_keyword);
		label_output = format_tools::get_string(label_lines);
		format_tools::text_column lines;
		lines.text.push_back(item_lines);
		lines.width.push_back(item_width);
		lines.text.push_back(label_lines);
		lines.width.push_back(label_width);
		unsigned int lines_in_column = 0;
		output = format_tools::fuse_columns_into_row(lines, lines_in_column);
	}
	else
	{
		item_lines = format_tools::add_newline_characters(item_lines);
		output = format_tools::get_string(item_lines);
	}

	if (output.length() > 0)
	{
		output.erase((output.length() - 1), 1);
	}
	return output;
}

void menu::set_controls(std::vector<int> select, int up, int down, int quit)
{
	_select.clear();
	for (unsigned int i = 0; i < select.size(); i++)
	{
		_select.push_back(select[i]);
	}
	_up = up;
	_down = down;
	_quit = quit;
}

void menu::get_controls(std::vector<int>& select, int& up, int& down, int& quit)
{
	select.clear();
	for (unsigned int i = 0; i < _select.size(); i++)
	{
		select.push_back(_select[i]);
	}
	up = _up;
	down = _down;
	quit = _quit;
}

void menu::set_separater_characters(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char)
{
	if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), horizontal_char) != 0)
	{
		log.log_status(INVALID_VALUE, "menu::set_separater_characters");
	}
	else if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), vertical_char) != 0)
	{
		log.log_status(INVALID_VALUE, "menu::set_separater_characters");
	}
	else if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), intersection_char) != 0)
	{
		log.log_status(INVALID_VALUE, "menu::set_separater_characters");
	}
	else if (std::count(format_tools::invalid_characters.begin(), format_tools::invalid_characters.end(), endpoint_char) != 0)
	{
		log.log_status(INVALID_VALUE, "menu::set_separater_characters");
	}
	else
	{
		_horizontal_char = horizontal_char;
		_vertical_char = vertical_char;
		_intersection_char = intersection_char;
		_endpoint_char = endpoint_char;
		log.log_status(SUCCESS, "menu::set_separater_characters");
	}
}

void menu::get_separater_characters(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char)
{
	horizontal_char = _horizontal_char;
	vertical_char = _vertical_char;
	intersection_char = _intersection_char;
	endpoint_char = _endpoint_char;
}

void menu::enable_quit()
{
	quit_enabled = true;
}

void menu::disable_quit()
{
	quit_enabled = false;
}

void menu::get_selection(std::string& selection, int& key_stroke)
{
	key_stroke = ascii_io::undefined;
	selection = "";
	do
	{
		display();
		key_stroke = ascii_io::getchar();
		if (std::count(_select.begin(), _select.end(), key_stroke) != 0)
		{
			selection = menu_items[cursor_line].name_id;
			break;
		}
		else if (key_stroke == _up)
		{
			if (cursor_line > 0)
			{
				if (cursor_line == top_line)
				{
					top_line--;
				}
				cursor_line--;
			}
		}
		else if (key_stroke == _down)
		{
			if (cursor_line < (menu_items.size() - 1))
			{
				if ((cursor_line - top_line + 1) == displayed_lines)
				{
					top_line++;
				}
				cursor_line++;
			}
		}
	} while ((key_stroke != _quit) || !quit_enabled);
}

void menu::display()
{
	if (frame_stale())
	{
		sync();
		frame_display();
	}
	else if (dec_enabled())
	{
		unsigned int width = get_width();
		int x_origin = get_x_origin();
		int y_origin = get_y_origin();
		int cursor_x = 0;
		int cursor_y = 0;
		ascii_io::get_cursor_position(cursor_x, cursor_y);
		std::string menu_output = build_output();
		std::vector<std::string> lines = format_tools::get_lines(menu_output);
		lines = format_tools::remove_newline_characters(lines);
		lines = format_tools::fill_lines(lines, width, get_alignment());
		std::string adjusted_menu_output = format_tools::get_string(lines);
		std::vector<format_tools::index_format> dec_regions = dec_format(adjusted_menu_output, width);
		std::vector<format_tools::content_format> regions = format_tools::convert(dec_regions, adjusted_menu_output);
		regions = format_tools::fit_to_width(regions, width);
		int line = 0;
		unsigned int line_length = 0;
		ascii_io::move_cursor_to_position(x_origin, y_origin);
		for (unsigned int i = 0; i < regions.size(); i++)
		{
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
#ifdef _WIN32
		ascii_io::disable_dec();
#endif
		ascii_io::move_cursor_to_position(cursor_x, cursor_y);
	}
	else
	{
		std::vector<std::string> lines = format_tools::get_lines(build_output());
		lines = format_tools::remove_newline_characters(lines);
		lines = format_tools::fill_lines(lines, get_width(), get_alignment());
		int x_origin = get_x_origin();
		int y_origin = get_y_origin();
		int cursor_x = 0;
		int cursor_y = 0;
		ascii_io::get_cursor_position(cursor_x, cursor_y);
		for (unsigned int i = 0; i < lines.size(); i++)
		{
			ascii_io::move_cursor_to_position(x_origin, y_origin + i);
			ascii_io::print(lines[i]);
		}
		ascii_io::move_cursor_to_position(cursor_x, cursor_y);
	}
}

void menu::sync()
{
	set_output_to_frame(build_output());
}

void menu::separate_items(bool separate)
{
	_separate_items = separate;
}

bool menu::label_exists()
{
	bool exists = false;
	for (unsigned int i = 0; i < menu_items.size(); i++)
	{
		if (menu_items[i].label != "")
		{
			exists = true;
			break;
		}
	}
	return exists;
}

unsigned int menu::get_longest_item_length()
{
	unsigned int longest_length = 0;
	for (unsigned int i = 0; i < menu_items.size(); i++)
	{
		if (menu_items[i].name_id.length() > longest_length)
		{
			longest_length = menu_items[i].name_id.length();
		}
	}
	return longest_length;
}

unsigned int menu::get_longest_label_length()
{
	unsigned int longest_length = 0;
	for (unsigned int i = 0; i < menu_items.size(); i++)
	{
		if (menu_items[i].label.length() > longest_length)
		{
			longest_length = menu_items[i].label.length();
		}
	}
	return longest_length;
}