#include "validate_map_config.h"
#include "../build_map_field_titles/build_map_field_titles.h"
#include <iostream>

int validate_map_config::validate_parenthesis(std::string content)
{
	char previous_parenthesis = ' ';
	char parenthesis = ' ';
	int validity = 0;
	int open = 0;
	int close = 0;
	for (unsigned int i = 0; i < content.length(); i++)
	{
		if (content[i] == '(')
		{
			previous_parenthesis = parenthesis;
			parenthesis = '(';
			open++;
			if (parenthesis == previous_parenthesis)
			{
				validity = 1;
				break;
			}
		}
		else if (content[i] == ')')
		{
			close++;
			previous_parenthesis = parenthesis;
			parenthesis = ')';
			if (parenthesis == previous_parenthesis)
			{
				validity = 1;
				break;
			}
		}
	}

	if (open != close)
	{
		validity = 1;
	}
	else if ((open == 0) || (close == 0))
	{
		validity = 1;
	}
	return validity;
}

int validate_map_config::validate_parameters(std::string content, bool action_tile_field)
{
	char parenthesis = ' ';
	int validity = 0;
	int parameter = 0;
	for (unsigned int i = 0; i < content.length(); i++)
	{
		if (content[i] == '(')
		{
			parenthesis = '(';
		}
		else if(content[i] == ')')
		{
			parenthesis = ')';
			parameter = 0;
		}
		else if (content[i] == ',')
		{
			parameter++;
		}

		if (parenthesis == '(')
		{
			if (!(isdigit(content[i]) || ((content[i] == '-') && action_tile_field && ((parameter == 0) || (parameter == 1))) || (content[i] == ',') || (content[i] == '(')))
			{
				validity = 1;
			}
		}
	}
	return validity;
}

int validate_map_config::validate_number_of_parameters(std::string content, int number_of_parameters)
{
	char parenthesis = ' ';
	int validity = 0;
	std::string parameter_content = "";
	int parameters = 0;
	for (unsigned int i = 0; i < content.length(); i++)
	{
		if ((content[i] == '(') || (content[i] == ')'))
		{
			parenthesis = content[i];
		}

		if (((content[i] == ')') || (content[i] == ',')) && (parameter_content != ""))
		{
			parameters++;
			parameter_content = "";
		}

		if ((parenthesis == '(') && (content[i] != ',') && (content[i] != '(') && (content[i] != ')'))
		{
			parameter_content = parameter_content + content[i];
		}

		if ((content[i] == ')') && (parameters != number_of_parameters))
		{
			validity = 1;
			break;
		}

		if (content[i] == ')')
		{
			parameters = 0;
		}
	}
	return validity;
}

int validate_map_config::validate_array_index(std::string content, int max_row, int max_column)
{
	std::vector<row_column> two_dimensional_spaces;
	row_column two_dimensional_space;
	two_dimensional_space.row = "";
	two_dimensional_space.column = "";
	int parameter = -1;

	for (unsigned int i = 0; i < content.length(); i++)
	{
		if ((parameter == 2) && isdigit(content[i]))
		{
			two_dimensional_space.row = two_dimensional_space.row + content[i];
		}
		else if ((parameter == 3) && isdigit(content[i]))
		{
			two_dimensional_space.column = two_dimensional_space.column + content[i];
		}

		if (content[i] == '(')
		{
			parameter = 0;
		}
		else if (content[i] == ',')
		{
			parameter++;
		}
		else if (content[i] == ')')
		{
			parameter = -1;
			two_dimensional_spaces.push_back(two_dimensional_space);
			two_dimensional_space.row = "";
			two_dimensional_space.column = "";
		}
	}

	for (unsigned int i = 0; i < two_dimensional_spaces.size(); i++)
	{
		if (multiple(two_dimensional_spaces, two_dimensional_spaces[i]) || (stoi(two_dimensional_spaces[i].row) >= max_row) || (stoi(two_dimensional_spaces[i].column) >= max_column))
		{
			return 1;
		}
	}

	return 0;
}

int validate_map_config::validate_map_index(std::string content, int max_row, int max_column)
{
	std::vector<std::string> rows;
	std::vector<std::string> columns;
	std::string row = "";
	std::string column = "";
	int parameter = -1;
	int validity = 0;
	for (unsigned int i = 0; i < content.length(); i++)
	{

		if (parameter == 0)
		{
			if (isdigit(content[i]))
			{
				row = row + content[i];
			}
			else if (content[i] == '-')
			{
				rows.push_back(row);
				row = "";
			}
			
		}
		else if (parameter == 1)
		{
			if (isdigit(content[i]))
			{
				column = column + content[i];
			}
			else if (content[i] == '-')
			{
				columns.push_back(column);
				column = "";
			}
		}

		if (content[i] == '(')
		{
			parameter = 0;
		}
		else if (content[i] == ',')
		{
			parameter++;
		}
		else if (content[i] == ')')
		{
			parameter = -1;
			rows.push_back(row);
			columns.push_back(column);
			row = "";
			column = "";
		}
	}

	for (unsigned int i = 0; i < rows.size(); i++)
	{
		if (stoi(rows[i]) >= max_row)
		{
			return 1;
		}
	}

	for (unsigned int i = 0; i < columns.size(); i++)
	{
		if (stoi(columns[i]) >= max_column)
		{
			return 1;
		}
	}

	return validity;
}

int validate_map_config::validate_number_of_entries(std::string content, int number_of_entries)
{
	int entries = 0;
	int validity = 0;
	for (unsigned int i = 0; i < content.length(); i++)
	{
		if (content[i] == ')')
		{
			entries++;
		}
	}

	if (entries != number_of_entries)
	{
		validity = 1;
	}

	return validity;
}

int validate_map_config::validate_hyphen_range(std::string content)
{
	std::string number = "";
	std::string previous_number = "";
	int validity = 0;
	for (unsigned int i = 0; i < content.length(); i++)
	{
		if (isdigit(content[i]))
		{
			number = number + content[i];
		}
		else if((content[i] == ',') || (content[i] == ')'))
		{
			if (is_number(number) && is_number(previous_number))
			{
				if (stoi(number) <= stoi(previous_number))
				{
					validity = 1;
					break;
				}
			}
			else if ((previous_number != "") && (number == ""))
			{
				validity = 1;
			}
			number = "";
			previous_number = "";
		}
		else if (content[i] == '-')
		{
			if (number == "")
			{
				validity = 1;
				break;
			}
			previous_number = number;
			number = "";
		}
	}
	return validity;
}

std::string validate_map_config::get_map_dimension_field(std::string content)
{
	size_t start_position = content.find(build_map_field_titles::array_dimensions_begin) + build_map_field_titles::array_dimensions_begin.length();
	size_t stop_position = content.find(build_map_field_titles::array_dimensions_end);
	std::string dimension_field = "";
	for (unsigned int i = start_position; i < stop_position; i++)
	{
		dimension_field = dimension_field + content[i];
	}
	return dimension_field;
}

std::string validate_map_config::get_map_action_tiles_field(std::string content)
{
	size_t start_position = content.find(build_map_field_titles::action_tiles_begin) + build_map_field_titles::action_tiles_begin.length();
	size_t stop_position = content.find(build_map_field_titles::action_tiles_end);
	std::string action_tiles_field = "";
	for (unsigned int i = start_position; i < stop_position; i++)
	{
		action_tiles_field = action_tiles_field + content[i];
	}
	return action_tiles_field;
}

std::string validate_map_config::get_map(std::string content)
{
	int start_row = get_map_boundary_row(content);
	int start_column = get_map_boundary_column(content);
	int stop_index = get_map_end_index(content);
	int row = 0;
	int column = 0;
	std::string map = "";
	for (int i = 0; i < stop_index; i++)
	{
		if ((column > start_column) && (row > start_row))
		{
			map = map + content[i];
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

	return map;
}

std::string validate_map_config::remove_spaces(std::string content)
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

int validate_map_config::get_map_boundary_row(std::string content)
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
			else if(!(((content[i] == ' ') && (previous_character == ' ')) || ((content[i] == ' ') && (previous_character == '\n')) || (isdigit(content[i]) && (previous_character == ' '))))
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

int validate_map_config::get_map_boundary_column(std::string content)
{
	size_t stop_position = content.find(build_map_field_titles::map_end);
	int column = -1;
	int row = -1;
	std::vector<int> valid_columns;
	for (unsigned int i = 0; i < stop_position; i++)
	{
		if (content[i] == ' ')
		{
			if (row >= 1)
			{
				valid_columns.push_back(column);
			}
		}
		else
		{
			int index = find_element(valid_columns, column);
			if (index != -1)
			{
				valid_columns.erase(valid_columns.begin() + index);
			}
		}

		column++;

		if (content[i] == '\n')
		{
			row++;
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


int validate_map_config::get_map_end_index(std::string content)
{
	int index = -1;
	index = content.find(build_map_field_titles::map_end);
	return index;
}

void validate_map_config::get_array_dimensions(std::string content, int& row, int& column)
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

void validate_map_config::get_map_dimensions(std::string content, int& row, int& column)
{
	row = get_rows(content);
	column = get_columns(content);
}

int validate_map_config::char_to_int(char character)
{
	return (int(character) - 48);
}

int validate_map_config::find_element(std::vector<int> storage, int element)
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

bool validate_map_config::multiple(std::vector<row_column> storage, row_column element)
{
	int occurances = 0;
	bool multiple_elements = false;
	for (unsigned int i = 0; i < storage.size(); i++)
	{
		if ((storage[i].row == element.row) && (storage[i].column == element.column))
		{
			occurances++;
		}
	}

	if (occurances >= 2)
	{
		multiple_elements = true;
	}

	return multiple_elements;
}

bool validate_map_config::is_number(std::string number_string)
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

int validate_map_config::get_rows(std::string board)
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

int validate_map_config::get_columns(std::string board)
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