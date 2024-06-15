#pragma once
#include <string>
#include <vector>
#include "widget.h"
#include "frame.h"

class menu : public widget
{
public:
	menu(frame* parent);
	int append_item(std::string item);
	void set_curser(char curser);
	void set_controls(int select, int up, int down, int quit);
	std::string get_selection();
	void enable_quit();
private:
	
	std::vector<std::string> menu_items;
	char _curser = '*';
	unsigned int curser_row = 0;
	int _select = ascii_io::enter;
	int _up = ascii_io::up;
	int _down = ascii_io::down;
	int _quit = ascii_io::q;
	bool quit_enabled = false;
	std::string build_output();
	bool item_exists(std::string item);
};