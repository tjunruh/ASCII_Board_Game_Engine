#include <ascii_io.h>
#include <frame.h>
#include <label.h>
#include <ascii_board.h>
#include <menu.h>


int main()
{
	ascii_io::ascii_engine_init();
	frame* my_frame = new frame();
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
	my_board.load_configuration("board_configs/multi_line_test_cursor_config.txt", "cursor", -1, -1, '*');
	my_board.load_configuration("board_configs/multi_line_test_x_config.txt", "player 1", -1, -1, '*');
	my_board.load_configuration("board_configs/multi_line_test_o_config.txt", "player 2", -1, -1, '*');
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

