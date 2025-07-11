#pragma once

#include <string>
#include <vector>

namespace validate_board_config
{
	struct row_column
	{
		std::string row;
		std::string column;

		bool operator==(const row_column& comparison)
		{
			return (row == comparison.row && column == comparison.column);
		}
	};
	int validate(const std::string& content, std::string& debug_log);
	int validate_enclosing_characters(const std::string& content, int& error_line, std::string& error_line_content, char begin_character, char end_character);
	int validate_number_of_parameters(const std::string& content, int number_of_parameters, int& error_line, std::string& error_line_content);
	int validate_parameters(const std::string& content, bool action_tile_field, int& error_line, std::string& error_line_content);
	int validate_hyphen_range(const std::string& content, int& error_line, std::string& error_line_content);
	bool is_integer(const std::string& number_string);
	bool is_float(const std::string& number_string);
	bool is_string(const std::string& string_string);
	int validate_board_begin(const std::string &content);
	int validate_board_end(const std::string &content);
	int validate_array_dimensions_begin(const std::string &content);
	int validate_array_dimensions_end(const std::string &content);
	int validate_action_tiles_begin(const std::string &content);
	int validate_action_tiles_end(const std::string &content);
	int validate_metadata_begin(const std::string& content);
	int validate_metadata_end(const std::string& content);
	int validate_line_length(const std::string& content, int& error_line, std::string& error_line_content);
	int validate_array_index(const std::string &content, int max_row, int max_column, int& error_line, std::string& error_line_content);
	int validate_board_index(const std::string &content, int max_row, int max_column, int& error_line, std::string& error_line_content);
	int validate_metadata_parameters(const std::string& content, int& error_line, std::string& error_line_content);
	void get_board_dimensions(const std::string &content, int& row, int& column);
	bool multiple(std::vector<row_column> storage, row_column element);
	bool uniform(std::vector<row_column> storage);
	int get_rows(const std::string &content);
	int get_columns(const std::string &content);
};