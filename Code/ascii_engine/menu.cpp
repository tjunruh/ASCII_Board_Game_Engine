#include "../ascii_engine_dll_files/pch.h"
#include "menu.h"
#include "widget_types.h"

menu::menu(frame* parent, std::string special_operation, bool start_logging, std::string logging_file_path) : widget(parent, special_operation)
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
}

int menu::append_item(std::string item)
{
	int status = 1;
	if (!item_exists(item))
	{
		menu_items.push_back(item);
		status = 0;
		set_output_to_frame(build_output());
	}
	return status;
}

void menu::set_curser(char curser)
{
	_curser = curser;
}

bool menu::item_exists(std::string item)
{
	bool exists = false;
	for (unsigned int i = 0; i < menu_items.size(); i++)
	{
		if (menu_items[i] == item)
		{
			exists = true;
			break;
		}
	}
	return exists;
}

std::string menu::build_output()
{
	std::string output = "";
	for (unsigned int i = 0; i < menu_items.size(); i++)
	{
		if (curser_row == i)
		{
			output = output + _curser + " ";
		}
		else
		{
			output = output + "  ";
		}
		
		output = output + menu_items[i];

		if (i < (menu_items.size() - 1))
		{
			output = output + "\n";
		}
	}
	return output;
}

void menu::set_controls(int select, int up, int down, int quit)
{
	_select = select;
	_up = up;
	_down = down;
	_quit = quit;
}

void menu::enable_quit()
{
	quit_enabled = true;
}

std::string menu::get_selection()
{
	int input = 0;
	std::string selected_item = "";
	do
	{
		display();
		input = ascii_io::getchar();
		if (input == _select)
		{
			selected_item = menu_items[curser_row];
			break;
		}
		else if (input == _up)
		{
			if (curser_row > 0)
			{
				curser_row--;
			}
		}
		else if (input == _down)
		{
			if (curser_row < (menu_items.size() - 1))
			{
				curser_row++;
			}
		}
	} while ((input != _quit) || quit_enabled);
	return selected_item;
}

void menu::display()
{
	if (frame_stale())
	{
		sync();
		frame_display();
	}
	else
	{
		std::vector<std::string> lines = format_tools::get_lines(build_output());
		lines = format_tools::remove_newline_characters(lines);
		lines = format_tools::fill_lines(lines, get_width(), get_alignment());
		int x_origin = get_x_origin();
		int y_origin = get_y_origin();
		int curser_x = 0;
		int curser_y = 0;
		ascii_io::get_curser_position(curser_x, curser_y);
		for (unsigned int i = 0; i < lines.size(); i++)
		{
			ascii_io::move_curser_to_position(x_origin, y_origin + i);
			ascii_io::print(lines[i]);
		}
		ascii_io::move_curser_to_position(curser_x, curser_y);
	}
}

void menu::sync()
{
	set_output_to_frame(build_output());
}