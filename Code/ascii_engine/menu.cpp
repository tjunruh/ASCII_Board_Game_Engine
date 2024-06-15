#include "menu.h"
#include "widget_types.h"

menu::menu(frame* parent) : widget(parent)
{
	set_widget_type(MENU);
}

int menu::append_item(std::string item)
{
	int status = 1;
	if (!item_exists(item))
	{
		menu_items.push_back(item);
		status = 0;
		set_output(build_output());
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
		set_output(build_output());
		refresh();
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