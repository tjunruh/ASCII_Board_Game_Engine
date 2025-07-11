#include "pch.h"
#ifdef __linux__
#include <gtest/gtest.h>
#endif
#ifdef _WIN32
#include "../ascii_engine/label.h"
#include "../file_manager/file_manager.h"
#include "../ascii_engine/error_codes.h"
#include "../ascii_engine/frame.h"
#include "../ascii_engine/format_tools.h"
#elif __linux__
#include <ascii_engine/label.h>
#include <ascii_engine/file_manager.h>
#include <ascii_engine/error_codes.h>
#include <ascii_engine/frame.h>
#include <ascii_engine/format_tools.h>
#endif

#include "expected_display_data.h"

#include <string>
#include <algorithm>

class label_test : public testing::Test
{
protected:

	void run_test(std::string frame_output, std::vector<label> labels, expected_display_data answer)
	{
		ASSERT_EQ(labels.size(), answer.heights.size());
		ASSERT_EQ(labels.size(), answer.widths.size());
		ASSERT_EQ(labels.size(), answer.x_origins.size());
		ASSERT_EQ(labels.size(), answer.y_origins.size());
		if (answer.heights_with_spacing.size() != 0)
		{
			ASSERT_EQ(labels.size(), answer.heights_with_spacing.size());
		}

		if (answer.widths_with_spacing.size() != 0)
		{
			ASSERT_EQ(labels.size(), answer.widths_with_spacing.size());
		}

		EXPECT_EQ(frame_output, answer.output) << "Frame output:\n" + frame_output;

		for (unsigned int i = 0; i < answer.x_origins.size(); i++)
		{
			EXPECT_EQ(labels[i].get_x_origin(), answer.x_origins[i]) << "x origin test for label " + std::to_string(i);
		}

		for (unsigned int i = 0; i < answer.y_origins.size(); i++)
		{
			EXPECT_EQ(labels[i].get_y_origin(), answer.y_origins[i]) << "y origin test for label " + std::to_string(i);
		}

		for (unsigned int i = 0; i < answer.heights.size(); i++)
		{
			EXPECT_EQ(labels[i].get_height(), answer.heights[i]) << "heights test for label " + std::to_string(i);
		}

		for (unsigned int i = 0; i < answer.widths.size(); i++)
		{
			EXPECT_EQ(labels[i].get_width(), answer.widths[i]) << "widths test for label " + std::to_string(i);
		}

		for (unsigned int i = 0; i < answer.heights_with_spacing.size(); i++)
		{
			EXPECT_EQ(labels[i].get_height(true), answer.heights_with_spacing[i]) << "heights with spacing test for label " + std::to_string(i);
		}

		for (unsigned int i = 0; i < answer.widths_with_spacing.size(); i++)
		{
			EXPECT_EQ(labels[i].get_width(true), answer.widths_with_spacing[i]) << "widths with spacing test for label " + std::to_string(i);
		}
	}

	void set_color_test(label& local_test_label, std::vector<format_tools::index_format> colors, std::vector<format_tools::index_format> colors_match, std::string expected_status_function, int expected_status_code, int test_num)
	{
		std::string log_content = "";
		local_test_label.reset_logging("label.log");
		local_test_label.set_colors(colors);
		int status = file_manager::read_file("label.log", log_content);
		ASSERT_EQ(status, 0) << std::to_string(test_num);
		EXPECT_NE(log_content.find(expected_status_function + " status: " + std::to_string(expected_status_code)), std::string::npos) << "Test Number: " + std::to_string(test_num) + "\nExpected function: " + expected_status_function + "\nExpected code: " + std::to_string(expected_status_code);
		std::vector<format_tools::index_format> returned_colors = local_test_label.get_colors();

		ASSERT_EQ(colors_match.size(), returned_colors.size()) << "Test Number: " + std::to_string(test_num);
		for (unsigned int i = 0; i < colors_match.size(); i++)
		{
			EXPECT_EQ(colors_match[i].index, returned_colors[i].index) << "Test Number: " + std::to_string(test_num) + "\nIndex: " + std::to_string(i);
			EXPECT_EQ(colors_match[i].format.background_format, returned_colors[i].format.background_format) << "Test Number: " + std::to_string(test_num) + "\nIndex: " + std::to_string(i);
			EXPECT_EQ(colors_match[i].format.foreground_format, returned_colors[i].format.foreground_format) << "Test Number: " + std::to_string(test_num) + "\nIndex: " + std::to_string(i);
			EXPECT_EQ(colors_match[i].format.dec, returned_colors[i].format.dec) << "Test Number: " + std::to_string(test_num) + "\nIndex: " + std::to_string(i);
		}
	}

	void format_equivalent_test(std::vector<format_tools::index_format> correct_answer, std::vector<format_tools::index_format> test_format, int test_num)
	{
		std::sort(correct_answer.begin(), correct_answer.end(), format_tools::index_format_sorting_functor());
		std::sort(test_format.begin(), test_format.end(), format_tools::index_format_sorting_functor());
		ASSERT_EQ(test_format.size(), correct_answer.size()) << "Test num: " + std::to_string(test_num) + "\ncorrect_answer vector and test_colors vector have different lengths.";
		for (unsigned int i = 0; i < correct_answer.size(); i++)
		{
			EXPECT_EQ(test_format[i].index, correct_answer[i].index) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
			EXPECT_EQ(test_format[i].format.background_format, correct_answer[i].format.background_format) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
			EXPECT_EQ(test_format[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
			EXPECT_EQ(test_format[i].format.dec, correct_answer[i].format.dec) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
		}
	}
};

TEST_F(label_test, get_widget_type)
{
	frame* local_test_frame = new frame();
	label local_test_label_1(local_test_frame);
	EXPECT_EQ(local_test_label_1.get_widget_type(), LABEL);
	delete(local_test_frame);
}

TEST_F(label_test, is_selectable)
{
	frame* local_test_frame = new frame();
	label local_test_label_1(local_test_frame);
	EXPECT_EQ(local_test_label_1.is_selectable(), false);
	delete(local_test_frame);
}

TEST_F(label_test, set_get_controls_test)
{
	frame* local_test_frame = new frame();
	label local_test_label_1(local_test_frame, "none", 0, true);
	local_test_label_1.set_controls(ascii_io::w, ascii_io::s, ascii_io::a, ascii_io::d, ascii_io::ESC);
	int up = ascii_io::undefined;
	int down = ascii_io::undefined;
	int left = ascii_io::undefined;
	int right = ascii_io::undefined;
	int quit = ascii_io::undefined;
	local_test_label_1.get_controls(up, down, left, right, quit);
	EXPECT_EQ(up, ascii_io::w);
	EXPECT_EQ(down, ascii_io::s);
	EXPECT_EQ(quit, ascii_io::ESC);
	delete(local_test_frame);
}

TEST_F(label_test, set_color)
{
	format_tools::common_format empty_format;
	std::vector<format_tools::index_format> empty_color;
	std::vector<format_tools::index_format> color1 =
	{
		{-1, empty_format, ' '}
	};

	std::vector<format_tools::index_format> color2 =
	{
		{0, empty_format, ' '}
	};

	std::vector<format_tools::index_format> color3 =
	{
		{9, empty_format, ' '}
	};

	frame* local_test_frame = new frame();
	label local_test_label_1(local_test_frame, "none", 0, true);
	set_color_test(local_test_label_1, color2, empty_color, "label::set_colors", INVALID_INDEX, 0);
	local_test_label_1.set_output("012345678");
	set_color_test(local_test_label_1, color1, empty_color, "label::set_colors", INVALID_INDEX, 1);
	set_color_test(local_test_label_1, color2, color2, "label::set_colors", SUCCESS, 2);
	set_color_test(local_test_label_1, color3, color2, "label::set_colors", INVALID_INDEX, 3);
	local_test_label_1.set_output("0123456789");
	set_color_test(local_test_label_1, color3, color3, "label::set_colors", SUCCESS, 4);

	delete(local_test_frame);
}

TEST_F(label_test, test_basic)
{
	const expected_display_data correct_answer =
	{
		"This is widget 1.                                 This                                              \n"
		"                                                  is                                                \n"
		"                                                  widget                                            \n"
		"                                                  2                                                 \n"
		"This is widget                                                                                      \n"
		"3                                                                                                   \n"
		"This is                          This                             This is widget 6                  \n"
		"widget                           is                                                                 \n"
		"4                                widget                                                             \n"
		"                                 5                                                                  ",
		{ 0, 50, 0, 0, 33, 66 },
		{ 0, 0, 4, 6, 6, 6 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 1, 4, 2, 3, 4, 1 },
		{},
		{}
	};
	
	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(10);
	local_test_frame->set_fake_console_width(100);
	std::vector<label> labels;
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.");
	local_test_label_1.add_border(true);
	local_test_label_1.add_border(false);
	labels.push_back(local_test_label_1);
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	labels.push_back(local_test_label_2);
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	labels.push_back(local_test_label_3);
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4");
	labels.push_back(local_test_label_4);
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	labels.push_back(local_test_label_5);
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6");
	labels.push_back(local_test_label_6);
	std::string output = local_test_frame->get_frame_output();

	run_test(output, labels, correct_answer);

	delete(local_test_frame);
}

TEST_F(label_test, test_border)
{
	const expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"| This is widget 1.                              || This                                           |\n"
		".------------------------------------------------.| is                                             |\n"
		"                                                  | widget                                         |\n"
		"                                                  | 2                                              |\n"
		"                                                  .------------------------------------------------.\n"
		".--------------------------------------------------------------------------------------------------.\n"
		"| This is widget                                                                                   |\n"
		"| 3                                                                                                |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"| This is                       || This                          || This is widget 6              | \n"
		"| widget                        || is                            |.-------------------------------. \n"
		"| 4                             || widget                        |                                  \n"
		".-------------------------------.| 5                             |                                  \n"
		"                                 .-------------------------------.                                  ",
		{ 2, 52, 2, 2, 35, 68 },
		{ 1, 1, 7, 11, 11, 11 },
		{ 46, 46, 96, 29, 29, 29 },
		{ 1, 4, 2, 3, 4, 1 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 3, 6, 4, 5, 6, 3 }
	};

	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<label> labels;
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.");
	local_test_label_1.add_border(true);
	labels.push_back(local_test_label_1);
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border(true);
	labels.push_back(local_test_label_2);
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border(true);
	labels.push_back(local_test_label_3);
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4");
	local_test_label_4.add_border(true);
	labels.push_back(local_test_label_4);
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border(true);
	labels.push_back(local_test_label_5);
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6");
	local_test_label_6.add_border(true);
	labels.push_back(local_test_label_6);
	std::string output = local_test_frame->get_frame_output();

	run_test(output, labels, correct_answer);

	delete(local_test_frame);
}

TEST_F(label_test, test_newline)
{
	const expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"| This is widget 1.                              || This                                           |\n"
		"|                                                || is                                             |\n"
		"|                                                || widget                                         |\n"
		"|                                                || 2                                              |\n"
		".------------------------------------------------..------------------------------------------------.\n"
		".--------------------------------------------------------------------------------------------------.\n"
		"| This is widget                                                                                   |\n"
		"| 3                                                                                                |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"| This is                       || This                          || This is widget 6              | \n"
		"| widget                        || is                            ||                               | \n"
		"| 4                             || widget                        ||                               | \n"
		"|                               || 5                             ||                               | \n"
		".-------------------------------..-------------------------------..-------------------------------. ",
		{ 2, 52, 2, 2, 35, 68 },
		{ 1, 1, 7, 11, 11, 11 },
		{ 46, 46, 96, 29, 29, 29 },
		{ 4, 4, 2, 4, 4, 4 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 6, 6, 4, 6, 6, 6 }
	};

	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<label> labels;
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.\n\n\n");
	local_test_label_1.add_border(true);
	labels.push_back(local_test_label_1);
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border(true);
	labels.push_back(local_test_label_2);
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border(true);
	labels.push_back(local_test_label_3);
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4\n");
	local_test_label_4.add_border(true);
	labels.push_back(local_test_label_4);
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border(true);
	labels.push_back(local_test_label_5);
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6\n\n\n");
	local_test_label_6.add_border(true);
	labels.push_back(local_test_label_6);
	std::string output = local_test_frame->get_frame_output();

	run_test(output, labels, correct_answer);

	delete(local_test_frame);
}

TEST_F(label_test, test_merge)
{
	const expected_display_data correct_answer =
	{
		"This is widget 1.                                 This                                              \n"
		"This is widget 2.                                 is                                                \n"
		"                                                  widget                                            \n"
		"                                                  3                                                 \n"
		"This is widget                                                                                      \n"
		"4                                                                                                   \n"
		"This is                          This                             This is widget 7                  \n"
		"widget                           is                               This is widget 8                  \n"
		"5                                widget                                                             \n"
		"                                 6                                                                  ",
		{ 0, 0, 50, 0, 0, 33, 66, 66 },
		{ 0, 1, 0, 4, 6, 6, 6, 7 },
		{ 50, 50, 50, 100, 33, 33, 33, 33 },
		{ 1, 1, 4, 2, 3, 4, 1, 1 },
		{},
		{}
	};
	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(10);
	local_test_frame->set_fake_console_width(100);
	std::vector<label> labels;
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.");
	labels.push_back(local_test_label_1);
	label local_test_label_2(local_test_frame, "merge");
	local_test_label_2.set_output("This is widget 2.");
	labels.push_back(local_test_label_2);
	label local_test_label_3(local_test_frame);
	local_test_label_3.set_output("This\nis\nwidget\n3");
	labels.push_back(local_test_label_3);
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is widget\n4");
	labels.push_back(local_test_label_4);
	label local_test_label_5(local_test_frame, "new line");
	local_test_label_5.set_output("This is\nwidget\n5");
	labels.push_back(local_test_label_5);
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This\nis\nwidget\n6");
	labels.push_back(local_test_label_6);
	label local_test_label_7(local_test_frame);
	local_test_label_7.set_output("This is widget 7");
	labels.push_back(local_test_label_7);
	label local_test_label_8(local_test_frame, "merge");
	local_test_label_8.set_output("This is widget 8");
	labels.push_back(local_test_label_8);
	std::string output = local_test_frame->get_frame_output();
	
	run_test(output, labels, correct_answer);

	const expected_display_data correct_answer_2=
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"| This is widget 1.                              || This                                           |\n"
		".------------------------------------------------.| is                                             |\n"
		".------------------------------------------------.| widget                                         |\n"
		"| This is widget 2.                              || 3                                              |\n"
		".------------------------------------------------..------------------------------------------------.\n"
		".--------------------------------------------------------------------------------------------------.\n"
		"| This is widget                                                                                   |\n"
		"| 4                                                                                                |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"| This is                       || This                          || This is widget 7              | \n"
		"| widget                        || is                            |.-------------------------------. \n"
		"| 5                             || widget                        |.-------------------------------. \n"
		".-------------------------------.| 6                             || This is widget 8              | \n"
		"                                 .-------------------------------..-------------------------------. ",
		{ 2, 2, 52, 2, 2, 35, 68, 68 },
		{ 1, 4, 1, 7, 11, 11, 11, 14 },
		{ 46, 46, 46, 96, 29, 29, 29, 29 },
		{ 1, 1, 4, 2, 3, 4, 1, 1 },
		{ 50, 50, 50, 100, 33, 33, 33, 33 },
		{ 3, 3, 6, 4, 5, 6, 3, 3 }
	};
	labels.clear();
	local_test_frame->set_fake_console_height(16);
	local_test_label_1.add_border(true);
	labels.push_back(local_test_label_1);
	local_test_label_2.add_border(true);
	labels.push_back(local_test_label_2);
	local_test_label_3.add_border(true);
	labels.push_back(local_test_label_3);
	local_test_label_4.add_border(true);
	labels.push_back(local_test_label_4);
	local_test_label_5.add_border(true);
	labels.push_back(local_test_label_5);
	local_test_label_6.add_border(true);
	labels.push_back(local_test_label_6);
	local_test_label_7.add_border(true);
	labels.push_back(local_test_label_7);
	local_test_label_8.add_border(true);
	labels.push_back(local_test_label_8);
	output = local_test_frame->get_frame_output();
	
	run_test(output, labels, correct_answer_2);

	delete(local_test_frame);
}

TEST_F(label_test, test_spacing)
{
	expected_display_data correct_answer =
	{
		"                                                  .-----------------------------------------------. \n"
		".-----------------------------------------------. | This                                          | \n"
		"| This is widget 1.                             | | is                                            | \n"
		".-----------------------------------------------. | widget                                        | \n"
		"                                                  | 2                                             | \n"
		"                                                  .-----------------------------------------------. \n"
		"                                                                                                    \n"
		"     .----------------------------------------------------------------------------------------.     \n"
		"     | This is widget                                                                         |     \n"
		"     | 3                                                                                      |     \n"
		"     .----------------------------------------------------------------------------------------.     \n"
		"                                                                                                    \n"
		"                                                                                                    \n"
		"                                 .-------------------------------. .-----------------------------.  \n"
		".-------------------------------.| This                          | | This is widget 6            |  \n"
		"| This is                       || is                            | .-----------------------------.  \n"
		"| widget                        || widget                        |                                  \n"
		"| 4                             || 5                             |                                  \n"
		".-------------------------------..-------------------------------.                                  \n"
		"                                                                                                    ",
		{ 2, 52, 7, 2, 35, 69 },
		{ 2, 1, 8, 15, 14, 14 },
		{ 45, 45, 86, 29, 29, 27 },
		{ 1, 4, 2, 3, 4, 1 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 5, 6, 7, 7, 6, 3 }
	};
	
	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<label> labels;
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.");
	local_test_label_1.add_border(true);
	local_test_label_1.set_spacing(1, 1, 0, 1);
	labels.push_back(local_test_label_1);
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border(true);
	local_test_label_2.set_spacing(0, 0, 0, 1);
	labels.push_back(local_test_label_2);
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border(true);
	local_test_label_3.set_spacing(1, 2, 5, 5);
	labels.push_back(local_test_label_3);
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4");
	local_test_label_4.add_border(true);
	local_test_label_4.set_spacing(1, 1, 0, 0);
	labels.push_back(local_test_label_4);
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border(true);
	labels.push_back(local_test_label_5);
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6");
	local_test_label_6.add_border(true);
	local_test_label_6.set_spacing(0, 0, 1, 1);
	labels.push_back(local_test_label_6);
	std::string output = local_test_frame->get_frame_output();
	
	run_test(output, labels, correct_answer);

	delete(local_test_frame);
}

TEST_F(label_test, test_width_multiplier)
{
	expected_display_data correct_answer =
	{
		"                                                                 .-------------------------------.  \n"
		"                .-------------------------------.                | This                          |  \n"
		"                | This is widget 1.             |                | is                            |  \n"
		"                .-------------------------------.                | widget                        |  \n"
		"                                                                 | 2                             |  \n"
		"                                                                 .-------------------------------.  \n"
		"                                                                                                    \n"
		"                                 .-------------------------------.                                  \n"
		"                                 | This is widget                |                                  \n"
		"                                 | 3                             |                                  \n"
		"                                 .-------------------------------.                                  \n"
		"                                                                                                    \n"
		"                                                                                                    \n"
		"                           .----------------.         .-------------------------------------------. \n"
		".----------------.         | This           |         | This is widget 6                          | \n"
		"| This is        |         | is             |         .-------------------------------------------. \n"
		"| widget         |         | widget         |                                                       \n"
		"| 4              |         | 5              |                                                       \n"
		".----------------.         .----------------.                                                       \n"
		"                                                                                                    ",
		{ 18, 67, 35, 2, 29, 56 },
		{ 2, 1, 8, 15, 14, 14 },
		{ 29, 29, 29, 14, 14, 41 },
		{ 1, 4, 2, 3, 4, 1 },
		{ 57, 41, 99, 27, 27, 45 },
		{ 5, 6, 7, 7, 6, 3 }
	};

	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<label> labels;
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.");
	local_test_label_1.add_border(true);
	local_test_label_1.set_spacing(1, 1, 0, 1);
	local_test_label_1.use_spacing_width_multipliers(true);
	local_test_label_1.set_width_multiplier(2);
	local_test_label_1.set_spacing_width_multipliers(1, 0.5);
	labels.push_back(local_test_label_1);
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border(true);
	local_test_label_2.set_spacing(0, 0, 0, 1);
	local_test_label_2.use_spacing_width_multipliers(true);
	local_test_label_2.set_width_multiplier(2);
	local_test_label_2.set_spacing_width_multipliers(0.5, 0);
	labels.push_back(local_test_label_2);
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border(true);
	local_test_label_3.set_spacing(1, 2, 5, 5);
	local_test_label_3.use_spacing_width_multipliers(true);
	local_test_label_3.set_width_multiplier(1);
	local_test_label_3.set_spacing_width_multipliers(1, 1);
	labels.push_back(local_test_label_3);
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4");
	local_test_label_4.add_border(true);
	local_test_label_4.set_spacing(1, 1, 0, 0);
	local_test_label_4.use_spacing_width_multipliers(true);
	local_test_label_4.set_width_multiplier(1);
	local_test_label_4.set_spacing_width_multipliers(0, 0.5);
	labels.push_back(local_test_label_4);
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border(true);
	local_test_label_5.use_spacing_width_multipliers(true);
	local_test_label_5.set_width_multiplier(1);
	local_test_label_5.set_spacing_width_multipliers(0, 0.5);
	labels.push_back(local_test_label_5);
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6");
	local_test_label_6.add_border(true);
	local_test_label_6.set_spacing(0, 0, 1, 1);
	local_test_label_6.use_spacing_width_multipliers(true);
	local_test_label_6.set_width_multiplier(2.5);
	local_test_label_6.set_spacing_width_multipliers(0, 0);
	labels.push_back(local_test_label_6);
	std::string output = local_test_frame->get_frame_output();

	run_test(output, labels, correct_answer);

	delete(local_test_frame);
}

TEST_F(label_test, right_alignment)
{
	expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"|                              This is widget 1. ||                                           This |\n"
		"|                                                ||                                             is |\n"
		"|                                                ||                                         widget |\n"
		"|                                                ||                                              2 |\n"
		".------------------------------------------------..------------------------------------------------.\n"
		".--------------------------------------------------------------------------------------------------.\n"
		"|                                                                                   This is widget |\n"
		"|                                                                                                3 |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"|                       This is ||                          This ||              This is widget 6 | \n"
		"|                        widget ||                            is ||                               | \n"
		"|                             4 ||                        widget ||                               | \n"
		"|                               ||                             5 ||                               | \n"
		".-------------------------------..-------------------------------..-------------------------------. ",
		{ 2, 52, 2, 2, 35, 68 },
		{ 1, 1, 7, 11, 11, 11 },
		{ 46, 46, 96, 29, 29, 29 },
		{ 4, 4, 2, 4, 4, 4 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 6, 6, 4, 6, 6, 6 }
	};

	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<label> labels;
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.\n\n\n");
	local_test_label_1.add_border(true);
	local_test_label_1.set_alignment("right");
	labels.push_back(local_test_label_1);
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border(true);
	local_test_label_2.set_alignment("right");
	labels.push_back(local_test_label_2);
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border(true);
	local_test_label_3.set_alignment("right");
	labels.push_back(local_test_label_3);
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4\n");
	local_test_label_4.add_border(true);
	local_test_label_4.set_alignment("right");
	labels.push_back(local_test_label_4);
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border(true);
	local_test_label_5.set_alignment("right");
	labels.push_back(local_test_label_5);
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6\n\n\n");
	local_test_label_6.add_border(true);
	local_test_label_6.set_alignment("right");
	labels.push_back(local_test_label_6);
	std::string output = local_test_frame->get_frame_output();
	
	run_test(output, labels, correct_answer);

	delete(local_test_frame);
}

TEST_F(label_test, center_alignment)
{
	expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"|               This is widget 1.                ||                      This                      |\n"
		"|                                                ||                       is                       |\n"
		"|                                                ||                     widget                     |\n"
		"|                                                ||                       2                        |\n"
		".------------------------------------------------..------------------------------------------------.\n"
		".--------------------------------------------------------------------------------------------------.\n"
		"|                                          This is widget                                          |\n"
		"|                                                3                                                 |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"|            This is            ||             This              ||       This is widget 6        | \n"
		"|            widget             ||              is               ||                               | \n"
		"|               4               ||            widget             ||                               | \n"
		"|                               ||               5               ||                               | \n"
		".-------------------------------..-------------------------------..-------------------------------. ",
		{ 2, 52, 2, 2, 35, 68 },
		{ 1, 1, 7, 11, 11, 11 },
		{ 46, 46, 96, 29, 29, 29 },
		{ 4, 4, 2, 4, 4, 4 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 6, 6, 4, 6, 6, 6 }
	};

	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<label> labels;
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.\n\n\n");
	local_test_label_1.add_border(true);
	local_test_label_1.set_alignment("center");
	labels.push_back(local_test_label_1);
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border(true);
	local_test_label_2.set_alignment("center");
	labels.push_back(local_test_label_2);
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border(true);
	local_test_label_3.set_alignment("center");
	labels.push_back(local_test_label_3);
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4\n");
	local_test_label_4.add_border(true);
	local_test_label_4.set_alignment("center");
	labels.push_back(local_test_label_4);
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border(true);
	local_test_label_5.set_alignment("center");
	labels.push_back(local_test_label_5);
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6\n\n\n");
	local_test_label_6.add_border(true);
	local_test_label_6.set_alignment("center");
	labels.push_back(local_test_label_6);
	std::string output = local_test_frame->get_frame_output();
	
	run_test(output, labels, correct_answer);

	delete(local_test_frame);
}

TEST_F(label_test, center_block_alignment)
{
	expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"|               This is widget 1.                ||                     This                       |\n"
		"|                                                ||                     is                         |\n"
		"|                                                ||                     widget                     |\n"
		"|                                                ||                     2                          |\n"
		".------------------------------------------------..------------------------------------------------.\n"
		".--------------------------------------------------------------------------------------------------.\n"
		"|                                          This is widget                                          |\n"
		"|                                          3                                                       |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"|            This is            ||            This               ||       This is widget 6        | \n"
		"|            widget             ||            is                 ||                               | \n"
		"|            4                  ||            widget             ||                               | \n"
		"|                               ||            5                  ||                               | \n"
		".-------------------------------..-------------------------------..-------------------------------. ",
		{ 2, 52, 2, 2, 35, 68 },
		{ 1, 1, 7, 11, 11, 11 },
		{ 46, 46, 96, 29, 29, 29 },
		{ 4, 4, 2, 4, 4, 4 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 6, 6, 4, 6, 6, 6 }
	};
	
	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<label> labels;
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.\n\n\n");
	local_test_label_1.add_border(true);
	local_test_label_1.set_alignment("center block");
	labels.push_back(local_test_label_1);
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border(true);
	local_test_label_2.set_alignment("center block");
	labels.push_back(local_test_label_2);
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border(true);
	local_test_label_3.set_alignment("center block");
	labels.push_back(local_test_label_3);
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4\n");
	local_test_label_4.add_border(true);
	local_test_label_4.set_alignment("center block");
	labels.push_back(local_test_label_4);
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border(true);
	local_test_label_5.set_alignment("center block");
	labels.push_back(local_test_label_5);
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6\n\n\n");
	local_test_label_6.add_border(true);
	local_test_label_6.set_alignment("center block");
	labels.push_back(local_test_label_6);
	std::string output = local_test_frame->get_frame_output();
	
	run_test(output, labels, correct_answer);

	delete(local_test_frame);
}

TEST_F(label_test, test_line_constraint)
{
	const expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"| This is widget 1.                              || This                                           |\n"
		"|                                                |.------------------------------------------------.\n"
		"|                                                |                                                  \n"
		"|                                                |                                                  \n"
		".------------------------------------------------.                                                  \n"
		".--------------------------------------------------------------------------------------------------.\n"
		"| This is widget                                                                                   |\n"
		"| 3                                                                                                |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"| This is                       || This                          || This is widget 6              | \n"
		"| widget                        || is                            ||                               | \n"
		".-------------------------------.| widget                        ||                               | \n"
		"                                 .-------------------------------.|                               | \n"
		"                                                                  .-------------------------------. ",
		{ 2, 52, 2, 2, 35, 68 },
		{ 1, 1, 7, 11, 11, 11 },
		{ 46, 46, 96, 29, 29, 29 },
		{ 4, 1, 2, 2, 3, 4 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 6, 3, 4, 4, 5, 6 }
	};

	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<label> labels;
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.\n\n\n");
	local_test_label_1.add_border(true);
	labels.push_back(local_test_label_1);
	label local_test_label_2(local_test_frame, "none", 1);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border(true);
	labels.push_back(local_test_label_2);
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border(true);
	labels.push_back(local_test_label_3);
	label local_test_label_4(local_test_frame, "new line", 2);
	local_test_label_4.set_output("This is\nwidget\n4\n");
	local_test_label_4.add_border(true);
	labels.push_back(local_test_label_4);
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border(true);
	local_test_label_5.set_lines_count(3);
	labels.push_back(local_test_label_5);
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6\n\n\n");
	local_test_label_6.add_border(true);
	labels.push_back(local_test_label_6);
	std::string output = local_test_frame->get_frame_output();

	run_test(output, labels, correct_answer);

	delete(local_test_frame);
}

TEST_F(label_test, test_scroll)
{
	const expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"| This is widget 1.                              || 2                                              |\n"
		"|                                                |.------------------------------------------------.\n"
		"|                                                |                                                  \n"
		"|                                                |                                                  \n"
		".------------------------------------------------.                                                  \n"
		".--------------------------------------------------------------------------------------------------.\n"
		"| This is widget                                                                                   |\n"
		"| 3                                                                                                |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"| widget                        || is                            || This is widget 6              | \n"
		"| 4                             || widget                        ||                               | \n"
		".-------------------------------.| 5                             ||                               | \n"
		"                                 .-------------------------------.|                               | \n"
		"                                                                  .-------------------------------. ",
		{ 2, 52, 2, 2, 35, 68 },
		{ 1, 1, 7, 11, 11, 11 },
		{ 46, 46, 96, 29, 29, 29 },
		{ 4, 1, 2, 2, 3, 4 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 6, 3, 4, 4, 5, 6 }
	};

	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<label> labels;
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.\n\n\n");
	local_test_label_1.add_border(true);
	labels.push_back(local_test_label_1);
	label local_test_label_2(local_test_frame, "none", 1);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border(true);
	labels.push_back(local_test_label_2);
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border(true);
	labels.push_back(local_test_label_3);
	label local_test_label_4(local_test_frame, "new line", 2);
	local_test_label_4.set_output("This is\nwidget\n4\n");
	local_test_label_4.add_border(true);
	labels.push_back(local_test_label_4);
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border(true);
	local_test_label_5.set_lines_count(3);
	labels.push_back(local_test_label_5);
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6\n\n\n");
	local_test_label_6.add_border(true);
	labels.push_back(local_test_label_6);
	std::string output = local_test_frame->get_frame_output();
	local_test_label_2.scroll_down(3, false);
	local_test_label_4.scroll_down(2, false);
	local_test_label_4.scroll_up(1, false);
	local_test_label_5.scroll_down(1, false);
	output = local_test_frame->get_frame_output();

	run_test(output, labels, correct_answer);

	delete(local_test_frame);
}

TEST_F(label_test, test_scroll_out_of_bounds)
{
	const expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"| This is widget 1.                              || 2                                              |\n"
		"|                                                |.------------------------------------------------.\n"
		"|                                                |                                                  \n"
		"|                                                |                                                  \n"
		".------------------------------------------------.                                                  \n"
		".--------------------------------------------------------------------------------------------------.\n"
		"| This is widget                                                                                   |\n"
		"| 3                                                                                                |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"| This is                       || is                            || This is widget 6              | \n"
		"| widget                        || widget                        ||                               | \n"
		".-------------------------------.| 5                             ||                               | \n"
		"                                 .-------------------------------.|                               | \n"
		"                                                                  .-------------------------------. ",
		{ 2, 52, 2, 2, 35, 68 },
		{ 1, 1, 7, 11, 11, 11 },
		{ 46, 46, 96, 29, 29, 29 },
		{ 4, 1, 2, 2, 3, 4 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 6, 3, 4, 4, 5, 6 }
	};

	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<label> labels;
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.\n\n\n");
	local_test_label_1.add_border(true);
	labels.push_back(local_test_label_1);
	label local_test_label_2(local_test_frame, "none", 1);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border(true);
	labels.push_back(local_test_label_2);
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border(true);
	labels.push_back(local_test_label_3);
	label local_test_label_4(local_test_frame, "new line", 2);
	local_test_label_4.set_output("This is\nwidget\n4\n");
	local_test_label_4.add_border(true);
	labels.push_back(local_test_label_4);
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border(true);
	local_test_label_5.set_lines_count(3);
	labels.push_back(local_test_label_5);
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6\n\n\n");
	local_test_label_6.add_border(true);
	labels.push_back(local_test_label_6);
	std::string output = local_test_frame->get_frame_output();
	local_test_label_2.scroll_down(100, false);
	local_test_label_4.scroll_down(100, false);
	local_test_label_4.scroll_up(100, false);
	local_test_label_5.scroll_down(100, false);
	output = local_test_frame->get_frame_output();

	run_test(output, labels, correct_answer);

	delete(local_test_frame);
}

TEST_F(label_test, embedded_color_test)
{
	const expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"| This is widget 1                               || This is widget 2                               |\n"
		".------------------------------------------------..------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"| This is widget 3              || This is widget 4              || This is widget 5              | \n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"| This is widget 6              || This is widget 7              || This is widget 8              | \n"
		".-------------------------------..-------------------------------..-------------------------------. ",
		{ 2, 52, 2, 35, 68, 2, 35, 68 },
		{ 1, 1, 4, 4, 4, 7, 7, 7 },
		{ 46, 46, 29, 29, 29, 29, 29, 29 },
		{ 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 50, 50, 33, 33, 33, 33, 33, 33 },
		{ 3, 3, 3, 3, 3, 3, 3, 3 }
	};

	// foreground colors
	format_tools::common_format black_foreground;
	black_foreground.foreground_format = format_tools::black;

	format_tools::common_format red_foreground;
	red_foreground.foreground_format = format_tools::red;

	format_tools::common_format green_foreground;
	green_foreground.foreground_format = format_tools::green;

	format_tools::common_format yellow_foreground;
	yellow_foreground.foreground_format = format_tools::yellow;

	format_tools::common_format blue_foreground;
	blue_foreground.foreground_format = format_tools::blue;

	format_tools::common_format magenta_foreground;
	magenta_foreground.foreground_format = format_tools::magenta;

	format_tools::common_format cyan_foreground;
	cyan_foreground.foreground_format = format_tools::cyan;

	format_tools::common_format white_foreground;
	white_foreground.foreground_format = format_tools::white;

	// background colors
	format_tools::common_format black_background;
	black_background.background_format = format_tools::black;

	format_tools::common_format red_background;
	red_background.background_format = format_tools::red;

	format_tools::common_format green_background;
	green_background.background_format = format_tools::green;

	format_tools::common_format yellow_background;
	yellow_background.background_format = format_tools::yellow;

	format_tools::common_format blue_background;
	blue_background.background_format = format_tools::blue;

	format_tools::common_format magenta_background;
	magenta_background.background_format = format_tools::magenta;

	format_tools::common_format cyan_background;
	cyan_background.background_format = format_tools::cyan;

	format_tools::common_format white_background;
	white_background.background_format = format_tools::white;

	// mixed colors
	format_tools::common_format black_foreground_white_background;
	black_foreground_white_background.foreground_format = format_tools::black;
	black_foreground_white_background.background_format = format_tools::white;

	format_tools::common_format red_foreground_cyan_background;
	red_foreground_cyan_background.foreground_format = format_tools::red;
	red_foreground_cyan_background.background_format = format_tools::cyan;

	format_tools::common_format green_foreground_magenta_background;
	green_foreground_magenta_background.foreground_format = format_tools::green;
	green_foreground_magenta_background.background_format = format_tools::magenta;

	format_tools::common_format yellow_foreground_blue_background;
	yellow_foreground_blue_background.foreground_format = format_tools::yellow;
	yellow_foreground_blue_background.background_format = format_tools::blue;

	format_tools::common_format blue_foreground_yellow_background;
	blue_foreground_yellow_background.foreground_format = format_tools::blue;
	blue_foreground_yellow_background.background_format = format_tools::yellow;

	format_tools::common_format magenta_foreground_green_background;
	magenta_foreground_green_background.foreground_format = format_tools::magenta;
	magenta_foreground_green_background.background_format = format_tools::green;

	format_tools::common_format cyan_foreground_red_background;
	cyan_foreground_red_background.foreground_format = format_tools::cyan;
	cyan_foreground_red_background.background_format = format_tools::red;

	format_tools::common_format white_foreground_black_background;
	white_foreground_black_background.foreground_format = format_tools::white;
	white_foreground_black_background.background_format = format_tools::black;

	format_tools::common_format no_format;

	const std::vector<format_tools::index_format> format_1 =
	{
		{0, black_foreground, ' '},
		{5, black_foreground_white_background, ' '},
		{8, white_background, ' '},
		{15, no_format, ' '}
	};

	const std::vector<format_tools::index_format> format_2 =
	{
		{0, cyan_background, ' '},
		{5, red_foreground_cyan_background, ' '},
		{8, red_foreground, ' '},
		{15, no_format, ' '}
	};

	const std::vector<format_tools::index_format> format_3 =
	{
		{0, green_foreground, ' '},
		{5, green_foreground_magenta_background, ' '},
		{8, magenta_background, ' '},
		{15, no_format, ' '}
	};

	const std::vector<format_tools::index_format> format_4 =
	{
		{0, blue_background, ' '},
		{5, yellow_foreground_blue_background, ' '},
		{8, yellow_foreground, ' '},
		{15, no_format, ' '}
	};

	const std::vector<format_tools::index_format> format_5 =
	{
		{0, blue_foreground, ' '},
		{5, blue_foreground_yellow_background, ' '},
		{8, yellow_background, ' '},
		{15, no_format, ' '}
	};

	const std::vector<format_tools::index_format> format_6 =
	{
		{0, green_background, ' '},
		{5, magenta_foreground_green_background, ' '},
		{8, magenta_foreground, ' '},
		{15, no_format, ' '}
	};

	const std::vector<format_tools::index_format> format_7 =
	{
		{0, cyan_foreground, ' '},
		{5, cyan_foreground_red_background, ' '},
		{8, red_background, ' '},
		{15, no_format, ' '}
	};

	const std::vector<format_tools::index_format> format_8 =
	{
		{0, black_background, ' '},
		{5, white_foreground_black_background, ' '},
		{8, white_foreground, ' '},
		{15, no_format, ' '}
	};

	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(9);
	local_test_frame->set_fake_console_width(100);
	std::vector<label> labels;
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("<black_foreground>This <black_foreground><white_background>is <white_background>widget <no_color>1");
	local_test_label_1.add_border(true);
	labels.push_back(local_test_label_1);
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("<cyan_background>This <cyan_background><red_foreground>is <red_foreground>widget <no_color>2");
	local_test_label_2.add_border(true);
	labels.push_back(local_test_label_2);
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("<green_foreground>This <green_foreground><magenta_background>is <magenta_background>widget <no_color>3");
	local_test_label_3.add_border(true);
	labels.push_back(local_test_label_3);
	label local_test_label_4(local_test_frame);
	local_test_label_4.set_output("<blue_background>This <blue_background><yellow_foreground>is <yellow_foreground>widget <no_color>4");
	local_test_label_4.add_border(true);
	labels.push_back(local_test_label_4);
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("<blue_foreground>This <blue_foreground><yellow_background>is <yellow_background>widget <no_color>5");
	local_test_label_5.add_border(true);
	labels.push_back(local_test_label_5);
	label local_test_label_6(local_test_frame, "new line");
	local_test_label_6.set_output("<green_background>This <green_background><magenta_foreground>is <magenta_foreground>widget <no_color>6");
	local_test_label_6.add_border(true);
	labels.push_back(local_test_label_6);
	label local_test_label_7(local_test_frame);
	local_test_label_7.set_output("<cyan_foreground>This <cyan_foreground><red_background>is <red_background>widget <no_color>7");
	local_test_label_7.add_border(true);
	labels.push_back(local_test_label_7);
	label local_test_label_8(local_test_frame);
	local_test_label_8.set_output("<black_background>This <black_background><white_foreground>is <white_foreground>widget <no_color>8");
	local_test_label_8.add_border(true);
	labels.push_back(local_test_label_8);
	std::string output = local_test_frame->get_frame_output();

	run_test(output, labels, correct_answer);

	format_equivalent_test(format_1, local_test_label_1.get_colors(), 0);
	format_equivalent_test(format_2, local_test_label_2.get_colors(), 1);
	format_equivalent_test(format_3, local_test_label_3.get_colors(), 2);
	format_equivalent_test(format_4, local_test_label_4.get_colors(), 3);
	format_equivalent_test(format_5, local_test_label_5.get_colors(), 4);
	format_equivalent_test(format_6, local_test_label_6.get_colors(), 5);
	format_equivalent_test(format_7, local_test_label_7.get_colors(), 6);
	format_equivalent_test(format_8, local_test_label_8.get_colors(), 7);

	delete(local_test_frame);
}