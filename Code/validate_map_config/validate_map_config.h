#pragma once

#include <string>
#include <vector>

class validate_map_config
{
public:
	int validate(std::string content, bool debug);
	std::string get_map_dimension_field(std::string content);
	std::string get_map_action_tiles_field(std::string content);
	std::string get_map(std::string content);
	std::string remove_spaces(std::string content);
	void get_array_dimensions(std::string content, int& row, int& column);

private:
	struct row_column
	{
		std::string row;
		std::string column;
	};
	int validate_parenthesis(std::string content);
	int validate_parameters(std::string content, bool action_tile_field);
	int validate_number_of_parameters(std::string content, int number_of_parameters);
	int validate_array_index(std::string content, int max_row, int max_column);
	int validate_map_index(std::string content, int max_row, int max_column);
	int validate_number_of_entries(std::string content, int number_of_entries);
	int validate_hyphen_range(std::string content);
	void get_map_dimensions(std::string content, int& row, int& column);
	int get_map_boundary_row(std::string content);
	int get_map_boundary_column(std::string content);
	int get_map_end_index(std::string content);
	int char_to_int(char character);
	int find_element(std::vector<int> storage, int element);
	bool multiple(std::vector<row_column> storage, row_column element);
	bool is_number(std::string number_string);
	int get_rows(std::string content);
	int get_columns(std::string content);
};