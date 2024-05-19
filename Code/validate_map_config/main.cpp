#include "validate_map_config.h"
#include "../file_manager/file_manager.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "You must include the following argument:\n[1] Path to text file containing config\n" << std::endl;
		return 1;
	}

	validate_map_config map_validator;
	std::string path = argv[1];
	std::string content = "";
	if (file_manager::read_file(path, content) == 1)
	{
		std::cout << "Invalid file path.\n" << std::endl;
		return 1;
	}
	std::string map = "";
	std::string dimension_field = "";
	std::string action_tiles_field = "";
	map = map_validator.get_map(content);
	dimension_field = map_validator.get_map_dimension_field(content);
	action_tiles_field = map_validator.get_map_action_tiles_field(content);
	dimension_field = map_validator.remove_spaces(dimension_field);
	action_tiles_field = map_validator.remove_spaces(action_tiles_field);

	std::cout << map << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << dimension_field << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << action_tiles_field << std::endl;
	std::cout << "------------------------------" << std::endl;

	if (map_validator.validate_parenthesis(dimension_field) == 1)
	{
		std::cout << "Failed: Parenthesis mismatch in dimension field." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Passed: Parenthesis validation in dimension field." << std::endl;
	}

	if (map_validator.validate_parenthesis(action_tiles_field) == 1)
	{
		std::cout << "Failed: Parenthesis mismatch in action tiles field." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Passed: Parenthesis validation in action tiles field." << std::endl;
	}

	if (map_validator.validate_number_of_parameters(dimension_field, 2) == 1)
	{
		std::cout << "Failed: Incorrect number of parameters in dimension field parenthesis (2 expected)." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Passed: Correct number of parameters in dimension field parenthesis." << std::endl;
	}

	if (map_validator.validate_number_of_parameters(action_tiles_field, 4) == 1)
	{
		std::cout << "Failed: Incorrect number of parameters in action tiles field parenthesis (4 expected)." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Passed: Correct number of parameters in action tiles field parenthesis." << std::endl;
	}

	if (map_validator.validate_parameters(dimension_field, false) == 1)
	{
		std::cout << "Failed: Invalid parameter in dimension field." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Passed: Valid parameters in dimension filed." << std::endl;
	}

	if (map_validator.validate_parameters(action_tiles_field, true) == 1)
	{
		std::cout << "Failed: Invalid parameter in action tiles field." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Passed: Valid parameters in action tiles field." << std::endl;
	}

	if (map_validator.validate_hyphen_range(action_tiles_field) == 1)
	{
		std::cout << "Failed: Invalid range using hyphen in action tiles field." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Passed: Valid range using hyphen in action tiles field." << std::endl;
	}

	int row = 0;
	int column = 0;

	map_validator.get_array_dimensions(dimension_field, row, column);

	if ((row == -1) || (column == -1))
	{
		std::cout << "Error reading array dimensions." << std::endl;
		return 1;
	}

	if (map_validator.validate_array_index(action_tiles_field, row, column) == 1)
	{
		std::cout << "Failed: Array dimension invalid in action tiles field." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Passed: Array dimensions valid." << std::endl;
	}

	map_validator.get_map_dimensions(map, row, column);

	if (map_validator.validate_map_index(action_tiles_field, row, column) == 1)
	{
		std::cout << "Failed: Map dimension out of bounds in action tiles field." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Passed: Map dimensions valid." << std::endl;
	}

	std::cout << "All validations passed." << std::endl;

	return 0;
}