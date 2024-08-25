#pragma once

#include <string>
#include <vector>

#ifdef _WIN32
#ifdef VALIDATE_BOARD_CONFIG_EXPORTS
#define VALIDATE_BOARD_CONFIG_API __declspec(dllexport)
#else
#define VALIDATE_BOARD_CONFIG_API __declspec(dllimport)
#endif
#endif

class validate_board_config
{
public:
	int validate(const std::string& content, std::string& debug_log);

private:
	struct row_column
	{
		std::string row;
		std::string column;
	};
	int validate_board_begin(const std::string &content);
	int validate_board_end(const std::string &content);
	int validate_array_dimensions_begin(const std::string &content);
	int validate_array_dimensions_end(const std::string &content);
	int validate_action_tiles_begin(const std::string &content);
	int validate_action_tiles_end(const std::string &content);
	int validate_parenthesis(const std::string &content);
	int validate_parameters(const std::string &content, bool action_tile_field);
	int validate_number_of_parameters(const std::string &content, int number_of_parameters);
	int validate_array_index(const std::string &content, int max_row, int max_column);
	int validate_board_index(const std::string &content, int max_row, int max_column);
	int validate_number_of_entries(const std::string &content, int number_of_entries);
	int validate_hyphen_range(const std::string &content);
	void get_board_dimensions(const std::string &content, int& row, int& column);
	bool multiple(std::vector<row_column> storage, row_column element);
	bool is_number(const std::string &number_string);
	int get_rows(const std::string &content);
	int get_columns(const std::string &content);
};