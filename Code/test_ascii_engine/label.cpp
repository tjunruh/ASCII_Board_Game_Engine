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

#include <string>

class label_test : public testing::Test
{
protected:
	const std::string frame_output_1 =
		"This is widget 1.                                 This                                              \n"
		"                                                  is                                                \n"
		"                                                  widget                                            \n"
		"                                                  2                                                 \n"
		"This is widget                                                                                      \n"
		"3                                                                                                   \n"
		"This is                          This                             This is widget 6                  \n"
		"widget                           is                                                                 \n"
		"4                                widget                                                             \n"
		"                                 5                                                                  ";
	const std::vector<int> frame_output_1_x_origins = {0, 50, 0, 0, 33, 66};
	const std::vector<int> frame_output_1_y_origins = { 0, 0, 4, 6, 6, 6 };
	const std::vector<unsigned int> frame_output_1_widths = { 50, 50, 100, 33, 33, 33 };
	const std::vector<unsigned int> frame_output_1_heights = { 1, 4, 2, 3, 4, 1 };

	const std::string frame_output_2 =
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
		"                                 .-------------------------------.                                  ";
	const std::vector<int> frame_output_2_x_origins = { 2, 52, 2, 2, 35, 68 };
	const std::vector<int> frame_output_2_y_origins = { 1, 1, 7, 11, 11, 11 };
	const std::vector<unsigned int> frame_output_2_widths = { 46, 46, 96, 29, 29, 29 };
	const std::vector<unsigned int> frame_output_2_heights = { 1, 4, 2, 3, 4, 1 };
	const std::vector<unsigned int> frame_output_2_widths_with_spacing = { 50, 50, 100, 33, 33, 33 };
	const std::vector<unsigned int> frame_output_2_heights_with_spacing = { 3, 6, 4, 5, 6, 3 };

	const std::string frame_output_3 =
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
		".-------------------------------..-------------------------------..-------------------------------. ";
	const std::vector<int> frame_output_3_x_origins = { 2, 52, 2, 2, 35, 68 };
	const std::vector<int> frame_output_3_y_origins = { 1, 1, 7, 11, 11, 11 };
	const std::vector<unsigned int> frame_output_3_widths = { 46, 46, 96, 29, 29, 29 };
	const std::vector<unsigned int> frame_output_3_heights = { 4, 4, 2, 4, 4, 4 };
	const std::vector<unsigned int> frame_output_3_widths_with_spacing = { 50, 50, 100, 33, 33, 33 };
	const std::vector<unsigned int> frame_output_3_heights_with_spacing = { 6, 6, 4, 6, 6, 6 };

	const std::string frame_output_4 =
		"This is widget 1.                                 This                                              \n"
		"This is widget 2.                                 is                                                \n"
		"                                                  widget                                            \n"
		"                                                  3                                                 \n"
		"This is widget                                                                                      \n"
		"4                                                                                                   \n"
		"This is                          This                             This is widget 7                  \n"
		"widget                           is                               This is widget 8                  \n"
		"5                                widget                                                             \n"
		"                                 6                                                                  ";
	const std::vector<int> frame_output_4_x_origins = { 0, 0, 50, 0, 0, 33, 66, 66 };
	const std::vector<int> frame_output_4_y_origins = { 0, 1, 0, 4, 6, 6, 6, 7 };
	const std::vector<unsigned int> frame_output_4_widths = { 50, 50, 50, 100, 33, 33, 33, 33 };
	const std::vector<unsigned int> frame_output_4_heights = { 1, 1, 4, 2, 3, 4, 1, 1 };

	const std::string frame_output_5 =
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
		"                                 .-------------------------------..-------------------------------. ";
	const std::vector<int> frame_output_5_x_origins = { 2, 2, 52, 2, 2, 35, 68, 68 };
	const std::vector<int> frame_output_5_y_origins = { 1, 4, 1, 7, 11, 11, 11, 14 };
	const std::vector<unsigned int> frame_output_5_widths = { 46, 46, 46, 96, 29, 29, 29, 29 };
	const std::vector<unsigned int> frame_output_5_heights = { 1, 1, 4, 2, 3, 4, 1, 1 };
	const std::vector<unsigned int> frame_output_5_widths_with_spacing = { 50, 50, 50, 100, 33, 33, 33, 33 };
	const std::vector<unsigned int> frame_output_5_heights_with_spacing = { 3, 3, 6, 4, 5, 6, 3, 3 };

	const std::string frame_output_6 =
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
		"                                 .-------------------------------.                                  ";
	const std::vector<int> frame_output_6_x_origins = { 2, 52, 35, 2, 35, 68 };
	const std::vector<int> frame_output_6_y_origins = { 1, 1, 7, 11, 11, 11 };
	const std::vector<unsigned int> frame_output_6_widths = { 46, 46, 29, 29, 29, 29 };
	const std::vector<unsigned int> frame_output_6_heights = { 1, 4, 2, 3, 4, 1 };
	const std::vector<unsigned int> frame_output_6_widths_with_spacing = { 50, 50, 33, 33, 33, 33 };
	const std::vector<unsigned int> frame_output_6_heights_with_spacing = { 3, 6, 4, 5, 6, 3 };

	const std::string frame_output_7 =
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
		"                                                                                                    ";
	const std::vector<int> frame_output_7_x_origins = { 2, 52, 7, 2, 35, 69 };
	const std::vector<int> frame_output_7_y_origins = { 2, 1, 8, 15, 14, 14 };
	const std::vector<unsigned int> frame_output_7_widths = { 45, 45, 86, 29, 29, 27 };
	const std::vector<unsigned int> frame_output_7_heights = { 1, 4, 2, 3, 4, 1 };
	const std::vector<unsigned int> frame_output_7_widths_with_spacing = { 50, 50, 100, 33, 33, 33 };
	const std::vector<unsigned int> frame_output_7_heights_with_spacing = { 5, 6, 7, 7, 6, 3 };

	const std::string frame_output_8 =
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
		".-------------------------------..-------------------------------..-------------------------------. ";
	const std::vector<int> frame_output_8_x_origins = { 2, 52, 2, 2, 35, 68 };
	const std::vector<int> frame_output_8_y_origins = { 1, 1, 7, 11, 11, 11 };
	const std::vector<unsigned int> frame_output_8_widths = { 46, 46, 96, 29, 29, 29 };
	const std::vector<unsigned int> frame_output_8_heights = { 4, 4, 2, 4, 4, 4 };
	const std::vector<unsigned int> frame_output_8_widths_with_spacing = { 50, 50, 100, 33, 33, 33 };
	const std::vector<unsigned int> frame_output_8_heights_with_spacing = { 6, 6, 4, 6, 6, 6 };

	const std::string frame_output_9 =
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
		".-------------------------------..-------------------------------..-------------------------------. ";
	const std::vector<int> frame_output_9_x_origins = { 2, 52, 2, 2, 35, 68 };
	const std::vector<int> frame_output_9_y_origins = { 1, 1, 7, 11, 11, 11 };
	const std::vector<unsigned int> frame_output_9_widths = { 46, 46, 96, 29, 29, 29 };
	const std::vector<unsigned int> frame_output_9_heights = { 4, 4, 2, 4, 4, 4 };
	const std::vector<unsigned int> frame_output_9_widths_with_spacing = { 50, 50, 100, 33, 33, 33 };
	const std::vector<unsigned int> frame_output_9_heights_with_spacing = { 6, 6, 4, 6, 6, 6 };

	const std::string frame_output_10 =
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
		".-------------------------------..-------------------------------..-------------------------------. ";
	const std::vector<int> frame_output_10_x_origins = { 2, 52, 2, 2, 35, 68 };
	const std::vector<int> frame_output_10_y_origins = { 1, 1, 7, 11, 11, 11 };
	const std::vector<unsigned int> frame_output_10_widths = { 46, 46, 96, 29, 29, 29 };
	const std::vector<unsigned int> frame_output_10_heights = { 4, 4, 2, 4, 4, 4 };
	const std::vector<unsigned int> frame_output_10_widths_with_spacing = { 50, 50, 100, 33, 33, 33 };
	const std::vector<unsigned int> frame_output_10_heights_with_spacing = { 6, 6, 4, 6, 6, 6 };

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

TEST_F(label_test, test_basic)
{
	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(10);
	local_test_frame->set_fake_console_width(100);
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.");
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4");
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6");
	std::string output = local_test_frame->get_frame_output();
	EXPECT_EQ(output, frame_output_1) << "Frame output:\n" + output;

	// test origins
	EXPECT_EQ(local_test_label_1.get_x_origin(), frame_output_1_x_origins[0]);
	EXPECT_EQ(local_test_label_1.get_y_origin(), frame_output_1_y_origins[0]);

	EXPECT_EQ(local_test_label_2.get_x_origin(), frame_output_1_x_origins[1]);
	EXPECT_EQ(local_test_label_2.get_y_origin(), frame_output_1_y_origins[1]);

	EXPECT_EQ(local_test_label_3.get_x_origin(), frame_output_1_x_origins[2]);
	EXPECT_EQ(local_test_label_3.get_y_origin(), frame_output_1_y_origins[2]);

	EXPECT_EQ(local_test_label_4.get_x_origin(), frame_output_1_x_origins[3]);
	EXPECT_EQ(local_test_label_4.get_y_origin(), frame_output_1_y_origins[3]);

	EXPECT_EQ(local_test_label_5.get_x_origin(), frame_output_1_x_origins[4]);
	EXPECT_EQ(local_test_label_5.get_y_origin(), frame_output_1_y_origins[4]);

	EXPECT_EQ(local_test_label_6.get_x_origin(), frame_output_1_x_origins[5]);
	EXPECT_EQ(local_test_label_6.get_y_origin(), frame_output_1_y_origins[5]);

	// test width and height
	EXPECT_EQ(local_test_label_1.get_width(), frame_output_1_widths[0]);
	EXPECT_EQ(local_test_label_1.get_height(), frame_output_1_heights[0]);

	EXPECT_EQ(local_test_label_2.get_width(), frame_output_1_widths[1]);
	EXPECT_EQ(local_test_label_2.get_height(), frame_output_1_heights[1]);

	EXPECT_EQ(local_test_label_3.get_width(), frame_output_1_widths[2]);
	EXPECT_EQ(local_test_label_3.get_height(), frame_output_1_heights[2]);

	EXPECT_EQ(local_test_label_4.get_width(), frame_output_1_widths[3]);
	EXPECT_EQ(local_test_label_4.get_height(), frame_output_1_heights[3]);

	EXPECT_EQ(local_test_label_5.get_width(), frame_output_1_widths[4]);
	EXPECT_EQ(local_test_label_5.get_height(), frame_output_1_heights[4]);

	EXPECT_EQ(local_test_label_6.get_width(), frame_output_1_widths[5]);
	EXPECT_EQ(local_test_label_6.get_height(), frame_output_1_heights[5]);

	delete(local_test_frame);
}

TEST_F(label_test, test_border)
{
	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.");
	local_test_label_1.add_border();
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border();
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border();
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4");
	local_test_label_4.add_border();
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border();
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6");
	local_test_label_6.add_border();
	std::string output = local_test_frame->get_frame_output();
	EXPECT_EQ(output, frame_output_2) << "Frame output:\n" + output;

	// test origins
	EXPECT_EQ(local_test_label_1.get_x_origin(), frame_output_2_x_origins[0]);
	EXPECT_EQ(local_test_label_1.get_y_origin(), frame_output_2_y_origins[0]);

	EXPECT_EQ(local_test_label_2.get_x_origin(), frame_output_2_x_origins[1]);
	EXPECT_EQ(local_test_label_2.get_y_origin(), frame_output_2_y_origins[1]);

	EXPECT_EQ(local_test_label_3.get_x_origin(), frame_output_2_x_origins[2]);
	EXPECT_EQ(local_test_label_3.get_y_origin(), frame_output_2_y_origins[2]);

	EXPECT_EQ(local_test_label_4.get_x_origin(), frame_output_2_x_origins[3]);
	EXPECT_EQ(local_test_label_4.get_y_origin(), frame_output_2_y_origins[3]);

	EXPECT_EQ(local_test_label_5.get_x_origin(), frame_output_2_x_origins[4]);
	EXPECT_EQ(local_test_label_5.get_y_origin(), frame_output_2_y_origins[4]);

	EXPECT_EQ(local_test_label_6.get_x_origin(), frame_output_2_x_origins[5]);
	EXPECT_EQ(local_test_label_6.get_y_origin(), frame_output_2_y_origins[5]);

	// test width and height without spacing
	EXPECT_EQ(local_test_label_1.get_width(), frame_output_2_widths[0]);
	EXPECT_EQ(local_test_label_1.get_height(), frame_output_2_heights[0]);

	EXPECT_EQ(local_test_label_2.get_width(), frame_output_2_widths[1]);
	EXPECT_EQ(local_test_label_2.get_height(), frame_output_2_heights[1]);

	EXPECT_EQ(local_test_label_3.get_width(), frame_output_2_widths[2]);
	EXPECT_EQ(local_test_label_3.get_height(), frame_output_2_heights[2]);

	EXPECT_EQ(local_test_label_4.get_width(), frame_output_2_widths[3]);
	EXPECT_EQ(local_test_label_4.get_height(), frame_output_2_heights[3]);

	EXPECT_EQ(local_test_label_5.get_width(), frame_output_2_widths[4]);
	EXPECT_EQ(local_test_label_5.get_height(), frame_output_2_heights[4]);

	EXPECT_EQ(local_test_label_6.get_width(), frame_output_2_widths[5]);
	EXPECT_EQ(local_test_label_6.get_height(), frame_output_2_heights[5]);

	// test width and height with spacing
	EXPECT_EQ(local_test_label_1.get_width(true), frame_output_2_widths_with_spacing[0]);
	EXPECT_EQ(local_test_label_1.get_height(true), frame_output_2_heights_with_spacing[0]);

	EXPECT_EQ(local_test_label_2.get_width(true), frame_output_2_widths_with_spacing[1]);
	EXPECT_EQ(local_test_label_2.get_height(true), frame_output_2_heights_with_spacing[1]);

	EXPECT_EQ(local_test_label_3.get_width(true), frame_output_2_widths_with_spacing[2]);
	EXPECT_EQ(local_test_label_3.get_height(true), frame_output_2_heights_with_spacing[2]);

	EXPECT_EQ(local_test_label_4.get_width(true), frame_output_2_widths_with_spacing[3]);
	EXPECT_EQ(local_test_label_4.get_height(true), frame_output_2_heights_with_spacing[3]);

	EXPECT_EQ(local_test_label_5.get_width(true), frame_output_2_widths_with_spacing[4]);
	EXPECT_EQ(local_test_label_5.get_height(true), frame_output_2_heights_with_spacing[4]);

	EXPECT_EQ(local_test_label_6.get_width(true), frame_output_2_widths_with_spacing[5]);
	EXPECT_EQ(local_test_label_6.get_height(true), frame_output_2_heights_with_spacing[5]);

	delete(local_test_frame);
}

TEST_F(label_test, test_newline)
{
	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.\n\n\n");
	local_test_label_1.add_border();
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border();
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border();
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4\n");
	local_test_label_4.add_border();
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border();
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6\n\n\n");
	local_test_label_6.add_border();
	std::string output = local_test_frame->get_frame_output();
	EXPECT_EQ(output, frame_output_3) << "Frame output:\n" + output;

	// test origins
	EXPECT_EQ(local_test_label_1.get_x_origin(), frame_output_3_x_origins[0]);
	EXPECT_EQ(local_test_label_1.get_y_origin(), frame_output_3_y_origins[0]);

	EXPECT_EQ(local_test_label_2.get_x_origin(), frame_output_3_x_origins[1]);
	EXPECT_EQ(local_test_label_2.get_y_origin(), frame_output_3_y_origins[1]);

	EXPECT_EQ(local_test_label_3.get_x_origin(), frame_output_3_x_origins[2]);
	EXPECT_EQ(local_test_label_3.get_y_origin(), frame_output_3_y_origins[2]);

	EXPECT_EQ(local_test_label_4.get_x_origin(), frame_output_3_x_origins[3]);
	EXPECT_EQ(local_test_label_4.get_y_origin(), frame_output_3_y_origins[3]);

	EXPECT_EQ(local_test_label_5.get_x_origin(), frame_output_3_x_origins[4]);
	EXPECT_EQ(local_test_label_5.get_y_origin(), frame_output_3_y_origins[4]);

	EXPECT_EQ(local_test_label_6.get_x_origin(), frame_output_3_x_origins[5]);
	EXPECT_EQ(local_test_label_6.get_y_origin(), frame_output_3_y_origins[5]);

	// test width and height without spacing
	EXPECT_EQ(local_test_label_1.get_width(), frame_output_3_widths[0]);
	EXPECT_EQ(local_test_label_1.get_height(), frame_output_3_heights[0]);

	EXPECT_EQ(local_test_label_2.get_width(), frame_output_3_widths[1]);
	EXPECT_EQ(local_test_label_2.get_height(), frame_output_3_heights[1]);

	EXPECT_EQ(local_test_label_3.get_width(), frame_output_3_widths[2]);
	EXPECT_EQ(local_test_label_3.get_height(), frame_output_3_heights[2]);

	EXPECT_EQ(local_test_label_4.get_width(), frame_output_3_widths[3]);
	EXPECT_EQ(local_test_label_4.get_height(), frame_output_3_heights[3]);

	EXPECT_EQ(local_test_label_5.get_width(), frame_output_3_widths[4]);
	EXPECT_EQ(local_test_label_5.get_height(), frame_output_3_heights[4]);

	EXPECT_EQ(local_test_label_6.get_width(), frame_output_3_widths[5]);
	EXPECT_EQ(local_test_label_6.get_height(), frame_output_3_heights[5]);

	// test width and height with spacing
	EXPECT_EQ(local_test_label_1.get_width(true), frame_output_3_widths_with_spacing[0]);
	EXPECT_EQ(local_test_label_1.get_height(true), frame_output_3_heights_with_spacing[0]);

	EXPECT_EQ(local_test_label_2.get_width(true), frame_output_3_widths_with_spacing[1]);
	EXPECT_EQ(local_test_label_2.get_height(true), frame_output_3_heights_with_spacing[1]);

	EXPECT_EQ(local_test_label_3.get_width(true), frame_output_3_widths_with_spacing[2]);
	EXPECT_EQ(local_test_label_3.get_height(true), frame_output_3_heights_with_spacing[2]);

	EXPECT_EQ(local_test_label_4.get_width(true), frame_output_3_widths_with_spacing[3]);
	EXPECT_EQ(local_test_label_4.get_height(true), frame_output_3_heights_with_spacing[3]);

	EXPECT_EQ(local_test_label_5.get_width(true), frame_output_3_widths_with_spacing[4]);
	EXPECT_EQ(local_test_label_5.get_height(true), frame_output_3_heights_with_spacing[4]);

	EXPECT_EQ(local_test_label_6.get_width(true), frame_output_3_widths_with_spacing[5]);
	EXPECT_EQ(local_test_label_6.get_height(true), frame_output_3_heights_with_spacing[5]);
	delete(local_test_frame);
}

TEST_F(label_test, test_merge)
{
	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(10);
	local_test_frame->set_fake_console_width(100);
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.");
	label local_test_label_2(local_test_frame, "merge");
	local_test_label_2.set_output("This is widget 2.");
	label local_test_label_3(local_test_frame);
	local_test_label_3.set_output("This\nis\nwidget\n3");
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is widget\n4");
	label local_test_label_5(local_test_frame, "new line");
	local_test_label_5.set_output("This is\nwidget\n5");
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This\nis\nwidget\n6");
	label local_test_label_7(local_test_frame);
	local_test_label_7.set_output("This is widget 7");
	label local_test_label_8(local_test_frame, "merge");
	local_test_label_8.set_output("This is widget 8");
	std::string output = local_test_frame->get_frame_output();
	EXPECT_EQ(output, frame_output_4) << "Frame output:\n" + output;

	// test origins
	EXPECT_EQ(local_test_label_1.get_x_origin(), frame_output_4_x_origins[0]);
	EXPECT_EQ(local_test_label_1.get_y_origin(), frame_output_4_y_origins[0]);

	EXPECT_EQ(local_test_label_2.get_x_origin(), frame_output_4_x_origins[1]);
	EXPECT_EQ(local_test_label_2.get_y_origin(), frame_output_4_y_origins[1]);

	EXPECT_EQ(local_test_label_3.get_x_origin(), frame_output_4_x_origins[2]);
	EXPECT_EQ(local_test_label_3.get_y_origin(), frame_output_4_y_origins[2]);

	EXPECT_EQ(local_test_label_4.get_x_origin(), frame_output_4_x_origins[3]);
	EXPECT_EQ(local_test_label_4.get_y_origin(), frame_output_4_y_origins[3]);

	EXPECT_EQ(local_test_label_5.get_x_origin(), frame_output_4_x_origins[4]);
	EXPECT_EQ(local_test_label_5.get_y_origin(), frame_output_4_y_origins[4]);

	EXPECT_EQ(local_test_label_6.get_x_origin(), frame_output_4_x_origins[5]);
	EXPECT_EQ(local_test_label_6.get_y_origin(), frame_output_4_y_origins[5]);

	EXPECT_EQ(local_test_label_7.get_x_origin(), frame_output_4_x_origins[6]);
	EXPECT_EQ(local_test_label_7.get_y_origin(), frame_output_4_y_origins[6]);

	EXPECT_EQ(local_test_label_8.get_x_origin(), frame_output_4_x_origins[7]);
	EXPECT_EQ(local_test_label_8.get_y_origin(), frame_output_4_y_origins[7]);

	// test width and height without spacing
	EXPECT_EQ(local_test_label_1.get_width(), frame_output_4_widths[0]);
	EXPECT_EQ(local_test_label_1.get_height(), frame_output_4_heights[0]);

	EXPECT_EQ(local_test_label_2.get_width(), frame_output_4_widths[1]);
	EXPECT_EQ(local_test_label_2.get_height(), frame_output_4_heights[1]);

	EXPECT_EQ(local_test_label_3.get_width(), frame_output_4_widths[2]);
	EXPECT_EQ(local_test_label_3.get_height(), frame_output_4_heights[2]);

	EXPECT_EQ(local_test_label_4.get_width(), frame_output_4_widths[3]);
	EXPECT_EQ(local_test_label_4.get_height(), frame_output_4_heights[3]);

	EXPECT_EQ(local_test_label_5.get_width(), frame_output_4_widths[4]);
	EXPECT_EQ(local_test_label_5.get_height(), frame_output_4_heights[4]);

	EXPECT_EQ(local_test_label_6.get_width(), frame_output_4_widths[5]);
	EXPECT_EQ(local_test_label_6.get_height(), frame_output_4_heights[5]);

	local_test_frame->set_fake_console_height(16);
	local_test_label_1.add_border();
	local_test_label_2.add_border();
	local_test_label_3.add_border();
	local_test_label_4.add_border();
	local_test_label_5.add_border();
	local_test_label_6.add_border();
	local_test_label_7.add_border();
	local_test_label_8.add_border();
	output = local_test_frame->get_frame_output();
	EXPECT_EQ(output, frame_output_5) << "Frame output:\n" + output;

	// test origins
	EXPECT_EQ(local_test_label_1.get_x_origin(), frame_output_5_x_origins[0]);
	EXPECT_EQ(local_test_label_1.get_y_origin(), frame_output_5_y_origins[0]);

	EXPECT_EQ(local_test_label_2.get_x_origin(), frame_output_5_x_origins[1]);
	EXPECT_EQ(local_test_label_2.get_y_origin(), frame_output_5_y_origins[1]);

	EXPECT_EQ(local_test_label_3.get_x_origin(), frame_output_5_x_origins[2]);
	EXPECT_EQ(local_test_label_3.get_y_origin(), frame_output_5_y_origins[2]);

	EXPECT_EQ(local_test_label_4.get_x_origin(), frame_output_5_x_origins[3]);
	EXPECT_EQ(local_test_label_4.get_y_origin(), frame_output_5_y_origins[3]);

	EXPECT_EQ(local_test_label_5.get_x_origin(), frame_output_5_x_origins[4]);
	EXPECT_EQ(local_test_label_5.get_y_origin(), frame_output_5_y_origins[4]);

	EXPECT_EQ(local_test_label_6.get_x_origin(), frame_output_5_x_origins[5]);
	EXPECT_EQ(local_test_label_6.get_y_origin(), frame_output_5_y_origins[5]);

	EXPECT_EQ(local_test_label_7.get_x_origin(), frame_output_5_x_origins[6]);
	EXPECT_EQ(local_test_label_7.get_y_origin(), frame_output_5_y_origins[6]);

	EXPECT_EQ(local_test_label_8.get_x_origin(), frame_output_5_x_origins[7]);
	EXPECT_EQ(local_test_label_8.get_y_origin(), frame_output_5_y_origins[7]);

	// test width and height without spacing
	EXPECT_EQ(local_test_label_1.get_width(), frame_output_5_widths[0]);
	EXPECT_EQ(local_test_label_1.get_height(), frame_output_5_heights[0]);

	EXPECT_EQ(local_test_label_2.get_width(), frame_output_5_widths[1]);
	EXPECT_EQ(local_test_label_2.get_height(), frame_output_5_heights[1]);

	EXPECT_EQ(local_test_label_3.get_width(), frame_output_5_widths[2]);
	EXPECT_EQ(local_test_label_3.get_height(), frame_output_5_heights[2]);

	EXPECT_EQ(local_test_label_4.get_width(), frame_output_5_widths[3]);
	EXPECT_EQ(local_test_label_4.get_height(), frame_output_5_heights[3]);

	EXPECT_EQ(local_test_label_5.get_width(), frame_output_5_widths[4]);
	EXPECT_EQ(local_test_label_5.get_height(), frame_output_5_heights[4]);

	EXPECT_EQ(local_test_label_6.get_width(), frame_output_5_widths[5]);
	EXPECT_EQ(local_test_label_6.get_height(), frame_output_5_heights[5]);

	// test width and height with spacing
	EXPECT_EQ(local_test_label_1.get_width(true), frame_output_5_widths_with_spacing[0]);
	EXPECT_EQ(local_test_label_1.get_height(true), frame_output_5_heights_with_spacing[0]);

	EXPECT_EQ(local_test_label_2.get_width(true), frame_output_5_widths_with_spacing[1]);
	EXPECT_EQ(local_test_label_2.get_height(true), frame_output_5_heights_with_spacing[1]);

	EXPECT_EQ(local_test_label_3.get_width(true), frame_output_5_widths_with_spacing[2]);
	EXPECT_EQ(local_test_label_3.get_height(true), frame_output_5_heights_with_spacing[2]);

	EXPECT_EQ(local_test_label_4.get_width(true), frame_output_5_widths_with_spacing[3]);
	EXPECT_EQ(local_test_label_4.get_height(true), frame_output_5_heights_with_spacing[3]);

	EXPECT_EQ(local_test_label_5.get_width(true), frame_output_5_widths_with_spacing[4]);
	EXPECT_EQ(local_test_label_5.get_height(true), frame_output_5_heights_with_spacing[4]);

	EXPECT_EQ(local_test_label_6.get_width(true), frame_output_5_widths_with_spacing[5]);
	EXPECT_EQ(local_test_label_6.get_height(true), frame_output_5_heights_with_spacing[5]);
	delete(local_test_frame);
}

TEST_F(label_test, test_spacer)
{
	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.");
	local_test_label_1.add_border();
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border();
	spacer local_test_spacer_1(local_test_frame, 1, "new line");
	label local_test_label_3(local_test_frame);
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border();
	spacer local_test_spacer_2(local_test_frame, 1);
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4");
	local_test_label_4.add_border();
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border();
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6");
	local_test_label_6.add_border();
	std::string output = local_test_frame->get_frame_output();
	EXPECT_EQ(output, frame_output_6) << "Frame output:\n" + output;
	
	// test origins
	EXPECT_EQ(local_test_label_1.get_x_origin(), frame_output_6_x_origins[0]);
	EXPECT_EQ(local_test_label_1.get_y_origin(), frame_output_6_y_origins[0]);

	EXPECT_EQ(local_test_label_2.get_x_origin(), frame_output_6_x_origins[1]);
	EXPECT_EQ(local_test_label_2.get_y_origin(), frame_output_6_y_origins[1]);

	EXPECT_EQ(local_test_label_3.get_x_origin(), frame_output_6_x_origins[2]);
	EXPECT_EQ(local_test_label_3.get_y_origin(), frame_output_6_y_origins[2]);

	EXPECT_EQ(local_test_label_4.get_x_origin(), frame_output_6_x_origins[3]);
	EXPECT_EQ(local_test_label_4.get_y_origin(), frame_output_6_y_origins[3]);

	EXPECT_EQ(local_test_label_5.get_x_origin(), frame_output_6_x_origins[4]);
	EXPECT_EQ(local_test_label_5.get_y_origin(), frame_output_6_y_origins[4]);

	EXPECT_EQ(local_test_label_6.get_x_origin(), frame_output_6_x_origins[5]);
	EXPECT_EQ(local_test_label_6.get_y_origin(), frame_output_6_y_origins[5]);

	// test width and height without spacing
	EXPECT_EQ(local_test_label_1.get_width(), frame_output_6_widths[0]);
	EXPECT_EQ(local_test_label_1.get_height(), frame_output_6_heights[0]);

	EXPECT_EQ(local_test_label_2.get_width(), frame_output_6_widths[1]);
	EXPECT_EQ(local_test_label_2.get_height(), frame_output_6_heights[1]);

	EXPECT_EQ(local_test_label_3.get_width(), frame_output_6_widths[2]);
	EXPECT_EQ(local_test_label_3.get_height(), frame_output_6_heights[2]);

	EXPECT_EQ(local_test_label_4.get_width(), frame_output_6_widths[3]);
	EXPECT_EQ(local_test_label_4.get_height(), frame_output_6_heights[3]);

	EXPECT_EQ(local_test_label_5.get_width(), frame_output_6_widths[4]);
	EXPECT_EQ(local_test_label_5.get_height(), frame_output_6_heights[4]);

	EXPECT_EQ(local_test_label_6.get_width(), frame_output_6_widths[5]);
	EXPECT_EQ(local_test_label_6.get_height(), frame_output_6_heights[5]);

	// test width and height with spacing
	EXPECT_EQ(local_test_label_1.get_width(true), frame_output_6_widths_with_spacing[0]);
	EXPECT_EQ(local_test_label_1.get_height(true), frame_output_6_heights_with_spacing[0]);

	EXPECT_EQ(local_test_label_2.get_width(true), frame_output_6_widths_with_spacing[1]);
	EXPECT_EQ(local_test_label_2.get_height(true), frame_output_6_heights_with_spacing[1]);

	EXPECT_EQ(local_test_label_3.get_width(true), frame_output_6_widths_with_spacing[2]);
	EXPECT_EQ(local_test_label_3.get_height(true), frame_output_6_heights_with_spacing[2]);

	EXPECT_EQ(local_test_label_4.get_width(true), frame_output_6_widths_with_spacing[3]);
	EXPECT_EQ(local_test_label_4.get_height(true), frame_output_6_heights_with_spacing[3]);

	EXPECT_EQ(local_test_label_5.get_width(true), frame_output_6_widths_with_spacing[4]);
	EXPECT_EQ(local_test_label_5.get_height(true), frame_output_6_heights_with_spacing[4]);

	EXPECT_EQ(local_test_label_6.get_width(true), frame_output_6_widths_with_spacing[5]);
	EXPECT_EQ(local_test_label_6.get_height(true), frame_output_6_heights_with_spacing[5]);
	delete(local_test_frame);
}

TEST_F(label_test, test_spacing)
{
	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.");
	local_test_label_1.add_border();
	local_test_label_1.set_spacing(1, 1, 0, 1);
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border();
	local_test_label_2.set_spacing(0, 0, 0, 1);
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border();
	local_test_label_3.set_spacing(1, 2, 5, 5);
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4");
	local_test_label_4.add_border();
	local_test_label_4.set_spacing(1, 1, 0, 0);
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border();
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6");
	local_test_label_6.add_border();
	local_test_label_6.set_spacing(0, 0, 1, 1);
	std::string output = local_test_frame->get_frame_output();
	EXPECT_EQ(output, frame_output_7) << "Frame output:\n" + output;

	// test origins
	EXPECT_EQ(local_test_label_1.get_x_origin(), frame_output_7_x_origins[0]);
	EXPECT_EQ(local_test_label_1.get_y_origin(), frame_output_7_y_origins[0]);

	EXPECT_EQ(local_test_label_2.get_x_origin(), frame_output_7_x_origins[1]);
	EXPECT_EQ(local_test_label_2.get_y_origin(), frame_output_7_y_origins[1]);

	EXPECT_EQ(local_test_label_3.get_x_origin(), frame_output_7_x_origins[2]);
	EXPECT_EQ(local_test_label_3.get_y_origin(), frame_output_7_y_origins[2]);

	EXPECT_EQ(local_test_label_4.get_x_origin(), frame_output_7_x_origins[3]);
	EXPECT_EQ(local_test_label_4.get_y_origin(), frame_output_7_y_origins[3]);

	EXPECT_EQ(local_test_label_5.get_x_origin(), frame_output_7_x_origins[4]);
	EXPECT_EQ(local_test_label_5.get_y_origin(), frame_output_7_y_origins[4]);

	EXPECT_EQ(local_test_label_6.get_x_origin(), frame_output_7_x_origins[5]);
	EXPECT_EQ(local_test_label_6.get_y_origin(), frame_output_7_y_origins[5]);

	// test width and height without spacing
	EXPECT_EQ(local_test_label_1.get_width(), frame_output_7_widths[0]);
	EXPECT_EQ(local_test_label_1.get_height(), frame_output_7_heights[0]);

	EXPECT_EQ(local_test_label_2.get_width(), frame_output_7_widths[1]);
	EXPECT_EQ(local_test_label_2.get_height(), frame_output_7_heights[1]);

	EXPECT_EQ(local_test_label_3.get_width(), frame_output_7_widths[2]);
	EXPECT_EQ(local_test_label_3.get_height(), frame_output_7_heights[2]);

	EXPECT_EQ(local_test_label_4.get_width(), frame_output_7_widths[3]);
	EXPECT_EQ(local_test_label_4.get_height(), frame_output_7_heights[3]);

	EXPECT_EQ(local_test_label_5.get_width(), frame_output_7_widths[4]);
	EXPECT_EQ(local_test_label_5.get_height(), frame_output_7_heights[4]);

	EXPECT_EQ(local_test_label_6.get_width(), frame_output_7_widths[5]);
	EXPECT_EQ(local_test_label_6.get_height(), frame_output_7_heights[5]);

	// test width and height with spacing
	EXPECT_EQ(local_test_label_1.get_width(true), frame_output_7_widths_with_spacing[0]);
	EXPECT_EQ(local_test_label_1.get_height(true), frame_output_7_heights_with_spacing[0]);

	EXPECT_EQ(local_test_label_2.get_width(true), frame_output_7_widths_with_spacing[1]);
	EXPECT_EQ(local_test_label_2.get_height(true), frame_output_7_heights_with_spacing[1]);

	EXPECT_EQ(local_test_label_3.get_width(true), frame_output_7_widths_with_spacing[2]);
	EXPECT_EQ(local_test_label_3.get_height(true), frame_output_7_heights_with_spacing[2]);

	EXPECT_EQ(local_test_label_4.get_width(true), frame_output_7_widths_with_spacing[3]);
	EXPECT_EQ(local_test_label_4.get_height(true), frame_output_7_heights_with_spacing[3]);

	EXPECT_EQ(local_test_label_5.get_width(true), frame_output_7_widths_with_spacing[4]);
	EXPECT_EQ(local_test_label_5.get_height(true), frame_output_7_heights_with_spacing[4]);

	EXPECT_EQ(local_test_label_6.get_width(true), frame_output_7_widths_with_spacing[5]);
	EXPECT_EQ(local_test_label_6.get_height(true), frame_output_7_heights_with_spacing[5]);
	delete(local_test_frame);
}

TEST_F(label_test, right_alignment)
{
	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.\n\n\n");
	local_test_label_1.add_border();
	local_test_label_1.set_alignment("right");
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border();
	local_test_label_2.set_alignment("right");
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border();
	local_test_label_3.set_alignment("right");
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4\n");
	local_test_label_4.add_border();
	local_test_label_4.set_alignment("right");
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border();
	local_test_label_5.set_alignment("right");
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6\n\n\n");
	local_test_label_6.add_border();
	local_test_label_6.set_alignment("right");
	std::string output = local_test_frame->get_frame_output();
	EXPECT_EQ(output, frame_output_8) << "Frame output:\n" + output;

	// test origins
	EXPECT_EQ(local_test_label_1.get_x_origin(), frame_output_8_x_origins[0]);
	EXPECT_EQ(local_test_label_1.get_y_origin(), frame_output_8_y_origins[0]);

	EXPECT_EQ(local_test_label_2.get_x_origin(), frame_output_8_x_origins[1]);
	EXPECT_EQ(local_test_label_2.get_y_origin(), frame_output_8_y_origins[1]);

	EXPECT_EQ(local_test_label_3.get_x_origin(), frame_output_8_x_origins[2]);
	EXPECT_EQ(local_test_label_3.get_y_origin(), frame_output_8_y_origins[2]);

	EXPECT_EQ(local_test_label_4.get_x_origin(), frame_output_8_x_origins[3]);
	EXPECT_EQ(local_test_label_4.get_y_origin(), frame_output_8_y_origins[3]);

	EXPECT_EQ(local_test_label_5.get_x_origin(), frame_output_8_x_origins[4]);
	EXPECT_EQ(local_test_label_5.get_y_origin(), frame_output_8_y_origins[4]);

	EXPECT_EQ(local_test_label_6.get_x_origin(), frame_output_8_x_origins[5]);
	EXPECT_EQ(local_test_label_6.get_y_origin(), frame_output_8_y_origins[5]);

	// test width and height without spacing
	EXPECT_EQ(local_test_label_1.get_width(), frame_output_8_widths[0]);
	EXPECT_EQ(local_test_label_1.get_height(), frame_output_8_heights[0]);

	EXPECT_EQ(local_test_label_2.get_width(), frame_output_8_widths[1]);
	EXPECT_EQ(local_test_label_2.get_height(), frame_output_8_heights[1]);

	EXPECT_EQ(local_test_label_3.get_width(), frame_output_8_widths[2]);
	EXPECT_EQ(local_test_label_3.get_height(), frame_output_8_heights[2]);

	EXPECT_EQ(local_test_label_4.get_width(), frame_output_8_widths[3]);
	EXPECT_EQ(local_test_label_4.get_height(), frame_output_8_heights[3]);

	EXPECT_EQ(local_test_label_5.get_width(), frame_output_8_widths[4]);
	EXPECT_EQ(local_test_label_5.get_height(), frame_output_8_heights[4]);

	EXPECT_EQ(local_test_label_6.get_width(), frame_output_8_widths[5]);
	EXPECT_EQ(local_test_label_6.get_height(), frame_output_8_heights[5]);

	// test width and height with spacing
	EXPECT_EQ(local_test_label_1.get_width(true), frame_output_8_widths_with_spacing[0]);
	EXPECT_EQ(local_test_label_1.get_height(true), frame_output_8_heights_with_spacing[0]);

	EXPECT_EQ(local_test_label_2.get_width(true), frame_output_8_widths_with_spacing[1]);
	EXPECT_EQ(local_test_label_2.get_height(true), frame_output_8_heights_with_spacing[1]);

	EXPECT_EQ(local_test_label_3.get_width(true), frame_output_8_widths_with_spacing[2]);
	EXPECT_EQ(local_test_label_3.get_height(true), frame_output_8_heights_with_spacing[2]);

	EXPECT_EQ(local_test_label_4.get_width(true), frame_output_8_widths_with_spacing[3]);
	EXPECT_EQ(local_test_label_4.get_height(true), frame_output_8_heights_with_spacing[3]);

	EXPECT_EQ(local_test_label_5.get_width(true), frame_output_8_widths_with_spacing[4]);
	EXPECT_EQ(local_test_label_5.get_height(true), frame_output_8_heights_with_spacing[4]);

	EXPECT_EQ(local_test_label_6.get_width(true), frame_output_8_widths_with_spacing[5]);
	EXPECT_EQ(local_test_label_6.get_height(true), frame_output_8_heights_with_spacing[5]);
	delete(local_test_frame);
}

TEST_F(label_test, center_alignment)
{
	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.\n\n\n");
	local_test_label_1.add_border();
	local_test_label_1.set_alignment("center");
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border();
	local_test_label_2.set_alignment("center");
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border();
	local_test_label_3.set_alignment("center");
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4\n");
	local_test_label_4.add_border();
	local_test_label_4.set_alignment("center");
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border();
	local_test_label_5.set_alignment("center");
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6\n\n\n");
	local_test_label_6.add_border();
	local_test_label_6.set_alignment("center");
	std::string output = local_test_frame->get_frame_output();
	EXPECT_EQ(output, frame_output_9) << "Frame output:\n" + output;

	// test origins
	EXPECT_EQ(local_test_label_1.get_x_origin(), frame_output_9_x_origins[0]);
	EXPECT_EQ(local_test_label_1.get_y_origin(), frame_output_9_y_origins[0]);

	EXPECT_EQ(local_test_label_2.get_x_origin(), frame_output_9_x_origins[1]);
	EXPECT_EQ(local_test_label_2.get_y_origin(), frame_output_9_y_origins[1]);

	EXPECT_EQ(local_test_label_3.get_x_origin(), frame_output_9_x_origins[2]);
	EXPECT_EQ(local_test_label_3.get_y_origin(), frame_output_9_y_origins[2]);

	EXPECT_EQ(local_test_label_4.get_x_origin(), frame_output_9_x_origins[3]);
	EXPECT_EQ(local_test_label_4.get_y_origin(), frame_output_9_y_origins[3]);

	EXPECT_EQ(local_test_label_5.get_x_origin(), frame_output_9_x_origins[4]);
	EXPECT_EQ(local_test_label_5.get_y_origin(), frame_output_9_y_origins[4]);

	EXPECT_EQ(local_test_label_6.get_x_origin(), frame_output_9_x_origins[5]);
	EXPECT_EQ(local_test_label_6.get_y_origin(), frame_output_9_y_origins[5]);

	// test width and height without spacing
	EXPECT_EQ(local_test_label_1.get_width(), frame_output_9_widths[0]);
	EXPECT_EQ(local_test_label_1.get_height(), frame_output_9_heights[0]);

	EXPECT_EQ(local_test_label_2.get_width(), frame_output_9_widths[1]);
	EXPECT_EQ(local_test_label_2.get_height(), frame_output_9_heights[1]);

	EXPECT_EQ(local_test_label_3.get_width(), frame_output_9_widths[2]);
	EXPECT_EQ(local_test_label_3.get_height(), frame_output_9_heights[2]);

	EXPECT_EQ(local_test_label_4.get_width(), frame_output_9_widths[3]);
	EXPECT_EQ(local_test_label_4.get_height(), frame_output_9_heights[3]);

	EXPECT_EQ(local_test_label_5.get_width(), frame_output_9_widths[4]);
	EXPECT_EQ(local_test_label_5.get_height(), frame_output_9_heights[4]);

	EXPECT_EQ(local_test_label_6.get_width(), frame_output_9_widths[5]);
	EXPECT_EQ(local_test_label_6.get_height(), frame_output_9_heights[5]);

	// test width and height with spacing
	EXPECT_EQ(local_test_label_1.get_width(true), frame_output_9_widths_with_spacing[0]);
	EXPECT_EQ(local_test_label_1.get_height(true), frame_output_9_heights_with_spacing[0]);

	EXPECT_EQ(local_test_label_2.get_width(true), frame_output_9_widths_with_spacing[1]);
	EXPECT_EQ(local_test_label_2.get_height(true), frame_output_9_heights_with_spacing[1]);

	EXPECT_EQ(local_test_label_3.get_width(true), frame_output_9_widths_with_spacing[2]);
	EXPECT_EQ(local_test_label_3.get_height(true), frame_output_9_heights_with_spacing[2]);

	EXPECT_EQ(local_test_label_4.get_width(true), frame_output_9_widths_with_spacing[3]);
	EXPECT_EQ(local_test_label_4.get_height(true), frame_output_9_heights_with_spacing[3]);

	EXPECT_EQ(local_test_label_5.get_width(true), frame_output_9_widths_with_spacing[4]);
	EXPECT_EQ(local_test_label_5.get_height(true), frame_output_9_heights_with_spacing[4]);

	EXPECT_EQ(local_test_label_6.get_width(true), frame_output_9_widths_with_spacing[5]);
	EXPECT_EQ(local_test_label_6.get_height(true), frame_output_9_heights_with_spacing[5]);
	delete(local_test_frame);
}

TEST_F(label_test, center_block_alignment)
{
	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	label local_test_label_1(local_test_frame);
	local_test_label_1.set_output("This is widget 1.\n\n\n");
	local_test_label_1.add_border();
	local_test_label_1.set_alignment("center block");
	label local_test_label_2(local_test_frame);
	local_test_label_2.set_output("This\nis\nwidget\n2");
	local_test_label_2.add_border();
	local_test_label_2.set_alignment("center block");
	label local_test_label_3(local_test_frame, "new line");
	local_test_label_3.set_output("This is widget\n3");
	local_test_label_3.add_border();
	local_test_label_3.set_alignment("center block");
	label local_test_label_4(local_test_frame, "new line");
	local_test_label_4.set_output("This is\nwidget\n4\n");
	local_test_label_4.add_border();
	local_test_label_4.set_alignment("center block");
	label local_test_label_5(local_test_frame);
	local_test_label_5.set_output("This\nis\nwidget\n5");
	local_test_label_5.add_border();
	local_test_label_5.set_alignment("center block");
	label local_test_label_6(local_test_frame);
	local_test_label_6.set_output("This is widget 6\n\n\n");
	local_test_label_6.add_border();
	local_test_label_6.set_alignment("center block");
	std::string output = local_test_frame->get_frame_output();
	EXPECT_EQ(output, frame_output_10) << "Frame output:\n" + output;

	// test origins
	EXPECT_EQ(local_test_label_1.get_x_origin(), frame_output_10_x_origins[0]);
	EXPECT_EQ(local_test_label_1.get_y_origin(), frame_output_10_y_origins[0]);

	EXPECT_EQ(local_test_label_2.get_x_origin(), frame_output_10_x_origins[1]);
	EXPECT_EQ(local_test_label_2.get_y_origin(), frame_output_10_y_origins[1]);

	EXPECT_EQ(local_test_label_3.get_x_origin(), frame_output_10_x_origins[2]);
	EXPECT_EQ(local_test_label_3.get_y_origin(), frame_output_10_y_origins[2]);

	EXPECT_EQ(local_test_label_4.get_x_origin(), frame_output_10_x_origins[3]);
	EXPECT_EQ(local_test_label_4.get_y_origin(), frame_output_10_y_origins[3]);

	EXPECT_EQ(local_test_label_5.get_x_origin(), frame_output_10_x_origins[4]);
	EXPECT_EQ(local_test_label_5.get_y_origin(), frame_output_10_y_origins[4]);

	EXPECT_EQ(local_test_label_6.get_x_origin(), frame_output_10_x_origins[5]);
	EXPECT_EQ(local_test_label_6.get_y_origin(), frame_output_10_y_origins[5]);

	// test width and height without spacing
	EXPECT_EQ(local_test_label_1.get_width(), frame_output_10_widths[0]);
	EXPECT_EQ(local_test_label_1.get_height(), frame_output_10_heights[0]);

	EXPECT_EQ(local_test_label_2.get_width(), frame_output_10_widths[1]);
	EXPECT_EQ(local_test_label_2.get_height(), frame_output_10_heights[1]);

	EXPECT_EQ(local_test_label_3.get_width(), frame_output_10_widths[2]);
	EXPECT_EQ(local_test_label_3.get_height(), frame_output_10_heights[2]);

	EXPECT_EQ(local_test_label_4.get_width(), frame_output_10_widths[3]);
	EXPECT_EQ(local_test_label_4.get_height(), frame_output_10_heights[3]);

	EXPECT_EQ(local_test_label_5.get_width(), frame_output_10_widths[4]);
	EXPECT_EQ(local_test_label_5.get_height(), frame_output_10_heights[4]);

	EXPECT_EQ(local_test_label_6.get_width(), frame_output_10_widths[5]);
	EXPECT_EQ(local_test_label_6.get_height(), frame_output_10_heights[5]);

	// test width and height with spacing
	EXPECT_EQ(local_test_label_1.get_width(true), frame_output_10_widths_with_spacing[0]);
	EXPECT_EQ(local_test_label_1.get_height(true), frame_output_10_heights_with_spacing[0]);

	EXPECT_EQ(local_test_label_2.get_width(true), frame_output_10_widths_with_spacing[1]);
	EXPECT_EQ(local_test_label_2.get_height(true), frame_output_10_heights_with_spacing[1]);

	EXPECT_EQ(local_test_label_3.get_width(true), frame_output_10_widths_with_spacing[2]);
	EXPECT_EQ(local_test_label_3.get_height(true), frame_output_10_heights_with_spacing[2]);

	EXPECT_EQ(local_test_label_4.get_width(true), frame_output_10_widths_with_spacing[3]);
	EXPECT_EQ(local_test_label_4.get_height(true), frame_output_10_heights_with_spacing[3]);

	EXPECT_EQ(local_test_label_5.get_width(true), frame_output_10_widths_with_spacing[4]);
	EXPECT_EQ(local_test_label_5.get_height(true), frame_output_10_heights_with_spacing[4]);

	EXPECT_EQ(local_test_label_6.get_width(true), frame_output_10_widths_with_spacing[5]);
	EXPECT_EQ(local_test_label_6.get_height(true), frame_output_10_heights_with_spacing[5]);
	delete(local_test_frame);
}