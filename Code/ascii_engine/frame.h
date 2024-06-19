#pragma once
#include <string>
#include <vector>
#include "ascii_io.h"
#include "widget_types.h"
#include "console.h"

class frame
{
public:
	friend class widget;
	frame(console* parent, int number_of_rows, int number_of_columns);
	unsigned int get_column_size(unsigned int column);
	int set_column_size(unsigned int column, unsigned int spacing);
	void display();
	void set_controls(int select, int quit, int up, int down, int right, int left);
	int get_selection();
private:
	struct widget_info
	{
		int id = -1;
		std::string output;
		int row = 0;
		int column = 0;
		std::string allignment = "left";
		int top_spacing = 0;
		int bottom_spacing = 0;
		int right_spacing = 0;
		int left_spacing = 0;
		bool add_border = false;
		char vertical_border = '|';
		char horizontal_border = '-';
		char corner_border = '.';
		int widget_type = WIDGET;
	};

	const std::string right_allignment_keyword = "right";
	const std::string left_allignment_keyword = "left";
	const std::string center_allignment_keyword = "center";
	int add_widget();
	int set_position(int id, int row, int column);
	int set_output(int id, const std::string& output);
	int set_allignment(int id, std::string allignment);
	int set_spacing(int id, int top, int bottom, int right, int left);
	int set_widget_type(int id, int type);
	int set_vertical_border(int id, char border);
	int set_horizontal_border(int id, char border);
	int set_corner_border(int id, char border);
	int add_border(int id);
	bool widget_exists(int id);
	int generate_widget_id();
	std::vector<int> get_row_ids(int row);
	std::vector<int> sort_row_ids(std::vector<int> ids);
	int get_min_id_index(std::vector<int> ids);
	bool in_range(int value, int begin, int end);
	std::string get_output(int id);
	int get_widget(int id, widget_info& return_value);
	int get_widget(int row, int column, widget_info& return_value);
	unsigned int get_widget_width(const widget_info& item);
	std::vector<std::string> get_widget_lines(int id);
	std::vector<std::string> split_string(std::string str, char split_character);
	std::string get_spacing(unsigned int length, char space_char);
	std::string fill_line(std::string input, unsigned int length, std::string allignment);
	std::vector<std::string> add_lines(std::vector<std::string> lines, unsigned int number_of_added_lines, unsigned int line_length);
	std::string fuse_columns_into_row(std::vector<std::vector<std::string>> columns_content);
	void cut_word(const std::string& word, unsigned int length, std::string& first_section, std::string& second_section);
	void update();

	struct lane
	{
		unsigned int size;
		unsigned int index;
	};

	int total_rows = 0;
	int total_columns = 0;
	std::string frame_output;

	std::vector<widget_info> widgets;
	std::vector<lane> columns;
	int _select = ascii_io::enter;
	int _up = ascii_io::up;
	int _down = ascii_io::down;
	int _right = ascii_io::right;
	int _left = ascii_io::left;
	int _quit = ascii_io::q;
	int frame_id;
	console* parent_console;
};