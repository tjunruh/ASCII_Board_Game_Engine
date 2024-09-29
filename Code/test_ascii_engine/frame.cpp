#include "pch.h"
#ifdef __linux__
#include <gtest/gtest.h>
#endif
#ifdef _WIN32
#include "../ascii_engine/frame.h"
#include "../ascii_engine/format_tools.h"
#include "../file_manager/file_manager.h"
#include "../ascii_engine/error_codes.h"
#include "../ascii_engine/label.h"
#elif
#include <ascii_engine/frame.h>
#include <ascii_engine/frame.h>
#include <ascii_engine/file_manager.h>
#include <ascii_engine/error_codes.h>
#include <ascii_engine/label.h>
#endif

class frame_test : public testing::Test
{
protected:
	void set_get_controls(frame* test_frame, int select, int quit, int up, int down, int left, int right, bool set, int test_num)
	{
		if (set)
		{
			test_frame->set_controls(select, quit, up, down, left, right);
		}
		else
		{
			int returned_select = 0;
			int returned_quit = 0;
			int returned_up = 0;
			int returned_down = 0;
			int returned_left = 0;
			int returned_right = 0;
			test_frame->get_controls(returned_select, returned_quit, returned_up, returned_down, returned_left, returned_right);
			EXPECT_EQ(select, returned_select) << std::to_string(test_num);
			EXPECT_EQ(quit, returned_quit) << std::to_string(test_num);
			EXPECT_EQ(up, returned_up) << std::to_string(test_num);
			EXPECT_EQ(down, returned_down) << std::to_string(test_num);
			EXPECT_EQ(left, returned_left) << std::to_string(test_num);
			EXPECT_EQ(right, returned_right) << std::to_string(test_num);
		}
	}

	void set_get_width_multiplier(frame* test_frame, int row, int column, float multiplier, std::string expected_status_function, int expected_status_code, bool set, int test_num)
	{
		std::string log_content = "";
		if (set)
		{
			test_frame->reset_logging("frame.log");
			int status = file_manager::read_file("frame.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			test_frame->set_coordinate_width_multiplier(multiplier, row, column);
			status = file_manager::read_file("frame.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
		}
		else
		{
			test_frame->reset_logging("frame.log");
			int status = file_manager::read_file("frame.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			float returned_multiplier = test_frame->get_coordinate_width_multiplier(row, column);
			status = file_manager::read_file("frame.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
			EXPECT_EQ(multiplier, returned_multiplier) << std::to_string(test_num);
		}
	}

	void set_get_spacer_character(frame* test_frame, char character, std::string expected_status_function, int expected_status_code, bool set, int test_num)
	{
		if (set)
		{
			std::string log_content = "";
			test_frame->reset_logging("frame.log");
			int status = file_manager::read_file("frame.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			test_frame->set_spacer_character(character);
			status = file_manager::read_file("frame.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
		}
		else
		{
			char returned_character = test_frame->get_spacer_character();
			EXPECT_EQ(character, returned_character) << std::to_string(test_num);
		}
	}

	void set_get_dec_format_characters(frame* test_frame, char horizontal_char, char vertical_char, char intersection_char, char endpoint_char, std::string expected_status_function, int expected_status_code, bool set, int test_num)
	{
		if (set)
		{
			std::string log_content = "";
			test_frame->reset_logging("frame.log");
			int status = file_manager::read_file("frame.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			test_frame->set_dec_format_characters(horizontal_char, vertical_char, intersection_char, endpoint_char);
			status = file_manager::read_file("frame.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
		}
		else
		{
			char returned_horizontal_char = ' ';
			char returned_vertical_char = ' ';
			char returned_intersection_char = ' ';
			char returned_endpoint_char = ' ';
			test_frame->get_dec_format_characters(returned_horizontal_char, returned_vertical_char, returned_intersection_char, returned_endpoint_char);
			EXPECT_EQ(horizontal_char, returned_horizontal_char) << std::to_string(test_num);
			EXPECT_EQ(vertical_char, returned_vertical_char) << std::to_string(test_num);
			EXPECT_EQ(intersection_char, returned_intersection_char) << std::to_string(test_num);
			EXPECT_EQ(endpoint_char, returned_endpoint_char) << std::to_string(test_num);
		}
	}

	void set_get_default_background_color(frame* test_frame, int color, std::string expected_status_function, int expected_status_code, bool set, int test_num)
	{
		if (set)
		{
			std::string log_content = "";
			test_frame->reset_logging("frame.log");
			int status = file_manager::read_file("frame.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			test_frame->set_default_background_color(color);
			status = file_manager::read_file("frame.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
		}
		else
		{
			int returned_color = test_frame->get_default_background_color();
			EXPECT_EQ(color, returned_color) << std::to_string(test_num);
		}
	}

	void set_get_default_foreground_color(frame* test_frame, int color, std::string expected_status_function, int expected_status_code, bool set, int test_num)
	{
		if (set)
		{
			std::string log_content = "";
			test_frame->reset_logging("frame.log");
			int status = file_manager::read_file("frame.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			test_frame->set_default_foreground_color(color);
			status = file_manager::read_file("frame.log", log_content);
			ASSERT_EQ(status, 0) << std::to_string(test_num);
			EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
		}
		else
		{
			int returned_color = test_frame->get_default_foreground_color();
			EXPECT_EQ(color, returned_color) << std::to_string(test_num);
		}
	}
};

TEST_F(frame_test, set_get_controls_test)
{
	frame* test_frame = new frame();
	set_get_controls(test_frame, ascii_io::enter, ascii_io::q, ascii_io::up, ascii_io::down, ascii_io::left, ascii_io::right, true, 0);
	set_get_controls(test_frame, ascii_io::enter, ascii_io::q, ascii_io::up, ascii_io::down, ascii_io::left, ascii_io::right, false, 1);
	delete(test_frame);
}

TEST_F(frame_test, set_get_coordinate_width_multiplier_test)
{
	frame* test_frame = new frame(true, "frame.log");
	label label_1(test_frame);
	label label_2(test_frame);
	label label_3(test_frame, "new line");
	label label_4(test_frame, "new line");
	label label_5(test_frame);
	label label_6(test_frame);
	set_get_width_multiplier(test_frame, 0, 0, 1.5, "frame::set_coordinate_width_multiplier", SUCCESS, true, 0);
	set_get_width_multiplier(test_frame, 0, 1, 2, "frame::set_coordinate_width_multiplier", SUCCESS, true, 1);
	set_get_width_multiplier(test_frame, 1, 0, 3, "frame::set_coordinate_width_multiplier", SUCCESS, true, 2);
	set_get_width_multiplier(test_frame, 2, 0, 1.2, "frame::set_coordinate_width_multiplier", SUCCESS, true, 3);
	set_get_width_multiplier(test_frame, 2, 1, 1.75, "frame::set_coordinate_width_multiplier", SUCCESS, true, 4);
	set_get_width_multiplier(test_frame, 2, 2, 2, "frame::set_coordinate_width_multiplier", SUCCESS, true, 5);

	set_get_width_multiplier(test_frame, 0, 0, -1, "frame::set_coordinate_width_multiplier", INVALID_VALUE, true, 6);
	set_get_width_multiplier(test_frame, 0, 2, 5, "frame::set_coordinate_width_multiplier", ELEMENT_NOT_FOUND, true, 7);
	set_get_width_multiplier(test_frame, 3, 0, 5, "frame::set_coordinate_width_multiplier", ELEMENT_NOT_FOUND, true, 8);

	set_get_width_multiplier(test_frame, 0, 0, 1.5, "frame::get_coordinate_width_multiplier", SUCCESS, false, 9);
	set_get_width_multiplier(test_frame, 0, 1, 2, "frame::get_coordinate_width_multiplier", SUCCESS, false, 10);
	set_get_width_multiplier(test_frame, 1, 0, 3, "frame::get_coordinate_width_multiplier", SUCCESS, false, 11);
	set_get_width_multiplier(test_frame, 2, 0, 1.2, "frame::get_coordinate_width_multiplier", SUCCESS, false, 12);
	set_get_width_multiplier(test_frame, 2, 1, 1.75, "frame::get_coordinate_width_multiplier", SUCCESS, false, 13);
	set_get_width_multiplier(test_frame, 2, 2, 2, "frame::get_coordinate_width_multiplier", SUCCESS, false, 14);

	set_get_width_multiplier(test_frame, 0, 2, 0, "frame::get_coordinate_width_multiplier", ELEMENT_NOT_FOUND, false, 15);
	set_get_width_multiplier(test_frame, 3, 0, 0, "frame::get_coordinate_width_multiplier", ELEMENT_NOT_FOUND, false, 16);
	delete(test_frame);
}

TEST_F(frame_test, set_get_spacer_character_test)
{
	frame* test_frame = new frame(true);
	set_get_spacer_character(test_frame, '\n', "frame::set_spacer_character", INVALID_VALUE, true, 0);
	set_get_spacer_character(test_frame, '=', "frame::set_spacer_character", SUCCESS, true, 1);
	set_get_spacer_character(test_frame, '=', "N/A", UNDEFINED, false, 2);
	delete(test_frame);
}

TEST_F(frame_test, enable_disable_dec_test)
{
	frame* test_frame = new frame(true);
	test_frame->enable_dec();
	EXPECT_EQ(test_frame->dec_enabled(), true);
	test_frame->disable_dec();
	EXPECT_EQ(test_frame->dec_enabled(), false);
	delete(test_frame);
}

TEST_F(frame_test, enable_disable_color_test)
{
	frame* test_frame = new frame(true);
	test_frame->enable_color();
	EXPECT_EQ(test_frame->color_enabled(), true);
	test_frame->disable_color();;
	EXPECT_EQ(test_frame->color_enabled(), false);
	delete(test_frame);
}

TEST_F(frame_test, set_get_dec_format_characters_test)
{
	frame* test_frame = new frame(true);
	set_get_dec_format_characters(test_frame, ':', '=', 'x', ',', "frame::set_dec_format_characters", SUCCESS, true, 0);
	set_get_dec_format_characters(test_frame, '\n', '*', '*', '*', "frame::set_dec_format_characters", INVALID_VALUE, true, 1);
	set_get_dec_format_characters(test_frame, '*', '\n', '*', '*', "frame::set_dec_format_characters", INVALID_VALUE, true, 2);
	set_get_dec_format_characters(test_frame, '*', '*', '\n', '*', "frame::set_dec_format_characters", INVALID_VALUE, true, 3);
	set_get_dec_format_characters(test_frame, '*', '*', '*', '\n', "frame::set_dec_format_characters", INVALID_VALUE, true, 4);
	set_get_dec_format_characters(test_frame, ':', '=', 'x', ',', "N/A", UNDEFINED, false, 5);
	delete(test_frame);
}

TEST_F(frame_test, set_get_default_background_color_test)
{
	frame* test_frame = new frame(true);
	set_get_default_background_color(test_frame, format_tools::blue, "frame::set_default_background_color", SUCCESS, true, 0);
	set_get_default_background_color(test_frame, 1000, "frame::set_default_background_color", INVALID_VALUE, true, 1);
	set_get_default_background_color(test_frame, format_tools::blue, "N/A", UNDEFINED, false, 2);
	delete(test_frame);
}

TEST_F(frame_test, set_get_default_foreground_color_test)
{
	frame* test_frame = new frame(true);
	set_get_default_foreground_color(test_frame, format_tools::blue, "frame::set_default_foreground_color", SUCCESS, true, 0);
	set_get_default_foreground_color(test_frame, 1000, "frame::set_default_foreground_color", INVALID_VALUE, true, 1);
	set_get_default_foreground_color(test_frame, format_tools::blue, "N/A", UNDEFINED, false, 2);
	delete(test_frame);
}