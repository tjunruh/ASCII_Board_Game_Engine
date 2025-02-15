#include "pch.h"
#ifdef __linux__
#include <gtest/gtest.h>
#endif
#ifdef _WIN32
#include "../file_manager/file_manager.h"
#include "../ascii_engine/error_codes.h"
#include "../ascii_engine/frame.h"
#include "../ascii_engine/widget.h"
#include "../ascii_engine/format_tools.h"
#elif __linux__
#include <ascii_engine/file_manager.h>
#include <ascii_engine/error_codes.h>
#include <ascii_engine/frame.h>
#include <ascii_engine/widget.h>
#include <ascii_engine/format_tools.h>
#endif

class widget_test : public testing::Test
{
protected:
	void set_get_alignment(widget& local_test_widget, std::string alignment, int expected_status_code, std::string expected_status_function, bool get, int test_num)
	{
		std::string log_content = "";
		local_test_widget.reset_logging("widget.log");
		if (get)
		{
			std::string returned_alignment = local_test_widget.get_alignment();
			EXPECT_EQ(alignment, returned_alignment) << std::to_string(test_num);
		}
		else
		{
			local_test_widget.set_alignment(alignment);

		}
		int status = file_manager::read_file("widget.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << std::to_string(test_num);
	}

	void set_get_spacing(widget& local_test_widget, int top, int bottom, int left, int right, int expected_status_code, std::string expected_status_function, bool get, int test_num)
	{
		std::string log_content = "";
		local_test_widget.reset_logging("widget.log");
		if (get)
		{
			int returned_top = 0;
			int returned_bottom = 0;
			int returned_left = 0;
			int returned_right = 0;
			local_test_widget.get_spacing(returned_top, returned_bottom, returned_left, returned_right);
			EXPECT_EQ(top, returned_top) << std::to_string(test_num);
			EXPECT_EQ(bottom, returned_bottom) << std::to_string(test_num);
			EXPECT_EQ(left, returned_left) << std::to_string(test_num);
			EXPECT_EQ(right, returned_right) << std::to_string(test_num);
		}
		else
		{
			local_test_widget.set_spacing(top, bottom, left, right);

		}
		int status = file_manager::read_file("widget.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << std::to_string(test_num);
	}

	void set_get_border_spacing(widget& local_test_widget, int top, int bottom, int left, int right, int expected_status_code, std::string expected_status_function, bool get, int test_num)
	{
		std::string log_content = "";
		local_test_widget.reset_logging("widget.log");
		if (get)
		{
			int returned_top = 0;
			int returned_bottom = 0;
			int returned_left = 0;
			int returned_right = 0;
			local_test_widget.get_border_spacing(returned_top, returned_bottom, returned_left, returned_right);
			EXPECT_EQ(top, returned_top) << std::to_string(test_num);
			EXPECT_EQ(bottom, returned_bottom) << std::to_string(test_num);
			EXPECT_EQ(left, returned_left) << std::to_string(test_num);
			EXPECT_EQ(right, returned_right) << std::to_string(test_num);
		}
		else
		{
			local_test_widget.set_border_spacing(top, bottom, left, right);

		}
		int status = file_manager::read_file("widget.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << std::to_string(test_num);
	}

	void set_get_horizontal_border(widget& local_test_widget, char border, int expected_status_code, std::string expected_status_function, bool get, int test_num)
	{
		std::string log_content = "";
		local_test_widget.reset_logging("widget.log");
		if (get)
		{
			char returned_border = local_test_widget.get_horizontal_border();
			EXPECT_EQ(border, returned_border) << std::to_string(test_num);
		}
		else
		{
			local_test_widget.set_horizontal_border(border);

		}
		int status = file_manager::read_file("widget.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << std::to_string(test_num);
	}

	void set_get_vertical_border(widget& local_test_widget, char border, int expected_status_code, std::string expected_status_function, bool get, int test_num)
	{
		std::string log_content = "";
		local_test_widget.reset_logging("widget.log");
		if (get)
		{
			char returned_border = local_test_widget.get_vertical_border();
			EXPECT_EQ(border, returned_border) << std::to_string(test_num);
		}
		else
		{
			local_test_widget.set_vertical_border(border);

		}
		int status = file_manager::read_file("widget.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << std::to_string(test_num);
	}

	void set_get_corner_border(widget& local_test_widget, char border, int expected_status_code, std::string expected_status_function, bool get, int test_num)
	{
		std::string log_content = "";
		local_test_widget.reset_logging("widget.log");
		if (get)
		{
			char returned_border = local_test_widget.get_corner_border();
			EXPECT_EQ(border, returned_border) << std::to_string(test_num);
		}
		else
		{
			local_test_widget.set_corner_border(border);

		}
		int status = file_manager::read_file("widget.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << std::to_string(test_num);
	}

	void set_get_highlight_character(widget& local_test_widget, char highlight_character, int expected_status_code, std::string expected_status_function, bool get, int test_num)
	{
		std::string log_content = "";
		local_test_widget.reset_logging("widget.log");
		if (get)
		{
			char returned_highlight_character = local_test_widget.get_highlight_character();
			EXPECT_EQ(highlight_character, returned_highlight_character) << std::to_string(test_num);
		}
		else
		{
			local_test_widget.set_highlight_character(highlight_character);

		}
		int status = file_manager::read_file("widget.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << std::to_string(test_num);
	}

	void set_get_width_multiplier(widget& local_test_widget, float multiplier, std::string expected_status_function, int expected_status_code, bool set, int test_num)
	{
		std::string log_content = "";
		if (set)
		{
			local_test_widget.reset_logging("widget.log");
			int status = file_manager::read_file("widget.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			local_test_widget.set_width_multiplier(multiplier);
			status = file_manager::read_file("widget.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
		}
		else
		{
			local_test_widget.reset_logging("widget.log");
			int status = file_manager::read_file("widget.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			float returned_multiplier = local_test_widget.get_width_multiplier();
			status = file_manager::read_file("widget.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
			EXPECT_EQ(multiplier, returned_multiplier) << std::to_string(test_num);
		}
	}

	void set_get_spacing_width_multipliers(widget& local_test_widget, float left_multiplier, float right_multiplier, std::string expected_status_function, int expected_status_code, bool set, int test_num)
	{
		std::string log_content = "";
		if (set)
		{
			local_test_widget.reset_logging("widget.log");
			int status = file_manager::read_file("widget.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			local_test_widget.set_spacing_width_multipliers(left_multiplier, right_multiplier);
			status = file_manager::read_file("widget.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
		}
		else
		{
			local_test_widget.reset_logging("widget.log");
			int status = file_manager::read_file("widget.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			float returned_left_multiplier = 0.0;
			float returned_right_multiplier = 0.0;
			local_test_widget.get_spacing_width_multipliers(returned_left_multiplier, returned_right_multiplier);
			status = file_manager::read_file("widget.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
			EXPECT_EQ(left_multiplier, returned_left_multiplier) << std::to_string(test_num);
			EXPECT_EQ(right_multiplier, returned_right_multiplier) << std::to_string(test_num);
		}
	}

	void set_get_border_spacing_width_multipliers(widget& local_test_widget, float left_multiplier, float right_multiplier, std::string expected_status_function, int expected_status_code, bool set, int test_num)
	{
		std::string log_content = "";
		if (set)
		{
			local_test_widget.reset_logging("widget.log");
			int status = file_manager::read_file("widget.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			local_test_widget.set_border_spacing_width_multipliers(left_multiplier, right_multiplier);
			status = file_manager::read_file("widget.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
		}
		else
		{
			local_test_widget.reset_logging("widget.log");
			int status = file_manager::read_file("widget.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			float returned_left_multiplier = 0.0;
			float returned_right_multiplier = 0.0;
			local_test_widget.get_border_spacing_width_multipliers(returned_left_multiplier, returned_right_multiplier);
			status = file_manager::read_file("widget.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
			EXPECT_EQ(left_multiplier, returned_left_multiplier) << std::to_string(test_num);
			EXPECT_EQ(right_multiplier, returned_right_multiplier) << std::to_string(test_num);
		}
	}
};

TEST_F(widget_test, set_get_alignment)
{
	frame* local_test_frame = new frame();
	widget local_test_widget(local_test_frame);
	local_test_widget.start_logging("widget.log");
	std::string log_content = "";
	int status = file_manager::read_file("widget.log", log_content);
	ASSERT_EQ(status, 0);
	set_get_alignment(local_test_widget, format_tools::left_alignment_keyword, SUCCESS, "widget::set_alignment", false, 0);
	set_get_alignment(local_test_widget, format_tools::left_alignment_keyword, SUCCESS, "widget::get_alignment", true, 1);
	set_get_alignment(local_test_widget, format_tools::center_alignment_keyword, SUCCESS, "widget::set_alignment", false, 2);
	set_get_alignment(local_test_widget, format_tools::center_alignment_keyword, SUCCESS, "widget::get_alignment", true, 3);
	set_get_alignment(local_test_widget, format_tools::right_alignment_keyword, SUCCESS, "widget::set_alignment", false, 4);
	set_get_alignment(local_test_widget, format_tools::right_alignment_keyword, SUCCESS, "widget::get_alignment", true, 5);
	set_get_alignment(local_test_widget, "gibberish", INVALID_VALUE, "widget::set_alignment", false, 6);
	set_get_alignment(local_test_widget, format_tools::right_alignment_keyword, SUCCESS, "widget::get_alignment", true, 7);
	set_get_alignment(local_test_widget, format_tools::center_block_alignment_keyword, SUCCESS, "widget::set_alignment", false, 8);
	set_get_alignment(local_test_widget, format_tools::center_block_alignment_keyword, SUCCESS, "widget::get_alignment", true, 9);
	status = file_manager::delete_file("widget.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(widget_test, set_get_spacing)
{
	frame* local_test_frame = new frame();
	widget local_test_widget(local_test_frame);
	local_test_widget.start_logging("widget.log");
	std::string log_content = "";
	int status = file_manager::read_file("widget.log", log_content);
	ASSERT_EQ(status, 0);
	set_get_spacing(local_test_widget, 5, 5, 10, 10, SUCCESS, "widget::set_spacing", false, 0);
	set_get_spacing(local_test_widget, 5, 5, 10, 10, SUCCESS, "widget::get_spacing", true, 1);
	set_get_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::set_spacing", false, 2);
	set_get_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_spacing", true, 3);
	set_get_spacing(local_test_widget, -1, 5, 10, 10, INVALID_VALUE, "widget::set_spacing", false, 4);
	set_get_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_spacing", true, 5);
	set_get_spacing(local_test_widget, 5, -1, 10, 10, INVALID_VALUE, "widget::set_spacing", false, 6);
	set_get_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_spacing", true, 7);
	set_get_spacing(local_test_widget, 5, 5, -1, 10, INVALID_VALUE, "widget::set_spacing", false, 8);
	set_get_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_spacing", true, 9);
	set_get_spacing(local_test_widget, 5, 5, 10, -1, INVALID_VALUE, "widget::set_spacing", false, 10);
	set_get_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_spacing", true, 11);
	status = file_manager::delete_file("widget.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(widget_test, set_get_border_spacing)
{
	frame* local_test_frame = new frame();
	widget local_test_widget(local_test_frame);
	local_test_widget.start_logging("widget.log");
	std::string log_content = "";
	int status = file_manager::read_file("widget.log", log_content);
	ASSERT_EQ(status, 0);
	set_get_spacing(local_test_widget, 10, 10, 20, 20, SUCCESS, "widget::set_spacing", false, 0);
	set_get_border_spacing(local_test_widget, 5, 5, 10, 10, SUCCESS, "widget::set_border_spacing", false, 1);
	set_get_border_spacing(local_test_widget, 5, 5, 10, 10, SUCCESS, "widget::get_border_spacing", true, 2);
	set_get_border_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::set_border_spacing", false, 3);
	set_get_border_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_border_spacing", true, 4);
	set_get_border_spacing(local_test_widget, -1, 5, 10, 10, INVALID_VALUE, "widget::set_border_spacing", false, 5);
	set_get_border_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_border_spacing", true, 6);
	set_get_border_spacing(local_test_widget, 5, -1, 10, 10, INVALID_VALUE, "widget::set_border_spacing", false, 7);
	set_get_border_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_border_spacing", true, 8);
	set_get_border_spacing(local_test_widget, 5, 5, -1, 10, INVALID_VALUE, "widget::set_border_spacing", false, 9);
	set_get_border_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_border_spacing", true, 10);
	set_get_border_spacing(local_test_widget, 5, 5, 10, -1, INVALID_VALUE, "widget::set_border_spacing", false, 11);
	set_get_border_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_border_spacing", true, 12);
	set_get_border_spacing(local_test_widget, 11, 5, 10, 10, INVALID_VALUE, "widget::set_border_spacing", false, 13);
	set_get_border_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_border_spacing", true, 14);
	set_get_border_spacing(local_test_widget, 5, 11, 10, 10, INVALID_VALUE, "widget::set_border_spacing", false, 15);
	set_get_border_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_border_spacing", true, 16);
	set_get_border_spacing(local_test_widget, 5, 5, 21, 10, INVALID_VALUE, "widget::set_border_spacing", false, 17);
	set_get_border_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_border_spacing", true, 18);
	set_get_border_spacing(local_test_widget, 5, 5, 10, 21, INVALID_VALUE, "widget::set_border_spacing", false, 19);
	set_get_border_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_border_spacing", true, 20);
	set_get_border_spacing(local_test_widget, 9, 9, 19, 19, SUCCESS, "widget::set_border_spacing", false, 21);
	set_get_spacing(local_test_widget, 3, 3, 6, 6, SUCCESS, "widget::set_spacing", false, 22);
	set_get_border_spacing(local_test_widget, 3, 3, 6, 6, SUCCESS, "widget::get_border_spacing", true, 23);
	set_get_border_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::set_border_spacing", false, 24);
	set_get_border_spacing(local_test_widget, 0, 0, 0, 0, SUCCESS, "widget::get_border_spacing", true, 25);
	status = file_manager::delete_file("widget.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(widget_test, set_get_horizontal_border)
{
	frame* local_test_frame = new frame();
	widget local_test_widget(local_test_frame);
	local_test_widget.start_logging("widget.log");
	std::string log_content = "";
	int status = file_manager::read_file("widget.log", log_content);
	ASSERT_EQ(status, 0);
	set_get_horizontal_border(local_test_widget, '\"', SUCCESS, "widget::set_horizontal_border", false, 0);
	set_get_horizontal_border(local_test_widget, '\"', SUCCESS, "widget::get_horizontal_border", true, 1);
	set_get_horizontal_border(local_test_widget, '\n', INVALID_VALUE, "widget::set_horizontal_border", false, 2);
	set_get_horizontal_border(local_test_widget, '\"', SUCCESS, "widget::get_horizontal_border", true, 3);
	set_get_horizontal_border(local_test_widget, '\a', INVALID_VALUE, "widget::set_horizontal_border", false, 4);
	set_get_horizontal_border(local_test_widget, '\"', SUCCESS, "widget::get_horizontal_border", true, 5);
	set_get_horizontal_border(local_test_widget, '\b', INVALID_VALUE, "widget::set_horizontal_border", false, 6);
	set_get_horizontal_border(local_test_widget, '\"', SUCCESS, "widget::get_horizontal_border", true, 7);
	set_get_horizontal_border(local_test_widget, '\f', INVALID_VALUE, "widget::set_horizontal_border", false, 8);
	set_get_horizontal_border(local_test_widget, '\"', SUCCESS, "widget::get_horizontal_border", true, 9);
	set_get_horizontal_border(local_test_widget, '\r', INVALID_VALUE, "widget::set_horizontal_border", false, 10);
	set_get_horizontal_border(local_test_widget, '\"', SUCCESS, "widget::get_horizontal_border", true, 11);
	set_get_horizontal_border(local_test_widget, '\t', INVALID_VALUE, "widget::set_horizontal_border", false, 12);
	set_get_horizontal_border(local_test_widget, '\"', SUCCESS, "widget::get_horizontal_border", true, 13);
	set_get_horizontal_border(local_test_widget, '\v', INVALID_VALUE, "widget::set_horizontal_border", false, 14);
	set_get_horizontal_border(local_test_widget, '\"', SUCCESS, "widget::get_horizontal_border", true, 15);
	set_get_horizontal_border(local_test_widget, '\0', INVALID_VALUE, "widget::set_horizontal_border", false, 16);
	set_get_horizontal_border(local_test_widget, '\"', SUCCESS, "widget::get_horizontal_border", true, 17);
	status = file_manager::delete_file("widget.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(widget_test, set_get_vertical_border)
{
	frame* local_test_frame = new frame();
	widget local_test_widget(local_test_frame);
	local_test_widget.start_logging("widget.log");
	std::string log_content = "";
	int status = file_manager::read_file("widget.log", log_content);
	ASSERT_EQ(status, 0);
	set_get_vertical_border(local_test_widget, '\"', SUCCESS, "widget::set_vertical_border", false, 0);
	set_get_vertical_border(local_test_widget, '\"', SUCCESS, "widget::get_vertical_border", true, 1);
	set_get_vertical_border(local_test_widget, '\n', INVALID_VALUE, "widget::set_vertical_border", false, 2);
	set_get_vertical_border(local_test_widget, '\"', SUCCESS, "widget::get_vertical_border", true, 3);
	set_get_vertical_border(local_test_widget, '\a', INVALID_VALUE, "widget::set_vertical_border", false, 4);
	set_get_vertical_border(local_test_widget, '\"', SUCCESS, "widget::get_vertical_border", true, 5);
	set_get_vertical_border(local_test_widget, '\b', INVALID_VALUE, "widget::set_vertical_border", false, 6);
	set_get_vertical_border(local_test_widget, '\"', SUCCESS, "widget::get_vertical_border", true, 7);
	set_get_vertical_border(local_test_widget, '\f', INVALID_VALUE, "widget::set_vertical_border", false, 8);
	set_get_vertical_border(local_test_widget, '\"', SUCCESS, "widget::get_vertical_border", true, 9);
	set_get_vertical_border(local_test_widget, '\r', INVALID_VALUE, "widget::set_vertical_border", false, 10);
	set_get_vertical_border(local_test_widget, '\"', SUCCESS, "widget::get_vertical_border", true, 11);
	set_get_vertical_border(local_test_widget, '\t', INVALID_VALUE, "widget::set_vertical_border", false, 12);
	set_get_vertical_border(local_test_widget, '\"', SUCCESS, "widget::get_vertical_border", true, 13);
	set_get_vertical_border(local_test_widget, '\v', INVALID_VALUE, "widget::set_vertical_border", false, 14);
	set_get_vertical_border(local_test_widget, '\"', SUCCESS, "widget::get_vertical_border", true, 15);
	set_get_vertical_border(local_test_widget, '\0', INVALID_VALUE, "widget::set_vertical_border", false, 16);
	set_get_vertical_border(local_test_widget, '\"', SUCCESS, "widget::get_vertical_border", true, 17);
	status = file_manager::delete_file("widget.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(widget_test, set_get_corner_border)
{
	frame* local_test_frame = new frame();
	widget local_test_widget(local_test_frame);
	local_test_widget.start_logging("widget.log");
	std::string log_content = "";
	int status = file_manager::read_file("widget.log", log_content);
	ASSERT_EQ(status, 0);
	set_get_corner_border(local_test_widget, '\"', SUCCESS, "widget::set_corner_border", false, 0);
	set_get_corner_border(local_test_widget, '\"', SUCCESS, "widget::get_corner_border", true, 1);
	set_get_corner_border(local_test_widget, '\n', INVALID_VALUE, "widget::set_corner_border", false, 2);
	set_get_corner_border(local_test_widget, '\"', SUCCESS, "widget::get_corner_border", true, 3);
	set_get_corner_border(local_test_widget, '\a', INVALID_VALUE, "widget::set_corner_border", false, 4);
	set_get_corner_border(local_test_widget, '\"', SUCCESS, "widget::get_corner_border", true, 5);
	set_get_corner_border(local_test_widget, '\b', INVALID_VALUE, "widget::set_corner_border", false, 6);
	set_get_corner_border(local_test_widget, '\"', SUCCESS, "widget::get_corner_border", true, 7);
	set_get_corner_border(local_test_widget, '\f', INVALID_VALUE, "widget::set_corner_border", false, 8);
	set_get_corner_border(local_test_widget, '\"', SUCCESS, "widget::get_corner_border", true, 9);
	set_get_corner_border(local_test_widget, '\r', INVALID_VALUE, "widget::set_corner_border", false, 10);
	set_get_corner_border(local_test_widget, '\"', SUCCESS, "widget::get_corner_border", true, 11);
	set_get_corner_border(local_test_widget, '\t', INVALID_VALUE, "widget::set_corner_border", false, 12);
	set_get_corner_border(local_test_widget, '\"', SUCCESS, "widget::get_corner_border", true, 13);
	set_get_corner_border(local_test_widget, '\v', INVALID_VALUE, "widget::set_corner_border", false, 14);
	set_get_corner_border(local_test_widget, '\"', SUCCESS, "widget::get_corner_border", true, 15);
	set_get_corner_border(local_test_widget, '\0', INVALID_VALUE, "widget::set_corner_border", false, 16);
	set_get_corner_border(local_test_widget, '\"', SUCCESS, "widget::get_corner_border", true, 17);
	status = file_manager::delete_file("widget.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(widget_test, set_get_highlight_character)
{
	frame* local_test_frame = new frame();
	widget local_test_widget(local_test_frame);
	local_test_widget.start_logging("widget.log");
	std::string log_content = "";
	int status = file_manager::read_file("widget.log", log_content);
	ASSERT_EQ(status, 0);
	set_get_highlight_character(local_test_widget, '\"', SUCCESS, "widget::set_highlight_character", false, 0);
	set_get_highlight_character(local_test_widget, '\"', SUCCESS, "widget::get_highlight_character", true, 1);
	set_get_highlight_character(local_test_widget, '\n', INVALID_VALUE, "widget::set_highlight_character", false, 2);
	set_get_highlight_character(local_test_widget, '\"', SUCCESS, "widget::get_highlight_character", true, 3);
	set_get_highlight_character(local_test_widget, '\a', INVALID_VALUE, "widget::set_highlight_character", false, 4);
	set_get_highlight_character(local_test_widget, '\"', SUCCESS, "widget::get_highlight_character", true, 5);
	set_get_highlight_character(local_test_widget, '\b', INVALID_VALUE, "widget::set_highlight_character", false, 6);
	set_get_highlight_character(local_test_widget, '\"', SUCCESS, "widget::get_highlight_character", true, 7);
	set_get_highlight_character(local_test_widget, '\f', INVALID_VALUE, "widget::set_highlight_character", false, 8);
	set_get_highlight_character(local_test_widget, '\"', SUCCESS, "widget::get_highlight_character", true, 9);
	set_get_highlight_character(local_test_widget, '\r', INVALID_VALUE, "widget::set_highlight_character", false, 10);
	set_get_highlight_character(local_test_widget, '\"', SUCCESS, "widget::get_highlight_character", true, 11);
	set_get_highlight_character(local_test_widget, '\t', INVALID_VALUE, "widget::set_highlight_character", false, 12);
	set_get_highlight_character(local_test_widget, '\"', SUCCESS, "widget::get_highlight_character", true, 13);
	set_get_highlight_character(local_test_widget, '\v', INVALID_VALUE, "widget::set_highlight_character", false, 14);
	set_get_highlight_character(local_test_widget, '\"', SUCCESS, "widget::get_highlight_character", true, 15);
	set_get_highlight_character(local_test_widget, '\0', INVALID_VALUE, "widget::set_highlight_character", false, 16);
	set_get_highlight_character(local_test_widget, '\"', SUCCESS, "widget::get_highlight_character", true, 17);
	status = file_manager::delete_file("widget.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(widget_test, set_get_coordinate_width_multiplier_test)
{
	frame* local_test_frame = new frame();
	widget local_test_widget(local_test_frame);
	local_test_widget.start_logging("widget.log");
	std::string log_content = "";
	int status = file_manager::read_file("widget.log", log_content);
	ASSERT_EQ(status, 0);
	set_get_width_multiplier(local_test_widget, 1.5, "widget::set_width_multiplier", SUCCESS, true, 0);
	set_get_width_multiplier(local_test_widget, 0, "widget::set_width_multiplier", INVALID_VALUE, true, 1);
	set_get_width_multiplier(local_test_widget, -1, "widget::set_width_multiplier", INVALID_VALUE, true, 2);
	set_get_width_multiplier(local_test_widget, 1.5, "widget::get_width_multiplier", SUCCESS, false, 3);
	delete(local_test_frame);
}

TEST_F(widget_test, set_get_spacing_width_multiplier_test)
{
	frame* local_test_frame = new frame();
	widget local_test_widget(local_test_frame);
	local_test_widget.start_logging("widget.log");
	std::string log_content = "";
	int status = file_manager::read_file("widget.log", log_content);
	ASSERT_EQ(status, 0);
	set_get_spacing_width_multipliers(local_test_widget, 1.5, 1.5, "widget::set_spacing_width_multipliers", SUCCESS, true, 0);
	set_get_spacing_width_multipliers(local_test_widget, 0, 0, "widget::set_spacing_width_multipliers", SUCCESS, true, 1);
	set_get_spacing_width_multipliers(local_test_widget, 3.25, 0.78, "widget::set_spacing_width_multipliers", SUCCESS, true, 2);
	set_get_spacing_width_multipliers(local_test_widget, -0.001, 10.2, "widget::set_spacing_width_multipliers", INVALID_VALUE, true, 3);
	set_get_spacing_width_multipliers(local_test_widget, 6.54, -3.4, "widget::set_spacing_width_multipliers", INVALID_VALUE, true, 4);
	set_get_spacing_width_multipliers(local_test_widget, 3.25, 0.78, "widget::get_spacing_width_multipliers", SUCCESS, false, 5);
	delete(local_test_frame);
}

TEST_F(widget_test, set_get_border_spacing_width_multiplier_test)
{
	frame* local_test_frame = new frame();
	widget local_test_widget(local_test_frame);
	local_test_widget.start_logging("widget.log");
	std::string log_content = "";
	int status = file_manager::read_file("widget.log", log_content);
	ASSERT_EQ(status, 0);
	set_get_spacing_width_multipliers(local_test_widget, 1.5, 1.5, "widget::set_spacing_width_multipliers", SUCCESS, true, 0);
	set_get_border_spacing_width_multipliers(local_test_widget, 1.2, 1.2, "widget::set_border_spacing_width_multipliers", SUCCESS, true, 1);
	set_get_border_spacing_width_multipliers(local_test_widget, 1.5, 1.5, "widget::set_border_spacing_width_multipliers", SUCCESS, true, 2);
	set_get_border_spacing_width_multipliers(local_test_widget, 1.51, 1.5, "widget::set_border_spacing_width_multipliers", INVALID_VALUE, true, 3);
	set_get_border_spacing_width_multipliers(local_test_widget, 1.5, 1.5, "widget::get_border_spacing_width_multipliers", SUCCESS, false, 5);
	set_get_border_spacing_width_multipliers(local_test_widget, 1.5, 1.51, "widget::set_border_spacing_width_multipliers", INVALID_VALUE, true, 6);
	set_get_border_spacing_width_multipliers(local_test_widget, 1.5, 1.5, "widget::get_border_spacing_width_multipliers", SUCCESS, false, 7);
	set_get_border_spacing_width_multipliers(local_test_widget, -0.5, 1.6, "widget::set_border_spacing_width_multipliers", INVALID_VALUE, true, 8);
	set_get_border_spacing_width_multipliers(local_test_widget, 5.765, -4.21, "widget::set_border_spacing_width_multipliers", INVALID_VALUE, true, 9);
	set_get_border_spacing_width_multipliers(local_test_widget, 1.5, 1.5, "widget::get_border_spacing_width_multipliers", SUCCESS, false, 10);
	set_get_spacing_width_multipliers(local_test_widget, 0.5, 0.5, "widget::set_spacing_width_multipliers", SUCCESS, true, 11);
	set_get_border_spacing_width_multipliers(local_test_widget, 0.5, 0.5, "widget::get_border_spacing_width_multipliers", SUCCESS, false, 12);
	set_get_border_spacing_width_multipliers(local_test_widget, 0, 0, "widget::set_border_spacing_width_multipliers", SUCCESS, true, 13);
	set_get_border_spacing_width_multipliers(local_test_widget, 0, 0, "widget::get_border_spacing_width_multipliers", SUCCESS, false, 14);
	delete(local_test_frame);
}

TEST_F(widget_test, get_widget_type)
{
	frame* local_test_frame = new frame();
	widget local_test_widget(local_test_frame);
	local_test_widget.start_logging("widget.log");
	std::string log_content = "";
	int status = file_manager::read_file("widget.log", log_content);
	ASSERT_EQ(status, 0);
	int widget_type = local_test_widget.get_widget_type();
	EXPECT_EQ(widget_type, WIDGET);
	status = file_manager::delete_file("widget.log");
	ASSERT_EQ(status, 0);

	delete(local_test_frame);
}

TEST_F(widget_test, selectability)
{
	frame* local_test_frame = new frame();
	widget local_test_widget(local_test_frame);
	local_test_widget.selectable();
	EXPECT_EQ(local_test_widget.is_selectable(), true);
	local_test_widget.unselectable();
	EXPECT_EQ(local_test_widget.is_selectable(), false);
	delete(local_test_frame);
}