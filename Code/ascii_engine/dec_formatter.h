#pragma once
#include <string>
#include <vector>
#include "format_tools.h"

#ifdef _WIN32
#ifdef DEC_FORMATTER_EXPORTS
#define DEC_FORMATTER_API __declspec(dllexport)
#else
#define DEC_FORMATTER_API __declspec(dllimport)
#endif
#elif __linux__
#define DEC_FORMATTER_API
#endif

class dec_formatter
{
public:
	void set_format_chars(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char);
	std::vector<format_tools::index_format> format(std::string& format_content, unsigned int line_length=0);
	void get_format_chars(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char);
	char get_endpoint_char();
	void use_light_formatting(bool light_formatting);
#ifdef __linux__
	void print_dec_string(const std::string& input);
#endif
	const char bottom_right_corner = 'j';
	const char top_right_corner = 'k';
	const char top_left_corner = 'l';
	const char bottom_left_corner = 'm';
	const char intersection = 'n';
	const char horizontal_line = 'q';
	const char right_facing_intersection = 't';
	const char left_facing_intersection = 'u';
	const char up_facing_intersection = 'v';
	const char down_facing_intersection = 'w';
	const char vertical_line = 'x';

private:
	char determine_dec_character(char top, char bottom, char left, char right, char center);
#ifdef __linux__
	int get_dec_ncurses_code(char character);
#endif
	char _horizontal_char = '-';
	char _vertical_char = '|';
	char _intersection_char = '+';
	char _endpoint_char = '.';
	bool _use_light_formatting = false;
	std::vector<char> dec_trigger_characters =
	{
		_horizontal_char,
		_vertical_char,
		_intersection_char,
		_endpoint_char
	};

	std::vector<char> dec_horizontal_trigger_characters =
	{
		_horizontal_char,
		_intersection_char,
		_endpoint_char
	};

	std::vector<char> dec_vertical_trigger_characters =
	{
		_vertical_char,
		_intersection_char,
		_endpoint_char
	};

	const std::vector<char> dec_characters =
	{
		bottom_right_corner,
		top_right_corner,
		top_left_corner,
		bottom_left_corner,
		intersection,
		horizontal_line,
		right_facing_intersection,
		left_facing_intersection,
		up_facing_intersection,
		down_facing_intersection,
		vertical_line
	};
};