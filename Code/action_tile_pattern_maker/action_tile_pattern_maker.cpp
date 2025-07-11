#include "action_tile_pattern_maker.h"
#include "../board_config_field_parser/board_config_field_parser.h"
#include "../validate_board_config/validate_board_config.h"

int action_tile_pattern_maker::validate_action_tile_field(std::string action_tiles_field, std::string& debug_info)
{
	board_config_field_parser parser;
	std::string error_lines = "";
	debug_info = "";
	int error_line = -1;
	action_tiles_field = parser.remove_spaces(action_tiles_field);

	if (validate_board_config::validate_enclosing_characters(action_tiles_field, error_line, error_lines, '(', ')') == 1)
	{
		debug_info = debug_info + "Failed: Parenthesis mismatch or data not enclosed in action tiles field.\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of action tiles field.\n";
		debug_info = debug_info + error_lines + " << parenthesis mismatch or data not enclosed\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Parenthesis validation in action tiles field.\n";
	}

	if (validate_board_config::validate_enclosing_characters(action_tiles_field, error_line, error_lines, '{', '}') == 1)
	{
		debug_info = debug_info + "Failed: Curly brackets mismatch or data not enclosed in action tiles field.\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of action tiles field.\n";
		debug_info = debug_info + error_lines + " << curly brackets mismatch or data not enclosed\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Curley brackets validation in action tiles field.\n";
	}

	if (validate_board_config::validate_number_of_parameters(action_tiles_field, 4, error_line, error_lines) == 1)
	{
		debug_info = debug_info + "Failed: Incorrect number of parameters in action tiles field parenthesis (4 expected).\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of action tiles field.\n";
		debug_info = debug_info + error_lines + " << incorrect number of parameters\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Correct number of parameters in action tiles field parenthesis.\n";
	}

	if (validate_board_config::validate_parameters(action_tiles_field, true, error_line, error_lines) == 1)
	{
		debug_info = debug_info + "Failed: Invalid parameter in action tiles field.\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of action tiles field.\n";
		debug_info = debug_info + error_lines + " << invalid parameter\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Valid parameters in action tiles field.\n";
	}

	if (validate_board_config::validate_hyphen_range(action_tiles_field, error_line, error_lines) == 1)
	{
		debug_info = debug_info + "Failed: Invalid range using hyphen in action tiles field.\n";
		debug_info = debug_info + "Error on line " + std::to_string(error_line) + " of action tiles field.\n";
		debug_info = debug_info + error_lines + " << invalid range\n";
		return 1;
	}
	else
	{
		debug_info = debug_info + "Passed: Valid range using hyphen in action tiles field.\n";
	}

	debug_info = debug_info = "All validations passed.\n";

	return 0;
}

void action_tile_pattern_maker::parse_action_tiles(const std::string& action_tile_field)
{
	int parameter = 0;
	bool range_end = false;
	bool start_reading = false;
	bool start_collection = false;
	std::string array_row = "";
	std::string array_column = "";
	std::string map_start_row = "";
	std::string map_stop_row = "";
	std::string map_start_column = "";
	std::string map_stop_column = "";
	for (unsigned int i = 0; i < action_tile_field.length(); i++)
	{
		if (action_tile_field[i] == '(')
		{
			start_reading = true;
		}
		else if (start_reading)
		{
			if (action_tile_field[i] == ',')
			{
				parameter++;
				range_end = false;
			}
			else if (action_tile_field[i] == ')')
			{
				start_reading = false;
				parameter = 0;
				if (map_stop_row == "")
				{
					map_stop_row = map_start_row;
				}

				if (map_stop_column == "")
				{
					map_stop_column = map_start_column;
				}
				action_tile_section section;
				section.start_row = stoi(map_start_row);
				section.stop_row = stoi(map_stop_row);
				section.start_column = stoi(map_start_column);
				section.stop_column = stoi(map_stop_column);
				section.array_row = stoi(array_row);
				section.array_column = stoi(array_column);
				section.start_collection = start_collection;
				section.stop_collection = false;
				action_tile_sections.push_back(section);

				array_row = "";
				array_column = "";
				map_start_row = "";
				map_stop_row = "";
				map_start_column = "";
				map_stop_column = "";
				start_collection = false;
			}
			else if (action_tile_field[i] == '-')
			{
				range_end = true;
			}
			else if (isdigit(action_tile_field[i]))
			{
				if (parameter == 0)
				{
					if (range_end)
					{
						map_stop_row = map_stop_row + action_tile_field[i];
					}
					else
					{
						map_start_row = map_start_row + action_tile_field[i];
					}
				}
				else if (parameter == 1)
				{
					if (range_end)
					{
						map_stop_column = map_stop_column + action_tile_field[i];
					}
					else
					{
						map_start_column = map_start_column + action_tile_field[i];
					}
				}
				else if (parameter == 2)
				{
					array_row = array_row + action_tile_field[i];
				}
				else if (parameter == 3)
				{
					array_column = array_column + action_tile_field[i];
				}
			}
		}
		else if (action_tile_field[i] == '{')
		{
			start_collection = true;
		}
		else if (action_tile_field[i] == '}')
		{
			action_tile_section section;
			section.stop_collection = true;
			action_tile_sections.push_back(section);
		}
	}
}

void action_tile_pattern_maker::prime_action_tiles_field(const std::string& action_tiles_field)
{
	_action_tiles_field = action_tiles_field;
}

int action_tile_pattern_maker::set_row_increment(const std::string& increment)
{
	int status = 0;
	if (is_number(increment))
	{
		int numerical_increment = stoi(increment);
		if (numerical_increment >= 0)
		{
			row_increment = numerical_increment;
		}
		else
		{
			status = 1;
		}
	}
	else
	{
		status = 1;
	}

	return status;
}

int action_tile_pattern_maker::set_column_increment(const std::string& increment)
{
	int status = 0;
	if (is_number(increment))
	{
		int numerical_increment = stoi(increment);
		if (numerical_increment >= 0)
		{
			column_increment = numerical_increment;
		}
		else
		{
			status = 1;
		}
	}
	else
	{
		status = 1;
	}

	return status;
}

int action_tile_pattern_maker::set_array_row_increment(const std::string& increment)
{
	int status = 0;
	if (is_number(increment))
	{
		int numerical_increment = stoi(increment);
		if (numerical_increment >= 0)
		{
			array_row_increment = numerical_increment;
		}
		else
		{
			status = 1;
		}
	}
	else
	{
		status = 1;
	}

	return status;
}

int action_tile_pattern_maker::set_array_column_increment(const std::string& increment)
{
	int status = 0;
	if (is_number(increment))
	{
		int numerical_increment = stoi(increment);
		if (numerical_increment >= 0)
		{
			array_column_increment = numerical_increment;
		}
		else
		{
			status = 1;
		}
	}
	else
	{
		status = 1;
	}

	return status;
}

int action_tile_pattern_maker::set_pattern_generation_count(const std::string& count)
{
	int status = 0;
	if (is_number(count))
	{
		int numerical_count = stoi(count);
		if (numerical_count >= 0)
		{
			pattern_generation_count = numerical_count;
		}
		else
		{
			status = 1;
		}
	}
	else
	{
		status = 1;
	}

	return status;
}

std::string action_tile_pattern_maker::generate_pattern()
{
	_action_tiles_field = _action_tiles_field + "\n";
	for (int i = 1; i <= pattern_generation_count; i++)
	{
		std::string pattern = "";
		for (unsigned int j = 0; j < action_tile_sections.size(); j++)
		{
			if (!action_tile_sections[j].stop_collection)
			{
				if (action_tile_sections[j].start_collection)
				{
					pattern = pattern + "{ ";
				}

				pattern = pattern + "(" + std::to_string(action_tile_sections[j].start_row + (row_increment * i));

				if (action_tile_sections[j].start_row != action_tile_sections[j].stop_row)
				{
					pattern = pattern + "-" + std::to_string(action_tile_sections[j].stop_row + (row_increment * i));
				}

				pattern = pattern + "," + std::to_string(action_tile_sections[j].start_column + (column_increment * i));

				if (action_tile_sections[j].start_column != action_tile_sections[j].stop_column)
				{
					pattern = pattern + '-' + std::to_string(action_tile_sections[j].stop_column + (column_increment * i));
				}

				pattern = pattern + "," + std::to_string(action_tile_sections[j].array_row + (array_row_increment * i));

				pattern = pattern + ',' + std::to_string(action_tile_sections[j].array_column + (array_column_increment * i));

				pattern = pattern + ") ";
			}
			else
			{
				pattern = pattern + "}\n";
			}
			
		}

		_action_tiles_field = _action_tiles_field + pattern + "\n";
	}

	return _action_tiles_field;
}

bool action_tile_pattern_maker::is_number(const std::string& number_string)
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