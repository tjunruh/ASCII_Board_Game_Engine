#pragma once
#include <string>
#include <vector>
#include "widget.h"
#include "frame.h"

#ifdef _WIN32
#ifdef MENU_EXPORTS
#define MENU_API __declspec(dllexport)
#else
#define MENU_API __declspec(dllimport)
#endif
#elif __linux__
#define MENU_API
#endif

class menu : public widget
{
public:
	MENU_API menu(frame* parent, std::string special_operation="none", bool start_logging=false, std::string logging_file_path="menu.log");
	MENU_API int append_item(std::string item);
	MENU_API void set_cursor(char cursor);
	MENU_API void set_controls(int select, int up, int down, int quit);
	MENU_API void get_controls(int& select, int& up, int& down, int& quit);
	MENU_API std::string get_selection();
	MENU_API void enable_quit();
	MENU_API void disable_quit();
	MENU_API void display();
	MENU_API void sync();
private:
	std::vector<std::string> menu_items;
	char _cursor = '*';
	unsigned int cursor_row = 0;
	int _select = ascii_io::enter;
	int _up = ascii_io::up;
	int _down = ascii_io::down;
	int _quit = ascii_io::q;
	bool quit_enabled = false;
	std::string build_output();
	bool item_exists(std::string item);
};