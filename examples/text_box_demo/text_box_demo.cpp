#include <ascii_engine/ascii_io.h>
#include <ascii_engine/frame.h>
#include <ascii_engine/label.h>
#include <ascii_engine/text_box.h>
#include <ascii_engine/console.h>
#include <string>

int main()
{
    ascii_io::ascii_engine_init(); // This function should always be called at the beginning of the program to initialize ascii engine

    // - widgets are placed on the frame in the order that they are created
    // - if neither "merge" nor "new line" are passed as a parameter, the widget will be placed on the same line and to the right of the other widgets in the line
    // - "merge" will place the widget below the preceding widget while still being in the same line
    // - "new line" will place the widget below on a new line
    frame* my_frame = new frame();

    // register the widgets in the console for mouse interaction
    console my_console;

    // uncomment below to enable line drawing
    //my_frame->enable_dec(true);

    label label_1(my_frame);
    label_1.set_output("Text box displaying 5 lines at once:");
    label_1.set_alignment("center");
    label_1.set_spacing(3, 0, 1, 1);

    text_box box_1(my_frame, "merge", 5);
    box_1.add_border(true);
    box_1.set_spacing(0, 0, 1, 1);
    my_console.register_widget(&box_1);

    label label_2(my_frame, "merge");
    label_2.set_output("Text box limited to only 10 characters:");
    label_2.set_alignment("center");
    label_2.set_spacing(5, 0, 1, 1);

    text_box box_2(my_frame, "merge", 5);
    box_2.add_border(true);
    box_2.set_max_characters(10);
    box_2.set_spacing(0, 0, 1, 1);
    my_console.register_widget(&box_2);

    label label_3(my_frame, "merge");
    label_3.set_output("Select me to set top left text box displayed lines to 10");
    label_3.add_border(true);
    label_3.set_selectable(true);
    label_3.set_spacing(1, 0, 1, 1);

    label label_4(my_frame);
    label_4.set_output("Text box displaying number of lines in terminal height minus 10");
    label_4.set_alignment("center");
    label_4.set_spacing(3, 0, 1, 1);

    text_box box_3(my_frame, "merge", -10);
    box_3.add_border(true);
    box_3.set_spacing(0, 0, 1, 1);
    my_console.register_widget(&box_3);

    label label_5(my_frame, "new line");
    label_5.set_output("EXIT");
    label_5.set_alignment("center");
    label_5.add_border(true);
    label_5.set_selectable(true);
    label_5.use_spacing_width_multipliers(true);
    label_5.set_spacing_width_multipliers(1.0, 1.0);
    my_console.register_widget(&label_5);

    do
    {
        console::event event = my_console.run();
        if (event.widget_id == label_5 && event.input == ascii_io::mouse_left_released)
        {
            break;
        }

    } while (true);

    delete(my_frame);
    ascii_io::ascii_engine_end(); // This function should always be called at the end of the program to properly shut ascii engine down
}