#include "pch.h"
#include "single_line_board_definitions.h"
#ifdef __linux__
#include <gtest/gtest.h>
#endif
#ifdef _WIN32
#include "../ascii_engine/ascii_board.h"
#include "../file_manager/file_manager.h"
#include "../ascii_engine/error_codes.h"
#include "../ascii_engine/frame.h"
#include "../ascii_engine/format_tools.h"
#elif __linux__
#include <ascii_engine/ascii_board.h>
#include <ascii_engine/file_manager.h>
#include <ascii_engine/error_codes.h>
#include <ascii_engine/frame.h>
#include <ascii_engine/format_tools.h>
#endif

#include <string>
#include <vector>

class ascii_board_test : public testing::Test
{
protected:
#ifdef _WIN32
	std::string board_config_path = "test_board_config.txt";
	std::string upside_down_board_config_path = "test_board_config_upside_down.txt";
	std::string cursor_config_path = "test_cursor_config.txt";
	std::string x_config_path = "test_x_config.txt";
#elif __linux__
	std::string board_config_path = "Code/test_ascii_engine/test_configs/test_board_config.txt";
	std::string upside_down_board_config_path = "Code/test_ascii_engine/test_configs/test_board_config_upside_down.txt";
	std::string cursor_config_path = "Code/test_ascii_engine/test_configs/test_cursor_config.txt";
	std::string x_config_path = "Code/test_ascii_engine/test_configs/test_x_config.txt";
#endif
	frame* global_test_frame = new frame();
	ascii_board global_test_board = ascii_board(global_test_frame, board_config_path, "default", "none", true, "global_ascii_board.log");
	int total_rows = 10;
	int total_columns = 10;
	

	std::vector<format_tools::index_format> empty_colors;
	tile_configuration cursor_config_tile{-1, -1, "(*)", '*', empty_colors};
	std::vector<tile_configuration> cursor_config_tile_vector = { cursor_config_tile };
	board_configuration cursor_config_board{ "cursor", cursor_config_tile_vector };

	tile_configuration x_config_tile{ -1, -1, "*x*", '*', empty_colors };
	std::vector<tile_configuration> x_config_tile_vector = { x_config_tile };
	board_configuration x_config_board{ "x", x_config_tile_vector };

	tile_configuration o_config_tile{ -1, -1, "*o*", '*', empty_colors };
	std::vector<tile_configuration> o_config_tile_vector = { o_config_tile };
	board_configuration o_config_board{ "o", o_config_tile_vector };

	tile_configuration arrow_config_tile{ -1, -1, "**>", '*', empty_colors };
	std::vector<tile_configuration> arrow_config_tile_vector = { arrow_config_tile };
	board_configuration arrow_config_board{ "arrow", arrow_config_tile_vector };

	tile_configuration duplicate_name_config_tile{ -1, -1, "*x*", '*', empty_colors };
	std::vector<tile_configuration> duplicate_name_config_tile_vector = { duplicate_name_config_tile };
	board_configuration duplicate_name_config_board{ "cursor", duplicate_name_config_tile_vector };

	tile_configuration out_of_bounds_config_tile{ 41, 0, "(*)", '*', empty_colors };
	std::vector<tile_configuration> out_of_bounds_config_tile_vector = { out_of_bounds_config_tile };
	board_configuration out_of_bounds_config_board{ "out_of_bounds", out_of_bounds_config_tile_vector };

	std::vector<tile_configuration> overlapping_config_tile_vector = { cursor_config_tile, x_config_tile };
	board_configuration overlapping_config_board{ "overlapping", overlapping_config_tile_vector };
	
	std::vector<tile_configuration> invalid_name_config_tile_vector = { cursor_config_tile };
	board_configuration invalid_name_config_board{ "", invalid_name_config_tile_vector };

	void add_configuration_structure(ascii_board& local_test_board, board_configuration structure, std::string expected_error_function, int expected_error_code)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0);
		local_test_board.add_configuration(structure);
		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0);
		EXPECT_NE(log_content.find(expected_error_function + " status: " + std::to_string(expected_error_code)), std::string::npos) << "Expected function: " + expected_error_function + "\nExpected code: " + std::to_string(expected_error_code);
	}

	void add_or_load_configuration_parameters(ascii_board& local_test_board, std::string id, int row, int column, std::string value_or_file_path, char ignore_character, bool load, std::string expected_error_function, int expected_error_code)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0);
		if (!load)
		{
			local_test_board.add_configuration(id, row, column, value_or_file_path, ignore_character);
		}
		else if (load)
		{
			local_test_board.load_configuration(value_or_file_path, id, row, column, ignore_character);
		}

		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0);
		EXPECT_NE(log_content.find(expected_error_function + " status: " + std::to_string(expected_error_code)), std::string::npos) << "Expected function: " + expected_error_function + "\nExpected code: " + std::to_string(expected_error_code);
	}

	void add_or_load_configuration_parameters_with_colors(ascii_board& local_test_board, std::string id, int row, int column, std::string value_or_file_path, char ignore_character, std::vector<format_tools::index_format> colors, bool load, std::string expected_error_function, int expected_error_code)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0);
		if (!load)
		{
			local_test_board.add_configuration(id, row, column, value_or_file_path, ignore_character, colors);
		}
		else if (load)
		{
			local_test_board.load_configuration(value_or_file_path, id, row, column, ignore_character, colors);
		}

		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0);
		EXPECT_NE(log_content.find(expected_error_function + " status: " + std::to_string(expected_error_code)), std::string::npos) << "Expected function: " + expected_error_function + "\nExpected code: " + std::to_string(expected_error_code);
	}

	void set_sub_configuration_color_test(ascii_board& local_test_board, std::string id, std::string value, const std::vector<format_tools::index_format>& colors, std::string expected_status_function, int expected_status_code, int test_num)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0);
		local_test_board.set_sub_configuration_color(id, value, colors);
		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
	}

	void activate_deactivate(ascii_board& local_test_board, std::string id, const std::string& comparison, std::string expected_status_function, int expected_status_code, bool activate, int test_num)
	{
		std::string log_content = "";
		if (activate)
		{
			local_test_board.reset_logging("ascii_board.log");
			int status = file_manager::read_file("ascii_board.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos) << std::to_string(test_num);
			local_test_board.activate_configuration(id);
			status = file_manager::read_file("ascii_board.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
			
			std::string board = local_test_board.get_board();
			EXPECT_EQ(board, comparison) << std::to_string(test_num) << std::to_string(test_num);
		}
		else
		{
			local_test_board.reset_logging("ascii_board.log");
			int status = file_manager::read_file("ascii_board.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos) << std::to_string(test_num);
			local_test_board.deactivate_configuration(id);
			status = file_manager::read_file("ascii_board.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);

			std::string board = local_test_board.get_board();
			EXPECT_EQ(board, comparison) << std::to_string(test_num);
		}
		
	}

	void use_translation_test(ascii_board& local_test_board, std::string id, std::string expected_status_function, int expected_status_code, int test_num)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		local_test_board.use_translation(id);
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
	}

	void check_board(ascii_board& local_test_board, const std::string& comparission, int test_num)
	{
		std::string log_content = "";
		std::string board = local_test_board.get_board();
		EXPECT_EQ(board, comparission);
	}

	void activate_deactivate(ascii_board& local_test_board, std::string id, int row, int column, const std::string& comparison, std::string expected_status_function, int expected_status_code, bool activate, int test_num)
	{
		std::string log_content = "";
		if (activate)
		{
			local_test_board.reset_logging("ascii_board.log");
			int status = file_manager::read_file("ascii_board.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos) << std::to_string(test_num);
			local_test_board.activate_configuration(id, row, column);
			status = file_manager::read_file("ascii_board.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);

			std::string board = local_test_board.get_board();
			EXPECT_EQ(board, comparison) << std::to_string(test_num);
		}
		else
		{
			local_test_board.reset_logging("ascii_board.log");
			int status = file_manager::read_file("ascii_board.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos) << std::to_string(test_num);
			local_test_board.deactivate_configuration(id, row, column);
			status = file_manager::read_file("ascii_board.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);

			std::string board = local_test_board.get_board();
			EXPECT_EQ(board, comparison) << std::to_string(test_num);
		}
	}

	void set_or_clear(ascii_board& local_test_board, int row, int column, const std::string& comparison, std::string expected_status_function, int expected_status_code, int test_num, bool set, std::string value = "", char ignore_character = '*')
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		if (set)
		{
			if (row != -1 && column != -1)
			{
				local_test_board.set_tile(row, column, value, ignore_character);
			}
			else if (row == -1 && column == -1)
			{
				local_test_board.set_all(value, ignore_character);
			}
			else if (column == -1)
			{
				local_test_board.set_row(row, value, ignore_character);
			}
			else if (row == -1)
			{
				local_test_board.set_column(column, value, ignore_character);
			}
		}
		else
		{
			if (row != -1 && column != -1)
			{
				local_test_board.clear_tile(row, column);
			}
			else if (row == -1 && column == -1)
			{
				local_test_board.clear_all();
			}
			else if (column == -1)
			{
				local_test_board.clear_row(row);
			}
			else if (row == -1)
			{
				local_test_board.clear_column(column);
			}
		}

		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);

		std::string board = local_test_board.get_board();
		EXPECT_EQ(board, comparison) << std::to_string(test_num);
	}

	void set_or_clear(ascii_board& local_test_board, int row, int column, const std::string& comparison, std::string expected_status_function, int expected_status_code, int test_num, bool set, std::vector<format_tools::index_format> colors, std::string value = "", char ignore_character = '*')
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		if (set)
		{
			if (row != -1 && column != -1)
			{
				local_test_board.set_tile(row, column, value, ignore_character, colors);
			}
			else if (row == -1 && column == -1)
			{
				local_test_board.set_all(value, ignore_character, colors);
			}
			else if (column == -1)
			{
				local_test_board.set_row(row, value, ignore_character, colors);
			}
			else if (row == -1)
			{
				local_test_board.set_column(column, value, ignore_character, colors);
			}
		}
		else
		{
			if (row != -1 && column != -1)
			{
				local_test_board.clear_tile(row, column);
			}
			else if (row == -1 && column == -1)
			{
				local_test_board.clear_all();
			}
			else if (column == -1)
			{
				local_test_board.clear_row(row);
			}
			else if (row == -1)
			{
				local_test_board.clear_column(column);
			}
		}

		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);

		std::string board = local_test_board.get_board();
		EXPECT_EQ(board, comparison) << std::to_string(test_num);
	}

	bool colors_equivalent(std::vector<format_tools::index_format> input_colors, std::vector<format_tools::index_format> board_colors, int test_num)
	{
		std::string log_report = "";
		bool matching = false;
		if (input_colors.size() == 0 && board_colors.size() == 0)
		{
			matching = true;
		}
		for (unsigned int j = 0; j < input_colors.size(); j++)
		{
			log_report = log_report + "input color:\n";
			log_report = log_report + std::to_string(input_colors[j].format.background_format) + "\n";
			log_report = log_report + std::to_string(input_colors[j].format.foreground_format) + "\n";
			log_report = log_report + std::to_string(input_colors[j].format.dec) + "\n";
			log_report = log_report + std::to_string(input_colors[j].format.bold) + "\n";
			log_report = log_report + std::to_string(input_colors[j].index) + "\n";
			log_report = log_report + std::to_string(input_colors[j].flag_replacement) + "\n";
			log_report = log_report + "\n";
			matching = false;
			for (unsigned int i = 0; i < board_colors.size(); i++)
			{
				if ((board_colors[i].format.background_format == input_colors[j].format.background_format) &&
					(board_colors[i].format.foreground_format == input_colors[j].format.foreground_format) &&
					(board_colors[i].format.dec == input_colors[j].format.dec) &&
					(board_colors[i].index == input_colors[j].index) &&
					(board_colors[i].flag_replacement == input_colors[j].flag_replacement))
				{
					matching = true;
				}
				log_report = log_report + "board color:\n";
				log_report = log_report + std::to_string(board_colors[i].format.background_format) + "\n";
				log_report = log_report + std::to_string(board_colors[i].format.foreground_format) + "\n";
				log_report = log_report + std::to_string(board_colors[i].format.dec) + "\n";
				log_report = log_report + std::to_string(board_colors[i].format.bold) + "\n";
				log_report = log_report + std::to_string(board_colors[i].index) + "\n";
				log_report = log_report + std::to_string(board_colors[i].flag_replacement) + "\n";
				log_report = log_report + "\n";
			}

			if (!matching)
			{
				break;
			}
		}

		if (!matching)
		{
			ascii_io::print(log_report);
		}
		EXPECT_EQ(matching, true) << std::to_string(test_num);
		return matching;
	}

	void colors_equivalent(ascii_board local_test_board, std::vector<format_tools::index_format> input_colors, int row, int column, int test_num)
	{
		ascii_board::action_tile tile;
		if (row != -1 && column != -1)
		{
			tile = local_test_board.get_action_tile(row, column);
			if (tile.array_row != -1)
			{
				bool matching = colors_equivalent(input_colors, tile.colors, test_num);
				if (!matching)
				{
					ascii_io::print("row: " + std::to_string(row) + "\ncolumn: " + std::to_string(column) + "\n");
					ascii_io::print("============================================================\n");
				}
			}
		}
		else if (row == -1 && column == -1)
		{
			for (int i = 0; i < total_rows; i++)
			{
				for (int j = 0; j < total_columns; j++)
				{
					tile = local_test_board.get_action_tile(i, j);
					if (tile.array_row != -1)
					{
						bool matching = colors_equivalent(input_colors, tile.colors, test_num);
						if (!matching)
						{
							ascii_io::print("row: " + std::to_string(i) + "\ncolumn: " + std::to_string(j) + "\n");
							ascii_io::print("============================================================\n");
						}
					}
				}
			}
		}
		else if (column == -1)
		{
			for (int i = 0; i < total_columns; i++)
			{
				tile = local_test_board.get_action_tile(row, i);
				if (tile.array_row != -1)
				{
					bool matching = colors_equivalent(input_colors, tile.colors, test_num);
					if (!matching)
					{
						ascii_io::print("row: " + std::to_string(row) + "\ncolumn: " + std::to_string(i) + "\n");
						ascii_io::print("============================================================\n");
					}
				}
			}
		}
		else if (row == -1)
		{
			for (int i = 0; i < total_rows; i++)
			{
				tile = local_test_board.get_action_tile(i, column);
				if (tile.array_row != -1)
				{
					bool matching = colors_equivalent(input_colors, tile.colors, test_num);
					if (!matching)
					{
						ascii_io::print("row: " + std::to_string(i) + "\ncolumn: " + std::to_string(column) + "\n");
						ascii_io::print("============================================================\n");
					}
				}
			}
		}
	}

	bool action_tiles_equivalent(ascii_board::action_tile tile, ascii_board::action_tile comparision, int test_num)
	{
		bool equivalent = false;
		if ((tile.array_row == comparision.array_row) &&
			(tile.array_column == comparision.array_column) &&
			(action_tile_board_sections_equivalent(tile.board_section, comparision.board_section)) &&
			(tile.value == comparision.value) &&
			(tile.default_value == comparision.default_value) &&
			colors_equivalent(tile.colors, comparision.colors, test_num))
		{
			equivalent = true;
		}
		EXPECT_EQ(equivalent, true) << std::to_string(test_num);
		if (!equivalent)
		{
			std::string log_message = "";
			log_message = log_message + "array row: " + std::to_string(tile.array_row) + "\n";
			log_message = log_message + "array column: " + std::to_string(tile.array_column) + "\n";
			for (unsigned int i = 0; i < tile.board_section.size(); i++)
			{
				log_message = log_message + "boud start row: " + std::to_string(tile.board_section[i].board_start_row) + "\n";
				log_message = log_message + "board stop row: " + std::to_string(tile.board_section[i].board_stop_row) + "\n";
				log_message = log_message + "board start column: " + std::to_string(tile.board_section[i].board_start_column) + "\n";
				log_message = log_message + "board stop column: " + std::to_string(tile.board_section[i].board_stop_column) + "\n";
			}
			log_message = log_message + "value: |" + tile.value + "|\n";
			log_message = log_message + "default_value: |" + tile.default_value + "|\n";
			ascii_io::print(log_message);
		}
		return equivalent;
	}

	void set_get_tile_character(ascii_board& local_test_board, int row, int column, char character, int character_index, std::string comparision, std::string expected_status_function, int expected_status_code, bool set, int test_num)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		if (set)
		{
			local_test_board.set_tile_character(row, column, character, character_index);
		}
		else
		{
			char returned_character = local_test_board.get_tile_character(row, column, character_index);
			EXPECT_EQ(returned_character, character) << std::to_string(test_num);
		}
		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
	}

	void set_get_tile(ascii_board& local_test_board, int row, int column, std::string value, char ignore_character, std::string comparision, std::string expected_status_function, int expected_status_code, bool set, bool test_num)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		if (set)
		{
			local_test_board.set_tile(row, column, value, ignore_character);
		}
		else
		{
			std::string returned_value = local_test_board.get_tile(row, column);
			EXPECT_EQ(returned_value, value);
		}
		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
	}

	void test_get_action_tile(ascii_board& local_test_board, int row, int column, ascii_board::action_tile comparision, std::string expected_status_function, int expected_status_code, int test_num)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		ascii_board::action_tile tile = local_test_board.get_action_tile(row, column);
		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
		action_tiles_equivalent(tile, comparision, test_num);
	}

	void test_configuration_activated(ascii_board& local_test_board, std::string name_id, int row, int column, bool expected_activation, std::string expected_status_function, int expected_status_code, int test_num)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_EQ(local_test_board.configuration_activated(name_id, row, column), expected_activation) << std::to_string(test_num);
		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
	}

	void test_modify_configuration(ascii_board& local_test_board, std::string target_name_id, std::string modification_name_id, const std::string& comparison, std::string expected_status_function, int expected_status_code, int test_num)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		local_test_board.modify_configuration(target_name_id, modification_name_id);
		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
		std::string board = local_test_board.get_board();
		EXPECT_EQ(board, comparison) << std::to_string(test_num);
	}

	bool action_tile_board_sections_equivalent(std::vector<ascii_board::action_tile_board_section> section1, std::vector<ascii_board::action_tile_board_section> section2)
	{
		bool equivalent = false;
		for (unsigned int i = 0; i < section1.size(); i++)
		{
			for (unsigned int j = 0; j < section2.size(); j++)
			{
				if ((section1[i].board_start_row == section2[j].board_start_row) &&
					(section1[i].board_stop_row == section2[j].board_stop_row) &&
					(section1[i].board_start_column == section2[j].board_start_column) &&
					(section1[i].board_stop_column == section2[j].board_stop_column))
				{
					section2.erase(section2.begin() + j);
					break;
				}
			}
		}

		if (section2.size() == 0)
		{
			equivalent = true;
		}

		return equivalent;
	}
};

TEST_F(ascii_board_test, initialization)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);
	std::string log_content = "";
	int status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	EXPECT_NE(log_content.find("ascii_board::ascii_board status: 0"), std::string::npos);
	EXPECT_NE(log_content.find("All validations passed."), std::string::npos);
	EXPECT_EQ(local_test_board.get_board(), single_line_board_definitions::empty_board);
	status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	ascii_board local_test_board2(local_test_frame, "jibberish.txt", "default", "none", true);
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	EXPECT_NE(log_content.find("ascii_board::ascii_board status: " + std::to_string(INVALID_PATH)), std::string::npos);
	status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	ascii_board local_test_board3(local_test_frame, "jibberish.txt", "default");
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 1);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, add_configuration_structure)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);

	// add first valid configuration
	add_configuration_structure(local_test_board, cursor_config_board, "ascii_board::add_configuration", SUCCESS);
	// add second valid configuration
	add_configuration_structure(local_test_board, x_config_board, "ascii_board::add_configuration", SUCCESS);
	// add duplicate
	add_configuration_structure(local_test_board, duplicate_name_config_board, "ascii_board::add_configuration", DUPLICATE_ELEMENT);
	// add overlapping
	add_configuration_structure(local_test_board, overlapping_config_board, "ascii_board::add_configuration", DUPLICATE_ELEMENT);
	// add out of bounds index
	add_configuration_structure(local_test_board, out_of_bounds_config_board, "ascii_board::add_configuration", INVALID_INDEX);
	// add invalid name
	add_configuration_structure(local_test_board, invalid_name_config_board, "ascii_board::add_configuration", INVALID_VALUE);

	int status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, add_configuration_parameters)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);

	// add first valid configuration
	add_or_load_configuration_parameters(local_test_board, "cursor", -1, -1, "(*)", '*', false, "ascii_board::add_configuration", SUCCESS);
	// add second valid configuration
	add_or_load_configuration_parameters(local_test_board, "x", -1, -1, "*x*", '*', false, "ascii_board::add_configuration", SUCCESS);
	// add duplicate
	add_or_load_configuration_parameters(local_test_board, "cursor", -1, -1, "*x*", '*', false, "ascii_board::add_configuration", DUPLICATE_ELEMENT);
	// add out of bounds index
	add_or_load_configuration_parameters(local_test_board, "out_of_bounds", 41, 0, "(*)", '*', false, "ascii_board::add_configuration", INVALID_INDEX);
	// add invalid name
	add_or_load_configuration_parameters(local_test_board, "", -1, -1, "(*)", '*', false, "ascii_board::add_configuration", INVALID_VALUE);
	int status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, add_configuration_parameters_with_colors)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);

	// add first valid configuration
	add_or_load_configuration_parameters_with_colors(local_test_board, "cursor", -1, -1, "(*)", '*', empty_colors, false, "ascii_board::add_configuration", SUCCESS);
	// add second valid configuration
	add_or_load_configuration_parameters_with_colors(local_test_board, "x", -1, -1, "*x*", '*', empty_colors, false, "ascii_board::add_configuration", SUCCESS);
	// add duplicate
	add_or_load_configuration_parameters_with_colors(local_test_board, "cursor", -1, -1, "*x*", '*', empty_colors, false, "ascii_board::add_configuration", DUPLICATE_ELEMENT);
	// add out of bounds index
	add_or_load_configuration_parameters_with_colors(local_test_board, "out_of_bounds", 41, 0, "(*)", '*', empty_colors, false, "ascii_board::add_configuration", INVALID_INDEX);
	// add invalid name
	add_or_load_configuration_parameters_with_colors(local_test_board, "", -1, -1, "(*)", '*', empty_colors, false, "ascii_board::add_configuration", INVALID_VALUE);
	int status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, load_configuration)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default");

	// Valid path to config
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	std::string value = local_test_board.load_configuration(cursor_config_path);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	EXPECT_NE(log_content.find("ascii_board::load_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	EXPECT_EQ(value, "(*)");


	// Invalid path to config
	local_test_board.reset_logging("ascii_board.log");
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	value = local_test_board.load_configuration("jibberish.txt");
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	EXPECT_NE(log_content.find("ascii_board::load_configuration status: " + std::to_string(INVALID_PATH)), std::string::npos);
	EXPECT_EQ(value, "");

	status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, load_configuration_parameters)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);

	// add first valid configuration
	add_or_load_configuration_parameters(local_test_board, "cursor", -1, -1, cursor_config_path, '*', true, "ascii_board::add_configuration", SUCCESS);
	// add second valid configuration
	add_or_load_configuration_parameters(local_test_board, "x", -1, -1, x_config_path, '*', true, "ascii_board::add_configuration", SUCCESS);
	// add duplicate
	add_or_load_configuration_parameters(local_test_board, "cursor", -1, -1, x_config_path, '*', true, "ascii_board::add_configuration", DUPLICATE_ELEMENT);
	// add out of bounds index
	add_or_load_configuration_parameters(local_test_board, "out_of_bounds", 41, 0, cursor_config_path, '*', true, "ascii_board::add_configuration", INVALID_INDEX);
	// invalid path
	add_or_load_configuration_parameters(local_test_board, "invalid_path", -1, -1, "jibberish.txt", '*', true, "ascii_board::load_configuration", INVALID_PATH);
	// add invalid name
	add_or_load_configuration_parameters(local_test_board, "", -1, -1, cursor_config_path, '*', true, "ascii_board::add_configuration", INVALID_VALUE);

	int status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, load_configuration_parameters_with_colors)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);

	// add first valid configuration
	add_or_load_configuration_parameters_with_colors(local_test_board, "cursor", -1, -1, cursor_config_path, '*', empty_colors, true, "ascii_board::add_configuration", SUCCESS);
	// add second valid configuration
	add_or_load_configuration_parameters_with_colors(local_test_board, "x", -1, -1, x_config_path, '*', empty_colors, true, "ascii_board::add_configuration", SUCCESS);
	// add duplicate
	add_or_load_configuration_parameters_with_colors(local_test_board, "cursor", -1, -1, x_config_path, '*', empty_colors, true, "ascii_board::add_configuration", DUPLICATE_ELEMENT);
	// add out of bounds index
	add_or_load_configuration_parameters_with_colors(local_test_board, "out_of_bounds", 41, 0, cursor_config_path, '*', empty_colors, true, "ascii_board::add_configuration", INVALID_INDEX);
	// invalid path
	add_or_load_configuration_parameters_with_colors(local_test_board, "invalid_path", -1, -1, "jibberish.txt", '*', empty_colors, true, "ascii_board::load_configuration", INVALID_PATH);
	// add invalid name
	add_or_load_configuration_parameters_with_colors(local_test_board, "", -1, -1, cursor_config_path, '*', empty_colors, true, "ascii_board::add_configuration", INVALID_VALUE);

	int status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, sub_configuration_color_test)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);

	std::vector<format_tools::index_format> cursor_colors =
	{
		{0, {format_tools::green, format_tools::black, false, false}, ' '},
		{1, {format_tools::red, format_tools::black, false, false}, ' '},
		{2, {format_tools::none, format_tools::none, false, false}, ' '}
	};

	std::vector<format_tools::index_format> new_valid_cursor_colors =
	{
		{0, {format_tools::red, format_tools::red, true, false}, ' '},
		{1, {format_tools::none, format_tools::none, true, false}, ' '},
		{2, {format_tools::green, format_tools::green, true, false}, ' '}
	};

	std::vector<format_tools::index_format> new_low_invalid_cursor_colors =
	{
		{-1, {format_tools::red, format_tools::red, false, false}, ' '},
		{1, {format_tools::none, format_tools::none, false, false}, ' '},
		{2, {format_tools::green, format_tools::green, false, false}, ' '}
	};

	std::vector<format_tools::index_format> new_high_invalid_cursor_colors =
	{
		{0, {format_tools::red, format_tools::red, false, false}, ' '},
		{1, {format_tools::none, format_tools::none, false, false}, ' '},
		{3, {format_tools::green, format_tools::green, false, false}, ' '}
	};

	add_or_load_configuration_parameters_with_colors(local_test_board, "cursor", -1, -1, "(*)", '*', cursor_colors, false, "ascii_board::add_configuration", SUCCESS);
	set_sub_configuration_color_test(local_test_board, "cursor", "(*)", new_valid_cursor_colors, "ascii_board::set_sub_configuration_color", SUCCESS, 0);
	set_sub_configuration_color_test(local_test_board, "cursor", "(*)", new_low_invalid_cursor_colors, "ascii_board::set_sub_configuration_color", INVALID_INDEX, 1);
	set_sub_configuration_color_test(local_test_board, "cursor", "(*)", new_high_invalid_cursor_colors, "ascii_board::set_sub_configuration_color", INVALID_INDEX, 2);
	set_sub_configuration_color_test(local_test_board, "gibberish", "(*)", new_valid_cursor_colors, "ascii_board::set_sub_configuration_color", ELEMENT_NOT_FOUND, 3);
	set_sub_configuration_color_test(local_test_board, "cursor", "123", new_valid_cursor_colors, "ascii_board::set_sub_configuration_color", ELEMENT_NOT_FOUND, 4);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, activate_deactivate_configuration_by_id)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(cursor_config_board);
	local_test_board.add_configuration(x_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);

	activate_deactivate(local_test_board, "cursor", single_line_board_definitions::full_cursor_board, "ascii_board::set_all", SUCCESS, true, 0);
	activate_deactivate(local_test_board, "x", single_line_board_definitions::full_cursor_x_board, "ascii_board::set_all", SUCCESS, true, 1);
	activate_deactivate(local_test_board, "jibberish", single_line_board_definitions::full_cursor_x_board, "ascii_board::activate_configuration", ELEMENT_NOT_FOUND, true, 2);
	activate_deactivate(local_test_board, "jibberish", single_line_board_definitions::full_cursor_x_board, "ascii_board::deactivate_configuration", ELEMENT_NOT_FOUND, false, 3);
	activate_deactivate(local_test_board, "cursor", single_line_board_definitions::full_x_board, "ascii_board::set_all", SUCCESS, false, 4);
	activate_deactivate(local_test_board, "x", single_line_board_definitions::empty_board, "ascii_board::set_all", SUCCESS, false, 5);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, activate_deactivate_configuration_by_coordinate)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(cursor_config_board);
	local_test_board.add_configuration(x_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);

	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 0);
	activate_deactivate(local_test_board, "x", 0, 0, single_line_board_definitions::beginning_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 1);
	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::beginning_x_board, "ascii_board::set_tile", SUCCESS, false, 2);
	activate_deactivate(local_test_board, "x", 0, 0, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 3);
	activate_deactivate(local_test_board, "cursor", 5, 4, single_line_board_definitions::middle_cursor_board, "ascii_board::set_tile", SUCCESS, true, 4);
	activate_deactivate(local_test_board, "x", 5, 4, single_line_board_definitions::middle_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 5);
	activate_deactivate(local_test_board, "cursor", 5, 4, single_line_board_definitions::middle_x_board, "ascii_board::set_tile", SUCCESS, false, 6);
	activate_deactivate(local_test_board, "x", 5, 4, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 7);
	activate_deactivate(local_test_board, "cursor", 9, 9, single_line_board_definitions::end_cursor_board, "ascii_board::set_tile", SUCCESS, true, 8);
	activate_deactivate(local_test_board, "x", 9, 9, single_line_board_definitions::end_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 9);
	activate_deactivate(local_test_board, "cursor", 9, 9, single_line_board_definitions::end_x_board, "ascii_board::set_tile", SUCCESS, false, 10);
	activate_deactivate(local_test_board, "x", 9, 9, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 11);

	activate_deactivate(local_test_board, "jibberish", 0, 0, single_line_board_definitions::empty_board, "ascii_board::activate_configuration", ELEMENT_NOT_FOUND, true, 12);
	activate_deactivate(local_test_board, "jibberish", 0, 0, single_line_board_definitions::empty_board, "ascii_board::deactivate_configuration", ELEMENT_NOT_FOUND, false, 13);

	activate_deactivate(local_test_board, "cursor", 10, 0, single_line_board_definitions::empty_board, "ascii_board::activate_configuration", INVALID_INDEX, true, 14);
	activate_deactivate(local_test_board, "cursor", 10, 0, single_line_board_definitions::empty_board, "ascii_board::deactivate_configuration", INVALID_INDEX, false, 15);
	activate_deactivate(local_test_board, "cursor", 0, 10, single_line_board_definitions::empty_board, "ascii_board::activate_configuration", INVALID_INDEX, true, 16);
	activate_deactivate(local_test_board, "cursor", 0, 10, single_line_board_definitions::empty_board, "ascii_board::deactivate_configuration", INVALID_INDEX, false, 17);
	activate_deactivate(local_test_board, "cursor", 10, 10, single_line_board_definitions::empty_board, "ascii_board::activate_configuration", INVALID_INDEX, true, 18);
	activate_deactivate(local_test_board, "cursor", 10, 10, single_line_board_definitions::empty_board, "ascii_board::deactivate_configuration", INVALID_INDEX, false, 19);
	activate_deactivate(local_test_board, "cursor", 4, 2, single_line_board_definitions::empty_board, "ascii_board::activate_configuration", INVALID_INDEX, true, 20);
	activate_deactivate(local_test_board, "cursor", 4, 2, single_line_board_definitions::empty_board, "ascii_board::deactivate_configuration", INVALID_INDEX, false, 21);

	activate_deactivate(local_test_board, "x", 0, -1, single_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, true, 22);
	activate_deactivate(local_test_board, "x", 0, -1, single_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 23);
	activate_deactivate(local_test_board, "x", 5, -1, single_line_board_definitions::middle_row_x_board, "ascii_board::set_row", SUCCESS, true, 24);
	activate_deactivate(local_test_board, "x", 5, -1, single_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 25);
	activate_deactivate(local_test_board, "x", 9, -1, single_line_board_definitions::end_row_x_board, "ascii_board::set_row", SUCCESS, true, 26);
	activate_deactivate(local_test_board, "x", 9, -1, single_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 27);

	activate_deactivate(local_test_board, "x", -1, 0, single_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, true, 28);
	activate_deactivate(local_test_board, "x", -1, 0, single_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 29);
	activate_deactivate(local_test_board, "x", -1, 2, single_line_board_definitions::middle_column_x_board, "ascii_board::set_column", SUCCESS, true, 30);
	activate_deactivate(local_test_board, "x", -1, 2, single_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 31);
	activate_deactivate(local_test_board, "x", -1, 9, single_line_board_definitions::end_column_x_board, "ascii_board::set_column", SUCCESS, true, 32);
	activate_deactivate(local_test_board, "x", -1, 9, single_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 33);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, set_or_clear_tiles)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	
	set_or_clear(local_test_board, 0, 0, single_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, 0, true, "(*)", '*');
	set_or_clear(local_test_board, 0, 0, single_line_board_definitions::beginning_cursor_x_board, "ascii_board::set_tile", SUCCESS, 1, true, "*x*", '*');
	set_or_clear(local_test_board, 0, 0, single_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 2, false);
	set_or_clear(local_test_board, 5, 4, single_line_board_definitions::middle_cursor_board, "ascii_board::set_tile", SUCCESS, 3, true, "(*)", '*');
	set_or_clear(local_test_board, 5, 4, single_line_board_definitions::middle_cursor_x_board, "ascii_board::set_tile", SUCCESS, 4, true, "*x*", '*');
	set_or_clear(local_test_board, 5, 4, single_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 5, false);
	set_or_clear(local_test_board, 9, 9, single_line_board_definitions::end_cursor_board, "ascii_board::set_tile", SUCCESS, 6, true, "(*)", '*');
	set_or_clear(local_test_board, 9, 9, single_line_board_definitions::end_cursor_x_board, "ascii_board::set_tile", SUCCESS, 7, true, "*x*", '*');
	set_or_clear(local_test_board, 9, 9, single_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 8, false);

	set_or_clear(local_test_board, 10, 0, single_line_board_definitions::empty_board, "ascii_board::set_tile", INVALID_INDEX, 9, true, "(*)", '*');
	set_or_clear(local_test_board, 10, 0, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 10, false);
	set_or_clear(local_test_board, 0, 10, single_line_board_definitions::empty_board, "ascii_board::set_tile", INVALID_INDEX, 11, true, "(*)", '*');
	set_or_clear(local_test_board, 0, 10, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 12, false);
	set_or_clear(local_test_board, 10, 10, single_line_board_definitions::empty_board, "ascii_board::set_tile", INVALID_INDEX, 13, true, "(*)", '*');
	set_or_clear(local_test_board, 10, 10, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 14, false);
	set_or_clear(local_test_board, 4, 2, single_line_board_definitions::empty_board, "ascii_board::set_tile", INVALID_INDEX, 15, true, "(*)", '*');
	set_or_clear(local_test_board, 4, 2, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 16, false);

	set_or_clear(local_test_board, 0, -1, single_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, 17, true, "*x*", '*');
	set_or_clear(local_test_board, 0, -1, single_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 18, false);
	set_or_clear(local_test_board, 5, -1, single_line_board_definitions::middle_row_x_board, "ascii_board::set_row", SUCCESS, 19, true, "*x*", '*');
	set_or_clear(local_test_board, 5, -1, single_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 20, false);
	set_or_clear(local_test_board, 9, -1, single_line_board_definitions::end_row_x_board, "ascii_board::set_row", SUCCESS, 21, true, "*x*", '*');
	set_or_clear(local_test_board, 9, -1, single_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 22, false);

	set_or_clear(local_test_board, -1, 0, single_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, 23, true, "*x*", '*');
	set_or_clear(local_test_board, -1, 0, single_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 24, false);
	set_or_clear(local_test_board, -1, 2, single_line_board_definitions::middle_column_x_board, "ascii_board::set_column", SUCCESS, 25, true, "*x*", '*');
	set_or_clear(local_test_board, -1, 2, single_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 26, false);
	set_or_clear(local_test_board, -1, 9, single_line_board_definitions::end_column_x_board, "ascii_board::set_column", SUCCESS, 27, true, "*x*", '*');
	set_or_clear(local_test_board, -1, 9, single_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 28, false);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, set_or_clear_tiles_with_color)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);

	std::vector<format_tools::index_format> cursor_colors =
	{
		{0, {format_tools::green, format_tools::black, false, false}, ' '}
	};

	std::vector<format_tools::index_format> x_colors =
	{
		{1, {format_tools::red, format_tools::black, false, false}, ' '},
		{2, {format_tools::none, format_tools::none, false, false}, ' '}
	};

	std::vector<format_tools::index_format> cursor_x_colors =
	{
		{0, {format_tools::green, format_tools::black, true, false}, ' '},
		{1, {format_tools::red, format_tools::black, true, false}, ' '},
		{2, {format_tools::none, format_tools::none, true, false}, ' '}
	};

	set_or_clear(local_test_board, 0, 0, single_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, 0, true, cursor_colors, "(*)", '*');
	colors_equivalent(local_test_board, cursor_colors, 0, 0, 0);
	set_or_clear(local_test_board, 0, 0, single_line_board_definitions::beginning_cursor_x_board, "ascii_board::set_tile", SUCCESS, 1, true, cursor_x_colors, "*x*", '*');
	colors_equivalent(local_test_board, cursor_x_colors, 0, 0, 1);
	set_or_clear(local_test_board, 0, 0, single_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 2, false);
	colors_equivalent(local_test_board, empty_colors, 0, 0, 2);
	set_or_clear(local_test_board, 5, 4, single_line_board_definitions::middle_cursor_board, "ascii_board::set_tile", SUCCESS, 3, true, cursor_colors, "(*)", '*');
	colors_equivalent(local_test_board, cursor_colors, 5, 4, 3);
	set_or_clear(local_test_board, 5, 4, single_line_board_definitions::middle_cursor_x_board, "ascii_board::set_tile", SUCCESS, 4, true, cursor_x_colors, "*x*", '*');
	colors_equivalent(local_test_board, cursor_x_colors, 5, 4, 4);
	set_or_clear(local_test_board, 5, 4, single_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 5, false);
	colors_equivalent(local_test_board, empty_colors, 5, 4, 5);
	set_or_clear(local_test_board, 9, 9, single_line_board_definitions::end_cursor_board, "ascii_board::set_tile", SUCCESS, 6, true, cursor_colors, "(*)", '*');
	colors_equivalent(local_test_board, cursor_colors, 9, 9, 6);
	set_or_clear(local_test_board, 9, 9, single_line_board_definitions::end_cursor_x_board, "ascii_board::set_tile", SUCCESS, 7, true, cursor_x_colors, "*x*", '*');
	colors_equivalent(local_test_board, cursor_x_colors, 9, 9, 7);
	set_or_clear(local_test_board, 9, 9, single_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 8, false);
	colors_equivalent(local_test_board, empty_colors, 9, 9, 8);

	set_or_clear(local_test_board, 10, 0, single_line_board_definitions::empty_board, "ascii_board::set_tile", INVALID_INDEX, 9, true, cursor_colors, "(*)", '*');
	set_or_clear(local_test_board, 10, 0, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 10, false);
	set_or_clear(local_test_board, 0, 10, single_line_board_definitions::empty_board, "ascii_board::set_tile", INVALID_INDEX, 11, true, cursor_colors, "(*)", '*');
	set_or_clear(local_test_board, 0, 10, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 12, false);
	set_or_clear(local_test_board, 10, 10, single_line_board_definitions::empty_board, "ascii_board::set_tile", INVALID_INDEX, 13, true, cursor_colors, "(*)", '*');
	set_or_clear(local_test_board, 10, 10, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 14, false);
	set_or_clear(local_test_board, 4, 2, single_line_board_definitions::empty_board, "ascii_board::set_tile", INVALID_INDEX, 15, true, cursor_colors, "(*)", '*');
	set_or_clear(local_test_board, 4, 2, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 16, false);

	set_or_clear(local_test_board, 0, -1, single_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, 17, true, x_colors, "*x*", '*');
	colors_equivalent(local_test_board, x_colors, 0, -1, 9);
	set_or_clear(local_test_board, 0, -1, single_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 18, false);
	colors_equivalent(local_test_board, empty_colors, 0, -1, 10);
	set_or_clear(local_test_board, 5, -1, single_line_board_definitions::middle_row_x_board, "ascii_board::set_row", SUCCESS, 19, true, x_colors, "*x*", '*');
	colors_equivalent(local_test_board, x_colors, 5, -1, 11);
	set_or_clear(local_test_board, 5, -1, single_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 20, false);
	colors_equivalent(local_test_board, empty_colors, 5, -1, 12);
	set_or_clear(local_test_board, 9, -1, single_line_board_definitions::end_row_x_board, "ascii_board::set_row", SUCCESS, 21, true, x_colors, "*x*", '*');
	colors_equivalent(local_test_board, x_colors, 9, -1, 13);
	set_or_clear(local_test_board, 9, -1, single_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 22, false);
	colors_equivalent(local_test_board, empty_colors, 9, -1, 14);

	set_or_clear(local_test_board, -1, 0, single_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, 23, true, x_colors, "*x*", '*');
	colors_equivalent(local_test_board, x_colors, -1, 0, 15);
	set_or_clear(local_test_board, -1, 0, single_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 24, false);
	colors_equivalent(local_test_board, empty_colors, -1, 0, 16);
	set_or_clear(local_test_board, -1, 2, single_line_board_definitions::middle_column_x_board, "ascii_board::set_column", SUCCESS, 25, true, x_colors, "*x*", '*');
	colors_equivalent(local_test_board, x_colors, -1, 2, 17);
	set_or_clear(local_test_board, -1, 2, single_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 26, false);
	colors_equivalent(local_test_board, empty_colors, -1, 2, 18);
	set_or_clear(local_test_board, -1, 9, single_line_board_definitions::end_column_x_board, "ascii_board::set_column", SUCCESS, 27, true, x_colors, "*x*", '*');
	colors_equivalent(local_test_board, x_colors, -1, 9, 19);
	set_or_clear(local_test_board, -1, 9, single_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 28, false);
	colors_equivalent(local_test_board, empty_colors, -1, 9, 20);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, get_number_of_rows)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default");
	int rows = local_test_board.get_number_of_rows();
	EXPECT_EQ(rows, total_rows);
	delete(local_test_frame);
}

TEST_F(ascii_board_test, get_number_of_columns)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default");
	int columns = local_test_board.get_number_of_columns();
	EXPECT_EQ(columns, total_columns);
	delete(local_test_frame);
}

TEST_F(ascii_board_test, get_board)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default");
	std::string board = local_test_board.get_board();
	EXPECT_EQ(board, single_line_board_definitions::empty_board);
	delete(local_test_frame);
}

TEST_F(ascii_board_test, set_get_tile_character)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);
	set_get_tile_character(local_test_board, 0, 0, 'x', 1, single_line_board_definitions::beginning_x_board, "ascii_board::set_tile_character", SUCCESS, true, 0);
	set_get_tile_character(local_test_board, 0, 0, 'x', 1, single_line_board_definitions::beginning_x_board, "ascii_board::get_tile_character", SUCCESS, false, 1);
	set_get_tile_character(local_test_board, 0, 0, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::set_tile_character", SUCCESS, true, 2);
	set_get_tile_character(local_test_board, 0, 0, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", SUCCESS, false, 3);
	set_get_tile_character(local_test_board, 5, 4, 'x', 1, single_line_board_definitions::middle_x_board, "ascii_board::set_tile_character", SUCCESS, true, 4);
	set_get_tile_character(local_test_board, 5, 4, 'x', 1, single_line_board_definitions::middle_x_board, "ascii_board::get_tile_character", SUCCESS, false, 5);
	set_get_tile_character(local_test_board, 5, 4, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::set_tile_character", SUCCESS, true, 6);
	set_get_tile_character(local_test_board, 5, 4, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", SUCCESS, false, 7);
	set_get_tile_character(local_test_board, 9, 9, 'x', 1, single_line_board_definitions::end_x_board, "ascii_board::set_tile_character", SUCCESS, true, 8);
	set_get_tile_character(local_test_board, 9, 9, 'x', 1, single_line_board_definitions::end_x_board, "ascii_board::get_tile_character", SUCCESS, false, 9);
	set_get_tile_character(local_test_board, 9, 9, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::set_tile_character", SUCCESS, true, 10);
	set_get_tile_character(local_test_board, 9, 9, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", SUCCESS, false, 11);
	set_get_tile_character(local_test_board, -1, 0, 'x', 1, single_line_board_definitions::empty_board, "ascii_board::set_tile_character", INVALID_INDEX, true, 12);
	set_get_tile_character(local_test_board, -1, 0, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, false, 13);
	set_get_tile_character(local_test_board, 10, 0, 'x', 1, single_line_board_definitions::empty_board, "ascii_board::set_tile_character", INVALID_INDEX, true, 14);
	set_get_tile_character(local_test_board, 10, 0, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, false, 15);
	set_get_tile_character(local_test_board, 0, -1, 'x', 1, single_line_board_definitions::empty_board, "ascii_board::set_tile_character", INVALID_INDEX, true, 16);
	set_get_tile_character(local_test_board, 0, -1, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, false, 17);
	set_get_tile_character(local_test_board, 0, 10, 'x', 1, single_line_board_definitions::empty_board, "ascii_board::set_tile_character", INVALID_INDEX, true, 18);
	set_get_tile_character(local_test_board, 0, 10, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, false, 19);
	set_get_tile_character(local_test_board, 4, 2, 'x', 1, single_line_board_definitions::empty_board, "ascii_board::set_tile_character", INVALID_INDEX, true, 20);
	set_get_tile_character(local_test_board, 4, 2, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, false, 21);
	set_get_tile_character(local_test_board, 0, 0, 'x', 3, single_line_board_definitions::empty_board, "ascii_board::set_tile_character", INVALID_INDEX, true, 22);
	set_get_tile_character(local_test_board, 0, 0, ' ', 3, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, false, 23);
	set_get_tile_character(local_test_board, 0, 0, 'x', -1, single_line_board_definitions::empty_board, "ascii_board::set_tile_character", INVALID_INDEX, true, 24);
	set_get_tile_character(local_test_board, 0, 0, ' ', -1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, false, 25);
	delete(local_test_frame);
}

TEST_F(ascii_board_test, set_get_tile)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);
	set_get_tile(local_test_board, 0, 0, "(*)", '*', single_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 0);
	set_get_tile(local_test_board, 0, 0, "( )", '*', single_line_board_definitions::beginning_cursor_board, "ascii_board::get_tile", SUCCESS, false, 1);
	set_get_tile(local_test_board, 0, 0, "   ", '*', single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, true, 2);
	set_get_tile(local_test_board, 0, 0, "   ", '*', single_line_board_definitions::empty_board, "ascii_board::get_tile", SUCCESS, false, 3);
	set_get_tile(local_test_board, 5, 4, "(*)", '*', single_line_board_definitions::middle_cursor_board, "ascii_board::set_tile", SUCCESS, true, 4);
	set_get_tile(local_test_board, 5, 4, "( )", '*', single_line_board_definitions::middle_cursor_board, "ascii_board::get_tile", SUCCESS, false, 5);
	set_get_tile(local_test_board, 5, 4, "   ", '*', single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, true, 6);
	set_get_tile(local_test_board, 5, 4, "   ", '*', single_line_board_definitions::empty_board, "ascii_board::get_tile", SUCCESS, false, 7);
	set_get_tile(local_test_board, 9, 9, "(*)", '*', single_line_board_definitions::end_cursor_board, "ascii_board::set_tile", SUCCESS, true, 8);
	set_get_tile(local_test_board, 9, 9, "( )", '*', single_line_board_definitions::end_cursor_board, "ascii_board::get_tile", SUCCESS, false, 9);
	set_get_tile(local_test_board, 9, 9, "   ", '*', single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, true, 10);
	set_get_tile(local_test_board, 9, 9, "   ", '*', single_line_board_definitions::empty_board, "ascii_board::get_tile", SUCCESS, false, 11);
	set_get_tile(local_test_board, -1, 0, "(*)", '*', single_line_board_definitions::empty_board, "ascii_board::set_tile", INVALID_INDEX, true, 12);
	set_get_tile(local_test_board, -1, 0, "", '*', single_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, false, 13);
	set_get_tile(local_test_board, 10, 0, "(*)", '*', single_line_board_definitions::empty_board, "ascii_board::set_tile", INVALID_INDEX, true, 14);
	set_get_tile(local_test_board, 10, 0, "", '*', single_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, false, 15);
	set_get_tile(local_test_board, 0, -1, "(*)", '*', single_line_board_definitions::empty_board, "ascii_board::set_tile", INVALID_INDEX, true, 12);
	set_get_tile(local_test_board, 0, -1, "", '*', single_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, false, 13);
	set_get_tile(local_test_board, 0, 10, "(*)", '*', single_line_board_definitions::empty_board, "ascii_board::set_tile", INVALID_INDEX, true, 14);
	set_get_tile(local_test_board, 0, 10, "", '*', single_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, false, 15);
	set_get_tile(local_test_board, 4, 2, "(*)", '*', single_line_board_definitions::empty_board, "ascii_board::set_tile", INVALID_INDEX, true, 16);
	set_get_tile(local_test_board, 4, 2, "", '*', single_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, false, 17);
	delete(local_test_frame);
}

TEST_F(ascii_board_test, get_action_tile)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);
	ascii_board::action_tile beginning_empty_tile = { 0, 0, {{1, 1, 1, 3}}, "   ", "   ", empty_colors };
	ascii_board::action_tile beginning_cursor_tile = { 0, 0, {{1, 1, 1, 3}}, "   ", "( )", empty_colors };
	test_get_action_tile(local_test_board, 0, 0, beginning_empty_tile, "ascii_board::get_action_tile", SUCCESS, 0);
	local_test_board.set_tile(0, 0, "(*)", '*');
	test_get_action_tile(local_test_board, 0, 0, beginning_cursor_tile, "ascii_board::get_action_tile", SUCCESS, 0);
	delete(local_test_frame);
}

TEST_F(ascii_board_test, configuration_set)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);
	local_test_board.add_configuration(cursor_config_board);
	local_test_board.add_configuration(x_config_board);
	local_test_board.add_configuration(o_config_board);
	local_test_board.add_configuration(arrow_config_board);
	test_configuration_activated(local_test_board, "cursor", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 0);
	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 1);
	test_configuration_activated(local_test_board, "cursor", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 2);
	test_configuration_activated(local_test_board, "x", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 3);
	test_configuration_activated(local_test_board, "cursor", -1, 0, false, "ascii_board::configuration_activated", INVALID_INDEX, 4);
	test_configuration_activated(local_test_board, "cursor", 0, -1, false, "ascii_board::configuration_activated", INVALID_INDEX, 5);
	test_configuration_activated(local_test_board, "cursor", 10, 0, false, "ascii_board::configuration_activated", INVALID_INDEX, 5);
	test_configuration_activated(local_test_board, "cursor", 0, 10, false, "ascii_board::configuration_activated", INVALID_INDEX, 5);
	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 7);
	test_configuration_activated(local_test_board, "cursor", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 8);

	activate_deactivate(local_test_board, "x", 0, -1, single_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, true, 9);
	test_configuration_activated(local_test_board, "x", 0, 6, true, "ascii_board::configuration_activated", SUCCESS, 10);
	activate_deactivate(local_test_board, "x", 0, -1, single_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 11);
	test_configuration_activated(local_test_board, "x", 0, 6, false, "ascii_board::configuration_activated", SUCCESS, 12);
	
	activate_deactivate(local_test_board, "x", -1, 0, single_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, true, 13);
	test_configuration_activated(local_test_board, "x", 9, 0, true, "ascii_board::configuration_activated", SUCCESS, 14);
	activate_deactivate(local_test_board, "x", -1, 0, single_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 15);
	test_configuration_activated(local_test_board, "x", 9, 0, false, "ascii_board::configuration_activated", SUCCESS, 16);

	activate_deactivate(local_test_board, "x", -1, -1, single_line_board_definitions::full_x_board, "ascii_board::set_all", SUCCESS, true, 17);
	test_configuration_activated(local_test_board, "x", 9, 0, true, "ascii_board::configuration_activated", SUCCESS, 18);
	activate_deactivate(local_test_board, "x", -1, -1, single_line_board_definitions::empty_board, "ascii_board::set_all", SUCCESS, false, 19);
	test_configuration_activated(local_test_board, "x", 9, 0, false, "ascii_board::configuration_activated", SUCCESS, 20);

	activate_deactivate(local_test_board, "x", 0, 0, single_line_board_definitions::beginning_x_board, "ascii_board::set_tile", SUCCESS, true, 21);
	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::beginning_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 22);
	test_configuration_activated(local_test_board, "x", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 23);
	test_configuration_activated(local_test_board, "cursor", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 24);
	activate_deactivate(local_test_board, "x", 0, 0, single_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, false, 25);
	test_configuration_activated(local_test_board, "cursor", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 26);
	test_configuration_activated(local_test_board, "x", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 27);
	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 28);
	test_configuration_activated(local_test_board, "cursor", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 29);
	test_configuration_activated(local_test_board, "x", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 30);

	activate_deactivate(local_test_board, "x", 0, 0, single_line_board_definitions::beginning_x_board, "ascii_board::set_tile", SUCCESS, true, 31);
	activate_deactivate(local_test_board, "o", 0, 0, single_line_board_definitions::beginning_o_board, "ascii_board::set_tile", SUCCESS, true, 32);
	test_configuration_activated(local_test_board, "x", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 33);
	test_configuration_activated(local_test_board, "o", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 34);
	activate_deactivate(local_test_board, "o", 0, 0, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 35);

	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 36);
	activate_deactivate(local_test_board, "arrow", 0, 0, single_line_board_definitions::beginning_arrow_board, "ascii_board::set_tile", SUCCESS, true, 37);
	test_configuration_activated(local_test_board, "cursor", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 38);
	test_configuration_activated(local_test_board, "arrow", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 39);
	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 40);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, modify_configuration)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);
	local_test_board.add_configuration(cursor_config_board);
	local_test_board.add_configuration(x_config_board);
	local_test_board.add_configuration(o_config_board);
	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 0);
	test_modify_configuration(local_test_board, "cursor", "x", single_line_board_definitions::beginning_cursor_x_board, "ascii_board::modify_configuration", SUCCESS, 1);
	activate_deactivate(local_test_board, "x", 0, 0, single_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, false, 2);
	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 3);

	activate_deactivate(local_test_board, "x", 0, -1, single_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, true, 4);
	test_modify_configuration(local_test_board, "x", "cursor", single_line_board_definitions::beginning_row_cursor_x_board, "ascii_board::modify_configuration", SUCCESS, 5);
	activate_deactivate(local_test_board, "cursor", 0, -1, single_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, false, 6);
	activate_deactivate(local_test_board, "x", 0, -1, single_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 7);

	activate_deactivate(local_test_board, "x", -1, 0, single_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, true, 8);
	test_modify_configuration(local_test_board, "x", "cursor", single_line_board_definitions::beginning_column_cursor_x_board, "ascii_board::modify_configuration", SUCCESS, 9);
	activate_deactivate(local_test_board, "cursor", -1, 0, single_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, false, 10);
	activate_deactivate(local_test_board, "x", -1, 0, single_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 11);

	activate_deactivate(local_test_board, "x", -1, -1, single_line_board_definitions::full_x_board, "ascii_board::set_all", SUCCESS, true, 12);
	test_modify_configuration(local_test_board, "x", "cursor", single_line_board_definitions::full_cursor_x_board, "ascii_board::modify_configuration", SUCCESS, 13);
	activate_deactivate(local_test_board, "cursor", -1, -1, single_line_board_definitions::full_x_board, "ascii_board::set_all", SUCCESS, false, 14);
	activate_deactivate(local_test_board, "x", -1, -1, single_line_board_definitions::empty_board, "ascii_board::set_all", SUCCESS, false, 15);
	
	activate_deactivate(local_test_board, "x", 0, 0, single_line_board_definitions::beginning_x_board, "ascii_board::set_tile", SUCCESS, true, 16);
	test_modify_configuration(local_test_board, "x", "o", single_line_board_definitions::beginning_o_board, "ascii_board::modify_configuration", SUCCESS, 17);
	activate_deactivate(local_test_board, "o", 0, 0, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 18);

	test_modify_configuration(local_test_board, "x", "gibberish", single_line_board_definitions::empty_board, "ascii_board::modify_configuration", ELEMENT_NOT_FOUND, 19);
	test_modify_configuration(local_test_board, "gibberish", "x", single_line_board_definitions::empty_board, "ascii_board::modify_configuration", ELEMENT_NOT_FOUND, 20);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, load_translation)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);
	std::string log_content = "";
	local_test_board.reset_logging("ascii_board.log");
	local_test_board.load_board_translation("upside down", upside_down_board_config_path);
	int status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	EXPECT_NE(log_content.find("ascii_board::load_board_translation status: " + std::to_string(SUCCESS)), std::string::npos);
	EXPECT_NE(log_content.find("All validations passed."), std::string::npos);

	local_test_board.load_board_translation("bad file path", "gibberish.txt");
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	EXPECT_NE(log_content.find("ascii_board::load_board_translation status: " + std::to_string(INVALID_PATH)), std::string::npos);
	status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, use_translation)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, board_config_path, "default", "none", true);
	std::string log_content = "";
	local_test_board.reset_logging("ascii_board.log");
	local_test_board.load_board_translation("upside down", upside_down_board_config_path);
	int status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	EXPECT_NE(log_content.find("ascii_board::load_board_translation status: " + std::to_string(SUCCESS)), std::string::npos);
	EXPECT_NE(log_content.find("All validations passed."), std::string::npos);

	local_test_board.add_configuration(cursor_config_board);

	use_translation_test(local_test_board, "gibberish", "ascii_board::use_translation", ELEMENT_NOT_FOUND, 0);
	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 1);
	use_translation_test(local_test_board, "upside down", "ascii_board::use_translation", SUCCESS, 2);
	check_board(local_test_board, single_line_board_definitions::end_cursor_upside_down_board, 2);
	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::empty_upside_down_board, "ascii_board::set_tile", SUCCESS, false, 3);
	activate_deactivate(local_test_board, "cursor", 5, 4, single_line_board_definitions::middle_cursor_upside_down_board, "ascii_board::set_tile", SUCCESS, true, 4);
	activate_deactivate(local_test_board, "cursor", 5, 4, single_line_board_definitions::empty_upside_down_board, "ascii_board::set_tile", SUCCESS, false, 5);
	activate_deactivate(local_test_board, "cursor", 9, 9, single_line_board_definitions::beginning_cursor_upside_down_board, "ascii_board::set_tile", SUCCESS, true, 6);
	use_translation_test(local_test_board, "default", "ascii_board::use_translation", SUCCESS, 7);
	check_board(local_test_board, single_line_board_definitions::end_cursor_board, 8);

	delete(local_test_frame);
}