#include <ascii_io.h>
#include <frame.h>
#include <label.h>
#include <text_box.h>
#include <menu.h>

int main()
{
	ascii_io::ascii_engine_init(); // This function should always be called at the beginning of the program to initialize ascii engine

	// - widgets are placed on the frame in the order that they are created
	// - if neither "merge" nor "new line" are passed as a parameter, the widget will be placed on the same line and to the right of the other widgets in the line
	// - "merge" will place the widget below the preceding widget while still being in the same line
	// - "new line" will place the widget below on a new line
	frame* my_frame = new frame();
	label my_label(my_frame);
	label label_over_text_box(my_frame);
	text_box my_text_box(my_frame, "merge", 3);
	menu my_menu(my_frame, "new line");

	// uncomment below to enable line drawing
	//my_frame->enable_dec(true);

	my_label.add_border(true);
	my_label.set_spacing(5, 5, 25, 10);
	my_label.set_output("\n\nASCII ENGINE!!!\n\n");
	my_label.set_selectable(true); // label widget is not selectable by default

	label_over_text_box.set_spacing(5, 0, 25, 15);
	label_over_text_box.set_output("Write Something Here");
	label_over_text_box.set_alignment("center");
	my_text_box.add_border(true);
	my_text_box.set_spacing(0, 0, 25, 15);

	my_menu.set_spacing(5, 5, 25, 25);
	my_menu.add_border(true);
	my_menu.set_border_spacing(2, 2, 10, 10);
	my_menu.append_item("play");
	my_menu.append_item("win");
	my_menu.append_item("lose");
	my_menu.append_item("exit");
	my_menu.set_alignment("center");
	my_menu.enable_quit(true); // can exit menu with 'q' without selecting item
	my_menu.build();

	ascii_io::hide_cursor();

	my_frame->display();
	while (1)
	{
		int selection = my_frame->get_selection();

		if (selection == my_label)
		{
			my_label.set_output("\n\nGo and make a game with ascii engine!\n\n");
		}
		else if (selection == my_text_box)
		{
			int exit_key = my_text_box.write();
			ascii_io::hide_cursor(); // cursor will be shown after writing in the text box
			// by default, exit key from text box could be enter or escape
			if (exit_key == ascii_io::ESC)
			{
				my_text_box.clear();
			}
			else if (exit_key == ascii_io::enter)
			{
				std::string user_writing = my_text_box.get_text();
				my_label.set_output(user_writing);
			}
		}
		else if (selection == my_menu)
		{
			std::string menu_selection = "";
			int menu_exit_key = ascii_io::undefined;
			my_menu.get_selection(menu_selection, menu_exit_key);
			if (menu_exit_key == ascii_io::enter)
			{
				if (menu_selection == "play")
				{
					my_label.set_output("\n\nLet's play!\n\n");
				}
				else if (menu_selection == "win")
				{
					my_label.set_output("\n\nYou won!\n\n");
				}
				else if (menu_selection == "lose")
				{
					my_label.set_output("\n\nYou lost.\n\n");
				}
				else if (menu_selection == "exit")
				{
					break;
				}
			}
		}
	}

	ascii_io::show_cursor();
	
	delete(my_frame);
	ascii_io::ascii_engine_end(); // This function should always be called at the end of the program to properly shut ascii engine down
}