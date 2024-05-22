#pragma once
#include <string>
#include <vector>

class board_config_field_parser
{
public:
	std::string get_dimension_field(std::string content);
	std::string get_action_tiles_field(std::string content);
	std::string get_board(std::string content);
	std::string remove_spaces(std::string content);
	void get_array_dimensions(std::string content, int& row, int& column);

private:
	int get_board_boundary_row(std::string content);
	int get_board_boundary_column(std::string content);
	int get_board_end_index(std::string content);
	int char_to_int(char character);
	bool is_number(std::string number_string);
	int find_element(std::vector<int> storage, int element);
};