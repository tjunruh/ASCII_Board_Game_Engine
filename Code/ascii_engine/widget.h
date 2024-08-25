#pragma once
#include <string>
#include <vector>
#include "frame.h"
#include "logger.h"
#include "format_tools.h"

#ifdef _WIN32
#ifdef WIDGET_EXPORTS
#define WIDGET_API __declspec(dllexport)
#else
#define WIDGET_API __declspec(dllimport)
#endif
#endif

class widget
{
public:
	widget(frame* parent, std::string special_operation="none");
	void set_alignment(std::string alignment);
	void set_spacing(int top, int bottom, int left, int right);
	void set_border_spacing(int top, int bottom, int left, int right);
	void set_vertical_border(char border);
	void set_horizontal_border(char border);
	void set_corner_border(char border);
	void set_highlight_character(char character);
	void add_border();
	void refresh();
	void selectable();
	void unselectable();
	unsigned int get_width(bool include_spacing=false);
	unsigned int get_height(bool include_spacing=false);
	int get_x_origin();
	int get_y_origin();
	int get_widget_type();
	std::string get_output();
	std::string get_alignment();
	operator int() { return widget_id; }
protected:
	void set_output_to_frame(const std::string& text);
	void set_widget_type(int type);
	bool frame_stale();
	void frame_display();
	bool dec_enabled();
	bool color_enabled();
	void set_index_colors(const std::vector<format_tools::index_format>& index_colors);
	std::vector<format_tools::index_format> get_index_colors();
	std::vector<format_tools::index_format> dec_format(std::string& format_content, unsigned int line_length=0);
	int get_default_foreground_color();
	int get_default_background_color();

#ifdef __linux__
	void dec_print(const std::string& input);
#endif
	logger log;
private:
	frame *parent_frame;
	int widget_id;
	int widget_type = WIDGET;
};