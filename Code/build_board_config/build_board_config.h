#pragma once

#include <string>

class build_board_config 
{
public:
	std::string modify_content(const std::string &content);
	
private:
	int get_rows(const std::string &board);
	int get_columns(const std::string &board);
	int get_digits(int number);
	std::string get_digit(int number, int digit);
	std::string get_line(const std::string &content, int line_number);
};
