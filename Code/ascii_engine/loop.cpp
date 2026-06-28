#include "../ascii_engine_dll_files/pch.h"
#include "loop.h"
#include "error_codes.h"
#include "widget_types.h"

#ifdef __linux__
#include <algorithm>
#endif

int loop::start_logging(const std::string& file_path)
{
	int status = log.start_widget_logging(file_path, LOOP);
	return status;
}

int loop::reset_logging(const std::string& file_path)
{
	int status = log.log_reset(file_path, LOOP);
	return status;
}

void loop::stop_logging()
{
	log.stop_widget_logging();
}

int loop::add_widget(label* item)
{
	int status = UNDEFINED;

	if (frame_id == -1)
	{
		frame_id = item->get_parent_frame_id();
	}
	else if (item->get_parent_frame_id() != frame_id)
	{
		status = INVALID_VALUE;
	}

	if (status == UNDEFINED)
	{
		for (unsigned int i = 0; i < label_widgets.size(); i++)
		{
			if (label_widgets[i]->get_id() == item->get_id())
			{
				status = DUPLICATE_ELEMENT;
				break;
			}
		}

		if (status == UNDEFINED)
		{
			label_widgets.push_back(item);
		}
	}

	return status;
}

int loop::add_widget(text_box* item)
{
	int status = UNDEFINED;

	if (frame_id == -1)
	{
		frame_id = item->get_parent_frame_id();
	}
	else if (item->get_parent_frame_id() != frame_id)
	{
		status = INVALID_VALUE;
	}

	if (status == UNDEFINED)
	{
		for (unsigned int i = 0; i < text_box_widgets.size(); i++)
		{
			if (text_box_widgets[i]->get_id() == item->get_id())
			{
				status = DUPLICATE_ELEMENT;
				break;
			}
		}

		if (status == UNDEFINED)
		{
			text_box_widgets.push_back(item);
		}
	}

	return status;
}

int loop::add_widget(menu* item)
{
	int status = UNDEFINED;

	if (frame_id == -1)
	{
		frame_id = item->get_parent_frame_id();
	}
	else if (item->get_parent_frame_id() != frame_id)
	{
		status = INVALID_VALUE;
	}

	if (status == UNDEFINED)
	{
		for (unsigned int i = 0; i < menu_widgets.size(); i++)
		{
			if (menu_widgets[i]->get_id() == item->get_id())
			{
				status = DUPLICATE_ELEMENT;
				break;
			}
		}

		if (status == UNDEFINED)
		{
			menu_widgets.push_back(item);
		}
	}

	return status;
}

int loop::add_widget(ascii_board* item)
{
	int status = UNDEFINED;

	if (frame_id == -1)
	{
		frame_id = item->get_parent_frame_id();
	}
	else if (item->get_parent_frame_id() != frame_id)
	{
		status = INVALID_VALUE;
	}

	if (status == UNDEFINED)
	{
		for (unsigned int i = 0; i < ascii_board_widgets.size(); i++)
		{
			if (ascii_board_widgets[i]->get_id() == item->get_id())
			{
				status = DUPLICATE_ELEMENT;
				break;
			}
		}

		if (status == UNDEFINED)
		{
			ascii_board_widgets.push_back(item);
		}
	}

	return status;
}

loop::event loop::run_loop()
{
	event loop_event;
	initialize_display();
	while (true)
	{
		if (stashed_event.input == ascii_io::undefined)
		{
			loop_event.input = ascii_io::getchar(loop_event.mouse_x_position, loop_event.mouse_y_position);
		}
		else
		{
			loop_event = stashed_event;
			stashed_event.input = ascii_io::undefined;
		}

		loop_label_widgets_handle(loop_event);
		if (exit)
		{
			break;
		}

		loop_text_box_widgets_handle(loop_event);
		if (exit)
		{
			break;
		}

		loop_menu_widgets_handle(loop_event);
		if (exit)
		{
			break;
		}

		loop_ascii_board_widgets_handle(loop_event);
		if (exit)
		{
			break;
		}

		if (loop_event.input != ascii_io::mouse_left_pressed && loop_event.input != ascii_io::scroll_up && loop_event.input != ascii_io::scroll_down)
		{
			break;
		}
	}

	exit = false;
	return loop_event;
}

void loop::initialize_display()
{
	if (label_widgets.size() > 0)
	{
		if (label_widgets[0]->parent_frame->stale())
		{
			label_widgets[0]->display_entire_frame();
		}
		return;
	}

	if (text_box_widgets.size() > 0)
	{
		if (text_box_widgets[0]->parent_frame->stale())
		{
			text_box_widgets[0]->display_entire_frame();
		}
		return;
	}

	if (menu_widgets.size() > 0)
	{
		if (menu_widgets[0]->parent_frame->stale())
		{
			menu_widgets[0]->display_entire_frame();
		}
		return;
	}

	if (ascii_board_widgets.size() > 0)
	{
		if (ascii_board_widgets[0]->parent_frame->stale())
		{
			ascii_board_widgets[0]->display_entire_frame();
		}
	}
}

void loop::loop_label_widgets_handle(event& loop_event)
{
	if (loop_event.input == ascii_io::undefined || loop_event.input == ascii_io::mouse_left_pressed || loop_event.input == ascii_io::scroll_up || loop_event.input == ascii_io::scroll_down)
	{
		for (unsigned int i = 0; i < label_widgets.size(); i++)
		{
			if (label_widgets[i]->inside_widget_space(loop_event.mouse_x_position, loop_event.mouse_y_position))
			{
				loop_event.widget_id = label_widgets[i]->get_id();
				label_widgets[i]->in_runtime_loop = true;
				loop_event.input = label_widgets[i]->scroll();
				label_widgets[i]->in_runtime_loop = false;
				loop_event.mouse_x_position = label_widgets[i]->mouse_x_position;
				loop_event.mouse_y_position = label_widgets[i]->mouse_y_position;
				if (std::count(ascii_io::mouse_keys.begin(), ascii_io::mouse_keys.end(), loop_event.input) != 0)
				{
					loop_event.widget_id = get_widget_id_at_coordinate(label_widgets[i]->mouse_x_position, label_widgets[i]->mouse_y_position);
					if (loop_event.widget_id != -1)
					{
						if (loop_event.widget_id != label_widgets[i]->get_id())
						{
							stashed_event = loop_event;
						}
						exit = true;
					}
				}

				if (exit)
				{
					break;
				}
			}
		}
	}
}

void loop::loop_text_box_widgets_handle(event& loop_event)
{
	if (loop_event.input == ascii_io::undefined || loop_event.input == ascii_io::mouse_left_pressed || loop_event.input == ascii_io::scroll_up || loop_event.input == ascii_io::scroll_down)
	{
		for (unsigned int i = 0; i < text_box_widgets.size(); i++)
		{
			if (text_box_widgets[i]->inside_widget_space(loop_event.mouse_x_position, loop_event.mouse_y_position))
			{
				loop_event.widget_id = text_box_widgets[i]->get_id();
				text_box_widgets[i]->first_key_stroke_initialized = true;
				text_box_widgets[i]->in_runtime_loop = true;
				text_box_widgets[i]->mouse_x_position = loop_event.mouse_x_position;
				text_box_widgets[i]->mouse_y_position = loop_event.mouse_y_position;
				loop_event.input = text_box_widgets[i]->write();
				text_box_widgets[i]->in_runtime_loop = false;
				loop_event.mouse_x_position = text_box_widgets[i]->mouse_x_position;
				loop_event.mouse_y_position = text_box_widgets[i]->mouse_y_position;
				if (std::count(ascii_io::mouse_keys.begin(), ascii_io::mouse_keys.end(), loop_event.input) != 0)
				{
					loop_event.widget_id = get_widget_id_at_coordinate(text_box_widgets[i]->mouse_x_position, text_box_widgets[i]->mouse_y_position);
					if (loop_event.widget_id != -1)
					{
						if (loop_event.widget_id != text_box_widgets[i]->get_id())
						{
							stashed_event = loop_event;
						}
						exit = true;
					}
				}
				else
				{
					stashed_event = loop_event;
					stashed_event.input = ascii_io::undefined;
					exit = true;
				}

				if (exit)
				{
					break;
				}
			}
		}
	}
}

void loop::loop_menu_widgets_handle(event& loop_event)
{
	if (loop_event.input == ascii_io::undefined || loop_event.input == ascii_io::mouse_left_pressed || loop_event.input == ascii_io::scroll_up || loop_event.input == ascii_io::scroll_down || ascii_io::is_dragging())
	{
		for (unsigned int i = 0; i < menu_widgets.size(); i++)
		{
			if (menu_widgets[i]->inside_widget_space(loop_event.mouse_x_position, loop_event.mouse_y_position))
			{
				loop_event.widget_id = menu_widgets[i]->get_id();
				std::string discarded_selection = "";
				menu_widgets[i]->first_key_stroke_initialized = true;
				menu_widgets[i]->in_runtime_loop = true;
				menu_widgets[i]->mouse_x_position = loop_event.mouse_x_position;
				menu_widgets[i]->mouse_y_position = loop_event.mouse_y_position;
				menu_widgets[i]->get_selection(discarded_selection, loop_event.input);
				menu_widgets[i]->in_runtime_loop = false;
				loop_event.mouse_x_position = menu_widgets[i]->mouse_x_position;
				loop_event.mouse_y_position = menu_widgets[i]->mouse_y_position;
				if (std::count(ascii_io::mouse_keys.begin(), ascii_io::mouse_keys.end(), loop_event.input) != 0)
				{
					loop_event.widget_id = get_widget_id_at_coordinate(menu_widgets[i]->mouse_x_position, menu_widgets[i]->mouse_y_position);
					if (loop_event.widget_id != -1)
					{
						if (loop_event.widget_id != menu_widgets[i]->get_id())
						{
							stashed_event = loop_event;
						}
						exit = true;
					}
				}
				else
				{
					stashed_event = loop_event;
					stashed_event.input = ascii_io::undefined;
					exit = true;
				}

				menu_widgets[i]->display();

				if (exit)
				{
					break;
				}
			}
		}
	}
}

void loop::loop_ascii_board_widgets_handle(event& loop_event)
{
	if (loop_event.input == ascii_io::undefined || loop_event.input == ascii_io::mouse_left_pressed)
	{
		for (unsigned int i = 0; i < ascii_board_widgets.size(); i++)
		{
			if (ascii_board_widgets[i]->inside_widget_space(loop_event.mouse_x_position, loop_event.mouse_y_position))
			{
				loop_event.widget_id = ascii_board_widgets[i]->get_id();
				exit = true;
				break;
			}
		}
	}
}

int loop::get_widget_id_at_coordinate(int x, int y)
{
	int id = -1;
	for (unsigned int i = 0; i < label_widgets.size(); i++)
	{
		if (label_widgets[i]->inside_widget_space(x, y))
		{
			return label_widgets[i]->get_id();
		}
	}

	for (unsigned int i = 0; i < text_box_widgets.size(); i++)
	{
		if (text_box_widgets[i]->inside_widget_space(x, y))
		{
			return text_box_widgets[i]->get_id();
		}
	}

	for (unsigned int i = 0; i < menu_widgets.size(); i++)
	{
		if (menu_widgets[i]->inside_widget_space(x, y))
		{
			return menu_widgets[i]->get_id();
		}
	}

	for (unsigned int i = 0; i < ascii_board_widgets.size(); i++)
	{
		if (ascii_board_widgets[i]->inside_widget_space(x, y))
		{
			return ascii_board_widgets[i]->inside_widget_space(x, y);
		}
	}

	return id;
}