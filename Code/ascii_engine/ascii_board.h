#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "widget.h"
#include "frame.h"
#include "board_metadata.h"

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
	struct action_tile_board_section
	{
		int board_start_row = -1;
		int board_stop_row = -1;
		int board_start_column = -1;
		int board_stop_column = -1;
	};

	struct sub_tile_configuration
	{
		std::string name_id = "";
		std::string value = "";
		char ignore_character = '\0';
	};

private:
	struct action_tile_skeleton
	{
		int array_row = -1;
		int array_column = -1;
		std::vector<action_tile_board_section> board_section;
		std::string default_value = "";
	};

	struct board_translation
	{
		std::string name_id = "";
		std::string board = "";
		std::vector<action_tile_skeleton> action_tile_skeletons;
		board_metadata metadata;
	};

public:
	struct action_tile
	{
		int array_row = -1;
		int array_column = -1;
		std::vector<action_tile_board_section> board_section;
		std::string default_value = "";
		std::string value = "";
		std::vector<format_tools::index_format> colors;
		std::vector<sub_tile_configuration> activated_configs;
		bool edited = false;
	};

	ASCII_BOARD_API ascii_board(frame* parent, const std::string& path, const std::string& name_id, const std::string& special_operation = "none", int lines_count = 0, bool start_logging = false, const std::string& logging_file_path = "ascii_board.log");
	ASCII_BOARD_API void clear_tile(int row, int column);
	ASCII_BOARD_API void clear_row(int row);
	ASCII_BOARD_API void clear_column(int column);
	ASCII_BOARD_API void clear_all();
	ASCII_BOARD_API std::string get_tile(int row, int column);
	ASCII_BOARD_API void set_tile(int row, int column, std::string value);
	ASCII_BOARD_API char get_tile_character(int row, int column, unsigned int character_index);
	ASCII_BOARD_API std::string get_board();
	ASCII_BOARD_API std::vector<format_tools::index_format> get_colors();
	ASCII_BOARD_API void get_board_and_colors(std::string& game_board, std::vector<format_tools::index_format>& colors);
	ASCII_BOARD_API void add_configuration(board_configuration configuration);
	ASCII_BOARD_API void add_configuration(const std::string& name_id, int row, int column, const std::string& value, char ignore_character);
	ASCII_BOARD_API void add_configuration(const std::string& name_id, int row, int column, const std::string& value, char ignore_character, const std::vector<format_tools::index_format>& colors);
	ASCII_BOARD_API void add_configuration(const std::string& name_id, int row, int column, const std::string& value, char ignore_character, int foreground_format, int background_format, bool bold, bool include_spaces = false);
	ASCII_BOARD_API void activate_configuration(const std::string& name_id, int row, int column);
	ASCII_BOARD_API void activate_configuration(const std::string& name_id);
	ASCII_BOARD_API void deactivate_configuration(const std::string& name_id, int row, int column);
	ASCII_BOARD_API void deactivate_configuration(const std::string& name_id);
	ASCII_BOARD_API std::string load_configuration(const std::string& path);
	ASCII_BOARD_API void load_configuration(const std::string& path, const std::string& name_id, int row, int column, char ignore_character);
	ASCII_BOARD_API void load_configuration(const std::string& path, const std::string& name_id, int row, int column, char ignore_character, const std::vector<format_tools::index_format>& colors);
	ASCII_BOARD_API void load_configuration(const std::string& path, const std::string& name_id, int row, int column, char ignore_character, int foreground_format, int background_format, bool bold, bool include_spaces = false);
	ASCII_BOARD_API void set_sub_configuration_color(const std::string& name_id, const std::string& value_match, const std::vector<format_tools::index_format>& colors);
	ASCII_BOARD_API int get_number_of_columns();
	ASCII_BOARD_API int get_number_of_rows();
	ASCII_BOARD_API void display();
	ASCII_BOARD_API void build();
	ASCII_BOARD_API action_tile get_action_tile(int row, int column);
	ASCII_BOARD_API bool configuration_activated(const std::string& name_id, int row, int column);
	ASCII_BOARD_API void modify_configuration(const std::string& target_name_id, const std::string& modification_name_id);
	ASCII_BOARD_API int load_board_translation(const std::string& name_id, const std::string& path, bool load_metadata=false);
	ASCII_BOARD_API void use_translation(const std::string& name_id, bool swap_metadata=false);
	ASCII_BOARD_API void set_lines_count(int lines_count);
	ASCII_BOARD_API void set_top_display_index(unsigned int index);
	ASCII_BOARD_API void set_left_display_index(unsigned int index);
	ASCII_BOARD_API void scroll_up(unsigned int amount = 1);
	ASCII_BOARD_API void scroll_down(unsigned int amount = 1);
	ASCII_BOARD_API void scroll_left(unsigned int amount = 1);
	ASCII_BOARD_API void scroll_right(unsigned int amount = 1);
	ASCII_BOARD_API void bring_tile_into_view(int row, int column, int top_padding = 0, int bottom_padding = 0, int left_padding = 0, int right_padding = 0);
	ASCII_BOARD_API board_metadata* get_metadata();

private:
	int max_rows = 0;
	int max_columns = 0;

	unsigned int board_lines_count = 0;
	unsigned int board_characters_in_line = 0;

	std::vector<action_tile> action_tiles;
	std::vector<board_configuration> board_configurations;
	std::vector<board_translation> board_translations;
	board_metadata metadata;
	void set_tile_range(int array_row, int array_column, int board_start_row, int board_stop_row, int board_start_column, int board_stop_column, std::vector<action_tile_skeleton>& action_tile_skeletons);
	void initialize_tiles(int rows, int columns, std::vector<action_tile_skeleton>& action_tile_skeletons);
	void set_tile_ranges(const std::string& content, std::vector<action_tile_skeleton>& action_tile_skeletons);
	void remove_inactive_tiles(std::vector<action_tile_skeleton>& action_tile_skeletons);
	void set_tile_default_values(const std::string& board_reference, std::vector<action_tile_skeleton>& action_tile_skeletons);
	void set_map_metadata(const std::string& content, board_translation& translation);
	std::string get_board_section(const std::string& board_reference, const std::vector<action_tile_board_section>& board_section);
	void build_board(std::string& board, std::vector<format_tools::index_format>& board_colors);
	unsigned int get_value_length(action_tile tile);
	bool configuration_present(const std::string& name_id);
	board_configuration get_configuration(const std::string& name_id);
	bool duplicate_point_present(board_configuration configuration);
	bool configuration_indexing_acceptable(board_configuration configuration);
	bool action_tile_index_exists(int row, int column);
	int get_action_tile_index(int row, int column);
	int get_board_config_index(const std::string& name_id);
	int get_tile_config_index(const std::string& name_id, int row, int column);
	void set_tile(tile_configuration configuration, bool activate, const std::string& name_id);
	void set_row(tile_configuration configuration, bool activate, const std::string& name_id);
	void set_column(tile_configuration configuration, bool activate, const std::string& name_id);
	void set_all(tile_configuration configuration, bool activate, const std::string& name_id);
	std::string fill_default_value_with_ignore_character(std::string config_value, std::string default_value, char ignore_character);
	void remove_activated_config(std::vector<sub_tile_configuration>& activated_configs, std::string name_id);
	bool trim_activated_configs(action_tile& tile);
	void refresh_action_tile_colors(action_tile& tile);
	bool configuration_activated(std::vector <sub_tile_configuration> activated_configurations, std::string name_id);
	int validate_translation(std::vector<action_tile_skeleton> action_tile_skeletons);
	std::string remove_configuration_format_characters(std::string content, char format_character);
	char get_format_character(const std::string& content);
	void newline_guard(board_translation& translation);
};
