#include "pch.h"
#include "single_line_board_definitions.h"
#include "multi_line_board_definitions.h"
#include "irregular_line_board_definitions.h"
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
	frame* global_test_frame = new frame();
	ascii_board global_test_board = ascii_board(global_test_frame, single_line_board_definitions::board_config_path, "default", "none", true, "global_ascii_board.log");
	int total_rows = 10;
	int total_columns = 10;

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
			
			local_test_board.build();
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

			local_test_board.build();
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
		local_test_board.build();
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

			local_test_board.build();
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

			local_test_board.build();
			std::string board = local_test_board.get_board();
			EXPECT_EQ(board, comparison) << std::to_string(test_num);
		}
	}

	void set_lines_count_test(ascii_board& local_test_board, int lines_count, const std::string& comparison, int test_num)
	{
		local_test_board.set_lines_count(lines_count);

		local_test_board.build();
		std::string displayed_board = local_test_board.get_displayed_output();
		EXPECT_EQ(displayed_board, comparison) << std::to_string(test_num);
	}

	void set_top_display_index_test(ascii_board& local_test_board, unsigned int top_display_index, const std::string& comparison, const std::string& expected_status_function, int expected_status_code, int test_num)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos) << std::to_string(test_num);
		local_test_board.set_top_display_index(top_display_index);
		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);

		local_test_board.build();
		std::string displayed_board = local_test_board.get_displayed_output();
		EXPECT_EQ(displayed_board, comparison) << std::to_string(test_num);
	}

	void set_left_display_index_test(ascii_board& local_test_board, unsigned int left_display_index, const std::string& comparison, const std::string& expected_status_function, int expected_status_code, int test_num)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos) << std::to_string(test_num);
		local_test_board.set_left_display_index(left_display_index);
		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);

		local_test_board.build();
		std::string displayed_board = local_test_board.get_displayed_output();
		EXPECT_EQ(displayed_board, comparison) << std::to_string(test_num);
	}

	void scroll_test(ascii_board& local_test_board, int scroll_amount, const std::string& direction, const std::string& comparison, int test_num)
	{
		if (direction == "up")
		{
			local_test_board.scroll_up(scroll_amount);
		}
		else if (direction == "down")
		{
			local_test_board.scroll_down(scroll_amount);
		}
		else if (direction == "left")
		{
			local_test_board.scroll_left(scroll_amount);
		}
		else if (direction == "right")
		{
			local_test_board.scroll_right(scroll_amount);
		}

		local_test_board.build();
		std::string displayed_board = local_test_board.get_displayed_output();
		EXPECT_EQ(displayed_board, comparison) << std::to_string(test_num);
	}

	void clear(ascii_board& local_test_board, int row, int column, const std::string& comparison, std::string expected_status_function, int expected_status_code, int test_num)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);

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

		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);

		local_test_board.build();
		std::string board = local_test_board.get_board();
		EXPECT_EQ(board, comparison) << std::to_string(test_num);
	}

	void clear(ascii_board& local_test_board, int row, int column, const std::string& comparison, std::string expected_status_function, int expected_status_code, int test_num, std::vector<format_tools::index_format> colors)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);

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

		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);

		local_test_board.build();
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

	void get_tile_character(ascii_board& local_test_board, int row, int column, char character, int character_index, std::string comparision, std::string expected_status_function, int expected_status_code, int test_num)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);

		char returned_character = local_test_board.get_tile_character(row, column, character_index);
		EXPECT_EQ(returned_character, character) << std::to_string(test_num);
		
		status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
	}

	void get_tile(ascii_board& local_test_board, int row, int column, std::string value, std::string comparision, std::string expected_status_function, int expected_status_code, int test_num)
	{
		std::string log_content = "";
		local_test_board.reset_logging("ascii_board.log");
		int status = file_manager::read_file("ascii_board.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);

		std::string returned_value = local_test_board.get_tile(row, column);
		EXPECT_EQ(returned_value, value);

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
		local_test_board.build();
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
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default", "none", 0, true);
	std::string log_content = "";
	int status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	EXPECT_NE(log_content.find("ascii_board::ascii_board status: 0"), std::string::npos);
	EXPECT_NE(log_content.find("All validations passed."), std::string::npos);
	local_test_board.build();
	EXPECT_EQ(local_test_board.get_board(), single_line_board_definitions::empty_board);
	status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	ascii_board local_test_board2(local_test_frame, "jibberish.txt", "default", "none", 0, true);
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
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default", "none", 0, true);

	// add first valid configuration
	add_configuration_structure(local_test_board, single_line_board_definitions::cursor_config_board, "ascii_board::add_configuration", SUCCESS);
	// add second valid configuration
	add_configuration_structure(local_test_board, single_line_board_definitions::x_config_board, "ascii_board::add_configuration", SUCCESS);
	// add duplicate
	add_configuration_structure(local_test_board, single_line_board_definitions::duplicate_name_config_board, "ascii_board::add_configuration", DUPLICATE_ELEMENT);
	// add overlapping
	add_configuration_structure(local_test_board, single_line_board_definitions::overlapping_config_board, "ascii_board::add_configuration", DUPLICATE_ELEMENT);
	// add out of bounds index
	add_configuration_structure(local_test_board, single_line_board_definitions::out_of_bounds_config_board, "ascii_board::add_configuration", INVALID_INDEX);
	// add invalid name
	add_configuration_structure(local_test_board, single_line_board_definitions::invalid_name_config_board, "ascii_board::add_configuration", INVALID_VALUE);

	int status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, add_configuration_parameters)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default", "none", 0, true);

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
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default", "none", 0, true);

	// add first valid configuration
	add_or_load_configuration_parameters_with_colors(local_test_board, "cursor", -1, -1, "(*)", '*', single_line_board_definitions::empty_colors, false, "ascii_board::add_configuration", SUCCESS);
	// add second valid configuration
	add_or_load_configuration_parameters_with_colors(local_test_board, "x", -1, -1, "*x*", '*', single_line_board_definitions::empty_colors, false, "ascii_board::add_configuration", SUCCESS);
	// add duplicate
	add_or_load_configuration_parameters_with_colors(local_test_board, "cursor", -1, -1, "*x*", '*', single_line_board_definitions::empty_colors, false, "ascii_board::add_configuration", DUPLICATE_ELEMENT);
	// add out of bounds index
	add_or_load_configuration_parameters_with_colors(local_test_board, "out_of_bounds", 41, 0, "(*)", '*', single_line_board_definitions::empty_colors, false, "ascii_board::add_configuration", INVALID_INDEX);
	// add invalid name
	add_or_load_configuration_parameters_with_colors(local_test_board, "", -1, -1, "(*)", '*', single_line_board_definitions::empty_colors, false, "ascii_board::add_configuration", INVALID_VALUE);
	int status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, load_configuration)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default");

	// Valid path to config
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	std::string value = local_test_board.load_configuration(single_line_board_definitions::cursor_config_path);
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
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default", "none", 0, true);

	// add first valid configuration
	add_or_load_configuration_parameters(local_test_board, "cursor", -1, -1, single_line_board_definitions::cursor_config_path, '*', true, "ascii_board::add_configuration", SUCCESS);
	// add second valid configuration
	add_or_load_configuration_parameters(local_test_board, "x", -1, -1, single_line_board_definitions::x_config_path, '*', true, "ascii_board::add_configuration", SUCCESS);
	// add duplicate
	add_or_load_configuration_parameters(local_test_board, "cursor", -1, -1, single_line_board_definitions::x_config_path, '*', true, "ascii_board::add_configuration", DUPLICATE_ELEMENT);
	// add out of bounds index
	add_or_load_configuration_parameters(local_test_board, "out_of_bounds", 41, 0, single_line_board_definitions::cursor_config_path, '*', true, "ascii_board::add_configuration", INVALID_INDEX);
	// invalid path
	add_or_load_configuration_parameters(local_test_board, "invalid_path", -1, -1, "jibberish.txt", '*', true, "ascii_board::load_configuration", INVALID_PATH);
	// add invalid name
	add_or_load_configuration_parameters(local_test_board, "", -1, -1, single_line_board_definitions::cursor_config_path, '*', true, "ascii_board::add_configuration", INVALID_VALUE);

	int status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, load_configuration_parameters_with_colors)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default", "none", 0, true);

	// add first valid configuration
	add_or_load_configuration_parameters_with_colors(local_test_board, "cursor", -1, -1, single_line_board_definitions::cursor_config_path, '*', single_line_board_definitions::empty_colors, true, "ascii_board::add_configuration", SUCCESS);
	// add second valid configuration
	add_or_load_configuration_parameters_with_colors(local_test_board, "x", -1, -1, single_line_board_definitions::x_config_path, '*', single_line_board_definitions::empty_colors, true, "ascii_board::add_configuration", SUCCESS);
	// add duplicate
	add_or_load_configuration_parameters_with_colors(local_test_board, "cursor", -1, -1, single_line_board_definitions::x_config_path, '*', single_line_board_definitions::empty_colors, true, "ascii_board::add_configuration", DUPLICATE_ELEMENT);
	// add out of bounds index
	add_or_load_configuration_parameters_with_colors(local_test_board, "out_of_bounds", 41, 0, single_line_board_definitions::cursor_config_path, '*', single_line_board_definitions::empty_colors, true, "ascii_board::add_configuration", INVALID_INDEX);
	// invalid path
	add_or_load_configuration_parameters_with_colors(local_test_board, "invalid_path", -1, -1, "jibberish.txt", '*', single_line_board_definitions::empty_colors, true, "ascii_board::load_configuration", INVALID_PATH);
	// add invalid name
	add_or_load_configuration_parameters_with_colors(local_test_board, "", -1, -1, single_line_board_definitions::cursor_config_path, '*', single_line_board_definitions::empty_colors, true, "ascii_board::add_configuration", INVALID_VALUE);

	int status = file_manager::delete_file("ascii_board.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, sub_configuration_color_test)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default", "none", 0, true);

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

TEST_F(ascii_board_test, activate_deactivate_configuration_by_id_single_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(single_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(single_line_board_definitions::x_config_board);
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

TEST_F(ascii_board_test, activate_deactivate_configuration_by_id_multi_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, multi_line_board_definitions::board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(multi_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(multi_line_board_definitions::x_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);

	activate_deactivate(local_test_board, "cursor", multi_line_board_definitions::full_cursor_board, "ascii_board::set_all", SUCCESS, true, 0);
	activate_deactivate(local_test_board, "x", multi_line_board_definitions::full_cursor_x_board, "ascii_board::set_all", SUCCESS, true, 1);
	activate_deactivate(local_test_board, "jibberish", multi_line_board_definitions::full_cursor_x_board, "ascii_board::activate_configuration", ELEMENT_NOT_FOUND, true, 2);
	activate_deactivate(local_test_board, "jibberish", multi_line_board_definitions::full_cursor_x_board, "ascii_board::deactivate_configuration", ELEMENT_NOT_FOUND, false, 3);
	activate_deactivate(local_test_board, "cursor", multi_line_board_definitions::full_x_board, "ascii_board::set_all", SUCCESS, false, 4);
	activate_deactivate(local_test_board, "x", multi_line_board_definitions::empty_board, "ascii_board::set_all", SUCCESS, false, 5);
}

TEST_F(ascii_board_test, activate_deactivate_configuration_by_id_irregular_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, irregular_line_board_definitions::board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(irregular_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(irregular_line_board_definitions::x_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);

	activate_deactivate(local_test_board, "cursor", irregular_line_board_definitions::full_cursor_board, "ascii_board::set_all", SUCCESS, true, 0);
	activate_deactivate(local_test_board, "x", irregular_line_board_definitions::full_cursor_x_board, "ascii_board::set_all", SUCCESS, true, 1);
	activate_deactivate(local_test_board, "jibberish", irregular_line_board_definitions::full_cursor_x_board, "ascii_board::activate_configuration", ELEMENT_NOT_FOUND, true, 2);
	activate_deactivate(local_test_board, "jibberish", irregular_line_board_definitions::full_cursor_x_board, "ascii_board::deactivate_configuration", ELEMENT_NOT_FOUND, false, 3);
	activate_deactivate(local_test_board, "cursor", irregular_line_board_definitions::full_x_board, "ascii_board::set_all", SUCCESS, false, 4);
	activate_deactivate(local_test_board, "x", irregular_line_board_definitions::empty_board, "ascii_board::set_all", SUCCESS, false, 5);
}

TEST_F(ascii_board_test, activate_deactivate_configuration_by_coordinate_single_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(single_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(single_line_board_definitions::x_config_board);
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

TEST_F(ascii_board_test, activate_deactivate_configuration_by_coordinate_multi_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, multi_line_board_definitions::board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(multi_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(multi_line_board_definitions::x_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);

	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 0);
	activate_deactivate(local_test_board, "x", 0, 0, multi_line_board_definitions::beginning_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 1);
	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::beginning_x_board, "ascii_board::set_tile", SUCCESS, false, 2);
	activate_deactivate(local_test_board, "x", 0, 0, multi_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 3);
	activate_deactivate(local_test_board, "cursor", 3, 3, multi_line_board_definitions::middle_cursor_board, "ascii_board::set_tile", SUCCESS, true, 4);
	activate_deactivate(local_test_board, "x", 3, 3, multi_line_board_definitions::middle_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 5);
	activate_deactivate(local_test_board, "cursor", 3, 3, multi_line_board_definitions::middle_x_board, "ascii_board::set_tile", SUCCESS, false, 6);
	activate_deactivate(local_test_board, "x", 3, 3, multi_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 7);
	activate_deactivate(local_test_board, "cursor", 5, 6, multi_line_board_definitions::end_cursor_board, "ascii_board::set_tile", SUCCESS, true, 8);
	activate_deactivate(local_test_board, "x", 5, 6, multi_line_board_definitions::end_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 9);
	activate_deactivate(local_test_board, "cursor", 5, 6, multi_line_board_definitions::end_x_board, "ascii_board::set_tile", SUCCESS, false, 10);
	activate_deactivate(local_test_board, "x", 5, 6, multi_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 11);

	activate_deactivate(local_test_board, "jibberish", 0, 0, multi_line_board_definitions::empty_board, "ascii_board::activate_configuration", ELEMENT_NOT_FOUND, true, 12);
	activate_deactivate(local_test_board, "jibberish", 0, 0, multi_line_board_definitions::empty_board, "ascii_board::deactivate_configuration", ELEMENT_NOT_FOUND, false, 13);

	activate_deactivate(local_test_board, "cursor", 6, 0, multi_line_board_definitions::empty_board, "ascii_board::activate_configuration", INVALID_INDEX, true, 14);
	activate_deactivate(local_test_board, "cursor", 6, 0, multi_line_board_definitions::empty_board, "ascii_board::deactivate_configuration", INVALID_INDEX, false, 15);
	activate_deactivate(local_test_board, "cursor", 0, 7, multi_line_board_definitions::empty_board, "ascii_board::activate_configuration", INVALID_INDEX, true, 16);
	activate_deactivate(local_test_board, "cursor", 0, 7, multi_line_board_definitions::empty_board, "ascii_board::deactivate_configuration", INVALID_INDEX, false, 17);
	activate_deactivate(local_test_board, "cursor", 6, 6, multi_line_board_definitions::empty_board, "ascii_board::activate_configuration", INVALID_INDEX, true, 18);
	activate_deactivate(local_test_board, "cursor", 6, 6, multi_line_board_definitions::empty_board, "ascii_board::deactivate_configuration", INVALID_INDEX, false, 19);

	activate_deactivate(local_test_board, "x", 0, -1, multi_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, true, 20);
	activate_deactivate(local_test_board, "x", 0, -1, multi_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 21);
	activate_deactivate(local_test_board, "x", 3, -1, multi_line_board_definitions::middle_row_x_board, "ascii_board::set_row", SUCCESS, true, 22);
	activate_deactivate(local_test_board, "x", 3, -1, multi_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 23);
	activate_deactivate(local_test_board, "x", 5, -1, multi_line_board_definitions::end_row_x_board, "ascii_board::set_row", SUCCESS, true, 24);
	activate_deactivate(local_test_board, "x", 5, -1, multi_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 25);

	activate_deactivate(local_test_board, "x", -1, 0, multi_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, true, 26);
	activate_deactivate(local_test_board, "x", -1, 0, multi_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 27);
	activate_deactivate(local_test_board, "x", -1, 3, multi_line_board_definitions::middle_column_x_board, "ascii_board::set_column", SUCCESS, true, 28);
	activate_deactivate(local_test_board, "x", -1, 3, multi_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 29);
	activate_deactivate(local_test_board, "x", -1, 6, multi_line_board_definitions::end_column_x_board, "ascii_board::set_column", SUCCESS, true, 30);
	activate_deactivate(local_test_board, "x", -1, 6, multi_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 31);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, activate_deactivate_configuration_by_coordinate_irregular_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, irregular_line_board_definitions::board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(irregular_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(irregular_line_board_definitions::x_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);

	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 0);
	activate_deactivate(local_test_board, "x", 0, 0, irregular_line_board_definitions::beginning_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 1);
	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::beginning_x_board, "ascii_board::set_tile", SUCCESS, false, 2);
	activate_deactivate(local_test_board, "x", 0, 0, irregular_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 3);
	activate_deactivate(local_test_board, "cursor", 1, 1, irregular_line_board_definitions::middle_cursor_board, "ascii_board::set_tile", SUCCESS, true, 4);
	activate_deactivate(local_test_board, "x", 1, 1, irregular_line_board_definitions::middle_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 5);
	activate_deactivate(local_test_board, "cursor", 1, 1, irregular_line_board_definitions::middle_x_board, "ascii_board::set_tile", SUCCESS, false, 6);
	activate_deactivate(local_test_board, "x", 1, 1, irregular_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 7);
	activate_deactivate(local_test_board, "cursor", 3, 2, irregular_line_board_definitions::end_cursor_board, "ascii_board::set_tile", SUCCESS, true, 8);
	activate_deactivate(local_test_board, "x", 3, 2, irregular_line_board_definitions::end_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 9);
	activate_deactivate(local_test_board, "cursor", 3, 2, irregular_line_board_definitions::end_x_board, "ascii_board::set_tile", SUCCESS, false, 10);
	activate_deactivate(local_test_board, "x", 3, 2, irregular_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 11);

	activate_deactivate(local_test_board, "jibberish", 0, 0, irregular_line_board_definitions::empty_board, "ascii_board::activate_configuration", ELEMENT_NOT_FOUND, true, 12);
	activate_deactivate(local_test_board, "jibberish", 0, 0, irregular_line_board_definitions::empty_board, "ascii_board::deactivate_configuration", ELEMENT_NOT_FOUND, false, 13);

	activate_deactivate(local_test_board, "cursor", 4, 0, irregular_line_board_definitions::empty_board, "ascii_board::activate_configuration", INVALID_INDEX, true, 14);
	activate_deactivate(local_test_board, "cursor", 4, 0, irregular_line_board_definitions::empty_board, "ascii_board::deactivate_configuration", INVALID_INDEX, false, 15);
	activate_deactivate(local_test_board, "cursor", 0, 3, irregular_line_board_definitions::empty_board, "ascii_board::activate_configuration", INVALID_INDEX, true, 16);
	activate_deactivate(local_test_board, "cursor", 0, 3, irregular_line_board_definitions::empty_board, "ascii_board::deactivate_configuration", INVALID_INDEX, false, 17);
	activate_deactivate(local_test_board, "cursor", 4, 3, irregular_line_board_definitions::empty_board, "ascii_board::activate_configuration", INVALID_INDEX, true, 18);
	activate_deactivate(local_test_board, "cursor", 4, 3, irregular_line_board_definitions::empty_board, "ascii_board::deactivate_configuration", INVALID_INDEX, false, 19);

	activate_deactivate(local_test_board, "x", 0, -1, irregular_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, true, 20);
	activate_deactivate(local_test_board, "x", 0, -1, irregular_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 21);
	activate_deactivate(local_test_board, "x", 1, -1, irregular_line_board_definitions::middle_row_x_board, "ascii_board::set_row", SUCCESS, true, 22);
	activate_deactivate(local_test_board, "x", 1, -1, irregular_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 23);
	activate_deactivate(local_test_board, "x", 3, -1, irregular_line_board_definitions::end_row_x_board, "ascii_board::set_row", SUCCESS, true, 24);
	activate_deactivate(local_test_board, "x", 3, -1, irregular_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 25);

	activate_deactivate(local_test_board, "x", -1, 0, irregular_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, true, 26);
	activate_deactivate(local_test_board, "x", -1, 0, irregular_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 27);
	activate_deactivate(local_test_board, "x", -1, 1, irregular_line_board_definitions::middle_column_x_board, "ascii_board::set_column", SUCCESS, true, 28);
	activate_deactivate(local_test_board, "x", -1, 1, irregular_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 29);
	activate_deactivate(local_test_board, "x", -1, 2, irregular_line_board_definitions::end_column_x_board, "ascii_board::set_column", SUCCESS, true, 30);
	activate_deactivate(local_test_board, "x", -1, 2, irregular_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 31);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, clear_tiles_single_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(single_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(single_line_board_definitions::x_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);
	
	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 0);
	activate_deactivate(local_test_board, "x", 0, 0, single_line_board_definitions::beginning_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 1);
	clear(local_test_board, 0, 0, single_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 2);
	activate_deactivate(local_test_board, "cursor", 5, 4, single_line_board_definitions::middle_cursor_board, "ascii_board::set_tile", SUCCESS, true, 3);
	activate_deactivate(local_test_board, "x", 5, 4, single_line_board_definitions::middle_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 4);
	clear(local_test_board, 5, 4, single_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 5);
	activate_deactivate(local_test_board, "cursor", 9, 9, single_line_board_definitions::end_cursor_board, "ascii_board::set_tile", SUCCESS, true, 6);
	activate_deactivate(local_test_board, "x", 9, 9, single_line_board_definitions::end_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 7);
	clear(local_test_board, 9, 9, single_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 8);

	clear(local_test_board, 10, 0, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 9);
	clear(local_test_board, 0, 10, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 10);
	clear(local_test_board, 10, 10, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 11);
	clear(local_test_board, 4, 2, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 12);

	activate_deactivate(local_test_board, "x", 0, -1, single_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, true, 13);
	clear(local_test_board, 0, -1, single_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 14);
	activate_deactivate(local_test_board, "x", 5, -1, single_line_board_definitions::middle_row_x_board, "ascii_board::set_row", SUCCESS, true, 15);
	clear(local_test_board, 5, -1, single_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 16);
	activate_deactivate(local_test_board, "x", 9, -1, single_line_board_definitions::end_row_x_board, "ascii_board::set_row", SUCCESS, true, 17);
	clear(local_test_board, 9, -1, single_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 18);

	activate_deactivate(local_test_board, "x", -1, 0, single_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, true, 19);
	clear(local_test_board, -1, 0, single_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 20);
	activate_deactivate(local_test_board, "x", -1, 2, single_line_board_definitions::middle_column_x_board, "ascii_board::set_column", SUCCESS, true, 21);
	clear(local_test_board, -1, 2, single_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 22);
	activate_deactivate(local_test_board, "x", -1, 9, single_line_board_definitions::end_column_x_board, "ascii_board::set_column", SUCCESS, true, 23);
	clear(local_test_board, -1, 9, single_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 24);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, clear_tiles_multi_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, multi_line_board_definitions::board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(multi_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(multi_line_board_definitions::x_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);

	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 0);
	activate_deactivate(local_test_board, "x", 0, 0, multi_line_board_definitions::beginning_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 1);
	clear(local_test_board, 0, 0, multi_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 2);
	activate_deactivate(local_test_board, "cursor", 3, 3, multi_line_board_definitions::middle_cursor_board, "ascii_board::set_tile", SUCCESS, true, 3);
	activate_deactivate(local_test_board, "x", 3, 3, multi_line_board_definitions::middle_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 4);
	clear(local_test_board, 3, 3, multi_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 5);
	activate_deactivate(local_test_board, "cursor", 5, 6, multi_line_board_definitions::end_cursor_board, "ascii_board::set_tile", SUCCESS, true, 6);
	activate_deactivate(local_test_board, "x", 5, 6, multi_line_board_definitions::end_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 7);
	clear(local_test_board, 5, 6, multi_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 8);

	clear(local_test_board, 6, 0, multi_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 9);
	clear(local_test_board, 0, 7, multi_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 10);
	clear(local_test_board, 6, 7, multi_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 11);

	activate_deactivate(local_test_board, "x", 0, -1, multi_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, true, 12);
	clear(local_test_board, 0, -1, multi_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 13);
	activate_deactivate(local_test_board, "x", 3, -1, multi_line_board_definitions::middle_row_x_board, "ascii_board::set_row", SUCCESS, true, 14);
	clear(local_test_board, 3, -1, multi_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 15);
	activate_deactivate(local_test_board, "x", 5, -1, multi_line_board_definitions::end_row_x_board, "ascii_board::set_row", SUCCESS, true, 16);
	clear(local_test_board, 5, -1, multi_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 17);

	activate_deactivate(local_test_board, "x", -1, 0, multi_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, true, 18);
	clear(local_test_board, -1, 0, multi_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 19);
	activate_deactivate(local_test_board, "x", -1, 3, multi_line_board_definitions::middle_column_x_board, "ascii_board::set_column", SUCCESS, true, 20);
	clear(local_test_board, -1, 3, multi_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 21);
	activate_deactivate(local_test_board, "x", -1, 6, multi_line_board_definitions::end_column_x_board, "ascii_board::set_column", SUCCESS, true, 22);
	clear(local_test_board, -1, 6, multi_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 23);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, clear_tiles_irregular_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, irregular_line_board_definitions::board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(irregular_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(irregular_line_board_definitions::x_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);

	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 0);
	activate_deactivate(local_test_board, "x", 0, 0, irregular_line_board_definitions::beginning_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 1);
	clear(local_test_board, 0, 0, irregular_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 2);
	activate_deactivate(local_test_board, "cursor", 1, 1, irregular_line_board_definitions::middle_cursor_board, "ascii_board::set_tile", SUCCESS, true, 3);
	activate_deactivate(local_test_board, "x", 1, 1, irregular_line_board_definitions::middle_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 4);
	clear(local_test_board, 1, 1, irregular_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 5);
	activate_deactivate(local_test_board, "cursor", 3, 2, irregular_line_board_definitions::end_cursor_board, "ascii_board::set_tile", SUCCESS, true, 6);
	activate_deactivate(local_test_board, "x", 3, 2, irregular_line_board_definitions::end_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 7);
	clear(local_test_board, 3, 2, irregular_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 8);

	clear(local_test_board, 4, 0, irregular_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 9);
	clear(local_test_board, 0, 3, irregular_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 10);
	clear(local_test_board, 4, 3, irregular_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 11);

	activate_deactivate(local_test_board, "x", 0, -1, irregular_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, true, 12);
	clear(local_test_board, 0, -1, irregular_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 13);
	activate_deactivate(local_test_board, "x", 1, -1, irregular_line_board_definitions::middle_row_x_board, "ascii_board::set_row", SUCCESS, true, 14);
	clear(local_test_board, 1, -1, irregular_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 15);
	activate_deactivate(local_test_board, "x", 3, -1, irregular_line_board_definitions::end_row_x_board, "ascii_board::set_row", SUCCESS, true, 16);
	clear(local_test_board, 3, -1, irregular_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 17);

	activate_deactivate(local_test_board, "x", -1, 0, irregular_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, true, 18);
	clear(local_test_board, -1, 0, irregular_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 19);
	activate_deactivate(local_test_board, "x", -1, 1, irregular_line_board_definitions::middle_column_x_board, "ascii_board::set_column", SUCCESS, true, 20);
	clear(local_test_board, -1, 1, irregular_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 21);
	activate_deactivate(local_test_board, "x", -1, 2, irregular_line_board_definitions::end_column_x_board, "ascii_board::set_column", SUCCESS, true, 22);
	clear(local_test_board, -1, 2, irregular_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 22);

	delete(local_test_frame);
}


TEST_F(ascii_board_test, clear_tiles_with_color)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default");
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
	const board_configuration cursor_config_board{ "cursor", {{ -1, -1, "(*)", '*', cursor_colors }} };

	const board_configuration x_config_board{ "x", {{ -1, -1, "*x*", '*', x_colors }} };

	local_test_board.add_configuration(cursor_config_board);
	local_test_board.add_configuration(x_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);

	

	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 0);
	colors_equivalent(local_test_board, cursor_colors, 0, 0, 0);
	activate_deactivate(local_test_board, "x", 0, 0, single_line_board_definitions::beginning_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 1);
	colors_equivalent(local_test_board, cursor_x_colors, 0, 0, 1);
	clear(local_test_board, 0, 0, single_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 2);
	colors_equivalent(local_test_board, single_line_board_definitions::empty_colors, 0, 0, 2);
	activate_deactivate(local_test_board, "cursor", 5, 4, single_line_board_definitions::middle_cursor_board, "ascii_board::set_tile", SUCCESS, true, 3);
	colors_equivalent(local_test_board, cursor_colors, 5, 4, 3);
	activate_deactivate(local_test_board, "x", 5, 4, single_line_board_definitions::middle_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 4);
	colors_equivalent(local_test_board, cursor_x_colors, 5, 4, 4);
	clear(local_test_board, 5, 4, single_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 5);
	colors_equivalent(local_test_board, single_line_board_definitions::empty_colors, 5, 4, 5);
	activate_deactivate(local_test_board, "cursor", 9, 9, single_line_board_definitions::end_cursor_board, "ascii_board::set_tile", SUCCESS, true, 6);
	colors_equivalent(local_test_board, cursor_colors, 9, 9, 6);
	activate_deactivate(local_test_board, "x", 9, 9, single_line_board_definitions::end_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 7);
	colors_equivalent(local_test_board, cursor_x_colors, 9, 9, 7);
	clear(local_test_board, 9, 9, single_line_board_definitions::empty_board, "ascii_board::clear_tile", SUCCESS, 8);
	colors_equivalent(local_test_board, single_line_board_definitions::empty_colors, 9, 9, 8);

	clear(local_test_board, 10, 0, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 9);
	clear(local_test_board, 0, 10, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 10);
	clear(local_test_board, 10, 10, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 11);
	clear(local_test_board, 4, 2, single_line_board_definitions::empty_board, "ascii_board::clear_tile", INVALID_INDEX, 12);

	activate_deactivate(local_test_board, "x", 0, -1, single_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, true, 13);
	colors_equivalent(local_test_board, x_colors, 0, -1, 13);
	clear(local_test_board, 0, -1, single_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 14);
	colors_equivalent(local_test_board, single_line_board_definitions::empty_colors, 0, -1, 14);
	activate_deactivate(local_test_board, "x", 5, -1, single_line_board_definitions::middle_row_x_board, "ascii_board::set_row", SUCCESS, true, 15);
	colors_equivalent(local_test_board, x_colors, 5, -1, 15);
	clear(local_test_board, 5, -1, single_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 16);
	colors_equivalent(local_test_board, single_line_board_definitions::empty_colors, 5, -1, 16);
	activate_deactivate(local_test_board, "x", 9, -1, single_line_board_definitions::end_row_x_board, "ascii_board::set_row", SUCCESS, true, 17);
	colors_equivalent(local_test_board, x_colors, 9, -1, 17);
	clear(local_test_board, 9, -1, single_line_board_definitions::empty_board, "ascii_board::clear_row", SUCCESS, 18);
	colors_equivalent(local_test_board, single_line_board_definitions::empty_colors, 9, -1, 18);

	activate_deactivate(local_test_board, "x", -1, 0, single_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, true, 19);
	colors_equivalent(local_test_board, x_colors, -1, 0, 19);
	clear(local_test_board, -1, 0, single_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 20);
	colors_equivalent(local_test_board, single_line_board_definitions::empty_colors, -1, 0, 20);
	activate_deactivate(local_test_board, "x", -1, 2, single_line_board_definitions::middle_column_x_board, "ascii_board::set_column", SUCCESS, true, 21);
	colors_equivalent(local_test_board, x_colors, -1, 2, 21);
	clear(local_test_board, -1, 2, single_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 22);
	colors_equivalent(local_test_board, single_line_board_definitions::empty_colors, -1, 2, 22);
	activate_deactivate(local_test_board, "x", -1, 9, single_line_board_definitions::end_column_x_board, "ascii_board::set_column", SUCCESS, true, 23);
	colors_equivalent(local_test_board, x_colors, -1, 9, 23);
	clear(local_test_board, -1, 9, single_line_board_definitions::empty_board, "ascii_board::clear_column", SUCCESS, 24);
	colors_equivalent(local_test_board, single_line_board_definitions::empty_colors, -1, 9, 24);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, get_number_of_rows)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default");
	int rows = local_test_board.get_number_of_rows();
	EXPECT_EQ(rows, total_rows);
	delete(local_test_frame);
}

TEST_F(ascii_board_test, get_number_of_columns)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default");
	int columns = local_test_board.get_number_of_columns();
	EXPECT_EQ(columns, total_columns);
	delete(local_test_frame);
}

TEST_F(ascii_board_test, get_board)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default");
	local_test_board.build();
	std::string board = local_test_board.get_board();
	EXPECT_EQ(board, single_line_board_definitions::empty_board);
	delete(local_test_frame);
}

TEST_F(ascii_board_test, set_get_tile_character)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(single_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(single_line_board_definitions::x_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);

	activate_deactivate(local_test_board, "x", 0, 0, single_line_board_definitions::beginning_x_board, "ascii_board::set_tile", SUCCESS, true, 0);
	get_tile_character(local_test_board, 0, 0, 'x', 1, single_line_board_definitions::beginning_x_board, "ascii_board::get_tile_character", SUCCESS, 1);
	activate_deactivate(local_test_board, "x", 0, 0, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 2);
	activate_deactivate(local_test_board, "x", 5, 4, single_line_board_definitions::middle_x_board, "ascii_board::set_tile", SUCCESS, true, 3);
	get_tile_character(local_test_board, 5, 4, 'x', 1, single_line_board_definitions::middle_x_board, "ascii_board::get_tile_character", SUCCESS, 4);
	activate_deactivate(local_test_board, "x", 5, 4, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 5);
	activate_deactivate(local_test_board, "x", 9, 9, single_line_board_definitions::end_x_board, "ascii_board::set_tile", SUCCESS, true, 6);
	get_tile_character(local_test_board, 9, 9, 'x', 1, single_line_board_definitions::end_x_board, "ascii_board::get_tile_character", SUCCESS, 7);
	activate_deactivate(local_test_board, "x", 9, 9, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 8);
	get_tile_character(local_test_board, -1, 0, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, 9);
	get_tile_character(local_test_board, 10, 0, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, 10);
	get_tile_character(local_test_board, 0, -1, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, 11);
	get_tile_character(local_test_board, 0, 10, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, 12);
	get_tile_character(local_test_board, 4, 2, ' ', 1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, 13);
	get_tile_character(local_test_board, 0, 0, ' ', 3, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, 14);
	get_tile_character(local_test_board, 0, 0, ' ', -1, single_line_board_definitions::empty_board, "ascii_board::get_tile_character", INVALID_INDEX, 15);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, get_tile_single_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(single_line_board_definitions::cursor_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);

	get_tile(local_test_board, 0, 0, "   ", single_line_board_definitions::beginning_cursor_board, "ascii_board::get_tile", SUCCESS, 0);
	get_tile(local_test_board, 5, 4, "   ", single_line_board_definitions::middle_cursor_board, "ascii_board::get_tile", SUCCESS, 1);
	get_tile(local_test_board, 9, 9, "   ", single_line_board_definitions::end_cursor_board, "ascii_board::get_tile", SUCCESS, 2);

	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 3);
	get_tile(local_test_board, 0, 0, "( )", single_line_board_definitions::beginning_cursor_board, "ascii_board::get_tile", SUCCESS, 4);
	activate_deactivate(local_test_board, "cursor", 0, 0, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 5);
	activate_deactivate(local_test_board, "cursor", 5, 4, single_line_board_definitions::middle_cursor_board, "ascii_board::set_tile", SUCCESS, true, 6);
	get_tile(local_test_board, 5, 4, "( )", single_line_board_definitions::middle_cursor_board, "ascii_board::get_tile", SUCCESS, 7);
	activate_deactivate(local_test_board, "cursor", 5, 4, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 8);
	activate_deactivate(local_test_board, "cursor", 9, 9, single_line_board_definitions::end_cursor_board, "ascii_board::set_tile", SUCCESS, true, 9);
	get_tile(local_test_board, 9, 9, "( )", single_line_board_definitions::end_cursor_board, "ascii_board::get_tile", SUCCESS, 10);
	activate_deactivate(local_test_board, "cursor", 9, 9, single_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 11);

	get_tile(local_test_board, -1, 0, "", single_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, 12);
	get_tile(local_test_board, 10, 0, "", single_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, 13);
	get_tile(local_test_board, 0, -1, "", single_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, 14);
	get_tile(local_test_board, 0, 10, "", single_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, 15);
	get_tile(local_test_board, 4, 2, "", single_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, 16);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, get_tile_multi_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, multi_line_board_definitions::board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(multi_line_board_definitions::cursor_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);

	get_tile(local_test_board, 0, 0, "             *             ", multi_line_board_definitions::empty_board, "ascii_board::get_tile", SUCCESS, 0);
	get_tile(local_test_board, 3, 3, "             *             ", multi_line_board_definitions::empty_board, "ascii_board::get_tile", SUCCESS, 1);
	get_tile(local_test_board, 5, 6, "             *             ", multi_line_board_definitions::empty_board, "ascii_board::get_tile", SUCCESS, 2);

	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 3);
	get_tile(local_test_board, 0, 0, " /     \\ |   *   | \\     / ", multi_line_board_definitions::beginning_cursor_board, "ascii_board::get_tile", SUCCESS, 4);
	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 5);
	activate_deactivate(local_test_board, "cursor", 3, 3, multi_line_board_definitions::middle_cursor_board, "ascii_board::set_tile", SUCCESS, true, 6);
	get_tile(local_test_board, 3, 3, " /     \\ |   *   | \\     / ", multi_line_board_definitions::middle_cursor_board, "ascii_board::get_tile", SUCCESS, 7);
	activate_deactivate(local_test_board, "cursor", 3, 3, multi_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 8);
	activate_deactivate(local_test_board, "cursor", 5, 6, multi_line_board_definitions::end_cursor_board, "ascii_board::set_tile", SUCCESS, true, 9);
	get_tile(local_test_board, 5, 6, " /     \\ |   *   | \\     / ", multi_line_board_definitions::end_cursor_board, "ascii_board::get_tile", SUCCESS, 10);
	activate_deactivate(local_test_board, "cursor", 5, 6, multi_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 11);

	get_tile(local_test_board, -1, 0, "", multi_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, 12);
	get_tile(local_test_board, 6, 0, "", multi_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, 13);
	get_tile(local_test_board, 0, -1, "", multi_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, 14);
	get_tile(local_test_board, 0, 7, "", multi_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, 15);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, get_tile_irregular_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, irregular_line_board_definitions::board_config_path, "default");
	int status = local_test_board.start_logging("ascii_board.log");
	ASSERT_EQ(status, 0);
	local_test_board.add_configuration(irregular_line_board_definitions::cursor_config_board);
	std::string log_content = "";
	status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	ASSERT_NE(log_content.find("ascii_board::add_configuration status: " + std::to_string(SUCCESS)), std::string::npos);
	ASSERT_EQ(log_content.find("ascii_board::add_configuration status: " + std::to_string(ELEMENT_NOT_FOUND)), std::string::npos);

	get_tile(local_test_board, 0, 0, "                                                                        ", irregular_line_board_definitions::empty_board, "ascii_board::get_tile", SUCCESS, 0);
	get_tile(local_test_board, 1, 1, "                                                                        ", irregular_line_board_definitions::empty_board, "ascii_board::get_tile", SUCCESS, 1);
	get_tile(local_test_board, 3, 2, "                                                                        ", irregular_line_board_definitions::empty_board, "ascii_board::get_tile", SUCCESS, 2);

	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 3);
	get_tile(local_test_board, 0, 0, "/        \\/          \\/            \\\\            /\\          /\\        /", irregular_line_board_definitions::beginning_cursor_board, "ascii_board::get_tile", SUCCESS, 4);
	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 5);
	activate_deactivate(local_test_board, "cursor", 1, 1, irregular_line_board_definitions::middle_cursor_board, "ascii_board::set_tile", SUCCESS, true, 6);
	get_tile(local_test_board, 1, 1, "/        \\/          \\/            \\\\            /\\          /\\        /", irregular_line_board_definitions::middle_cursor_board, "ascii_board::get_tile", SUCCESS, 7);
	activate_deactivate(local_test_board, "cursor", 1, 1, irregular_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 8);
	activate_deactivate(local_test_board, "cursor", 3, 2, irregular_line_board_definitions::end_cursor_board, "ascii_board::set_tile", SUCCESS, true, 9);
	get_tile(local_test_board, 3, 2, "/        \\/          \\/            \\\\            /\\          /\\        /", irregular_line_board_definitions::end_cursor_board, "ascii_board::get_tile", SUCCESS, 10);
	activate_deactivate(local_test_board, "cursor", 3, 2, irregular_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 11);

	get_tile(local_test_board, -1, 0, "", irregular_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, 12);
	get_tile(local_test_board, 4, 0, "", irregular_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, 13);
	get_tile(local_test_board, 0, -1, "", irregular_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, 14);
	get_tile(local_test_board, 0, 3, "", irregular_line_board_definitions::empty_board, "ascii_board::get_tile", INVALID_INDEX, 15);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, configuration_set_single_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default", "none", 0, true);
	local_test_board.add_configuration(single_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(single_line_board_definitions::x_config_board);
	local_test_board.add_configuration(single_line_board_definitions::o_config_board);
	local_test_board.add_configuration(single_line_board_definitions::arrow_config_board);
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

TEST_F(ascii_board_test, configuration_set_multi_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, multi_line_board_definitions::board_config_path, "default", "none", 0, true);
	local_test_board.add_configuration(multi_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(multi_line_board_definitions::x_config_board);
	local_test_board.add_configuration(multi_line_board_definitions::o_config_board);
	local_test_board.add_configuration(multi_line_board_definitions::arrow_config_board);
	test_configuration_activated(local_test_board, "cursor", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 0);
	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 1);
	test_configuration_activated(local_test_board, "cursor", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 2);
	test_configuration_activated(local_test_board, "x", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 3);
	test_configuration_activated(local_test_board, "cursor", -1, 0, false, "ascii_board::configuration_activated", INVALID_INDEX, 4);
	test_configuration_activated(local_test_board, "cursor", 0, -1, false, "ascii_board::configuration_activated", INVALID_INDEX, 5);
	test_configuration_activated(local_test_board, "cursor", 6, 0, false, "ascii_board::configuration_activated", INVALID_INDEX, 5);
	test_configuration_activated(local_test_board, "cursor", 0, 7, false, "ascii_board::configuration_activated", INVALID_INDEX, 5);
	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 7);
	test_configuration_activated(local_test_board, "cursor", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 8);

	activate_deactivate(local_test_board, "x", 0, -1, multi_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, true, 9);
	test_configuration_activated(local_test_board, "x", 0, 6, true, "ascii_board::configuration_activated", SUCCESS, 10);
	activate_deactivate(local_test_board, "x", 0, -1, multi_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 11);
	test_configuration_activated(local_test_board, "x", 0, 6, false, "ascii_board::configuration_activated", SUCCESS, 12);

	activate_deactivate(local_test_board, "x", -1, 0, multi_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, true, 13);
	test_configuration_activated(local_test_board, "x", 5, 0, true, "ascii_board::configuration_activated", SUCCESS, 14);
	activate_deactivate(local_test_board, "x", -1, 0, multi_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 15);
	test_configuration_activated(local_test_board, "x", 5, 0, false, "ascii_board::configuration_activated", SUCCESS, 16);

	activate_deactivate(local_test_board, "x", -1, -1, multi_line_board_definitions::full_x_board, "ascii_board::set_all", SUCCESS, true, 17);
	test_configuration_activated(local_test_board, "x", 5, 0, true, "ascii_board::configuration_activated", SUCCESS, 18);
	activate_deactivate(local_test_board, "x", -1, -1, multi_line_board_definitions::empty_board, "ascii_board::set_all", SUCCESS, false, 19);
	test_configuration_activated(local_test_board, "x", 5, 0, false, "ascii_board::configuration_activated", SUCCESS, 20);

	activate_deactivate(local_test_board, "x", 0, 0, multi_line_board_definitions::beginning_x_board, "ascii_board::set_tile", SUCCESS, true, 21);
	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::beginning_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 22);
	test_configuration_activated(local_test_board, "x", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 23);
	test_configuration_activated(local_test_board, "cursor", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 24);
	activate_deactivate(local_test_board, "x", 0, 0, multi_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, false, 25);
	test_configuration_activated(local_test_board, "cursor", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 26);
	test_configuration_activated(local_test_board, "x", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 27);
	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 28);
	test_configuration_activated(local_test_board, "cursor", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 29);
	test_configuration_activated(local_test_board, "x", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 30);

	activate_deactivate(local_test_board, "x", 0, 0, multi_line_board_definitions::beginning_x_board, "ascii_board::set_tile", SUCCESS, true, 31);
	activate_deactivate(local_test_board, "o", 0, 0, multi_line_board_definitions::beginning_o_board, "ascii_board::set_tile", SUCCESS, true, 32);
	test_configuration_activated(local_test_board, "x", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 33);
	test_configuration_activated(local_test_board, "o", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 34);
	activate_deactivate(local_test_board, "o", 0, 0, multi_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 35);

	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 36);
	activate_deactivate(local_test_board, "arrow", 0, 0, multi_line_board_definitions::beginning_arrow_board, "ascii_board::set_tile", SUCCESS, true, 37);
	test_configuration_activated(local_test_board, "cursor", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 38);
	test_configuration_activated(local_test_board, "arrow", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 39);
	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 40);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, configuration_set_irregular_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, irregular_line_board_definitions::board_config_path, "default", "none", 0, true);
	local_test_board.add_configuration(irregular_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(irregular_line_board_definitions::x_config_board);
	local_test_board.add_configuration(irregular_line_board_definitions::o_config_board);
	local_test_board.add_configuration(irregular_line_board_definitions::arrow_config_board);
	test_configuration_activated(local_test_board, "cursor", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 0);
	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 1);
	test_configuration_activated(local_test_board, "cursor", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 2);
	test_configuration_activated(local_test_board, "x", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 3);
	test_configuration_activated(local_test_board, "cursor", -1, 0, false, "ascii_board::configuration_activated", INVALID_INDEX, 4);
	test_configuration_activated(local_test_board, "cursor", 0, -1, false, "ascii_board::configuration_activated", INVALID_INDEX, 5);
	test_configuration_activated(local_test_board, "cursor", 4, 0, false, "ascii_board::configuration_activated", INVALID_INDEX, 5);
	test_configuration_activated(local_test_board, "cursor", 0, 3, false, "ascii_board::configuration_activated", INVALID_INDEX, 5);
	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 7);
	test_configuration_activated(local_test_board, "cursor", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 8);

	activate_deactivate(local_test_board, "x", 0, -1, irregular_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, true, 9);
	test_configuration_activated(local_test_board, "x", 0, 2, true, "ascii_board::configuration_activated", SUCCESS, 10);
	activate_deactivate(local_test_board, "x", 0, -1, irregular_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 11);
	test_configuration_activated(local_test_board, "x", 0, 2, false, "ascii_board::configuration_activated", SUCCESS, 12);

	activate_deactivate(local_test_board, "x", -1, 0, irregular_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, true, 13);
	test_configuration_activated(local_test_board, "x", 3, 0, true, "ascii_board::configuration_activated", SUCCESS, 14);
	activate_deactivate(local_test_board, "x", -1, 0, irregular_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 15);
	test_configuration_activated(local_test_board, "x", 3, 0, false, "ascii_board::configuration_activated", SUCCESS, 16);

	activate_deactivate(local_test_board, "x", -1, -1, irregular_line_board_definitions::full_x_board, "ascii_board::set_all", SUCCESS, true, 17);
	test_configuration_activated(local_test_board, "x", 3, 0, true, "ascii_board::configuration_activated", SUCCESS, 18);
	activate_deactivate(local_test_board, "x", -1, -1, irregular_line_board_definitions::empty_board, "ascii_board::set_all", SUCCESS, false, 19);
	test_configuration_activated(local_test_board, "x", 3, 0, false, "ascii_board::configuration_activated", SUCCESS, 20);

	activate_deactivate(local_test_board, "x", 0, 0, irregular_line_board_definitions::beginning_x_board, "ascii_board::set_tile", SUCCESS, true, 21);
	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::beginning_cursor_x_board, "ascii_board::set_tile", SUCCESS, true, 22);
	test_configuration_activated(local_test_board, "x", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 23);
	test_configuration_activated(local_test_board, "cursor", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 24);
	activate_deactivate(local_test_board, "x", 0, 0, irregular_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, false, 25);
	test_configuration_activated(local_test_board, "cursor", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 26);
	test_configuration_activated(local_test_board, "x", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 27);
	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 28);
	test_configuration_activated(local_test_board, "cursor", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 29);
	test_configuration_activated(local_test_board, "x", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 30);

	activate_deactivate(local_test_board, "x", 0, 0, irregular_line_board_definitions::beginning_x_board, "ascii_board::set_tile", SUCCESS, true, 31);
	activate_deactivate(local_test_board, "o", 0, 0, irregular_line_board_definitions::beginning_o_board, "ascii_board::set_tile", SUCCESS, true, 32);
	test_configuration_activated(local_test_board, "x", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 33);
	test_configuration_activated(local_test_board, "o", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 34);
	activate_deactivate(local_test_board, "o", 0, 0, irregular_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 35);

	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 36);
	activate_deactivate(local_test_board, "arrow", 0, 0, irregular_line_board_definitions::beginning_arrow_board, "ascii_board::set_tile", SUCCESS, true, 37);
	test_configuration_activated(local_test_board, "cursor", 0, 0, false, "ascii_board::configuration_activated", SUCCESS, 38);
	test_configuration_activated(local_test_board, "arrow", 0, 0, true, "ascii_board::configuration_activated", SUCCESS, 39);
	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 40);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, modify_configuration_single_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default", "none", 0, true);
	local_test_board.add_configuration(single_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(single_line_board_definitions::x_config_board);
	local_test_board.add_configuration(single_line_board_definitions::o_config_board);
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

TEST_F(ascii_board_test, modify_configuration_multi_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, multi_line_board_definitions::board_config_path, "default", "none", 0, true);
	local_test_board.add_configuration(multi_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(multi_line_board_definitions::x_config_board);
	local_test_board.add_configuration(multi_line_board_definitions::o_config_board);
	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 0);
	test_modify_configuration(local_test_board, "cursor", "x", multi_line_board_definitions::beginning_cursor_x_board, "ascii_board::modify_configuration", SUCCESS, 1);
	activate_deactivate(local_test_board, "x", 0, 0, multi_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, false, 2);
	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 3);

	activate_deactivate(local_test_board, "x", 0, -1, multi_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, true, 4);
	test_modify_configuration(local_test_board, "x", "cursor", multi_line_board_definitions::beginning_row_cursor_x_board, "ascii_board::modify_configuration", SUCCESS, 5);
	activate_deactivate(local_test_board, "cursor", 0, -1, multi_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, false, 6);
	activate_deactivate(local_test_board, "x", 0, -1, multi_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 7);

	activate_deactivate(local_test_board, "x", -1, 0, multi_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, true, 8);
	test_modify_configuration(local_test_board, "x", "cursor", multi_line_board_definitions::beginning_column_cursor_x_board, "ascii_board::modify_configuration", SUCCESS, 9);
	activate_deactivate(local_test_board, "cursor", -1, 0, multi_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, false, 10);
	activate_deactivate(local_test_board, "x", -1, 0, multi_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 11);

	activate_deactivate(local_test_board, "x", -1, -1, multi_line_board_definitions::full_x_board, "ascii_board::set_all", SUCCESS, true, 12);
	test_modify_configuration(local_test_board, "x", "cursor", multi_line_board_definitions::full_cursor_x_board, "ascii_board::modify_configuration", SUCCESS, 13);
	activate_deactivate(local_test_board, "cursor", -1, -1, multi_line_board_definitions::full_x_board, "ascii_board::set_all", SUCCESS, false, 14);
	activate_deactivate(local_test_board, "x", -1, -1, multi_line_board_definitions::empty_board, "ascii_board::set_all", SUCCESS, false, 15);

	activate_deactivate(local_test_board, "x", 0, 0, multi_line_board_definitions::beginning_x_board, "ascii_board::set_tile", SUCCESS, true, 16);
	test_modify_configuration(local_test_board, "x", "o", multi_line_board_definitions::beginning_o_board, "ascii_board::modify_configuration", SUCCESS, 17);
	activate_deactivate(local_test_board, "o", 0, 0, multi_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 18);

	test_modify_configuration(local_test_board, "x", "gibberish", multi_line_board_definitions::empty_board, "ascii_board::modify_configuration", ELEMENT_NOT_FOUND, 19);
	test_modify_configuration(local_test_board, "gibberish", "x", multi_line_board_definitions::empty_board, "ascii_board::modify_configuration", ELEMENT_NOT_FOUND, 20);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, modify_configuration_irregular_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, irregular_line_board_definitions::board_config_path, "default", "none", 0, true);
	local_test_board.add_configuration(irregular_line_board_definitions::cursor_config_board);
	local_test_board.add_configuration(irregular_line_board_definitions::x_config_board);
	local_test_board.add_configuration(irregular_line_board_definitions::o_config_board);
	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 0);
	test_modify_configuration(local_test_board, "cursor", "x", irregular_line_board_definitions::beginning_cursor_x_board, "ascii_board::modify_configuration", SUCCESS, 1);
	activate_deactivate(local_test_board, "x", 0, 0, irregular_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, false, 2);
	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 3);

	activate_deactivate(local_test_board, "x", 0, -1, irregular_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, true, 4);
	test_modify_configuration(local_test_board, "x", "cursor", irregular_line_board_definitions::beginning_row_cursor_x_board, "ascii_board::modify_configuration", SUCCESS, 5);
	activate_deactivate(local_test_board, "cursor", 0, -1, irregular_line_board_definitions::beginning_row_x_board, "ascii_board::set_row", SUCCESS, false, 6);
	activate_deactivate(local_test_board, "x", 0, -1, irregular_line_board_definitions::empty_board, "ascii_board::set_row", SUCCESS, false, 7);

	activate_deactivate(local_test_board, "x", -1, 0, irregular_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, true, 8);
	test_modify_configuration(local_test_board, "x", "cursor", irregular_line_board_definitions::beginning_column_cursor_x_board, "ascii_board::modify_configuration", SUCCESS, 9);
	activate_deactivate(local_test_board, "cursor", -1, 0, irregular_line_board_definitions::beginning_column_x_board, "ascii_board::set_column", SUCCESS, false, 10);
	activate_deactivate(local_test_board, "x", -1, 0, irregular_line_board_definitions::empty_board, "ascii_board::set_column", SUCCESS, false, 11);

	activate_deactivate(local_test_board, "x", -1, -1, irregular_line_board_definitions::full_x_board, "ascii_board::set_all", SUCCESS, true, 12);
	test_modify_configuration(local_test_board, "x", "cursor", irregular_line_board_definitions::full_cursor_x_board, "ascii_board::modify_configuration", SUCCESS, 13);
	activate_deactivate(local_test_board, "cursor", -1, -1, irregular_line_board_definitions::full_x_board, "ascii_board::set_all", SUCCESS, false, 14);
	activate_deactivate(local_test_board, "x", -1, -1, irregular_line_board_definitions::empty_board, "ascii_board::set_all", SUCCESS, false, 15);

	activate_deactivate(local_test_board, "x", 0, 0, irregular_line_board_definitions::beginning_x_board, "ascii_board::set_tile", SUCCESS, true, 16);
	test_modify_configuration(local_test_board, "x", "o", irregular_line_board_definitions::beginning_o_board, "ascii_board::modify_configuration", SUCCESS, 17);
	activate_deactivate(local_test_board, "o", 0, 0, irregular_line_board_definitions::empty_board, "ascii_board::set_tile", SUCCESS, false, 18);

	test_modify_configuration(local_test_board, "x", "gibberish", irregular_line_board_definitions::empty_board, "ascii_board::modify_configuration", ELEMENT_NOT_FOUND, 19);
	test_modify_configuration(local_test_board, "gibberish", "x", irregular_line_board_definitions::empty_board, "ascii_board::modify_configuration", ELEMENT_NOT_FOUND, 20);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, load_translation_single_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default", "none", 0, true);
	std::string log_content = "";
	local_test_board.reset_logging("ascii_board.log");
	local_test_board.load_board_translation("upside down", single_line_board_definitions::upside_down_board_config_path);
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

TEST_F(ascii_board_test, load_translation_multi_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, multi_line_board_definitions::board_config_path, "default", "none", 0, true);
	std::string log_content = "";
	local_test_board.reset_logging("ascii_board.log");
	local_test_board.load_board_translation("upside down", multi_line_board_definitions::upside_down_board_config_path);
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

TEST_F(ascii_board_test, load_translation_irregular_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, irregular_line_board_definitions::board_config_path, "default", "none", 0, true);
	std::string log_content = "";
	local_test_board.reset_logging("ascii_board.log");
	local_test_board.load_board_translation("upside down", irregular_line_board_definitions::upside_down_board_config_path);
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

TEST_F(ascii_board_test, use_translation_single_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default", "none", 0, true);
	std::string log_content = "";
	local_test_board.reset_logging("ascii_board.log");
	local_test_board.load_board_translation("upside down", single_line_board_definitions::upside_down_board_config_path);
	int status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	EXPECT_NE(log_content.find("ascii_board::load_board_translation status: " + std::to_string(SUCCESS)), std::string::npos);
	EXPECT_NE(log_content.find("All validations passed."), std::string::npos);

	local_test_board.add_configuration(single_line_board_definitions::cursor_config_board);

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

TEST_F(ascii_board_test, use_translation_multi_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, multi_line_board_definitions::board_config_path, "default", "none", 0, true);
	std::string log_content = "";
	local_test_board.reset_logging("ascii_board.log");
	local_test_board.load_board_translation("upside down", multi_line_board_definitions::upside_down_board_config_path);
	int status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	EXPECT_NE(log_content.find("ascii_board::load_board_translation status: " + std::to_string(SUCCESS)), std::string::npos);
	EXPECT_NE(log_content.find("All validations passed."), std::string::npos);

	local_test_board.add_configuration(multi_line_board_definitions::cursor_config_board);

	use_translation_test(local_test_board, "gibberish", "ascii_board::use_translation", ELEMENT_NOT_FOUND, 0);
	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 1);
	use_translation_test(local_test_board, "upside down", "ascii_board::use_translation", SUCCESS, 2);
	check_board(local_test_board, multi_line_board_definitions::end_cursor_upside_down_board, 2);
	activate_deactivate(local_test_board, "cursor", 0, 0, multi_line_board_definitions::empty_upside_down_board, "ascii_board::set_tile", SUCCESS, false, 3);
	activate_deactivate(local_test_board, "cursor", 2, 3, multi_line_board_definitions::middle_cursor_upside_down_board, "ascii_board::set_tile", SUCCESS, true, 4);
	activate_deactivate(local_test_board, "cursor", 2, 3, multi_line_board_definitions::empty_upside_down_board, "ascii_board::set_tile", SUCCESS, false, 5);
	activate_deactivate(local_test_board, "cursor", 5, 6, multi_line_board_definitions::beginning_cursor_upside_down_board, "ascii_board::set_tile", SUCCESS, true, 6);
	use_translation_test(local_test_board, "default", "ascii_board::use_translation", SUCCESS, 7);
	check_board(local_test_board, multi_line_board_definitions::end_cursor_board, 8);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, use_translation_irregular_line)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, irregular_line_board_definitions::board_config_path, "default", "none", 0, true);
	std::string log_content = "";
	local_test_board.reset_logging("ascii_board.log");
	local_test_board.load_board_translation("upside down", irregular_line_board_definitions::upside_down_board_config_path);
	int status = file_manager::read_file("ascii_board.log", log_content);
	ASSERT_EQ(status, 0);
	EXPECT_NE(log_content.find("ascii_board::load_board_translation status: " + std::to_string(SUCCESS)), std::string::npos);
	EXPECT_NE(log_content.find("All validations passed."), std::string::npos);

	local_test_board.add_configuration(irregular_line_board_definitions::cursor_config_board);

	use_translation_test(local_test_board, "gibberish", "ascii_board::use_translation", ELEMENT_NOT_FOUND, 0);
	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::beginning_cursor_board, "ascii_board::set_tile", SUCCESS, true, 1);
	use_translation_test(local_test_board, "upside down", "ascii_board::use_translation", SUCCESS, 2);
	check_board(local_test_board, irregular_line_board_definitions::end_cursor_upside_down_board, 2);
	activate_deactivate(local_test_board, "cursor", 0, 0, irregular_line_board_definitions::empty_upside_down_board, "ascii_board::set_tile", SUCCESS, false, 3);
	activate_deactivate(local_test_board, "cursor", 2, 1, irregular_line_board_definitions::middle_cursor_upside_down_board, "ascii_board::set_tile", SUCCESS, true, 4);
	activate_deactivate(local_test_board, "cursor", 2, 1, irregular_line_board_definitions::empty_upside_down_board, "ascii_board::set_tile", SUCCESS, false, 5);
	activate_deactivate(local_test_board, "cursor", 3, 2, irregular_line_board_definitions::beginning_cursor_upside_down_board, "ascii_board::set_tile", SUCCESS, true, 6);
	use_translation_test(local_test_board, "default", "ascii_board::use_translation", SUCCESS, 7);
	check_board(local_test_board, irregular_line_board_definitions::end_cursor_board, 8);

	delete(local_test_frame);
}

TEST_F(ascii_board_test, scrolling_board_test)
{
	frame* local_test_frame = new frame();
	ascii_board local_test_board(local_test_frame, single_line_board_definitions::board_config_path, "default", "none", 10, true);
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_width(42);
	local_test_frame->set_fake_console_height(21);
	local_test_frame->get_frame_output();
	local_test_board.build();
	EXPECT_EQ(single_line_board_definitions::empty_board_ten_lines, local_test_board.get_displayed_output());
	set_lines_count_test(local_test_board, 0, single_line_board_definitions::empty_board, 0);
	set_lines_count_test(local_test_board, 10, single_line_board_definitions::empty_board_ten_lines, 1);
	set_lines_count_test(local_test_board, -11, single_line_board_definitions::empty_board_ten_lines, 2);
	set_top_display_index_test(local_test_board, 5, single_line_board_definitions::empty_board_ten_lines_scrolled_down_five, "widget::set_top_line", SUCCESS, 3);
	set_top_display_index_test(local_test_board, 12, single_line_board_definitions::empty_board_ten_lines_scrolled_down_five, "ascii_board::set_top_display_index", INVALID_INDEX, 4);
	local_test_frame->set_fake_console_width(20);
	local_test_frame->get_frame_output();
	set_top_display_index_test(local_test_board, 0, single_line_board_definitions::empty_board_ten_lines_twenty_columns, "widget::set_top_line", SUCCESS, 5);
	set_left_display_index_test(local_test_board, 10, single_line_board_definitions::empty_board_ten_lines_twenty_columns_scrolled_right_ten, "widget::set_left_column", SUCCESS, 6);
	set_left_display_index_test(local_test_board, 23, single_line_board_definitions::empty_board_ten_lines_twenty_columns_scrolled_right_ten, "ascii_board::set_left_display_index", INVALID_INDEX, 7);
	set_left_display_index_test(local_test_board, 0, single_line_board_definitions::empty_board_ten_lines_twenty_columns, "widget::set_left_column", SUCCESS, 8);
	local_test_frame->set_fake_console_width(42);
	local_test_frame->get_frame_output();
	scroll_test(local_test_board, 5, "down", single_line_board_definitions::empty_board_ten_lines_scrolled_down_five, 9);
	scroll_test(local_test_board, 7, "down", single_line_board_definitions::empty_board_ten_lines_scrolled_down_eleven, 10);
	scroll_test(local_test_board, 11, "up", single_line_board_definitions::empty_board_ten_lines, 11);
	scroll_test(local_test_board, 1, "up", single_line_board_definitions::empty_board_ten_lines, 12);
	local_test_frame->set_fake_console_width(20);
	local_test_frame->get_frame_output();
	scroll_test(local_test_board, 10, "right", single_line_board_definitions::empty_board_ten_lines_twenty_columns_scrolled_right_ten, 13);
	scroll_test(local_test_board, 13, "right", single_line_board_definitions::empty_board_ten_lines_twenty_columns_scrolled_right_twenty_two, 14);
	scroll_test(local_test_board, 22, "left", single_line_board_definitions::empty_board_ten_lines_twenty_columns, 15);
	scroll_test(local_test_board, 1, "left", single_line_board_definitions::empty_board_ten_lines_twenty_columns, 16);
	delete(local_test_frame);
}