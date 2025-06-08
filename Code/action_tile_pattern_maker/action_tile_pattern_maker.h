#pragma once
#include <vector>
#include <string>

class action_tile_pattern_maker
{
public:
	int validate_action_tile_field(std::string action_tiles_field, std::string& error_line_content);
	void parse_action_tiles(const std::string& action_tiles_field);
	void prime_action_tiles_field(const std::string& action_tiles_field);
	int set_row_increment(const std::string& increment);
	int set_column_increment(const std::string& increment);
	int set_array_row_increment(const std::string& increment);
	int set_array_column_increment(const std::string& increment);
	int set_pattern_generation_count(const std::string& count);
	std::string generate_pattern();

private:
	bool is_number(const std::string& number_string);
	struct action_tile_section
	{
		int start_row = 0;
		int stop_row = 0;
		int start_column = 0;
		int stop_column = 0;
		int array_row = 0;
		int array_column = 0;
		bool start_collection = false;
		bool stop_collection = false;
	};

	int row_increment = 0;
	int column_increment = 0;
	int array_row_increment = 0;
	int array_column_increment = 0;
	int pattern_generation_count = 0;

	std::string _action_tiles_field = "";

	std::vector<action_tile_section> action_tile_sections;
};