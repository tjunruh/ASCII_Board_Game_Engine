#pragma once
#include <string>
#include <vector>
#include "ascii_io.h"
#include "widget_types.h"

class frame
{
public:
	friend class widget;
	frame();
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
		bool highlight = false;
		char highlight_character = '#';
		char vertical_border = '|';
		char horizontal_border = '-';
		char corner_border = '.';
		int widget_type = WIDGET;
		int level = 0;
	};

	const std::string right_allignment_keyword = "right";
	const std::string left_allignment_keyword = "left";
	const std::string center_allignment_keyword = "center";
	const std::string special_operation_new_line = "new line";
	const std::string special_operation_merge = "merge";
	const std::string special_operation_none = "none";
	int add_widget();
	int set_position(int id, int row, int column, int level);
	int append(int id, std::string special_operation="none");
	int set_output(int id, const std::string& output);
	int set_allignment(int id, std::string allignment);
	int set_spacing(int id, int top, int bottom, int right, int left);
	int set_widget_type(int id, int type);
	int set_vertical_border(int id, char border);
	int set_horizontal_border(int id, char border);
	int set_corner_border(int id, char border);
	int set_highlight_character(int id, char character);
	int add_border(int id);
	int highlight(int row, int column, int level);
	bool widget_exists(int id);
	bool widget_exists(int row, int column);
	int get_levels(int row, int column);
	int generate_widget_id();
	std::vector<int> get_row_ids(int row);
	std::vector<std::vector<int>> sort_row_ids(std::vector<int> ids);
	int get_min_column_index(const std::vector<widget_info>& widget_vec);
	int get_min_level_index(const std::vector<widget_info>& widget_vec);
	bool in_range(int value, int begin, int end);
	std::string get_output(int id);
	int get_widget(int id, widget_info& return_value);
	int get_widget(int row, int column, int level, widget_info& return_value);
	unsigned int get_widget_width(const widget_info& item, bool include_spacing);
	std::vector<std::string> get_widget_lines(int id);
	std::vector<std::string> split_string(std::string str, char split_character);
	std::string get_spacing(unsigned int length, char space_char);
	std::string fill_line(std::string input, unsigned int length, std::string allignment);
	std::vector<std::string> add_lines(std::vector<std::string> lines, unsigned int number_of_added_lines, unsigned int line_length);
	std::string fuse_columns_into_row(std::vector<std::vector<std::string>> columns_content, unsigned int widget_width_with_spacing);
	void cut_word(const std::string& word, unsigned int length, std::string& first_section, std::string& second_section);
	bool element_exists(const std::vector<int>& storage, int element);
	unsigned int get_total_rows();
	unsigned int get_columns_in_row(int row);
	std::string get_frame_output();
	std::vector<std::string> get_lines(const std::string& output_string);
	std::vector<std::string> remove_trailing_whitespace(const std::vector<std::string>& lines);
	void mask_output(std::string& output, const std::string& old_output);

	std::vector<widget_info> widgets;
	int _select = ascii_io::enter;
	int _up = ascii_io::up;
	int _down = ascii_io::down;
	int _right = ascii_io::right;
	int _left = ascii_io::left;
	int _quit = ascii_io::q;
	int frame_id;
	int append_row = 0;
	int append_column = -1;
	int append_level = 0;
	const std::vector<int> selectable_widgets = { MENU, BOARD };
#ifdef WIN32
	std::string previous_output = "";
	int previous_x = 0;
	int previous_y = 0;
#endif
};