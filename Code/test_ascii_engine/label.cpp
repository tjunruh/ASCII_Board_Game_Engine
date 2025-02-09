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
#include "../ascii_engine/spacer.h"
#elif __linux__
#include <ascii_engine/label.h>
#include <ascii_engine/file_manager.h>
#include <ascii_engine/error_codes.h>
#include <ascii_engine/frame.h>
#include <ascii_engine/format_tools.h>
#include <ascii_engine/spacer.h>
#endif

#include "expected_display_data.h"

#include <string>

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
	label local_test_label_1(local_test_frame, "none", true);
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

TEST_F(label_test, test_spacer)
{
	expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"| This is widget 1.                              || This                                           |\n"
		".------------------------------------------------.| is                                             |\n"
		"                                                  | widget                                         |\n"
		"                                                  | 2                                              |\n"
		"                                                  .------------------------------------------------.\n"
		"                                 .-------------------------------.                                  \n"
		"                                 | This is widget                |                                  \n"
		"                                 | 3                             |                                  \n"
		"                                 .-------------------------------.                                  \n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"| This is                       || This                          || This is widget 6              | \n"
		"| widget                        || is                            |.-------------------------------. \n"
		"| 4                             || widget                        |                                  \n"
		".-------------------------------.| 5                             |                                  \n"
		"                                 .-------------------------------.                                  ",
		{ 2, 52, 35, 2, 35, 68 },
		{ 1, 1, 7, 11, 11, 11 },
		{ 46, 46, 29, 29, 29, 29 },
		{ 1, 4, 2, 3, 4, 1 },
		{ 50, 50, 33, 33, 33, 33 },
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
	spacer local_test_spacer_1(local_test_frame, "new line");
	label local_test_label_3(local_test_frame);
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border(true);
	labels.push_back(local_test_label_3);
	spacer local_test_spacer_2(local_test_frame);
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