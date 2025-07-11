#include "../ascii_engine_dll_files/pch.h"
#include "board_config_field_parser.h"
#include "../board_config_field_titles/board_config_field_titles.h"

std::string board_config_field_parser::get_dimension_field(const std::string &content)
{
	size_t start_position = content.find(board_config_field_titles::array_dimensions_begin) + board_config_field_titles::array_dimensions_begin.length();
	size_t stop_position = content.find(board_config_field_titles::array_dimensions_end);
	std::string dimension_field = "";
	for (unsigned int i = start_position; i < stop_position; i++)
	{
		dimension_field = dimension_field + content[i];
	}
	return dimension_field;
}

std::string board_config_field_parser::get_action_tiles_field(const std::string &content)
{
	size_t start_position = content.find(board_config_field_titles::action_tiles_begin) + board_config_field_titles::action_tiles_begin.length();
	size_t stop_position = content.find(board_config_field_titles::action_tiles_end);
	std::string action_tiles_field = "";
	for (unsigned int i = start_position; i < stop_position; i++)
	{
		action_tiles_field = action_tiles_field + content[i];
	}
	return action_tiles_field;
}

std::string board_config_field_parser::get_metadata_field(const std::string& content)
{
	size_t start_position = content.find(board_config_field_titles::metadata_begin) + board_config_field_titles::metadata_begin.length();
	size_t stop_position = content.find(board_config_field_titles::metadata_end);
	std::string metadata_field = "";
	for (unsigned int i = start_position; i < stop_position; i++)
	{
		metadata_field = metadata_field + content[i];
	}
	return metadata_field;
}

std::string board_config_field_parser::get_board(const std::string &content)
{
	int start_row = get_board_boundary_row(content);
	int start_column = get_board_boundary_column(content);
	int stop_index = get_board_end_index(content);
	int row = 0;
	int column = 0;
	std::string board = "";
	for (int i = 0; i < stop_index; i++)
	{
		if ((column > start_column) && (row > start_row))
		{
			board = board + content[i];
		}

		if (content[i] == '\n')
		{
			row++;
			column = 0;
		}
		else
		{
			column++;
		}
	}

	if (board.back() == '\n')
	{
		board.erase((board.length() - 1), 1);
	}

	return board;
}

std::string board_config_field_parser::remove_spaces(const std::string &content)
{
	std::string updated_content = "";
	for (unsigned int i = 0; i < content.length(); i++)
	{
		if (content[i] != ' ')
		{
			updated_content = updated_content + content[i];
		}
	}
	return updated_content;
}

void board_config_field_parser::get_array_dimensions(const std::string &content, int& row, int& column)
{
	int parameter = -1;
	std::string parsed_row = "";
	std::string parsed_column = "";
	for (unsigned int i = 0; i < content.length(); i++)
	{
		if ((parameter == 0) && isdigit(content[i]))
		{
			parsed_row = parsed_row + content[i];
		}
		else if ((parameter == 1) && isdigit(content[i]))
		{
			parsed_column = parsed_column + content[i];
		}

		if (content[i] == '(')
		{
			parameter = 0;
		}
		else if (content[i] == ',')
		{
			parameter++;
		}
	}

	if (is_number(parsed_row))
	{
		row = stoi(parsed_row);
	}
	else
	{
		row = -1;
	}

	if (is_number(parsed_column))
	{
		column = stoi(parsed_column);
	}
	else
	{
		column = -1;
	}
}

int board_config_field_parser::get_board_boundary_row(const std::string &content)
{
	int row = -1;
	char previous_character = ' ';
	bool boundary_row = true;
	std::string row_content = "";
	for (unsigned int i = 0; i < content.length(); i++)
	{
		row_content = row_content + content[i];
		if (content[i] == '\n')
		{
			row++;
			if (boundary_row)
			{
				break;
			}
			else
			{
				boundary_row = true;
			}
			row_content = "";
		}
		else
		{
			if (isdigit(content[i]) && isdigit(previous_character))
			{
				if (!(((char_to_int(content[i]) - 1) == char_to_int(previous_character)) || ((content[i] == '0') && (previous_character == '9'))))
				{
					boundary_row = false;
				}
			}
			else if (!(((content[i] == ' ') && (previous_character == ' ')) || ((content[i] == ' ') && (previous_character == '\n')) || (isdigit(content[i]) && (previous_character == ' '))))
			{
				boundary_row = false;
			}
		}
		previous_character = content[i];
	}

	if (!boundary_row)
	{
		row = -1;
	}

	return row;
}

int board_config_field_parser::get_board_boundary_column(const std::string &content)
{
	size_t start_position = content.find(board_config_field_titles::board_begin) + board_config_field_titles::board_begin.length() + 1;
	size_t stop_position = content.find(board_config_field_titles::board_end);

	int column = 0;
	std::vector<int> valid_columns;
	std::vector<int> invalid_columns;
	for (unsigned int i = start_position; i < stop_position; i++)
	{
		if (content[i] == ' ')
		{
			if ((find_element(invalid_columns, column) == -1) && (find_element(valid_columns, column) == -1))
			{
				valid_columns.push_back(column);
			}
		}
		else
		{
			int valid_index = find_element(valid_columns, column);
			int invalid_index = find_element(invalid_columns, column);
			if (invalid_index == -1)
			{
				invalid_columns.push_back(column);
			}

			if (valid_index != -1)
			{
				valid_columns.erase(valid_columns.begin() + valid_index);
			}
		}

		column++;

		if (content[i] == '\n')
		{
			column = 0;
		}
	}

	int valid_column = -1;
	if (valid_columns.size() > 0)
	{
		valid_column = valid_columns[0];
		for (unsigned int i = 0; i < valid_columns.size(); i++)
		{
			if (valid_columns[i] < valid_column)
			{
				valid_column = valid_columns[i];
			}
		}
	}

	return valid_column;
}

int board_config_field_parser::get_board_end_index(const std::string &content)
{
	int index = -1;
	index = content.find(board_config_field_titles::board_end);
	return index;
}

int board_config_field_parser::char_to_int(char character)
{
	return (int(character) - 48);
}

bool board_config_field_parser::is_number(const std::string &number_string)
{
	bool number = true;
	if (number_string.length() == 0)
	{
		number = false;
	}
	else
	{
		for (unsigned int i = 0; i < number_string.length(); i++)
		{
			if (!isdigit(number_string[i]))
			{
				number = false;
				break;
			}
		}
	}

	return number;
}

int board_config_field_parser::find_element(std::vector<int> storage, int element)
{
	int index = -1;
	for (unsigned int i = 0; i < storage.size(); i++)
	{
		if (storage[i] == element)
		{
			index = i;
			break;
		}
	}
	return index;
}