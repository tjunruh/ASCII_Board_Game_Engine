#pragma once
#include <string>
#include <vector>
#include "widget.h"
#include "frame.h"

#ifdef _WIN32
#ifdef ASCII_BOARD_EXPORTS
#define ASCII_BOARD_API __declspec(dllexport)
#else
#define ASCII_BOARD_API __declspec(dllimport)
#endif
#elif __linux__
#define ASCII_BOARD_API
#endif

struct tile_configuration
{
	int row = -2;
	int column = -2;
	std::string value = "";
	char ignore_character = '\0';
	std::vector<format_tools::index_format> colors;
};

struct board_configuration
{
	std::string name_id;
	std::vector<tile_configuration> tile_configurations;
};

class ascii_board : public widget
{
public:
	ASCII_BOARD_API ascii_board(frame* parent, std::string path, std::string special_operation = "none", bool start_logging=false, std::string logging_file_path="ascii_board.log");
	ASCII_BOARD_API void clear_tile(int row, int column);
	ASCII_BOARD_API void clear_tiles();
	ASCII_BOARD_API void set_tile(int row, int column, std::string value, char ignore_character);
	ASCII_BOARD_API void set_tile(int row, int column, std::string value, char ignore_character, const std::vector<format_tools::index_format>& colors);
	ASCII_BOARD_API void set_row(int row, std::string value, char ignore_character);
	ASCII_BOARD_API void set_row(int row, std::string value, char ignore_character, const std::vector<format_tools::index_format>& colors);
	ASCII_BOARD_API void set_column(int column, std::string value, char ignore_character);
	ASCII_BOARD_API void set_column(int column, std::string value, char ignore_character, const std::vector<format_tools::index_format>& colors);
	ASCII_BOARD_API void set_all(std::string value, char ignore_character);
	ASCII_BOARD_API void set_all(std::string value, char ignore_character, const std::vector<format_tools::index_format>& colors);
	ASCII_BOARD_API void set_tile_character(int row, int column, char character, unsigned int character_index);
	ASCII_BOARD_API std::string get_tile(int row, int column);
	ASCII_BOARD_API char get_tile_character(int row, int column, unsigned int character_index);
	ASCII_BOARD_API std::string get_board();
	ASCII_BOARD_API void add_configuration(board_configuration configuration);
	ASCII_BOARD_API void add_configuration(std::string name_id, int row, int column, std::string value, char ignore_character);
	ASCII_BOARD_API void add_configuration(std::string name_id, int row, int column, std::string value, char ignore_character, const std::vector<format_tools::index_format>& colors);
	ASCII_BOARD_API void activate_configuration(int row, int column, std::string name_id);
	ASCII_BOARD_API void activate_configuration(std::string name_id);
	ASCII_BOARD_API void deactivate_configuration(int row, int column, std::string name_id);
	ASCII_BOARD_API void deactivate_configuration(std::string name_id);
	ASCII_BOARD_API std::string load_configuration(std::string path);
	ASCII_BOARD_API void load_configuration(std::string path, std::string name_id, int row, int column, char ignore_character);
	ASCII_BOARD_API void load_configuration(std::string path, std::string name_id, int row, int column, char ignore_character, const std::vector<format_tools::index_format>& colors);
	ASCII_BOARD_API int get_number_of_columns();
	ASCII_BOARD_API int get_number_of_rows();
	ASCII_BOARD_API void display();
	ASCII_BOARD_API void sync();

private:
	std::string board = "";
	std::vector<format_tools::index_format> board_colors;

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
		std::vector<format_tools::index_format> colors;
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
	unsigned int get_value_length(action_tile tile);
	bool configuration_present(std::string name_id);
	board_configuration get_configuration(std::string name_id);
	bool duplicate_point_present(board_configuration configuration);
	bool configuration_indexing_acceptable(board_configuration configuration);
	int get_action_tile_index(int row, int column);
	int get_board_config_index(std::string name_id);
	int get_tile_config_index(std::string name_id, int row, int column);
	void set_tile(tile_configuration configuration, bool activate);
	void set_row(tile_configuration configuration, bool activate);
	void set_column(tile_configuration configuration, bool activate);
	void set_all(tile_configuration configuration, bool activate);
};