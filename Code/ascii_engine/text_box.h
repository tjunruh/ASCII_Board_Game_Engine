#pragma once
#include <string>
#include <vector>
#include "frame.h"
#include "widget.h"
#include "format_tools.h"

#ifdef _WIN32
#ifdef TEXT_BOX_EXPORTS
#define TEXT_BOX_API __declspec(dllexport)
#else
#define TEXT_BOX_API __declspec(dllimport)
#endif
#elif __linux__
#define TEXT_BOX_API
#endif

class text_box : public widget
{
public:
	TEXT_BOX_API text_box(frame* parent, std::string special_operation = "none", unsigned int lines_count = 1, bool start_logging = false, std::string logging_file_path="text_box.log");
	TEXT_BOX_API unsigned int write();
	TEXT_BOX_API void set_max_characters(int characters);
	TEXT_BOX_API void clear();
	TEXT_BOX_API std::string get_text();
	TEXT_BOX_API void set_lines_count(unsigned int lines_count);
private:
	bool cursor_on_top_border();
	bool cursor_on_bottom_border();
	void display();
	unsigned int get_linear_cursor_position();
	void get_two_dimensional_cursor_position(unsigned int linear_position, int& x, int& y);
	unsigned int get_cursor_line();
	unsigned int get_cursor_column();
	unsigned int get_line_of_position(unsigned int position);
	void move_cursor_to_linear_position(unsigned int position);
	void fit_cursor_to_line();
	int x_origin = 0;
	int y_origin = 0;
	unsigned int saved_cursor_linear_position = 0;
	int max_characters = -1;
};

