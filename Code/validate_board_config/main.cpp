#include "validate_board_config.h"
#include "../file_manager/file_manager.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "You must include the following argument:\n[1] Path to text file containing config\n" << std::endl;
		return 1;
	}

	validate_board_config map_validator;
	std::string path = argv[1];
	std::string content = "";
	if (file_manager::read_file(path, content) == 1)
	{
		std::cout << "Invalid file path.\n" << std::endl;
		return 1;
	}
	
	if (map_validator.validate(content, true) == 1)
	{
		return 1;
	}

	return 0;
}