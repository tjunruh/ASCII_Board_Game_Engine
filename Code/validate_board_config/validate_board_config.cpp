#include "../ascii_engine_dll_files/pch.h"
#include "validate_board_config.h"
#include "../board_config_field_titles/board_config_field_titles.h"
#include "../board_config_field_parser/board_config_field_parser.h"
#include <algorithm>

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

int validate_board_config::validate_metadata_begin(const std::string& content)
{
	int validity = 0;
	if (content.find(board_config_field_titles::metadata_begin) == std::string::npos)
	{
		validity = 1;
	}
	return validity;
}

int validate_board_config::validate_metadata_end(const std::string& content)
{
	int validity = 0;
	if (content.find(board_config_field_titles::metadata_end) == std::string::npos)
	{
		validity = 1;
	}
	return validity;
}

int validate_board_config::validate_line_length(const std::string& content, int& error_line, std::string& error_line_content)
{
	int validity = 0;
	std::string line = "";
	unsigned int length = 0;
	bool compare = false;
	error_line = 0;
	for (unsigned int i = 0; i < content.length(); i++)
	{
		if (content[i] == '\n')
		{
			if (compare && (line.length() != length))
			{
				validity = 1;
				error_line_content = line;
				break;
			}
			length = line.length();
			compare = true;
			error_line++;
			line = "";
		}
		else
		{
			line = line + content[i];
		}
	}

	if ((line.length() != 0) && compare && (line.length() != length))
	{
		validity = 1;
		error_line_content = line;
	}

	return validity;
}

int validate_board_config::validate_enclosing_characters(const std::string &content, int& error_line, std::string& error_line_content, char begin_character, char end_character)
{
	char previous_enclosement = ' ';
	char enclosement = end_character;
	int validity = 0;
	error_line = 0;
	error_line_content = "";
	std::string previous_line_content = "";
	for (unsigned int i = 0; i < content.length(); i++)
	{
		error_line_content = error_line_content + content[i];
		if (content[i] == begin_character)
		{
			previous_enclosement = enclosement;
			enclosement = begin_character;
			if (enclosement == previous_enclosement)
			{
				validity = 1;
				break;
			}
		}
		else if (content[i] == end_character)
		{
			previous_enclosement = enclosement;
			enclosement = end_character;
			if (enclosement == previous_enclosement)
			{
				validity = 1;
				break;
			}
		}
		else if ((content[i] == '\n') && ((i + 1) < content.length()))
		{
			error_line++;
			previous_line_content = error_line_content;
			error_line_content = "";
		}
	}

	if (enclosement == begin_character)
	{
		validity = 1;
	}

	error_line_content = previous_line_content + error_line_content;

	return validity;
}

int validate_board_config::validate_parameters(const std::string &content, bool action_tile_field, int& error_line, std::string& error_line_content)
{
	char parenthesis = ' ';
	int validity = 0;
	int parameter = 0;
	error_line = 0;
	error_line_content = "";
	std::string previous_line_content = "";
	bool hyphen_found = false;
	int previous_parameter_begin_index = -2;
	for (int i = 0; (unsigned int)i < content.length(); i++)
	{
		error_line_content = error_line_content + content[i];
		if (content[i] == '(')
		{
			parenthesis = '(';
			previous_parameter_begin_index = i;
		}
		else if(content[i] == ')')
		{
			parenthesis = ')';
			parameter = 0;
			if ((previous_parameter_begin_index + 1) == i)
			{
				validity = 1;
				break;
			}
			hyphen_found = false;
		}
		else if (content[i] == ',')
		{
			parameter++;
			if ((previous_parameter_begin_index + 1) == i)
			{
				validity = 1;
				break;
			}
			previous_parameter_begin_index = i;
			hyphen_found = false;
		}
		else if (content[i] == '\n')
		{
			error_line++;
			previous_line_content = error_line_content;
			error_line_content = "";
		}

		if (parenthesis == '(')
		{
			if (!(isdigit(content[i]) || ((content[i] == '-') && action_tile_field && !hyphen_found && ((parameter == 0) || (parameter == 1))) || (content[i] == ',') || (content[i] == '(')))
			{
				validity = 1;
				break;
			}
		}

		if (content[i] == '-')
		{
			hyphen_found = true;
		}
	}

	error_line_content = previous_line_content + error_line_content;

	return validity;
}

int validate_board_config::validate_number_of_parameters(const std::string &content, int number_of_parameters, int& error_line, std::string& error_line_content)
{
	char parenthesis = ' ';
	int validity = 0;
	std::string parameter_content = "";
	int parameters = 0;
	error_line = 0;
	error_line_content = "";
	std::string previous_line_content = "";
	for (unsigned int i = 0; i < content.length(); i++)
	{
		error_line_content = error_line_content + content[i];
		if ((content[i] == '(') || (content[i] == ')'))
		{
			parenthesis = content[i];
		}

		if ((content[i] == ')') || (content[i] == ','))
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

		if (content[i] == '\n')
		{
			error_line++;
			previous_line_content = error_line_content;
			error_line_content = "";
		}
	}

	error_line_content = previous_line_content + error_line_content;

	return validity;
}

int validate_board_config::validate_array_index(const std::string &content, int max_row, int max_column, int& error_line, std::string& error_line_content)
{
	int validity = 0;
	std::vector<row_column> two_dimensional_spaces;
	std::vector<row_column> single_array_element_values;
	row_column two_dimensional_space;
	two_dimensional_space.row = "";
	two_dimensional_space.column = "";
	int parameter = -1;
	bool in_single_array_element_block = false;
	error_line = 0;
	error_line_content = "";
	std::string previous_line_content = "";
	for (unsigned int i = 0; i < content.length(); i++)
	{
		if (content[i] == '{')
		{
			in_single_array_element_block = true;
		}
		else if (content[i] == '}')
		{
			in_single_array_element_block = false;
			single_array_element_values.clear();
		}

		error_line_content = error_line_content + content[i];
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
			if ((multiple(two_dimensional_spaces, two_dimensional_space) && !in_single_array_element_block) || (stoi(two_dimensional_space.row) >= max_row) || (stoi(two_dimensional_space.column) >= max_column))
			{
				validity = 1;
				break;
			}

			if (in_single_array_element_block)
			{
				single_array_element_values.push_back(two_dimensional_space);
				if (!uniform(single_array_element_values))
				{
					validity = 1;
					break;
				}
			}
			two_dimensional_space.row = "";
			two_dimensional_space.column = "";
		}
		else if (content[i] == '\n')
		{
			error_line++;
			previous_line_content = error_line_content;
			error_line_content = "";
		}
	}

	error_line_content = previous_line_content + error_line_content;

	return validity;
}

int validate_board_config::validate_board_index(const std::string &content, int max_row, int max_column, int& error_line, std::string& error_line_content)
{
	std::string row = "";
	std::string column = "";
	int parameter = -1;
	int validity = 0;
	error_line = 0;
	error_line_content = "";
	std::string previous_line_content = "";
	for (unsigned int i = 0; i < content.length(); i++)
	{
		error_line_content = error_line_content + content[i];
		if (parameter == 0)
		{
			if (isdigit(content[i]))
			{
				row = row + content[i];
			}
			else if (content[i] == '-')
			{
				if (stoi(row) >= max_row)
				{
					validity = 1;
					break;
				}
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
				if (stoi(column) >= max_column)
				{
					validity = 1;
					break;
				}
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
			if ((stoi(row) >= max_row) || (stoi(column) >= max_column))
			{
				validity = 1;
				break;
			}
			row = "";
			column = "";
		}
		else if (content[i] == '\n')
		{
			error_line++;
			previous_line_content = error_line_content;
			error_line_content = "";
		}
	}

	error_line_content = previous_line_content + error_line_content;

	return validity;
}

int validate_board_config::validate_metadata_parameters(const std::string& content, int& error_line, std::string& error_line_content)
{
	char curly_bracket = ' ';
	char parenthesis = ' ';
	int validity = 0;
	int parameter = 0;
	error_line = 0;
	error_line_content = "";
	std::string previous_line_content = "";
	std::string row = "";
	std::string column = "";
	std::string key = "";
	std::string value = "";
	std::vector<std::string> keys;
	std::vector<row_column> coordinates;
	for (int i = 0; (unsigned int)i < content.length(); i++)
	{
		error_line_content = error_line_content + content[i];
		if (content[i] == '(')
		{
			parenthesis = '(';
		}
		else if (content[i] == ')')
		{
			parenthesis = ')';
			parameter = 0;
			if ((key.length() == 0) || (std::count(keys.begin(), keys.end(), key) != 0))
			{
				validity = 1;
				break;
			}
			else
			{
				keys.push_back(key);
			}

			if (value.length() > 0 && value[0] == '-')
			{
				value = value.erase(0, 1);
			}

			if (key == "row" && is_integer(value))
			{
				row = value;
			}
			else if (key == "column" && is_integer(value))
			{
				column = value;
			}

			if (!is_integer(value) && !is_float(value) && !is_string(value))
			{
				validity = 1;
				break;
			}

			key = "";
			value = "";
		}
		else if (content[i] == '{')
		{
			curly_bracket = '{';
		}
		else if (content[i] == '}')
		{
			curly_bracket = '}';
			if (row.length() == 0 || column.length() == 0)
			{
				validity = 1;
				error_line_content = error_line_content + " << required row or column parameter not found or are not integers";
				break;
			}
			else
			{
				row_column coordinate;
				coordinate.row = row;
				coordinate.column = column;
				if (std::count(coordinates.begin(), coordinates.end(), coordinate) != 0)
				{
					error_line_content = error_line_content + " << row and column coordinates cannot be duplicated";
					validity = 1;
					break;
				}
				else
				{
					coordinates.push_back(coordinate);
				}
			}

			row = "";
			column = "";
			keys.clear();
		}
		else if (content[i] == ',')
		{
			parameter++;
		}
		else if (content[i] == '\n')
		{
			error_line++;
			previous_line_content = error_line_content;
			error_line_content = "";
		}
		else if (parenthesis == '(')
		{
			if (parameter == 0)
			{
				key = key + content[i];
			}
			else if (parameter == 1)
			{
				value = value + content[i];
			}
		}
	}

	error_line_content = previous_line_content + error_line_content;

	return validity;
}

int validate_board_config::validate_hyphen_range(const std::string &content, int& error_line, std::string& error_line_content)
{
	std::string number = "";
	std::string previous_number = "";
	int validity = 0;
	error_line = 0;
	error_line_content = "";
	std::string previous_line_content = "";
	for (unsigned int i = 0; i < content.length(); i++)
	{
		error_line_content = error_line_content + content[i];
		if (isdigit(content[i]))
		{
			number = number + content[i];
		}
		else if((content[i] == ',') || (content[i] == ')'))
		{
			if (is_integer(number) && is_integer(previous_number))
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
				break;
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
		else if (content[i] == '\n')
		{
			error_line++;
			previous_line_content = error_line_content;
			error_line_content = "";
		}
	}

	error_line_content = previous_line_content + error_line_content;

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

bool validate_board_config::uniform(std::vector<row_column> storage)
{
	bool is_uniform = true;
	if (storage.size() > 0)
	{
		std::string first_row = storage[0].row;
		std::string first_column = storage[0].column;
		for (unsigned int i = 1; i < storage.size(); i++)
		{
			if ((storage[i].row != first_row) || (storage[i].column != first_column))
			{
				is_uniform = false;
				break;
			}
		}
	}

	return is_uniform;
}

bool validate_board_config::is_integer(const std::string &number_string)
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

bool validate_board_config::is_float(const std::string& number_string)
{
	bool number = true;
	bool decimal_found = false;
	if (number_string.length() == 0)
	{
		number = false;
	}
	else
	{
		for (unsigned int i = 0; i < number_string.length(); i++)
		{
			if (!isdigit(number_string[i]) && (number_string[i] != '.'))
			{
				number = false;
				break;
			}
			else if (number_string[i] == '.')
			{
				if (decimal_found)
				{
					number = false;
					break;
				}
				decimal_found = true;;
			}
		}
	}

	return number && decimal_found;
}

bool validate_board_config::is_string(const std::string& string_string)
{
	bool is_string = false;
	if (string_string.length() > 1 && string_string[0] == '\"' && string_string[string_string.length() - 1] == '\"')
	{
		is_string = true;
	}
	return is_string;
}

int validate_board_config::get_rows(const std::string &board)
{
	int rows = 0;
	if (board.length() > 0)
	{
		rows++;
	}

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

int validate_board_config::validate(const std::string &content, std::string& debug_info)
{
	debug_info = "";
	if (validate_board_begin(content) == 1)
	{
		debug_info = debug_info + "Failed: Board begin tag is missing or malformed.\n";
		debug_info = debug_info + "Missing: " + board_config_field_titles::board_begin + "\n";
		return 1;
	}
	else
	{
		debug_info = debug_info +  "Passed: Board begin tag found.\n";
	}

	if (validate_board_end(content) == 1)
	{
		debug_info = debug_info + "Failed: Board end tag is missing or malformed.\n";
		debug_info = debug_info + "Missing: " + board_config_field_titles::board_end + "\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Board end tag found.\n";
	}

	if (validate_array_dimensions_begin(content) == 1)
	{
		debug_info = debug_info + "Failed: Array dimenion begin tag is missing or malformed.\n";
		debug_info = debug_info + "Missing: " + board_config_field_titles::array_dimensions_begin + "\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Array dimensions begin tag found.\n";
	}

	if (validate_array_dimensions_end(content) == 1)
	{
		debug_info = debug_info + "Failed: Array dimensions end tag is missing or malformed.\n";
		debug_info = debug_info + "Missing: " + board_config_field_titles::array_dimensions_end + "\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Array dimensions end tag found.\n";
	}

	if (validate_action_tiles_begin(content) == 1)
	{
		debug_info = debug_info + "Failed: Action tiles begin tag is missing or malformed.\n";
		debug_info = debug_info + "Missing: " + board_config_field_titles::action_tiles_begin + "\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Action tiles begin tag found.\n";
	}

	if (validate_action_tiles_end(content) == 1)
	{
		debug_info = debug_info + "Failed: Action tiles end tag is missing or malformed.\n";
		debug_info = debug_info + "Missing: " + board_config_field_titles::action_tiles_end + "\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Action tiles end tag found.\n";
	}

	bool include_metadata = true;
	if (validate_metadata_begin(content) == 1)
	{
		debug_info = debug_info + "Failed: Metadata field begin tag is missing or malformed. - ignoring metadata\n";
		debug_info = debug_info + "Missing: " + board_config_field_titles::metadata_begin + "\n";
		include_metadata = false;
	}
	else
	{
		debug_info = debug_info + "Passed: Metadata field begin tag found.\n";
	}

	if (validate_metadata_end(content) == 1)
	{
		debug_info = debug_info + "Failed: Metadata field end tag is missing or malformed. - ignoring metadata\n";
		debug_info = debug_info + "Missing: " + board_config_field_titles::metadata_end + "\n";
		include_metadata = false;
	}
	else
	{
		debug_info = debug_info + "Passed: Metadata field end tag found.\n";
	}

	board_config_field_parser parser;
	std::string board = parser.get_board(content);
	std::string dimension_field = parser.get_dimension_field(content);
	std::string action_tiles_field = parser.get_action_tiles_field(content);
	std::string metadata_field = "";
	if (include_metadata)
	{
		metadata_field = parser.get_metadata_field(content);
	}
	dimension_field = parser.remove_spaces(dimension_field);
	action_tiles_field = parser.remove_spaces(action_tiles_field);
	metadata_field = parser.remove_spaces(metadata_field);
	int error_line = 0;
	std::string error_line_content = "";

	if (validate_line_length(board, error_line, error_line_content) == 1)
	{
		debug_info = debug_info + "Failed: Lines of board must be the same length.\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of board field.\n";
		debug_info = debug_info + error_line_content + " << line length is not the same as preceding lines\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Lines of board are the same length.\n";
	}

	if (validate_enclosing_characters(dimension_field, error_line, error_line_content, '(', ')') == 1)
	{
		debug_info = debug_info + "Failed: Parenthesis mismatch or data not enclosed in dimension field.\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of array dimensions field.\n";
		debug_info = debug_info + error_line_content + " << parenthesis mismatch or data not enclosed\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Parenthesis validation in dimension field.\n";
	}

	if (validate_enclosing_characters(action_tiles_field, error_line, error_line_content, '(', ')') == 1)
	{
		debug_info = debug_info + "Failed: Parenthesis mismatch or data not enclosed in action tiles field.\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of action tiles field.\n";
		debug_info = debug_info + error_line_content + " << parenthesis mismatch or data not enclosed\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Parenthesis validation in action tiles field.\n";
	}

	if (validate_enclosing_characters(action_tiles_field, error_line, error_line_content, '{', '}') == 1)
	{
		debug_info = debug_info + "Failed: Curly brackets mismatch or data not enclosed in action tiles field.\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of action tiles field.\n";
		debug_info = debug_info + error_line_content + " << curly brackets mismatch or data not enclosed\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Curley brackets validation in action tiles field.\n";
	}

	if (validate_number_of_parameters(dimension_field, 2, error_line, error_line_content) == 1)
	{
		debug_info = debug_info + "Failed: Incorrect number of parameters in dimension field parenthesis (2 expected).\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of array dimensions field.\n";
		debug_info = debug_info + error_line_content + " << incorrect number of parameters\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Correct number of parameters in dimension field parenthesis.\n";
	}
	
	if (validate_number_of_parameters(action_tiles_field, 4, error_line, error_line_content) == 1)
	{
		debug_info = debug_info + "Failed: Incorrect number of parameters in action tiles field parenthesis (4 expected).\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of action tiles field.\n";
		debug_info = debug_info + error_line_content + " << incorrect number of parameters\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Correct number of parameters in action tiles field parenthesis.\n";
	}
	
	if (validate_parameters(dimension_field, false, error_line, error_line_content) == 1)
	{
		debug_info = debug_info + "Failed: Invalid parameter in dimension field.\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of array dimensions field.\n";
		debug_info = debug_info + error_line_content + " << invalid parameter\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Valid parameters in dimension field.\n";
	}
	
	if (validate_parameters(action_tiles_field, true, error_line, error_line_content) == 1)
	{
		debug_info = debug_info + "Failed: Invalid parameter in action tiles field.\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of action tiles field.\n";
		debug_info = debug_info + error_line_content + " << invalid parameter\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Valid parameters in action tiles field.\n";
	}

	if (include_metadata)
	{
		if (validate_enclosing_characters(metadata_field, error_line, error_line_content, '(', ')') == 1)
		{
			debug_info = debug_info + "Failed: Parenthesis mismatch or data not enclosed in metadata field.\n";
			debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of metadata field.\n";
			debug_info = debug_info + error_line_content + " << parenthesis mismatch or data not enclosed\n";
			return 1;
		}
		else
		{
			debug_info = debug_info + "Passed: Parenthesis validation in metadata field.\n";
		}

		if (validate_enclosing_characters(metadata_field, error_line, error_line_content, '{', '}') == 1)
		{
			debug_info = debug_info + "Failed: Curly brackets mismatch or data not enclosed in metadata field.\n";
			debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of metadata field.\n";
			debug_info = debug_info + error_line_content + " << curly brackets mismatch or data not enclosed\n";
			return 1;
		}
		else
		{
			debug_info = debug_info + "Passed: Curly brackets validation in metadata field.\n";
		}

		if (validate_number_of_parameters(metadata_field, 2, error_line, error_line_content) == 1)
		{
			debug_info = debug_info + "Failed: Incorrect number of parameters in metadata field parenthesis (2 expected).\n";
			debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of metadata field.\n";
			debug_info = debug_info + error_line_content + " << incorrect number of parameters\n";
			return 1;
		}
		else
		{
			debug_info = debug_info + "Passed: Correct number of parameters in metadata field parenthesis.\n";
		}

		if (validate_metadata_parameters(metadata_field, error_line, error_line_content) == 1)
		{
			debug_info = debug_info + "Failed: Invalid parameter in metadata field.\n";
			debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of metadata field.\n";
			debug_info = debug_info + error_line_content + " << invalid parameter\n";
			return 1;
		}
		else
		{
			debug_info = debug_info + "Passed: Valid parameters in metadata field.\n";
		}
	}
	
	if (validate_hyphen_range(action_tiles_field, error_line, error_line_content) == 1)
	{
		debug_info = debug_info + "Failed: Invalid range using hyphen in action tiles field.\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of action tiles field.\n";
		debug_info = debug_info + error_line_content + " << invalid range\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Valid range using hyphen in action tiles field.\n";
	}

	int row = 0;
	int column = 0;

	parser.get_array_dimensions(dimension_field, row, column);

	if ((row == -1) || (column == -1))
	{
		debug_info = debug_info + "Error reading array dimensions.\n";
		return 1;
	}

	
	if (validate_array_index(action_tiles_field, row, column, error_line, error_line_content) == 1)
	{
		debug_info = debug_info + "Failed: Array dimension invalid in action tiles field.\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of array dimensions field.\n";
		debug_info = debug_info + error_line_content + " << invalid index\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Array dimensions valid.\n";
	}
	
	get_board_dimensions(board, row, column);

	
	if (validate_board_index(action_tiles_field, row, column, error_line, error_line_content) == 1)
	{
		debug_info = debug_info + "Failed: Board dimension out of bounds in action tiles field.\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of action tiles field.\n";
		debug_info = debug_info + error_line_content + " << invalid index\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Board dimensions valid.\n";
	}
	
	debug_info = debug_info + "All validations passed.\n";

	return 0;
}