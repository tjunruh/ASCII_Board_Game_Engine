#include "build_board_config.h"
#include "../file_manager/file_manager.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "You must include the following argument:\n[1] Path to text file containing map\n" << std::endl;
		return -1;
	}
	build_board_config config_builder;
	std::string path = argv[1];
	std::string board = "";
	if (file_manager::read_file(path, board) == 1)
	{
		std::cout << "Invalid file path.\n" << std::endl;
		return -1;
	}
	std::string updated_map = config_builder.modify_content(board);
	std::string base_path = file_manager::extract_path(path);
	std::string file_name = file_manager::extract_file(path);
	file_name = file_manager::remove_extension(file_name);
	file_name = file_name + "_config.txt";

	std::string save_path = base_path + file_name;
	if (file_manager::write_file(save_path, updated_map) == 1)
	{
		std::cout << "Failed to save config.\n" << std::endl;
		return -1;
	}
	return 0;
}