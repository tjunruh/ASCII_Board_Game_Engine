#pragma once
#include "ascii_io.h"
#include "label.h"
#include "text_box.h"
#include "menu.h"
#include "ascii_board.h"
#include "logger.h"
#include <vector>

#ifdef _WIN32
#ifdef LOOP_EXPORTS
#define LOOP_API __declspec(dllexport)
#else
#define LOOP_API __declspec(dllimport)
#endif
#elif __linux__
#define LOOP_API
#endif

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

	LOOP_API int start_logging(const std::string& file_path);
	LOOP_API int reset_logging(const std::string& file_path);
	LOOP_API void stop_logging();
	LOOP_API int add_widget(label* item);
	LOOP_API int add_widget(text_box* item);
	LOOP_API int add_widget(menu* item);
	LOOP_API int add_widget(ascii_board* item);
	LOOP_API event run_loop();

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