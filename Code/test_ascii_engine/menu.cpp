#include "pch.h"
#ifdef __linux__
#include <gtest/gtest.h>
#endif
#ifdef _WIN32
#include "../ascii_engine/menu.h"
#include "../file_manager/file_manager.h"
#include "../ascii_engine/error_codes.h"
#include "../ascii_engine/frame.h"
#include "../ascii_engine/spacer.h"
#elif __linux
#include <ascii_engine/menu.h>
#include <ascii_engine/file_manager.h>
#include <ascii_engine/error_codes.h>
#include <ascii_engine/frame.h>
#include <ascii_engine/spacer.h>
#endif

#include "expected_display_data.h"

#include <string>

class menu_test : public testing::Test
{
protected:

	void run_test(std::string frame_output, std::vector<menu> menus, expected_display_data answer)
	{
		ASSERT_EQ(menus.size(), answer.heights.size());
		ASSERT_EQ(menus.size(), answer.widths.size());
		ASSERT_EQ(menus.size(), answer.x_origins.size());
		ASSERT_EQ(menus.size(), answer.y_origins.size());
		if (answer.heights_with_spacing.size() != 0)
		{
			ASSERT_EQ(menus.size(), answer.heights_with_spacing.size());
		}

		if (answer.widths_with_spacing.size() != 0)
		{
			ASSERT_EQ(menus.size(), answer.widths_with_spacing.size());
		}

		EXPECT_EQ(frame_output, answer.output) << "Frame output:\n" + frame_output;

		for (unsigned int i = 0; i < answer.x_origins.size(); i++)
		{
			EXPECT_EQ(menus[i].get_x_origin(), answer.x_origins[i]) << "x origin test for menu " + std::to_string(i);
		}

		for (unsigned int i = 0; i < answer.y_origins.size(); i++)
		{
			EXPECT_EQ(menus[i].get_y_origin(), answer.y_origins[i]) << "y origin test for menu " + std::to_string(i);
		}

		for (unsigned int i = 0; i < answer.heights.size(); i++)
		{
			EXPECT_EQ(menus[i].get_height(), answer.heights[i]) << "heights test for menu " + std::to_string(i);
		}

		for (unsigned int i = 0; i < answer.widths.size(); i++)
		{
			EXPECT_EQ(menus[i].get_width(), answer.widths[i]) << "widths test for menu " + std::to_string(i);
		}

		for (unsigned int i = 0; i < answer.heights_with_spacing.size(); i++)
		{
			EXPECT_EQ(menus[i].get_height(true), answer.heights_with_spacing[i]) << "heights with spacing test for menu " + std::to_string(i);
		}

		for (unsigned int i = 0; i < answer.widths_with_spacing.size(); i++)
		{
			EXPECT_EQ(menus[i].get_width(true), answer.widths_with_spacing[i]) << "widths with spacing test for menu " + std::to_string(i);
		}
	}
};

TEST_F(menu_test, get_widget_type)
{
	frame* local_test_frame = new frame();
	menu local_test_menu_1(local_test_frame);
	EXPECT_EQ(local_test_menu_1.get_widget_type(), MENU);
	delete(local_test_frame);
}

TEST_F(menu_test, is_selectable)
{
	frame* local_test_frame = new frame();
	menu local_test_menu_1(local_test_frame);
	EXPECT_EQ(local_test_menu_1.is_selectable(), true);
	delete(local_test_frame);
}
TEST_F(menu_test, test_basic)
{
	const expected_display_data correct_answer =
	{
		"* 1                                               * 1                                               \n"
		"                                                    2                                               \n"
		"                                                    3                                               \n"
		"                                                    4                                               \n"
		"* First option                                                                                      \n"
		"  Second option                                                                                     \n"
		"* a                              * d                              * h                               \n"
		"  b                                e                                                                \n"
		"  c                                f                                                                \n"
		"                                   g                                                                ",
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
	std::vector<menu> menus;
	menu local_test_menu_1(local_test_frame);
	local_test_menu_1.append_item("1");
	menus.push_back(local_test_menu_1);
	menu local_test_menu_2(local_test_frame);
	local_test_menu_2.append_item("1");
	local_test_menu_2.append_item("2");
	local_test_menu_2.append_item("3");
	local_test_menu_2.append_item("4");
	menus.push_back(local_test_menu_2);
	menu local_test_menu_3(local_test_frame, "new line");
	local_test_menu_3.append_item("First option");
	local_test_menu_3.append_item("Second option");
	menus.push_back(local_test_menu_3);
	menu local_test_menu_4(local_test_frame, "new line");
	local_test_menu_4.append_item("a");
	local_test_menu_4.append_item("b");
	local_test_menu_4.append_item("c");
	menus.push_back(local_test_menu_4);
	menu local_test_menu_5(local_test_frame);
	local_test_menu_5.append_item("d");
	local_test_menu_5.append_item("e");
	local_test_menu_5.append_item("f");
	local_test_menu_5.append_item("g");
	menus.push_back(local_test_menu_5);
	menu local_test_menu_6(local_test_frame);
	local_test_menu_6.append_item("h");
	menus.push_back(local_test_menu_6);
	std::string output = local_test_frame->get_frame_output();
	
	run_test(output, menus, correct_answer);

	delete(local_test_frame);
}

TEST_F(menu_test, test_border)
{
	const expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"| * 1                                            || * 1                                            |\n"
		".------------------------------------------------.|   2                                            |\n"
		"                                                  |   3                                            |\n"
		"                                                  |   4                                            |\n"
		"                                                  .------------------------------------------------.\n"
		".--------------------------------------------------------------------------------------------------.\n"
		"| * First option                                                                                   |\n"
		"|   Second option                                                                                  |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"| * a                           || * d                           || * h                           | \n"
		"|   b                           ||   e                           |.-------------------------------. \n"
		"|   c                           ||   f                           |                                  \n"
		".-------------------------------.|   g                           |                                  \n"
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
	std::vector<menu> menus;
	menu local_test_menu_1(local_test_frame);
	local_test_menu_1.append_item("1");
	local_test_menu_1.add_border();
	menus.push_back(local_test_menu_1);
	menu local_test_menu_2(local_test_frame);
	local_test_menu_2.append_item("1");
	local_test_menu_2.append_item("2");
	local_test_menu_2.append_item("3");
	local_test_menu_2.append_item("4");
	local_test_menu_2.add_border();
	menus.push_back(local_test_menu_2);
	menu local_test_menu_3(local_test_frame, "new line");
	local_test_menu_3.append_item("First option");
	local_test_menu_3.append_item("Second option");
	local_test_menu_3.add_border();
	menus.push_back(local_test_menu_3);
	menu local_test_menu_4(local_test_frame, "new line");
	local_test_menu_4.append_item("a");
	local_test_menu_4.append_item("b");
	local_test_menu_4.append_item("c");
	local_test_menu_4.add_border();
	menus.push_back(local_test_menu_4);
	menu local_test_menu_5(local_test_frame);
	local_test_menu_5.append_item("d");
	local_test_menu_5.append_item("e");
	local_test_menu_5.append_item("f");
	local_test_menu_5.append_item("g");
	local_test_menu_5.add_border();
	menus.push_back(local_test_menu_5);
	menu local_test_menu_6(local_test_frame);
	local_test_menu_6.append_item("h");
	local_test_menu_6.add_border();
	menus.push_back(local_test_menu_6);
	std::string output = local_test_frame->get_frame_output();
	
	run_test(output, menus, correct_answer);

	delete(local_test_frame);
}

TEST_F(menu_test, test_merge)
{
	const expected_display_data correct_answer =
	{
		"* 1                                               * 1                                               \n"
		"* 2                                                 2                                               \n"
		"                                                    3                                               \n"
		"                                                    4                                               \n"
		"* First option                                                                                      \n"
		"  Second option                                                                                     \n"
		"* a                              * d                              * h                               \n"
		"  b                                e                              * i                               \n"
		"  c                                f                                                                \n"
		"                                   g                                                                ",
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
	std::vector<menu> menus;
	menu local_test_menu_1(local_test_frame);
	local_test_menu_1.append_item("1");
	menus.push_back(local_test_menu_1);
	menu local_test_menu_2(local_test_frame, "merge");
	local_test_menu_2.append_item("2");
	menus.push_back(local_test_menu_2);
	menu local_test_menu_3(local_test_frame);
	local_test_menu_3.append_item("1");
	local_test_menu_3.append_item("2");
	local_test_menu_3.append_item("3");
	local_test_menu_3.append_item("4");
	menus.push_back(local_test_menu_3);
	menu local_test_menu_4(local_test_frame, "new line");
	local_test_menu_4.append_item("First option");
	local_test_menu_4.append_item("Second option");
	menus.push_back(local_test_menu_4);
	menu local_test_menu_5(local_test_frame, "new line");
	local_test_menu_5.append_item("a");
	local_test_menu_5.append_item("b");
	local_test_menu_5.append_item("c");
	menus.push_back(local_test_menu_5);
	menu local_test_menu_6(local_test_frame);
	local_test_menu_6.append_item("d");
	local_test_menu_6.append_item("e");
	local_test_menu_6.append_item("f");
	local_test_menu_6.append_item("g");
	menus.push_back(local_test_menu_6);
	menu local_test_menu_7(local_test_frame);
	local_test_menu_7.append_item("h");
	menus.push_back(local_test_menu_7);
	menu local_test_menu_8(local_test_frame, "merge");
	local_test_menu_8.append_item("i");
	menus.push_back(local_test_menu_8);
	std::string output = local_test_frame->get_frame_output();
	
	run_test(output, menus, correct_answer);

	const expected_display_data correct_answer_2 =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"| * 1                                            || * 1                                            |\n"
		".------------------------------------------------.|   2                                            |\n"
		".------------------------------------------------.|   3                                            |\n"
		"| * 2                                            ||   4                                            |\n"
		".------------------------------------------------..------------------------------------------------.\n"
		".--------------------------------------------------------------------------------------------------.\n"
		"| * First option                                                                                   |\n"
		"|   Second option                                                                                  |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"| * a                           || * d                           || * h                           | \n"
		"|   b                           ||   e                           |.-------------------------------. \n"
		"|   c                           ||   f                           |.-------------------------------. \n"
		".-------------------------------.|   g                           || * i                           | \n"
		"                                 .-------------------------------..-------------------------------. ",
		{ 2, 2, 52, 2, 2, 35, 68, 68 },
		{ 1, 4, 1, 7, 11, 11, 11, 14 },
		{ 46, 46, 46, 96, 29, 29, 29, 29 },
		{ 1, 1, 4, 2, 3, 4, 1, 1 },
		{ 50, 50, 50, 100, 33, 33, 33, 33 },
		{ 3, 3, 6, 4, 5, 6, 3, 3 }
	};
	
	menus.clear();
	local_test_frame->set_fake_console_height(16);
	local_test_menu_1.add_border();
	menus.push_back(local_test_menu_1);
	local_test_menu_2.add_border();
	menus.push_back(local_test_menu_2);
	local_test_menu_3.add_border();
	menus.push_back(local_test_menu_3);
	local_test_menu_4.add_border();
	menus.push_back(local_test_menu_4);
	local_test_menu_5.add_border();
	menus.push_back(local_test_menu_5);
	local_test_menu_6.add_border();
	menus.push_back(local_test_menu_6);
	local_test_menu_7.add_border();
	menus.push_back(local_test_menu_7);
	local_test_menu_8.add_border();
	menus.push_back(local_test_menu_8);
	output = local_test_frame->get_frame_output();
	
	run_test(output, menus, correct_answer_2);

	delete(local_test_frame);
}

TEST_F(menu_test, test_spacer)
{
	const expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"| * 1                                            || * 1                                            |\n"
		".------------------------------------------------.|   2                                            |\n"
		"                                                  |   3                                            |\n"
		"                                                  |   4                                            |\n"
		"                                                  .------------------------------------------------.\n"
		"                                 .-------------------------------.                                  \n"
		"                                 | * First option                |                                  \n"
		"                                 |   Second option               |                                  \n"
		"                                 .-------------------------------.                                  \n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"| * a                           || * d                           || * h                           | \n"
		"|   b                           ||   e                           |.-------------------------------. \n"
		"|   c                           ||   f                           |                                  \n"
		".-------------------------------.|   g                           |                                  \n"
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
	std::vector<menu> menus;
	menu local_test_menu_1(local_test_frame);
	local_test_menu_1.append_item("1");
	local_test_menu_1.add_border();
	menus.push_back(local_test_menu_1);
	menu local_test_menu_2(local_test_frame);
	local_test_menu_2.append_item("1");
	local_test_menu_2.append_item("2");
	local_test_menu_2.append_item("3");
	local_test_menu_2.append_item("4");
	local_test_menu_2.add_border();
	menus.push_back(local_test_menu_2);
	spacer local_test_spacer_1(local_test_frame, 1, "new line");
	menu local_test_menu_3(local_test_frame);
	local_test_menu_3.append_item("First option");
	local_test_menu_3.append_item("Second option");
	local_test_menu_3.add_border();
	menus.push_back(local_test_menu_3);
	spacer local_test_spacer_2(local_test_frame, 1);
	menu local_test_menu_4(local_test_frame, "new line");
	local_test_menu_4.append_item("a");
	local_test_menu_4.append_item("b");
	local_test_menu_4.append_item("c");
	local_test_menu_4.add_border();
	menus.push_back(local_test_menu_4);
	menu local_test_menu_5(local_test_frame);
	local_test_menu_5.append_item("d");
	local_test_menu_5.append_item("e");
	local_test_menu_5.append_item("f");
	local_test_menu_5.append_item("g");
	local_test_menu_5.add_border();
	menus.push_back(local_test_menu_5);
	menu local_test_menu_6(local_test_frame);
	local_test_menu_6.append_item("h");
	local_test_menu_6.add_border();
	menus.push_back(local_test_menu_6);
	std::string output = local_test_frame->get_frame_output();
	
	run_test(output, menus, correct_answer);

	delete(local_test_frame);
}

TEST_F(menu_test, test_spacing)
{
	const expected_display_data correct_answer =
	{
		"                                                  .-----------------------------------------------. \n"
		".-----------------------------------------------. | * 1                                           | \n"
		"| * 1                                           | |   2                                           | \n"
		".-----------------------------------------------. |   3                                           | \n"
		"                                                  |   4                                           | \n"
		"                                                  .-----------------------------------------------. \n"
		"                                                                                                    \n"
		"     .----------------------------------------------------------------------------------------.     \n"
		"     | * First option                                                                         |     \n"
		"     |   Second option                                                                        |     \n"
		"     .----------------------------------------------------------------------------------------.     \n"
		"                                                                                                    \n"
		"                                                                                                    \n"
		"                                 .-------------------------------. .-----------------------------.  \n"
		".-------------------------------.| * d                           | | * h                         |  \n"
		"| * a                           ||   e                           | .-----------------------------.  \n"
		"|   b                           ||   f                           |                                  \n"
		"|   c                           ||   g                           |                                  \n"
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
	std::vector<menu> menus;
	menu local_test_menu_1(local_test_frame);
	local_test_menu_1.append_item("1");
	local_test_menu_1.add_border();
	local_test_menu_1.set_spacing(1, 1, 0, 1);
	menus.push_back(local_test_menu_1);
	menu local_test_menu_2(local_test_frame);
	local_test_menu_2.append_item("1");
	local_test_menu_2.append_item("2");
	local_test_menu_2.append_item("3");
	local_test_menu_2.append_item("4");
	local_test_menu_2.add_border();
	local_test_menu_2.set_spacing(0, 0, 0, 1);
	menus.push_back(local_test_menu_2);
	menu local_test_menu_3(local_test_frame, "new line");
	local_test_menu_3.append_item("First option");
	local_test_menu_3.append_item("Second option");
	local_test_menu_3.add_border();
	local_test_menu_3.set_spacing(1, 2, 5, 5);
	menus.push_back(local_test_menu_3);
	menu local_test_menu_4(local_test_frame, "new line");
	local_test_menu_4.append_item("a");
	local_test_menu_4.append_item("b");
	local_test_menu_4.append_item("c");
	local_test_menu_4.add_border();
	local_test_menu_4.set_spacing(1, 1, 0, 0);
	menus.push_back(local_test_menu_4);
	menu local_test_menu_5(local_test_frame);
	local_test_menu_5.append_item("d");
	local_test_menu_5.append_item("e");
	local_test_menu_5.append_item("f");
	local_test_menu_5.append_item("g");
	local_test_menu_5.add_border();
	menus.push_back(local_test_menu_5);
	menu local_test_menu_6(local_test_frame);
	local_test_menu_6.append_item("h");
	local_test_menu_6.add_border();
	local_test_menu_6.set_spacing(0, 0, 1, 1);
	menus.push_back(local_test_menu_6);
	std::string output = local_test_frame->get_frame_output();
	
	run_test(output, menus, correct_answer);
	delete(local_test_frame);
}

TEST_F(menu_test, test_border_spacing)
{
	const expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"| * 1                                            || * 1                                            |\n"
		"|                                                ||   2                                            |\n"
		"|                                                ||   3                                            |\n"
		"|                                                ||   4                                            |\n"
		".------------------------------------------------..------------------------------------------------.\n"
		".--------------------------------------------------------------------------------------------------.\n"
		"| * First option                                                                                   |\n"
		"|   Second option                                                                                  |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"| * a                           || * d                           || * h                           | \n"
		"|   b                           ||   e                           ||                               | \n"
		"|   c                           ||   f                           ||                               | \n"
		"|                               ||   g                           ||                               | \n"
		".-------------------------------..-------------------------------..-------------------------------. ",
		{ 2, 52, 2, 2, 35, 68 },
		{ 1, 1, 7, 11, 11, 11 },
		{ 46, 46, 96, 29, 29, 29 },
		{ 1, 4, 2, 3, 4, 1 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 6, 6, 4, 6, 6, 6 }
	};

	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<menu> menus;
	menu local_test_menu_1(local_test_frame);
	local_test_menu_1.append_item("1");
	local_test_menu_1.add_border();
	local_test_menu_1.set_spacing(0, 3, 0, 0);
	local_test_menu_1.set_border_spacing(0, 3, 0, 0);
	menus.push_back(local_test_menu_1);
	menu local_test_menu_2(local_test_frame);
	local_test_menu_2.append_item("1");
	local_test_menu_2.append_item("2");
	local_test_menu_2.append_item("3");
	local_test_menu_2.append_item("4");
	local_test_menu_2.add_border();
	menus.push_back(local_test_menu_2);
	menu local_test_menu_3(local_test_frame, "new line");
	local_test_menu_3.append_item("First option");
	local_test_menu_3.append_item("Second option");
	local_test_menu_3.add_border();
	menus.push_back(local_test_menu_3);
	menu local_test_menu_4(local_test_frame, "new line");
	local_test_menu_4.append_item("a");
	local_test_menu_4.append_item("b");
	local_test_menu_4.append_item("c");
	local_test_menu_4.add_border();
	local_test_menu_4.set_spacing(0, 1, 0, 0);
	local_test_menu_4.set_border_spacing(0, 1, 0, 0);
	menus.push_back(local_test_menu_4);
	menu local_test_menu_5(local_test_frame);
	local_test_menu_5.append_item("d");
	local_test_menu_5.append_item("e");
	local_test_menu_5.append_item("f");
	local_test_menu_5.append_item("g");
	local_test_menu_5.add_border();
	menus.push_back(local_test_menu_5);
	menu local_test_menu_6(local_test_frame);
	local_test_menu_6.append_item("h");
	local_test_menu_6.add_border();
	local_test_menu_6.set_spacing(0, 3, 0, 0);
	local_test_menu_6.set_border_spacing(0, 3, 0, 0);
	menus.push_back(local_test_menu_6);
	std::string output = local_test_frame->get_frame_output();

	run_test(output, menus, correct_answer);
	delete(local_test_frame);
}

TEST_F(menu_test, right_alignment)
{
	const expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"|                                            * 1 ||                                            * 1 |\n"
		"|                                                ||                                              2 |\n"
		"|                                                ||                                              3 |\n"
		"|                                                ||                                              4 |\n"
		".------------------------------------------------..------------------------------------------------.\n"
		".--------------------------------------------------------------------------------------------------.\n"
		"|                                                                                   * First option |\n"
		"|                                                                                    Second option |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"|                           * a ||                           * d ||                           * h | \n"
		"|                             b ||                             e ||                               | \n"
		"|                             c ||                             f ||                               | \n"
		"|                               ||                             g ||                               | \n"
		".-------------------------------..-------------------------------..-------------------------------. ",
		{ 2, 52, 2, 2, 35, 68 },
		{ 1, 1, 7, 11, 11, 11 },
		{ 46, 46, 96, 29, 29, 29 },
		{ 1, 4, 2, 3, 4, 1 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 6, 6, 4, 6, 6, 6 }
	};

	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<menu> menus;
	menu local_test_menu_1(local_test_frame);
	local_test_menu_1.append_item("1");
	local_test_menu_1.add_border();
	local_test_menu_1.set_spacing(0, 3, 0, 0);
	local_test_menu_1.set_border_spacing(0, 3, 0, 0);
	local_test_menu_1.set_alignment("right");
	menus.push_back(local_test_menu_1);
	menu local_test_menu_2(local_test_frame);
	local_test_menu_2.append_item("1");
	local_test_menu_2.append_item("2");
	local_test_menu_2.append_item("3");
	local_test_menu_2.append_item("4");
	local_test_menu_2.add_border();
	local_test_menu_2.set_alignment("right");
	menus.push_back(local_test_menu_2);
	menu local_test_menu_3(local_test_frame, "new line");
	local_test_menu_3.append_item("First option");
	local_test_menu_3.append_item("Second option");
	local_test_menu_3.add_border();
	local_test_menu_3.set_alignment("right");
	menus.push_back(local_test_menu_3);
	menu local_test_menu_4(local_test_frame, "new line");
	local_test_menu_4.append_item("a");
	local_test_menu_4.append_item("b");
	local_test_menu_4.append_item("c");
	local_test_menu_4.add_border();
	local_test_menu_4.set_spacing(0, 1, 0, 0);
	local_test_menu_4.set_border_spacing(0, 1, 0, 0);
	local_test_menu_4.set_alignment("right");
	menus.push_back(local_test_menu_4);
	menu local_test_menu_5(local_test_frame);
	local_test_menu_5.append_item("d");
	local_test_menu_5.append_item("e");
	local_test_menu_5.append_item("f");
	local_test_menu_5.append_item("g");
	local_test_menu_5.add_border();
	local_test_menu_5.set_alignment("right");
	menus.push_back(local_test_menu_5);
	menu local_test_menu_6(local_test_frame);
	local_test_menu_6.append_item("h");
	local_test_menu_6.add_border();
	local_test_menu_6.set_spacing(0, 3, 0, 0);
	local_test_menu_6.set_border_spacing(0, 3, 0, 0);
	local_test_menu_6.set_alignment("right");
	menus.push_back(local_test_menu_6);
	std::string output = local_test_frame->get_frame_output();

	run_test(output, menus, correct_answer);
	delete(local_test_frame);
}

TEST_F(menu_test, center_alignment)
{
	const expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"|                      * 1                       ||                      * 1                       |\n"
		"|                                                ||                        2                       |\n"
		"|                                                ||                        3                       |\n"
		"|                                                ||                        4                       |\n"
		".------------------------------------------------..------------------------------------------------.\n"
		".--------------------------------------------------------------------------------------------------.\n"
		"|                                          * First option                                          |\n"
		"|                                           Second option                                          |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"|              * a              ||              * d              ||              * h              | \n"
		"|                b              ||                e              ||                               | \n"
		"|                c              ||                f              ||                               | \n"
		"|                               ||                g              ||                               | \n"
		".-------------------------------..-------------------------------..-------------------------------. ",
		{ 2, 52, 2, 2, 35, 68 },
		{ 1, 1, 7, 11, 11, 11 },
		{ 46, 46, 96, 29, 29, 29 },
		{ 1, 4, 2, 3, 4, 1 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 6, 6, 4, 6, 6, 6 }
	};

	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<menu> menus;
	menu local_test_menu_1(local_test_frame);
	local_test_menu_1.append_item("1");
	local_test_menu_1.add_border();
	local_test_menu_1.set_spacing(0, 3, 0, 0);
	local_test_menu_1.set_border_spacing(0, 3, 0, 0);
	local_test_menu_1.set_alignment("center");
	menus.push_back(local_test_menu_1);
	menu local_test_menu_2(local_test_frame);
	local_test_menu_2.append_item("1");
	local_test_menu_2.append_item("2");
	local_test_menu_2.append_item("3");
	local_test_menu_2.append_item("4");
	local_test_menu_2.add_border();
	local_test_menu_2.set_alignment("center");
	menus.push_back(local_test_menu_2);
	menu local_test_menu_3(local_test_frame, "new line");
	local_test_menu_3.append_item("First option");
	local_test_menu_3.append_item("Second option");
	local_test_menu_3.add_border();
	local_test_menu_3.set_alignment("center");
	menus.push_back(local_test_menu_3);
	menu local_test_menu_4(local_test_frame, "new line");
	local_test_menu_4.append_item("a");
	local_test_menu_4.append_item("b");
	local_test_menu_4.append_item("c");
	local_test_menu_4.add_border();
	local_test_menu_4.set_spacing(0, 1, 0, 0);
	local_test_menu_4.set_border_spacing(0, 1, 0, 0);
	local_test_menu_4.set_alignment("center");
	menus.push_back(local_test_menu_4);
	menu local_test_menu_5(local_test_frame);
	local_test_menu_5.append_item("d");
	local_test_menu_5.append_item("e");
	local_test_menu_5.append_item("f");
	local_test_menu_5.append_item("g");
	local_test_menu_5.add_border();
	local_test_menu_5.set_alignment("center");
	menus.push_back(local_test_menu_5);
	menu local_test_menu_6(local_test_frame);
	local_test_menu_6.append_item("h");
	local_test_menu_6.add_border();
	local_test_menu_6.set_spacing(0, 3, 0, 0);
	local_test_menu_6.set_border_spacing(0, 3, 0, 0);
	local_test_menu_6.set_alignment("center");
	menus.push_back(local_test_menu_6);
	std::string output = local_test_frame->get_frame_output();

	run_test(output, menus, correct_answer);
	delete(local_test_frame);
}

TEST_F(menu_test, center_block_alignment)
{
	const expected_display_data correct_answer =
	{
		".------------------------------------------------..------------------------------------------------.\n"
		"|                      * 1                       ||                      * 1                       |\n"
		"|                                                ||                        2                       |\n"
		"|                                                ||                        3                       |\n"
		"|                                                ||                        4                       |\n"
		".------------------------------------------------..------------------------------------------------.\n"
		".--------------------------------------------------------------------------------------------------.\n"
		"|                                         * First option                                           |\n"
		"|                                           Second option                                          |\n"
		".--------------------------------------------------------------------------------------------------.\n"
		".-------------------------------..-------------------------------..-------------------------------. \n"
		"|              * a              ||              * d              ||              * h              | \n"
		"|                b              ||                e              ||                               | \n"
		"|                c              ||                f              ||                               | \n"
		"|                               ||                g              ||                               | \n"
		".-------------------------------..-------------------------------..-------------------------------. ",
		{ 2, 52, 2, 2, 35, 68 },
		{ 1, 1, 7, 11, 11, 11 },
		{ 46, 46, 96, 29, 29, 29 },
		{ 1, 4, 2, 3, 4, 1 },
		{ 50, 50, 100, 33, 33, 33 },
		{ 6, 6, 4, 6, 6, 6 }
	};

	frame* local_test_frame = new frame();
	local_test_frame->use_fake_console_dimensions();
	local_test_frame->set_fake_console_height(16);
	local_test_frame->set_fake_console_width(100);
	std::vector<menu> menus;
	menu local_test_menu_1(local_test_frame);
	local_test_menu_1.append_item("1");
	local_test_menu_1.add_border();
	local_test_menu_1.set_spacing(0, 3, 0, 0);
	local_test_menu_1.set_border_spacing(0, 3, 0, 0);
	local_test_menu_1.set_alignment("center block");
	menus.push_back(local_test_menu_1);
	menu local_test_menu_2(local_test_frame);
	local_test_menu_2.append_item("1");
	local_test_menu_2.append_item("2");
	local_test_menu_2.append_item("3");
	local_test_menu_2.append_item("4");
	local_test_menu_2.add_border();
	local_test_menu_2.set_alignment("center block");
	menus.push_back(local_test_menu_2);
	menu local_test_menu_3(local_test_frame, "new line");
	local_test_menu_3.append_item("First option");
	local_test_menu_3.append_item("Second option");
	local_test_menu_3.add_border();
	local_test_menu_3.set_alignment("center block");
	menus.push_back(local_test_menu_3);
	menu local_test_menu_4(local_test_frame, "new line");
	local_test_menu_4.append_item("a");
	local_test_menu_4.append_item("b");
	local_test_menu_4.append_item("c");
	local_test_menu_4.add_border();
	local_test_menu_4.set_spacing(0, 1, 0, 0);
	local_test_menu_4.set_border_spacing(0, 1, 0, 0);
	local_test_menu_4.set_alignment("center block");
	menus.push_back(local_test_menu_4);
	menu local_test_menu_5(local_test_frame);
	local_test_menu_5.append_item("d");
	local_test_menu_5.append_item("e");
	local_test_menu_5.append_item("f");
	local_test_menu_5.append_item("g");
	local_test_menu_5.add_border();
	local_test_menu_5.set_alignment("center block");
	menus.push_back(local_test_menu_5);
	menu local_test_menu_6(local_test_frame);
	local_test_menu_6.append_item("h");
	local_test_menu_6.add_border();
	local_test_menu_6.set_spacing(0, 3, 0, 0);
	local_test_menu_6.set_border_spacing(0, 3, 0, 0);
	local_test_menu_6.set_alignment("center block");
	menus.push_back(local_test_menu_6);
	std::string output = local_test_frame->get_frame_output();

	run_test(output, menus, correct_answer);
	delete(local_test_frame);
}