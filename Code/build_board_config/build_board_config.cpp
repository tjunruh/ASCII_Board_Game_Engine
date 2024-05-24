#include "build_board_config.h"
#include "../board_config_field_titles/board_config_field_titles.h"

int build_board_config::get_rows(const std::string &board)
{
	int rows = 0;
	for (unsigned int i = 0; i < board.length(); i++)
	{
		if (board[i] == '\n')
		{
			rows++;
		}
	}
	return rows;
}

int build_board_config::get_columns(const std::string &board)
{
	int max_columns = 0;
	int columns = 0;
	for (unsigned int i = 0; i < board.length(); i++)
	{
		if (board[i] == '\n')
		{
			if (columns > max_columns)
			{
				max_columns = columns;
			}
			columns = 0;
		}
		else
		{
			columns++;
		}
	}
	return max_columns;
}

int build_board_config::get_digits(int number)
{
	int digits = 0;
	if (number == 0)
	{
		digits = 1;
	}
	else
	{
		while (number != 0)
		{
			number = number / 10;
			digits++;
		}
	}
	
	return digits;
}

std::string build_board_config::get_digit(int number, int digit)
{
	std::string text_number = std::to_string(number);
	std::string return_digit = " ";
	if ((digit < (int)text_number.length()) && (digit >= 0))
	{
		return_digit = text_number[digit];
	}
	return return_digit;
}

std::string build_board_config::get_line(const std::string &content, int line_number)
{
	std::string line = "";
	int current_line_number = 0;
	for (unsigned int i = 0; i < content.length(); i++)
	{
		if (current_line_number == line_number)
		{
			line = line + content[i];
		}

		if (content[i] == '\n')
		{
			current_line_number++;
			if (current_line_number > line_number)
			{
				break;
			}
		}
	}
	return line;
}

std::string build_board_config::modify_content(const std::string &content)
{
	int rows = get_rows(content);
	int columns = get_columns(content);
	int horizontal_index_space = get_digits(rows);
	int vertical_index_space = get_digits(columns);
	int horizontal_margin_length = horizontal_index_space + 1;
	int vertical_margin_length = vertical_index_space;

	int total_rows_with_margin = rows + vertical_margin_length;
	std::string horizontal_margin = "";
	for (int i = 0; i < horizontal_margin_length; i++)
	{
		horizontal_margin = horizontal_margin + " ";
	}

	std::string modified_content = "";
	modified_content = modified_content + board_config_field_titles::board_begin + "\n";

	for (int i = 0; i <= total_rows_with_margin; i++)
	{
		if (i < vertical_margin_length)
		{
			modified_content = modified_content + horizontal_margin;
			for (int j = 0; j < columns; j++)
			{
				modified_content = modified_content + get_digit(j, (i + get_digits(j) - vertical_index_space));
			}
			modified_content = modified_content + "\n";
		}
		else
		{
			for (int j = 0; j < horizontal_margin_length; j++)
			{
				modified_content = modified_content + get_digit((i - vertical_margin_length), (j + get_digits(i - vertical_margin_length) - horizontal_index_space));
			}
			modified_content = modified_content + get_line(content, i - vertical_margin_length);
		}
	}

	modified_content = modified_content + "\n";
	modified_content = modified_content + board_config_field_titles::board_end + "\n\n\n";
	modified_content = modified_content + board_config_field_titles::array_dimensions_field;
	modified_content = modified_content + board_config_field_titles::array_dimensions_begin + "\n";
	modified_content = modified_content + board_config_field_titles::array_dimensions_initialization;
	modified_content = modified_content + board_config_field_titles::array_dimensions_end + "\n\n\n";
	modified_content = modified_content + board_config_field_titles::action_tile_field;
	modified_content = modified_content + board_config_field_titles::action_tiles_begin + "\n";
	modified_content = modified_content + board_config_field_titles::action_tile_initialization;
	modified_content = modified_content + board_config_field_titles::action_tiles_end + "\n\n\n";

	return modified_content;
}