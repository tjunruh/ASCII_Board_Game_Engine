#pragma once
#include <string>
#include <vector>

#ifdef _WIN32
#ifdef BOARD_CONFIG_FIELD_PARSER_EXPORT
#define BOARD_CONFIG_FIELD_PARSER_API __declspec(dllexport)
#else
#define BOARD_CONFIG_FIELD_PARSER_API __declspec(dllimport)
#endif
#endif

class board_config_field_parser
{
public:
	std::string get_dimension_field(const std::string &content);
	std::string get_action_tiles_field(const std::string &content);
	std::string get_board(const std::string &content);
	std::string remove_spaces(const std::string &content);
	void get_array_dimensions(const std::string &content, int& row, int& column);

private:
	int get_board_boundary_row(const std::string &content);
	int get_board_boundary_column(const std::string &content);
	int get_board_end_index(const std::string &content);
	int char_to_int(char character);
	bool is_number(const std::string &number_string);
	int find_element(std::vector<int> storage, int element);
};