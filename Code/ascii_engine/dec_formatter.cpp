#include "../ascii_engine_dll_files/pch.h"
#include "dec_formatter.h"

#ifdef __linux__
#include <algorithm>
#include <ncurses.h>
#endif

void dec_formatter::set_format_chars(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char)
{
	_horizontal_char = horizontal_char;
	_vertical_char = vertical_char;
	_intersection_char = intersection_char;
	_endpoint_char = endpoint_char;

	dec_trigger_characters =
	{
		_horizontal_char,
		_vertical_char,
		_intersection_char,
		_endpoint_char
	};

	dec_horizontal_trigger_characters =
	{
		_horizontal_char,
		_intersection_char,
		_endpoint_char
	};

	dec_vertical_trigger_characters =
	{
		_vertical_char,
		_intersection_char,
		_endpoint_char
	};
}

std::vector<format_tools::index_format> dec_formatter::format(std::string& format_content, unsigned int line_length)
{
	std::vector<std::string> format_lines;
	if (line_length == 0)
	{
		format_lines = format_tools::get_lines(format_content);
	}
	else
	{
		format_lines = format_tools::get_lines(format_content, line_length);
	}
	
	format_tools::index_format dec_or_ascii_region;
	if (format_content.length() > 0)
	{
		if (std::count(dec_trigger_characters.begin(), dec_trigger_characters.end(), format_content[0]) != 0)
		{
			dec_or_ascii_region.format.dec = true;
		}
		else
		{
			dec_or_ascii_region.format.dec = false;
		}
	}
	dec_or_ascii_region.index = 0;
	std::vector<format_tools::index_format> regions;
	int index = 0;
	for (unsigned int i = 0; i < format_lines.size(); i++)
	{
		for (unsigned int j = 0; j < format_lines[i].length(); j++)
		{
			if (std::count(dec_trigger_characters.begin(), dec_trigger_characters.end(), (format_lines[i])[j]) != 0)
			{
				char top = '\0';
				char bottom = '\0';
				char right = '\0';
				char left = '\0';
				if (((int)i - 1) >= 0)
				{
					if (j < format_lines[(int)i - 1].length())
					{
						top = (format_lines[(int)i - 1])[j];
					}
				}

				if ((i + 1) < format_lines.size())
				{
					if (j < format_lines[i + 1].length())
					{
						bottom = (format_lines[i + 1])[j];
					}
				}

				if ((j + 1) < format_lines[i].length())
				{
					right = (format_lines[i])[j + 1];
				}

				if (((int)j - 1) >= 0)
				{
					left = (format_lines[i])[(int)j - 1];
				}

				char character = determine_dec_character(top, bottom, left, right, (format_lines[i])[j]);
				if (std::count(dec_characters.begin(), dec_characters.end(), character) != 0)
				{
					format_content[index] = character;
					if (!dec_or_ascii_region.format.dec)
					{
						regions.push_back(dec_or_ascii_region);
						dec_or_ascii_region.format.dec = true;
						dec_or_ascii_region.index = index;
					}
				}
			}
			else
			{
				if (dec_or_ascii_region.format.dec)
				{
					regions.push_back(dec_or_ascii_region);
					dec_or_ascii_region.index = index;
					dec_or_ascii_region.format.dec = false;
				}
			}
			index++;
		}
	}

	if (dec_or_ascii_region.index != -1)
	{
		regions.push_back(dec_or_ascii_region);
	}

	return regions;
}

char dec_formatter::determine_dec_character(char top, char bottom, char left, char right, char center)
{
	int defined_count = 0;
	char character = ' ';
	if ((top == _vertical_char) || ((center == _vertical_char) && (std::count(dec_vertical_trigger_characters.begin(), dec_vertical_trigger_characters.end(), top) != 0)))
	{
		defined_count++;
	}

	if ((bottom == _vertical_char) || ((center == _vertical_char) && (std::count(dec_vertical_trigger_characters.begin(), dec_vertical_trigger_characters.end(), bottom) != 0)))
	{
		defined_count++;
	}

	if ((right == _horizontal_char) || ((center == _horizontal_char) && (std::count(dec_horizontal_trigger_characters.begin(), dec_horizontal_trigger_characters.end(), right) != 0)))
	{
		defined_count++;
	}

	if ((left == _horizontal_char) || ((center == _horizontal_char) && (std::count(dec_horizontal_trigger_characters.begin(), dec_horizontal_trigger_characters.end(), left) != 0)))
	{
		defined_count++;
	}

	if (defined_count == 2)
	{
		if ((top == _vertical_char) && (right == _horizontal_char))
		{
			character = bottom_left_corner;
		}
		else if ((top == _vertical_char) && (left == _horizontal_char))
		{
			character = bottom_right_corner;
		}
		else if ((bottom == _vertical_char) && (right == _horizontal_char))
		{
			character = top_left_corner;
		}
		else if ((bottom == _vertical_char) && (left == _horizontal_char))
		{
			character = top_right_corner;
		}
		else if ((std::count(dec_vertical_trigger_characters.begin(), dec_vertical_trigger_characters.end(), top) != 0) && (std::count(dec_vertical_trigger_characters.begin(), dec_vertical_trigger_characters.end(), bottom) != 0))
		{
			character = vertical_line;
		}
		else if ((std::count(dec_horizontal_trigger_characters.begin(), dec_horizontal_trigger_characters.end(), right) != 0) && (std::count(dec_horizontal_trigger_characters.begin(), dec_horizontal_trigger_characters.end(), left) != 0))
		{
			character = horizontal_line;
		}
	}
	else if (defined_count == 3)
	{
		if ((top == _vertical_char) && (bottom == _vertical_char) && (right == _horizontal_char))
		{
			character = right_facing_intersection;
		}
		else if ((top == _vertical_char) && (bottom == _vertical_char) && (left == _horizontal_char))
		{
			character = left_facing_intersection;
		}
		else if ((right == _horizontal_char) && (left == _horizontal_char) && (top == _vertical_char))
		{
			character = up_facing_intersection;
		}
		else if ((right == _horizontal_char) && (left == _horizontal_char) && (bottom == _vertical_char))
		{
			character = down_facing_intersection;
		}
	}
	else if (defined_count == 4)
	{
		character = intersection;
	}

	return character;
}

void dec_formatter::get_format_chars(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char)
{
	horizontal_char = _horizontal_char;
	vertical_char = _vertical_char;
	intersection_char = _intersection_char;
	endpoint_char = _endpoint_char;
}

char dec_formatter::get_endpoint_char()
{
	return _endpoint_char;
}

#ifdef __linux__
int dec_formatter::get_dec_ncurses_code(char character)
{
	int code = 0;
	if (character == bottom_right_corner)
	{
		code = ACS_LRCORNER;
	}
	else if (character == top_right_corner)
	{
		code = ACS_URCORNER;
	}
	else if (character == top_left_corner)
	{
		code = ACS_ULCORNER;
	}
	else if (character == bottom_left_corner)
	{
		code = ACS_LLCORNER;
	}
	else if (character == horizontal_line)
	{
		code = ACS_HLINE;
	}
	else if (character == intersection)
	{
		code = ACS_PLUS;
	}
	else if (character == right_facing_intersection)
	{
		code = ACS_LTEE;
	}
	else if (character == left_facing_intersection)
	{
		code = ACS_RTEE;
	}
	else if (character == up_facing_intersection)
	{
		code = ACS_BTEE;
	}
	else if (character == down_facing_intersection)
	{
		code = ACS_TTEE;
	}
	else if (character == vertical_line)
	{
		code = ACS_VLINE;
	}
	else
	{
		code = int(character);
	}

	return code;
}

void dec_formatter::print_dec_string(const std::string& input)
{
	for(unsigned int i = 0; i < input.length(); i++)
	{
		addch(get_dec_ncurses_code(input[i]));
	}
}

#endif