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
	MENU_API menu(frame* parent, std::string special_operation="none", unsigned int lines_count=0, bool start_logging=false, std::string logging_file_path="menu.log");
	MENU_API int append_item(std::string item);
	MENU_API int remove_item(std::string item);
	MENU_API void remove_all_items();
	MENU_API void set_lines_count(unsigned int lines_count);
	MENU_API int set_item_label(std::string item, const std::string& label);
	MENU_API void set_cursor(char cursor);
	MENU_API char get_cursor();
	MENU_API void set_controls(std::vector<int> select, int up, int down, int quit);
	MENU_API void get_controls(std::vector<int>& select, int& up, int& down, int& quit);
	MENU_API void set_separater_characters(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char);
	MENU_API void get_separater_characters(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char);
	MENU_API void get_selection(std::string& selection, int& key_stroke);
	MENU_API void enable_quit();
	MENU_API void disable_quit();
	MENU_API void display();
	MENU_API void sync();
	MENU_API void separate_items(bool separate);
private:
	struct item_structure
	{
		std::string name_id = "";
		std::string label = "";
	};
	std::vector<item_structure> menu_items;
	char _cursor = '*';
	unsigned int cursor_line = 0;
	std::vector<int> _select =
	{
		ascii_io::enter
	};
	int _up = ascii_io::up;
	int _down = ascii_io::down;
	int _quit = ascii_io::q;
	bool quit_enabled = false;
	bool no_lines_constraint = false;
	unsigned int displayed_lines = 0;
	unsigned int top_line = 0;
	bool _separate_items = false;
	char _horizontal_char = '-';
	char _vertical_char = '|';
	char _intersection_char = '+';
	char _endpoint_char = '.';
	std::string build_output();
	bool item_exists(std::string item);
	bool label_exists();
	unsigned int get_longest_item_length();
	unsigned int get_longest_label_length();
};