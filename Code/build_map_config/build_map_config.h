#pragma once

#include <string>

class build_map_config 
{
public:
	std::string modify_content(std::string content);
	
private:
	int get_rows(std::string board);
	int get_columns(std::string board);
	int get_digits(int number);
	std::string get_digit(int number, int digit);
	std::string get_line(std::string content, int line_number);
};
