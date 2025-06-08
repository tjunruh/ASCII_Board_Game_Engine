#include "action_tile_pattern_maker.h"
#include "../file_manager/file_manager.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc != 7)
	{
		std::cout << "You must include the following arguments:\n[1] Path to text_file constaining action tile pattern\n[2] row increment\n[3] column incrmeent\n[4] array row increment\n[5] array column incrment\n[6] number of times for the pattern to repeat\n" << std::endl;
		return 1;
	}

	action_tile_pattern_maker pattern_maker;
	std::string path = argv[1];
	std::string action_tiles_field = "";
	if (file_manager::read_file(path, action_tiles_field) == 1)
	{
		std::cout << "Invalid file path.\n" << std::endl;
		return 1;
	}
	std::string debug_log = "";
	if (pattern_maker.validate_action_tile_field(action_tiles_field, debug_log) == 1)
	{
		std::cout << debug_log << std::endl;
		return 1;
	}

	std::string row_increment = argv[2];
	std::string column_increment = argv[3];
	std::string array_row_increment = argv[4];
	std::string array_column_increment = argv[5];
	std::string pattern_count = argv[6];

	if (pattern_maker.set_row_increment(row_increment) == 1)
	{
		std::cout << "Invlid row increment" << std::endl;
		return 1;
	}

	if (pattern_maker.set_column_increment(column_increment) == 1)
	{
		std::cout << "Invlid column increment" << std::endl;
		return 1;
	}

	if (pattern_maker.set_array_row_increment(array_row_increment) == 1)
	{
		std::cout << "Invalid array row increment" << std::endl;
		return 1;
	}

	if (pattern_maker.set_array_column_increment(array_column_increment) == 1)
	{
		std::cout << "Invalid array column increment" << std::endl;
		return 1;
	}

	if (pattern_maker.set_pattern_generation_count(pattern_count) == 1)
	{
		std::cout << "Invalid pattern generation count" << std::endl;
		return 1;
	}

	pattern_maker.parse_action_tiles(action_tiles_field);
	pattern_maker.prime_action_tiles_field(action_tiles_field);

	std::string pattern = pattern_maker.generate_pattern();

	std::string base_path = file_manager::extract_path(path);
	std::string file_name = file_manager::extract_file(path);
	file_name = file_manager::remove_extension(file_name);
	file_name = file_name + "_pattern.txt";

	std::string save_path = base_path + file_name;
	if (file_manager::write_file(save_path, pattern) == 1)
	{
		std::cout << "Failed to save pattern.\n" << std::endl;
		return 1;
	}

	return 0;
}