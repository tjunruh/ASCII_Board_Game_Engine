#include "../ascii_engine_dll_files/pch.h"
#include "menu.h"
#include "widget_types.h"
#include "error_codes.h"
#include "format_tools.h"

#ifdef __linux__
#include <algorithm>
#endif

menu::menu(frame* parent, const std::string& special_operation, int lines_count, bool start_logging, const std::string& logging_file_path) : widget(parent, special_operation)
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
		if (lines_count > 0)
		{
			non_separated_lines_count = lines_count;
			line_subtraction_from_terminal_height = 0;
		}
		else if (lines_count < 0)
		{
			line_subtraction_from_terminal_height = lines_count;
			lines_count = dynamic_displayed_line_adjustment(line_subtraction_from_terminal_height);
		}

		set_displayed_lines(lines_count);
		set_line_constraint(true);
	}
}

int menu::append_item(const std::string& item)
{
	int status = DUPLICATE_ELEMENT;
	if (!item_exists(item))
	{
		item_structure item_initialization;
		item_initialization.name_id = item;
		menu_items.push_back(item_initialization);
		status = SUCCESS;
		if (!get_line_constraint())
		{
			set_displayed_lines(get_displayed_lines() + 1);
		}
	}
	log.log_status(status, "menu::append_item");
	return status;
}

int menu::remove_item(const std::string& item)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < menu_items.size(); i++)
	{
		if (menu_items[i].name_id == item)
		{
			unsigned int top_line_remainder = 0;
			unsigned int displayed_lines_remainder = 0;
			unsigned int top_item = line_to_item(get_top_line(), top_line_remainder);
			unsigned int displayed_items = line_to_item(get_displayed_lines(), displayed_lines_remainder);
			menu_items.erase(menu_items.begin() + i);
			status = SUCCESS;
			if (!get_line_constraint())
			{
				displayed_items--;
				set_displayed_lines(item_to_line(displayed_items, displayed_lines_remainder));
			}

			unsigned int bounded_top_item = bound_top_item(top_item, displayed_items);
			if (bounded_top_item != top_item)
			{
				top_item = bounded_top_item;
				set_top_line(item_to_line(top_item, top_line_remainder));
			}

			unsigned int bounded_cursor_item = bound_cursor_item(_cursor_item, top_item, get_stop_item(top_item, displayed_items));
			if (bounded_cursor_item != _cursor_item)
			{
				_cursor_item = bounded_cursor_item;
				set_cursor_line(item_to_line(_cursor_item, 1));
			}
			break;
		}
	}
	log.log_status(status, "menu::remove_item");
	return status;
}

void menu::set_lines_count(int lines_count)
{
	if (lines_count == 0)
	{
		set_line_constraint(false);
		set_top_line(0);
		set_displayed_lines(item_to_line(menu_items.size(), 1));
	}
	else
	{
		unsigned int top_line_remainder = 0;
		unsigned int displayed_lines_remainder = 0;
		unsigned int top_item = line_to_item(get_top_line(), top_line_remainder);
		unsigned int displayed_items = line_to_item(get_displayed_lines(), displayed_lines_remainder);
		if (lines_count > 0)
		{
			displayed_items = line_to_item(lines_count, displayed_lines_remainder);
			line_subtraction_from_terminal_height = 0;
		}
		else if (lines_count < 0)
		{
			line_subtraction_from_terminal_height = lines_count;
			displayed_items = line_to_item(dynamic_displayed_line_adjustment(line_subtraction_from_terminal_height), displayed_lines_remainder);
		}
		set_line_constraint(true);


		unsigned int bounded_top_item = bound_top_item(top_item, displayed_items);
		if (bounded_top_item != top_item)
		{
			top_item = bounded_top_item;
			set_top_line(item_to_line(top_item, top_line_remainder));
		}

		unsigned int bounded_cursor_item = bound_cursor_item(_cursor_item, top_item, get_stop_item(top_item, displayed_items));
		if (bounded_cursor_item != _cursor_item)
		{
			_cursor_item = bounded_cursor_item;
			set_cursor_line(item_to_line(_cursor_item, 1));
		}

		unsigned int displayed_lines = item_to_line(displayed_items, displayed_lines_remainder);

		if (_separate_items)
		{
			displayed_lines = fit_displayed_lines_for_separated_items(displayed_lines);
		}
		set_displayed_lines(displayed_lines);
	}
}

void menu::remove_all_items()
{
	menu_items.clear();
	set_top_line(0);
	set_cursor_line(item_to_line(0, 1));
	if (!get_line_constraint())
	{
		set_displayed_lines(0);
	}
}

int menu::set_item_label(const std::string& item, const std::string& label)
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

void menu::set_cursor_item(unsigned int item)
{
	unsigned int top_line_remainder = 0;
	unsigned int displayed_lines_remainder = 0;
	unsigned int top_item = line_to_item(get_top_line(), top_line_remainder);
	_cursor_item = bound_cursor_item(item, top_item, get_stop_item(top_item, line_to_item(get_displayed_lines(), displayed_lines_remainder)));
	set_cursor_line(item_to_line(_cursor_item, 1));
}

unsigned int menu::get_cursor_item()
{
	return _cursor_item;
}

bool menu::item_exists(const std::string& item)
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

	std::string separation_string = "   ";
	if (_separate_items)
	{
		separation_string = " " + std::string(1, _vertical_char) + " ";
	}

	for (unsigned int i = 0; i < menu_items.size(); i++)
	{
		if (_cursor_item == i)
		{
			item_output = item_output + _cursor + " ";
			set_cursor_line(item_to_line(i, 1));
		}
		else
		{
			item_output = item_output + "  ";
		}
		
		item_output = item_output + menu_items[i].name_id + "\n";
		if (_separate_items && ((i + 1) != menu_items.size()))
		{
			item_output = item_output + format_tools::get_spacing(item_width, _horizontal_char) + "\n";
		}

		if (build_label)
		{
			label_output = label_output + separation_string + menu_items[i].label + "\n";
			if (_separate_items && ((i + 1) != menu_items.size()))
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
		unsigned int top_line_remainder = 0;
		unsigned int top_item = line_to_item(get_top_line(), top_line_remainder);
		unsigned int displayed_lines_remainder = 0;
		unsigned int displayed_items = line_to_item(get_displayed_lines(), displayed_lines_remainder);

		if (std::count(_select.begin(), _select.end(), key_stroke) != 0)
		{
			if (menu_items.size() > 0)
			{
				selection = menu_items[_cursor_item].name_id;
			}
			break;
		}
		else if (key_stroke == _up)
		{
			if (_cursor_item > 0)
			{
				if (_cursor_item == top_item)
				{
					top_item--;
				}
				_cursor_item--;
				set_cursor_line(item_to_line(_cursor_item, 1));
			}
		}
		else if (key_stroke == _down)
		{
			if (_cursor_item < (menu_items.size() - 1))
			{
				if ((_cursor_item - top_item + 1) == displayed_items)
				{
					top_item++;
				}
				_cursor_item++;
				set_cursor_line(item_to_line(_cursor_item, 1));
			}
		}

		set_top_line(item_to_line(top_item, top_line_remainder));

	} while ((key_stroke != _quit) || !quit_enabled);
}

void menu::display()
{
	if (frame_stale())
	{
		if (line_subtraction_from_terminal_height != 0)
		{
			unsigned int displayed_lines_remainder = 0;
			unsigned int displayed_items = line_to_item(dynamic_displayed_line_adjustment(line_subtraction_from_terminal_height), displayed_lines_remainder);

			set_displayed_lines(item_to_line(displayed_items, displayed_lines_remainder));
			unsigned int top_line_remainder = 0;
			unsigned int top_item = line_to_item(get_top_line(), top_line_remainder);

			unsigned int bounded_top_item = bound_top_item(top_item, displayed_items);
			if (bounded_top_item != top_item)
			{
				top_item = bounded_top_item;
				set_top_line(item_to_line(top_item, top_line_remainder));
			}

			unsigned int bounded_cursor_item = bound_cursor_item(_cursor_item, top_item, get_stop_item(top_item, displayed_items));
			if (bounded_cursor_item != _cursor_item)
			{
				_cursor_item = bounded_cursor_item;
				set_cursor_line(item_to_line(_cursor_item, 1));
			}
		}
	}
	std::vector<std::string> displayed_output;
	get_displayed_output(displayed_output);
	widget_display(displayed_output, true);
}

void menu::build()
{
	set_output_to_frame(build_output());
}

void menu::separate_items(bool separate)
{
	if (separate != _separate_items)
	{
		if (!separate && non_separated_lines_count != 0)
		{
			set_displayed_lines(non_separated_lines_count);
		}
		else if (separate)
		{
			unsigned int displayed_lines = get_displayed_lines();
			unsigned int adjusted_displayed_lines = fit_displayed_lines_for_separated_items(displayed_lines);
			if (adjusted_displayed_lines != displayed_lines)
			{
				displayed_lines = adjusted_displayed_lines;
				set_displayed_lines(displayed_lines);
			}
		}

		_separate_items = separate;

		unsigned int top_line_remainder = 0;
		unsigned int displayed_lines_remainder = 0;
		unsigned int top_item = line_to_item(get_top_line(), top_line_remainder);
		unsigned int displayed_items = line_to_item(get_displayed_lines(), displayed_lines_remainder);

		unsigned int bounded_top_item = bound_top_item(top_item, displayed_items);
		if (bounded_top_item != top_item)
		{
			top_item = bounded_top_item;
			set_top_line(item_to_line(top_item, top_line_remainder));
		}

		unsigned int bounded_cursor_item = bound_cursor_item(_cursor_item, top_item, get_stop_item(top_item, displayed_items));
		if (bounded_cursor_item != _cursor_item)
		{
			_cursor_item = bounded_cursor_item;
			set_cursor_line(item_to_line(_cursor_item, 1));
		}
	}
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

unsigned int menu::get_stop_item(unsigned int top_item, unsigned int displayed_items)
{
	unsigned int stop_item;
	if (menu_items.size() < (displayed_items + top_item))
	{
		stop_item = menu_items.size();
	}
	else
	{
		stop_item = displayed_items + top_item;
	}

	return stop_item;
}

unsigned int menu::dynamic_displayed_line_adjustment(int line_subtraction)
{
	int x = 0;
	int y = 0;
	ascii_io::get_terminal_size(x, y);
	unsigned int lines = 0;
	if ((y + line_subtraction) > 0)
	{
		lines = (unsigned int)(y + line_subtraction);
	}
	else
	{
		lines = 1;
	}

	return lines;
}

void menu::set_cursor_line(unsigned int line)
{
	set_line_character(' ', item_to_line(last_cursor_item, last_cursor_line_remainder), 0);
	set_line_character(_cursor, line, 0);
	last_cursor_item = line_to_item(line, last_cursor_line_remainder);
}

unsigned int menu::line_to_item(unsigned int line, unsigned int& remainder)
{
	unsigned int item = line;
	if (_separate_items)
	{
		item = line / 2;
		remainder = line % 2;
	}
	return item;
}

unsigned int menu::item_to_line(unsigned int item, unsigned int remainder)
{
	unsigned int line = item;
	if (_separate_items)
	{
		line = item * 2 + remainder;
	}
	return line;
}

unsigned int menu::bound_top_item(unsigned int top_item, unsigned int displayed_items)
{
	if ((int)top_item > ((int)menu_items.size() - (int)displayed_items))
	{
		if (((int)menu_items.size() - (int)displayed_items) >= 0)
		{
			top_item = menu_items.size() - displayed_items;
		}
		else
		{
			top_item = 0;
		}
	}

	return top_item;
}

unsigned int menu::bound_cursor_item(unsigned int cursor_item, unsigned int top_item, unsigned int stop_item)
{
	if (cursor_item >= stop_item)
	{
		if ((int)(stop_item - 1) >= 0)
		{
			cursor_item = stop_item - 1;
		}
		else
		{
			cursor_item = 0;
		}
	}
	else if (cursor_item < top_item)
	{
		cursor_item = top_item;
	}

	return cursor_item;
}

unsigned int menu::fit_displayed_lines_for_separated_items(unsigned int displayed_lines)
{
	non_separated_lines_count = displayed_lines;
	if (displayed_lines > 3)
	{
		displayed_lines = displayed_lines - (displayed_lines + 1) % 2;
	}
	else
	{
		displayed_lines = 3;
	}
	return displayed_lines;
}