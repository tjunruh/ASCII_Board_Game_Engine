#include "pch.h"
#ifdef __linux__
#include <gtest/gtest.h>
#endif

#include <ascii_engine/console.h>
#include <ascii_engine/error_codes.h>
#include <ascii_engine/frame.h>
#include <ascii_engine/label.h>
#include <ascii_engine/text_box.h>
#include <ascii_engine/menu.h>
#include <ascii_engine/ascii_board.h>

TEST(console_test, register_label_widget)
{
	frame* test_frame = new frame();
	frame* test_frame_2 = new frame();

	label test_label(test_frame);
	label test_label_2(test_frame);
	label test_label_3(test_frame_2);

	console test_console;

	EXPECT_EQ(SUCCESS, test_console.register_widget(&test_label));
	EXPECT_EQ(SUCCESS, test_console.register_widget(&test_label_2));
	EXPECT_EQ(INVALID_VALUE, test_console.register_widget(&test_label_3));
	EXPECT_EQ(DUPLICATE_ELEMENT, test_console.register_widget(&test_label));
}

TEST(console_test, register_text_box_widget)
{
	frame* test_frame = new frame();
	frame* test_frame_2 = new frame();

	text_box test_text_box(test_frame);
	text_box test_text_box_2(test_frame);
	text_box test_text_box_3(test_frame_2);

	console test_console;

	EXPECT_EQ(SUCCESS, test_console.register_widget(&test_text_box));
	EXPECT_EQ(SUCCESS, test_console.register_widget(&test_text_box_2));
	EXPECT_EQ(INVALID_VALUE, test_console.register_widget(&test_text_box_3));
	EXPECT_EQ(DUPLICATE_ELEMENT, test_console.register_widget(&test_text_box));
}

TEST(console_test, register_menu_widget)
{
	frame* test_frame = new frame();
	frame* test_frame_2 = new frame();

	menu test_menu(test_frame);
	menu test_menu_2(test_frame);
	menu test_menu_3(test_frame_2);

	console test_console;

	EXPECT_EQ(SUCCESS, test_console.register_widget(&test_menu));
	EXPECT_EQ(SUCCESS, test_console.register_widget(&test_menu_2));
	EXPECT_EQ(INVALID_VALUE, test_console.register_widget(&test_menu_3));
	EXPECT_EQ(DUPLICATE_ELEMENT, test_console.register_widget(&test_menu));
}

TEST(console_test, register_ascii_board_test)
{
	frame* test_frame = new frame();
	frame* test_frame_2 = new frame();

	ascii_board test_board(test_frame, "Code/test_ascii_engine/test_configs/single_line_test_board_config.txt", "default");
	ascii_board test_board_2(test_frame, "Code/test_ascii_engine/test_configs/single_line_test_board_config.txt", "default");
	ascii_board test_board_3(test_frame_2, "Code/test_ascii_engine/test_configs/single_line_test_board_config.txt", "default");

	console test_console;

	EXPECT_EQ(SUCCESS, test_console.register_widget(&test_board));
	EXPECT_EQ(SUCCESS, test_console.register_widget(&test_board_2));
	EXPECT_EQ(INVALID_VALUE, test_console.register_widget(&test_board_3));
	EXPECT_EQ(DUPLICATE_ELEMENT, test_console.register_widget(&test_board));
}