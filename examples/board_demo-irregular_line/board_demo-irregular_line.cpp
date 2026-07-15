#include <ascii_engine/ascii_io.h>
#include <ascii_engine/frame.h>
#include <ascii_engine/label.h>
#include <ascii_engine/ascii_board.h>
#include <ascii_engine/menu.h>
#include <ascii_engine/console.h>
#include <ascii_engine/error_codes.h>
#include <ascii_engine/format_tools.h>
#include <string>


int main()
{
	ascii_io::ascii_engine_init();
	frame* my_frame = new frame();
	ascii_board my_board(my_frame, "board_configs/irregular_line_test_board_config.txt", "default");
	label my_label(my_frame);
	menu my_menu(my_frame, "merge");

	my_frame->enable_color(true);

	my_label.set_spacing(2, 2, 0, 0);
	my_label.set_alignment("center");
	my_label.set_output("ASCII Board Demo");

	my_board.set_alignment("center");
	my_board.load_configuration("board_configs/irregular_line_test_cursor_config.txt", "cursor", -1, -1, '*', format_tools::green, format_tools::none, false);
	my_board.load_configuration("board_configs/irregular_line_test_x_config.txt", "player 1", -1, -1, '*', format_tools::blue, format_tools::none, false);
	my_board.load_configuration("board_configs/irregular_line_test_o_config.txt", "player 2", -1, -1, '*', format_tools::red, format_tools::none, false);
	my_board.set_spacing(2, 2, 0, 10);
	int cursor_row = 2;
	int cursor_column = 1;
	my_board.activate_configuration("cursor", cursor_row, cursor_column);
	my_board.build();

	my_menu.set_spacing(2, 0, 0, 0);
	my_menu.add_border(true);
	my_menu.append_item("player 1");
	my_menu.append_item("player 2");
	my_menu.append_item("exit");
	my_menu.set_alignment("center");
	my_menu.enable_quit(true);
	my_menu.build();

	// register the widgets in the console for mouse interaction
	console my_console;

	my_console.register_widget(&my_board);
	my_console.register_widget(&my_menu);

	std::string player = "player 1";

	while (1)
	{
		console::event event = my_console.run();
		if (event.widget_id == my_board)
		{
			my_board.deactivate_configuration("cursor", cursor_row, cursor_column);
			if (event.input == ascii_io::mouse_left_released)
			{
				int new_cursor_row;
				int new_cursor_column;
				int status = my_board.get_tile_coordinate_from_mouse_position(event.mouse_x_position, event.mouse_y_position, new_cursor_row, new_cursor_column);
				if (status == SUCCESS)
				{
					cursor_row = new_cursor_row;
					cursor_column = new_cursor_column;
				}
			}
			else if (event.input == ascii_io::enter)
			{
				my_board.activate_configuration(player, cursor_row, cursor_column);
			}
			else if (event.input == ascii_io::up)
			{
				if (cursor_row - 1 >= 0)
				{
					cursor_row--;
				}
			}
			else if (event.input == ascii_io::down)
			{
				if (cursor_row + 1 < my_board.get_number_of_rows())
				{
					cursor_row++;
				}
			}
			else if (event.input == ascii_io::right)
			{
				if (cursor_column + 1 < my_board.get_number_of_columns())
				{
					cursor_column++;
				}
			}
			else if (event.input == ascii_io::left)
			{
				if (cursor_column - 1 >= 0)
				{
					cursor_column--;
				}
			}

			my_board.activate_configuration("cursor", cursor_row, cursor_column);
			my_board.build();
			my_board.display();
		}
		else if (event.widget_id == my_menu)
		{
			if (event.input == ascii_io::enter || event.input == ascii_io::mouse_left_released)
			{
				std::string selection = my_menu.get_selection();
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

	delete(my_frame);
	ascii_io::ascii_engine_end();
}

