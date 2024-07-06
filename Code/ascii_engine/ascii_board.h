#pragma once
#include <string>
#include <vector>
#include "widget.h"
#include "frame.h"

struct tile_configuration
{
	int row = -2;
	int column = -2;
	std::string value = "";
	char ignore_character = '\0';
};

struct board_configuration
{
	std::string name_id;
	std::vector<tile_configuration> tile_configurations;
};

class ascii_board : public widget
{
public:
	ascii_board(frame* parent, std::string path, int& status, std::string special_operation = "none");
	int clear_tile(int row, int column);
	void clear_tiles();
	int set_tile(int row, int column, std::string value, char ignore_character);
	int set_row(int row, std::string value, char ignore_character);
	int set_column(int column, std::string value, char ignore_character);
	int set_all(std::string value, char ignore_character);
	int set_tile_character(int row, int column, char character, int character_index);
	std::string get_tile(int row, int column);
	char get_tile_character(int row, int column, int character_index);
	std::string get_board();
	int add_configuration(board_configuration configuration);
	int activate_configuration(int row, int column, std::string name_id);
	int activate_configuration(std::string name_id);
	int deactivate_configuration(int row, int column, std::string name_id);
	int deactivate_configuration(std::string name_id);
	int get_number_of_columns();
	int get_number_of_rows();
	void set_output(const std::string& output);

private:
	std::string board = "";

	struct action_tile
	{
		int array_row = -1;
		int array_column = -1;
		int board_start_row = -1;
		int board_stop_row = -1;
		int board_start_column = -1;
		int board_stop_column = -1;
		std::string default_value = "";
		std::string value = "";
	};
	int max_rows = 0;
	int max_columns = 0;

	std::vector<action_tile> action_tiles;
	std::vector<board_configuration> board_configurations;
	void set_tile_range(int array_row, int array_column, int board_start_row, int board_stop_row, int board_start_column, int board_stop_column);
	void initialize_tiles(int rows, int columns);
	void set_tile_ranges(std::string content);
	void remove_inactive_tiles();
	void set_tile_default_values();
	std::string get_board_section(int start_row, int stop_row, int start_column, int stop_column);
	void update_board();
	int get_value_length(action_tile tile);
	bool configuration_present(std::string name_id);
	board_configuration get_configuration(std::string name_id);
	bool duplicate_point_present(board_configuration configuration);
	bool configuration_indexing_acceptable(board_configuration configuration);
	int get_action_tile_index(int row, int column);
	int get_board_config_index(std::string name_id);
	int get_tile_config_index(std::string name_id, int row, int column);
	int set_tile(tile_configuration configuration, bool activate);
	int set_row(tile_configuration configuration, bool activate);
	int set_column(tile_configuration configuration, bool activate);
	int set_all(tile_configuration configuration, bool activate);
};