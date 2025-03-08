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
	my_menu.set_spacing_width_multipliers(1, 1);

	// uncomment below to enable line drawing
	//my_frame->enable_dec(true);

	my_menu.add_border(true);
	my_menu.set_spacing(0, 0, 0, 1);
	for (unsigned int i = 0; i < 100; i++)
	{
		my_menu.append_item("Item " + std::to_string(i));
	}
	my_menu.append_item("Exit");
	my_menu.enable_quit(); // can exit menu with 'q' without selecting item
	my_menu.set_alignment("center");

	my_label.add_border(true);
	my_label.set_alignment("center");
	my_label.set_output("Select an Item.");

	ascii_io::hide_cursor();

	my_menu.set_lines_count(-6); // set the number of lines displayed in the menu 
		                         // (negative number will cause menu to use all lines available in frame minus the parameter)
		                         // (positive number will cause menu to always use number of lines specified by the parameter
		                         // (0 will cause the menu to use however many lines required to display all items)
	
	my_menu.separate_items(true); // Causes menu items to be separated by lines inside menu
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
			my_label.refresh();
		}

	}

	ascii_io::show_cursor();
	
	delete(my_frame);
	ascii_io::ascii_engine_end();
}