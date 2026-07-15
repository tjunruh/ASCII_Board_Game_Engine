#pragma once
#include "ascii_io.h"
#include "label.h"
#include "text_box.h"
#include "menu.h"
#include "ascii_board.h"
#include <vector>

#ifdef _WIN32
#ifdef CONSOLE_EXPORTS
#define CONSOLE_API __declspec(dllexport)
#else
#define CONSOLE_API __declspec(dllimport)
#endif
#elif __linux__
#define CONSOLE_API
#endif

class console
{
public:
	struct event
	{
		int widget_id = -1;
		int input = ascii_io::undefined;
		int mouse_x_position = -1;
		int mouse_y_position = -1;
	};

	CONSOLE_API int register_widget(label* item);
	CONSOLE_API int register_widget(text_box* item);
	CONSOLE_API int register_widget(menu* item);
	CONSOLE_API int register_widget(ascii_board* item);
	CONSOLE_API event run();

private:
	void initialize_display();
	void label_widgets_handle(event& loop_event);
	void text_box_widgets_handle(event& loop_event);
	void menu_widgets_handle(event& loop_event);
	void ascii_board_widgets_handle(event& loop_event);
	int get_widget_id_at_coordinate(int x, int y);
	std::vector<label*> label_widgets;
	std::vector<text_box*> text_box_widgets;
	std::vector<menu*> menu_widgets;
	std::vector<ascii_board*> ascii_board_widgets;
	int frame_id = -1;
	bool exit = false;
	event stashed_event;
	logger log;
	int last_widget_id = 0;
};