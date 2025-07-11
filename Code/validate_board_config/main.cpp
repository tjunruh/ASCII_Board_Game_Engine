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

	std::string path = argv[1];
	std::string content = "";
	if (file_manager::read_file(path, content) == 1)
	{
		std::cout << "Invalid file path.\n" << std::endl;
		return 1;
	}
	std::string debug_log = "";
	if (validate_board_config::validate(content, debug_log) == 1)
	{
		std::cout << debug_log << std::endl;
		return 1;
	}

	std::cout << debug_log << std::endl;
	return 0;
}