#pragma once

#include <string>

class build_map_config 
{
public:
	int write_file(std::string file_path, std::string content);
	int read_file(std::string file_path, std::string& extracted_content);
	std::string modify_content(std::string content);
	std::string extract_path(std::string path_with_file);
	std::string extract_file(std::string path_with_file);
	std::string remove_extension(std::string path_with_extension);
	
private:
	int get_rows(std::string board);
	int get_columns(std::string board);
	int get_digits(int number);
	std::string get_digit(int number, int digit);
	std::string get_line(std::string content, int line_number);
#ifdef _WIN32
	char path_seperator = '\\';
#elif __linux__
	char path_seperator = '/';
#endif
	std::string map_array_dimension_field = "** Define Dimensions of 2D Array Containing Action Tiles (Rows, Columns) **\n(,)\n";
	std::string map_action_tile_field = "** Define Actions Tiles (Map Row Range, Map Column Range, Array Row, Array Column) **\n(,,,)\n  .\n  .\n  .\n";

};
