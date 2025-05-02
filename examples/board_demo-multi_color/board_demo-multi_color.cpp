#include <ascii_io.h>
#include <frame.h>
#include <label.h>
#include <ascii_board.h>
#include <menu.h>
#include <format_tools.h>
#include <vector>

int main()
{
	std::vector<format_tools::index_format> cursor_color;
	std::vector<format_tools::index_format> player_1_color;
	std::vector<format_tools::index_format> player_2_color;

	format_tools::index_format blank_color;
	format_tools::index_format color;

	// color for cursor (index range is 0 to 26 since there are 27 characters
	// */*****\*
	// |*******|
	// *\*****/*
	color.format.foreground_format = format_tools::green;
	color.index = 1;
	cursor_color.push_back(color);
	blank_color.index = 2;
	cursor_color.push_back(blank_color);
	color.index = 7;
	cursor_color.push_back(color);
	blank_color.index = 8;
	cursor_color.push_back(blank_color);
	color.format.foreground_format = format_tools::red;
	color.index = 9;
	cursor_color.push_back(color);
	blank_color.index = 10;
	cursor_color.push_back(blank_color);
	color.index = 17;
	cursor_color.push_back(color);
	blank_color.index = 18;
	cursor_color.push_back(blank_color);
	color.index = 19;
	color.format.foreground_format = format_tools::yellow;
	cursor_color.push_back(color);
	blank_color.index = 20;
	cursor_color.push_back(blank_color);
	color.index = 25;
	cursor_color.push_back(color);
	blank_color.index = 26;
	cursor_color.push_back(blank_color);

	// color for player 1 piece which is an x (index range is 0 to 26 since there are 27 characters)
	// **\\ //**
	// ** { } **
	// **// \\**
	color.format.foreground_format = format_tools::blue;
	color.index = 2;
	player_1_color.push_back(color);
	blank_color.index = 7;
	player_1_color.push_back(blank_color);
	color.index = 12;
	color.format.foreground_format = format_tools::magenta;
	player_1_color.push_back(color);
	blank_color.index = 15;
	player_1_color.push_back(blank_color);
	color.format.foreground_format = format_tools::cyan;
	color.index = 20;
	player_1_color.push_back(color);
	blank_color.index = 25;
	player_1_color.push_back(blank_color);

	// color for player 2 piece which is an o (index range is 0 to 26 since there are 27 characters)
	//**//`\\**
	//**|   |**
	//**\\.//**
	color.format.foreground_format = format_tools::cyan;
	color.index = 2;
	player_2_color.push_back(color);
	blank_color.index = 7;
	player_2_color.push_back(blank_color);
	color.index = 11;
	color.format.foreground_format = format_tools::magenta;
	player_2_color.push_back(color);
	blank_color.index = 16;
	player_2_color.push_back(blank_color);
	color.format.foreground_format = format_tools::blue;
	color.index = 20;
	player_2_color.push_back(color);
	blank_color.index = 25;
	player_2_color.push_back(blank_color);


	ascii_io::ascii_engine_init();
	frame* my_frame = new frame();
	my_frame->enable_color(true);
	// uncomment two lines below for line drawing
	//my_frame->enable_dec(true);
	//my_frame->set_dec_format_characters('=', '|', '+', '.');
	label my_label(my_frame);
	ascii_board my_board(my_frame, "board_configs/multi_line_test_board_config.txt", "default", "new line");
	menu my_menu(my_frame, "new line");

	my_label.set_spacing(2, 2, 0, 0);
	my_label.set_alignment("center");
	my_label.set_output("ASCII Board Demo");

	my_board.set_alignment("center");
	my_board.load_configuration("board_configs/multi_line_test_cursor_config.txt", "cursor", -1, -1, '*', cursor_color);
	my_board.load_configuration("board_configs/multi_line_test_x_config.txt", "player 1", -1, -1, '*', player_1_color);
	my_board.load_configuration("board_configs/multi_line_test_o_config.txt", "player 2", -1, -1, '*', player_2_color);
	int cursor_row = 3;
	int cursor_column = 3;
	my_board.activate_configuration("cursor", cursor_row, cursor_column);
	my_board.build();

	my_menu.set_spacing(2, 0, 0, 0);
	my_menu.add_border(true);
	my_menu.append_item("player 1");
	my_menu.append_item("player 2");
	my_menu.append_item("exit");
	my_menu.set_alignment("center");
	my_menu.enable_quit();
	my_menu.build();

	ascii_io::hide_cursor();

	my_frame->display();

	std::string player = "player 1";

	while (1)
	{
		int widget_id = my_frame->get_selection();
		if (widget_id == my_board)
		{
			while (1)
			{
				int input = ascii_io::getchar();
				my_board.deactivate_configuration("cursor", cursor_row, cursor_column);
				if (input == ascii_io::enter)
				{
					my_board.activate_configuration(player, cursor_row, cursor_column);
				}
				else if (input == ascii_io::up)
				{
					if (cursor_row - 1 >= 0)
					{
						cursor_row--;
					}
				}
				else if (input == ascii_io::down)
				{
					if (cursor_row + 1 < my_board.get_number_of_rows())
					{
						cursor_row++;
					}
				}
				else if (input == ascii_io::right)
				{
					if (cursor_column + 1 < my_board.get_number_of_columns())
					{
						cursor_column++;
					}
				}
				else if (input == ascii_io::left)
				{
					if (cursor_column - 1 >= 0)
					{
						cursor_column--;
					}
				}
				else if (input == ascii_io::q)
				{
					my_board.activate_configuration("cursor", cursor_row, cursor_column);
					my_board.build();
					break;
				}

				my_board.activate_configuration("cursor", cursor_row, cursor_column);
				my_board.build();
				my_board.display();
			}
		}
		else if (widget_id == my_menu)
		{
			std::string selection = "";
			int exit_key_stroke = ascii_io::undefined;
			my_menu.get_selection(selection, exit_key_stroke);
			if (exit_key_stroke == ascii_io::enter)
			{
				if (selection != "exit")
				{
					player = selection;
				}
				else
				{
					break;
				}
			}
		}
	}

	ascii_io::show_cursor();

	delete(my_frame);
	ascii_io::ascii_engine_end();
}

