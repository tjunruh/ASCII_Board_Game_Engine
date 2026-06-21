#pragma once
#include "ascii_io.h"
#include "label.h"
#include "text_box.h"
#include "menu.h"
#include "ascii_board.h"
#include "logger.h"
#include <vector>

class loop
{
public:
	struct event
	{
		int widget_id = -1;
		int input = ascii_io::undefined;
		int mouse_x_position = -1;
		int mouse_y_position = -1;
	};

	int start_logging(const std::string& file_path);
	int reset_logging(const std::string& file_path);
	void stop_logging();
	int add_widget(label* item);
	int add_widget(text_box* item);
	int add_widget(menu* item);
	int add_widget(ascii_board* item);
	event run_loop();

private:
	void initialize_display();
	void loop_label_widgets_handle(event& loop_event);
	void loop_text_box_widgets_handle(event& loop_event);
	void loop_menu_widgets_handle(event& loop_event);
	void loop_ascii_board_widgets_handle(event& loop_event);
	std::vector<label*> label_widgets;
	std::vector<text_box*> text_box_widgets;
	std::vector<menu*> menu_widgets;
	std::vector<ascii_board*> ascii_board_widgets;
	int frame_id = -1;
	bool exit = false;
	event stashed_event;
	logger log;
};