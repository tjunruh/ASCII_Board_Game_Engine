#include <ascii_engine/ascii_io.h>
#include <ascii_engine/frame.h>
#include <ascii_engine/label.h>
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
    my_frame->enable_color(true);

    // register the widgets in the console for mouse interaction
    console my_console;

    // uncomment below to enable line drawing
    //my_frame->enable_dec(true);

    label label_1(my_frame);
    label_1.set_output("Foreground color sample label:");
    label_1.set_spacing(3, 0, 1, 1);
    my_console.register_widget(&label_1);

    std::string foreground_color_output = "Foreground colors supported:\n";
    foreground_color_output += "<black_foreground><white_background>black<no_color> \n";
    foreground_color_output += "<red_foreground>red<no_color> \n";
    foreground_color_output += "<green_foreground>green<no_color> \n";
    foreground_color_output += "<yellow_foreground>yellow<no_color> \n";
    foreground_color_output += "<blue_foreground>blue<no_color> \n";
    foreground_color_output += "<magenta_foreground>magenta<no_color> \n";
    foreground_color_output += "<cyan_foreground>cyan<no_color> \n";
    foreground_color_output += "<white_foreground>white<no_color> ";

    label label_2(my_frame, "merge");
    label_2.set_output(foreground_color_output);
    label_2.set_spacing(0, 0, 1, 1);
    label_2.add_border(true);
    my_console.register_widget(&label_2);

    label label_3(my_frame, "merge");
    label_3.set_output("Label displaing 5 lines at once:");
    label_3.set_spacing(3, 0, 1, 1);
    my_console.register_widget(&label_3);

    label label_4(my_frame, "merge", 5);
    label_4.set_output("1\n2\n3\n4\n5\n6\n7\n8\n9\n10");
    label_4.set_alignment("center");
    label_4.set_spacing(0, 0, 1, 1);
    label_4.set_selectable(true);
    label_4.add_border(true);
    my_console.register_widget(&label_4);

    label label_5(my_frame, "merge");
    label_5.set_output("Select me to set above label lines count to 10");
    label_5.set_spacing(1, 0, 1, 1);
    label_5.set_selectable(true);
    label_5.add_border(true);
    my_console.register_widget(&label_5);

    label label_6(my_frame, "merge");
    label_6.set_output("EXIT");
    label_6.set_spacing(1, 0, 1, 1);
    label_6.add_border(true);
    label_6.set_selectable(true);
    my_console.register_widget(&label_6);

    label label_7(my_frame);
    label_7.set_output("Background color sample label:");
    label_7.set_spacing(3, 0, 1, 1);
    my_console.register_widget(&label_7);

    std::string background_color_output = "Background colors supported:\n";
    background_color_output += "<black_background>black<no_color> \n";
    background_color_output += "<red_background>red<no_color> \n";
    background_color_output += "<green_background>green<no_color> \n";
    background_color_output += "<yellow_background>yellow<no_color> \n";
    background_color_output += "<blue_background>blue<no_color> \n";
    background_color_output += "<magenta_background>magenta<no_color> \n";
    background_color_output += "<cyan_background>cyan<no_color> \n";
    background_color_output += "<white_background><black_foreground>white<no_color> ";

    label label_8(my_frame, "merge");
    label_8.set_output(background_color_output);
    label_8.set_spacing(0, 0, 1, 1);
    label_8.add_border(true);
    my_console.register_widget(&label_8);

    label label_9(my_frame, "merge");
    label_9.set_output("Label displaying number of lines in terminal height minus 22");
    label_9.set_spacing(3, 0, 1, 1);
    my_console.register_widget(&label_9);

    label label_10(my_frame, "merge", -22);
    label_10.set_output("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50");
    label_10.set_alignment("center");
    label_10.set_spacing(0, 0, 1, 1);
    label_10.add_border(true);
    label_10.set_selectable(true);
    my_console.register_widget(&label_10);

    do
    {
        console::event event = my_console.run();
        if (event.widget_id == label_5 && event.input == ascii_io::mouse_left_released)
        {
            label_3.set_output("Label displaing 10 lines at once:");
            label_4.set_lines_count(10);
        }
        else if (event.widget_id == label_6 && event.input == ascii_io::mouse_left_released)
        {
            break;
        }
    } while (true);

    delete(my_frame);
    ascii_io::ascii_engine_end(); // This function should always be called at the end of the program to properly shut ascii engine down
}