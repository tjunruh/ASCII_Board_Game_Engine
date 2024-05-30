#pragma once
#include "console.h"
#include <string>
#include <vector>

class frame
{
public:
	void set_rows(unsigned int number_of_rows);
	void set_columns(unsigned int number_of_columns);
	unsigned int get_column_size(unsigned int column);
	int set_column_size(unsigned int column, unsigned int spacing);

private:
	struct widget
	{
		int id;
		std::string output;
		int row = 0;
		int column = 0;
		std::string allignment = "none";
		int top_spacing = 0;
		int bottom_spacing = 0;
		int right_spacing = 0;
		int left_spacing = 0;
	};

	const std::string right_allignment_keyword = "right";
	const std::string left_allignment_keyword = "left";
	const std::string center_allignment_keyword = "center";

	int add_widget();
	int set_position(int id, int row, int column);
	int set_output(int id, const std::string& output);
	int set_allignment(int id, std::string allignment);
	int set_spacing(int id, int top, int bottom, int right, int left);
	bool widget_exists(int id);
	int generate_widget_id();
	std::string format_row(int row);
	std::vector<int> get_row_ids(int row);
	std::vector<int> sort_row_ids(std::vector<int> ids);
	int get_min_id_index(std::vector<int> ids);
	bool in_range(int value, int begin, int end);
	std::string get_output(int id);
	int get_widget(int id, widget& return_value);
	std::vector<std::string> get_widget_lines(int id);
	std::vector<std::string> split_string(std::string str, char split_character);
	std::string get_spacing(unsigned int length);
	std::string fill_line(std::string input, unsigned int length, std::string allignment);
	std::vector<std::string> add_lines(std::vector<std::string> lines, unsigned int number_of_added_lines, unsigned int line_length);
	std::string fuse_columns_into_row(std::vector<std::vector<std::string>> columns_content);
	void update();

	struct lane
	{
		unsigned int size;
		unsigned int index;
	};

	int total_rows;
	int total_columns;
	std::string frame_output;

	std::vector<widget> widgets;
	std::vector<lane> columns;
};