#include <ascii_io.h>
#include <frame.h>
#include <menu.h>
#include <label.h>
#include <string>

int main()
{
	ascii_io::ascii_engine_init();

	// - widgets are placed on the frame in the order that they are created
	// - if neither "merge" nor "new line" are passed as a parameter, the widget will be placed on the same line and to the right of the other widgets in the line
	// - "merge" will place the widget below the preceding widget while still being in the same line
	// - "new line" will place the widget below on a new line
	frame* my_frame = new frame();
	menu my_menu(my_frame);
	label my_label(my_frame, "new line");

	my_menu.use_spacing_width_multipliers(true);
	my_menu.set_spacing_width_multipliers(0.5, 0.5);// reduce spacer width since menu will take up more width with labels included

	// uncomment below to enable line drawing
	//my_frame->enable_dec(true);

	my_menu.add_border(true);
	my_menu.set_spacing(0, 0, 0, 1);
	for (unsigned int i = 0; i < 10; i++)
	{
		my_menu.append_item(std::to_string(9 - i));
		my_menu.set_item_label(std::to_string(9 - i), "line " + std::to_string(i) + "    Select to jump to line " + std::to_string(9 - i)); // Add label for item
	}
	my_menu.append_item("Exit");
	my_menu.enable_quit(true); // can exit menu with 'q' without selecting item
	my_menu.set_alignment("center");

	my_label.add_border(true);
	my_label.set_alignment("center");
	my_label.set_output("Select an Item.");

	ascii_io::hide_cursor();
	my_menu.build();

	my_frame->display();
	while (1)
	{
		std::string selection = "";
		int key = ascii_io::undefined;
		my_menu.get_selection(selection, key);
		if (selection == "Exit")
		{
			break;
		}
		else
		{
			my_label.set_output(selection + " was selected.");
			my_label.display();
			my_menu.set_cursor_item(stoi(selection));
		}

	}

	ascii_io::show_cursor();
	
	delete(my_frame);
	ascii_io::ascii_engine_end();
}