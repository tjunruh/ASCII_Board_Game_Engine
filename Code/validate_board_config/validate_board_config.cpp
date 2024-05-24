#include "validate_board_config.h"
#include "../board_config_field_titles/board_config_field_titles.h"
#include "../board_config_field_parser/board_config_field_parser.h"
#include <iostream>

int validate_board_config::validate_board_begin(const std::string &content)
{
	int validity = 0;
	if (content.find(board_config_field_titles::board_begin) == std::string::npos)
	{
		validity = 1;
	}
	return validity;
}

int validate_board_config::validate_board_end(const std::string &content)
{
	int validity = 0;
	if (content.find(board_config_field_titles::board_end) == std::string::npos)
	{
		validity = 1;
	}
	return validity;
}

int validate_board_config::validate_array_dimensions_begin(const std::string &content)
{
	int validity = 0;
	if (content.find(board_config_field_titles::array_dimensions_begin) == std::string::npos)
	{
		validity = 1;
	}
	return validity;
}

int validate_board_config::validate_array_dimensions_end(const std::string &content)
{
	int validity = 0;
	if (content.find(board_config_field_titles::array_dimensions_end) == std::string::npos)
	{
		validity = 1;
	}
	return validity;
}

int validate_board_config::validate_action_tiles_begin(const std::string &content)
{
	int validity = 0;
	if (content.find(board_config_field_titles::action_tiles_begin) == std::string::npos)
	{
		validity = 1;
	}
	return validity;
}

int validate_board_config::validate_action_tiles_end(const std::string &content)
{
	int validity = 0;
	if (content.find(board_config_field_titles::action_tiles_end) == std::string::npos)
	{
		validity = 1;
	}
	return validity;
}

int validate_board_config::validate_parenthesis(const std::string &content)
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

int validate_board_config::validate_parameters(const std::string &content, bool action_tile_field)
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

int validate_board_config::validate_number_of_parameters(const std::string &content, int number_of_parameters)
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

int validate_board_config::validate_array_index(const std::string &content, int max_row, int max_column)
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

int validate_board_config::validate_board_index(const std::string &content, int max_row, int max_column)
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

int validate_board_config::validate_number_of_entries(const std::string &content, int number_of_entries)
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

int validate_board_config::validate_hyphen_range(const std::string &content)
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

void validate_board_config::get_board_dimensions(const std::string &content, int& row, int& column)
{
	row = get_rows(content);
	column = get_columns(content);
}

bool validate_board_config::multiple(std::vector<row_column> storage, row_column element)
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

bool validate_board_config::is_number(const std::string &number_string)
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

int validate_board_config::get_rows(const std::string &board)
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

int validate_board_config::get_columns(const std::string &board)
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

int validate_board_config::validate(const std::string &content, bool debug)
{
	if (validate_board_begin(content) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Board begin tag is missing or malformed." << std::endl;
		}
		return 1;
	}
	else if (debug)
	{
		std::cout << "Passed: Board begin tag found." << std::endl;
	}

	if (validate_board_end(content) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Board end tag is missing or malformed." << std::endl;
		}
		return 1;
	}
	else if (debug)
	{
		std::cout << "Passed: Board end tag found." << std::endl;
	}

	if (validate_array_dimensions_begin(content) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Array dimenion begin tag is missing or malformed." << std::endl;
		}
		return 1;
	}
	else if (debug)
	{
		std::cout << "Passed: Array dimensions begin tag found." << std::endl;
	}

	if (validate_array_dimensions_end(content) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Array dimensions end tag is missing or malformed." << std::endl;
		}
		return 1;
	}
	else if (debug)
	{
		std::cout << "Passed: Array dimensions end tag found." << std::endl;
	}

	if (validate_action_tiles_begin(content) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Action tiles begin tag is missing or malformed." << std::endl;
		}
		return 1;
	}
	else if (debug)
	{
		std::cout << "Passed: Action tiles begin tag found." << std::endl;
	}

	if (validate_action_tiles_end(content) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Action tiles end tag is missing or malformed." << std::endl;
		}
		return 1;
	}
	else if (debug)
	{
		std::cout << "Passed: Action tiles end tag found." << std::endl;
	}

	std::string board = "";
	std::string dimension_field = "";
	std::string action_tiles_field = "";
	board_config_field_parser parser;
	board = parser.get_board(content);
	dimension_field = parser.get_dimension_field(content);
	action_tiles_field = parser.get_action_tiles_field(content);
	dimension_field = parser.remove_spaces(dimension_field);
	action_tiles_field = parser.remove_spaces(action_tiles_field);

	if (validate_parenthesis(dimension_field) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Parenthesis mismatch in dimension field." << std::endl;
		}
		return 1;
	}
	else if (debug)
	{
		std::cout << "Passed: Parenthesis validation in dimension field." << std::endl;
	}

	if (validate_parenthesis(action_tiles_field) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Parenthesis mismatch in action tiles field." << std::endl;
		}
		return 1;
	}
	else if (debug)
	{
		std::cout << "Passed: Parenthesis validation in action tiles field." << std::endl;
	}

	if (validate_number_of_parameters(dimension_field, 2) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Incorrect number of parameters in dimension field parenthesis (2 expected)." << std::endl;
		}
		return 1;
	}
	else if (debug)
	{
		std::cout << "Passed: Correct number of parameters in dimension field parenthesis." << std::endl;
	}

	if (validate_number_of_parameters(action_tiles_field, 4) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Incorrect number of parameters in action tiles field parenthesis (4 expected)." << std::endl;
		}
		return 1;
	}
	else if (debug)
	{
		std::cout << "Passed: Correct number of parameters in action tiles field parenthesis." << std::endl;
	}

	if (validate_parameters(dimension_field, false) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Invalid parameter in dimension field." << std::endl;
		}
		return 1;
	}
	else if(debug)
	{
		std::cout << "Passed: Valid parameters in dimension filed." << std::endl;
	}

	if (validate_parameters(action_tiles_field, true) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Invalid parameter in action tiles field." << std::endl;
		}
		return 1;
	}
	else if(debug)
	{
		std::cout << "Passed: Valid parameters in action tiles field." << std::endl;
	}

	if (validate_hyphen_range(action_tiles_field) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Invalid range using hyphen in action tiles field." << std::endl;
		}
		return 1;
	}
	else if (debug)
	{
		std::cout << "Passed: Valid range using hyphen in action tiles field." << std::endl;
	}

	int row = 0;
	int column = 0;

	parser.get_array_dimensions(dimension_field, row, column);

	if ((row == -1) || (column == -1))
	{
		if (debug)
		{
			std::cout << "Error reading array dimensions." << std::endl;
		}
		return 1;
	}

	if (validate_array_index(action_tiles_field, row, column) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Array dimension invalid in action tiles field." << std::endl;
		}
		return 1;
	}
	else if (debug)
	{
		std::cout << "Passed: Array dimensions valid." << std::endl;
	}

	get_board_dimensions(board, row, column);

	if (validate_board_index(action_tiles_field, row, column) == 1)
	{
		if (debug)
		{
			std::cout << "Failed: Board dimension out of bounds in action tiles field." << std::endl;
		}
		return 1;
	}
	else if (debug)
	{
		std::cout << "Passed: Board dimensions valid." << std::endl;
	}

	if (debug)
	{
		std::cout << "All validations passed." << std::endl;
	}

	return 0;
}