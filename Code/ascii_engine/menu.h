#pragma once
#include <string>
#include <vector>
#include "widget.h"
#include "frame.h"
#include "controls.h"

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
	struct item_structure
	{
		std::string item = "";
		std::vector<std::string> labels;
	};
	MENU_API menu(frame* parent, const std::string& special_operation="none", int lines_count=0, bool start_logging=false, const std::string& logging_file_path="menu.log");
	MENU_API int append_item(const std::string& item);
	MENU_API int remove_item(const std::string& item);
	MENU_API void remove_all_items();
	MENU_API void set_lines_count(int lines_count);
	MENU_API int append_item_label(const std::string& item, const std::string& label);
	MENU_API int set_item_label(const std::string& item, unsigned int column, const std::string& label);
	MENU_API void use_top_row_as_heading(bool heading);
	MENU_API void set_cursor(char cursor);
	MENU_API char get_cursor();
	MENU_API void set_cursor_index(unsigned int index);
	MENU_API unsigned int get_cursor_index();
	MENU_API item_structure get_cursor_item_data();
	MENU_API int get_item_label(const std::string& item, unsigned int column, std::string& label);
	MENU_API void set_controls(std::vector<int> select, int up, int down, int left, int right, int quit);
	MENU_API void set_controls(controls* centralized_controls);
	MENU_API void get_controls(std::vector<int>& select, int& up, int& down, int& left, int& right, int& quit);
	MENU_API void set_separater_characters(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char);
	MENU_API void get_separater_characters(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char);
	MENU_API void get_selection(std::string& selection, int& key_stroke);
	MENU_API void enable_quit(bool enable);
	MENU_API void display();
	MENU_API void build();
	MENU_API void separate_items(bool separate);
	MENU_API std::vector<item_structure> get_menu_item_data();
private:
	std::vector<item_structure> menu_items;
	char _cursor = '*';
	unsigned int _cursor_index = 0;
	unsigned int last_cursor_item = 0;
	unsigned int last_cursor_line_remainder = 0;
	std::vector<int> _select =
	{
		ascii_io::enter
	};
	int _up = ascii_io::up;
	int _down = ascii_io::down;
	int _left = ascii_io::left;
	int _right = ascii_io::right;
	int _quit = ascii_io::q;
	bool quit_enabled = false;
	unsigned int non_separated_lines_count = 0;
	char _horizontal_char = '-';
	char _vertical_char = '|';
	char _intersection_char = '+';
	char _endpoint_char = '.';
	bool _heading = false;
	controls* _centralized_controls = nullptr;
	std::string build_output();
	bool item_exists(const std::string& item);
	bool label_exists();
	unsigned int get_longest_item_length();
	std::vector<unsigned int> get_longest_label_lengths();
	unsigned int get_stop_index(unsigned int top_index, unsigned int displayed_items);
	void set_cursor_line(unsigned int line);
	unsigned int bound_cursor_index(unsigned int cursor_index, unsigned int top_index, unsigned int stop_index);
	unsigned int fit_displayed_lines_for_separated_items(unsigned int displayed_lines);
};
