#include "build_map_config.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::string("You must include the following argument:\n[1] Path to text file containing map\n");
	}
	build_map_config config_builder;
	std::string path = argv[1];
	std::string map = "";
	if (config_builder.read_file(path, map) == 1)
	{
		throw std::string("Invalid file path.\n");
	}
	std::string updated_map = config_builder.modify_content(map);
	std::string base_path = config_builder.extract_path(path);
	std::string file_name = config_builder.extract_file(path);
	file_name = config_builder.remove_extension(file_name);
	file_name = file_name + "_config.txt";

	std::string save_path = base_path + file_name;
	if (config_builder.write_file(save_path, updated_map) == 1)
	{
		throw std::string("Failed to save config.\n");
	}
	return 0;
}