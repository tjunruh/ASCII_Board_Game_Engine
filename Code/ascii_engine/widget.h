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
#elif __linux__
#define WIDGET_API
#endif

class widget
{
public:
	WIDGET_API widget(frame* parent, std::string special_operation="none");
	WIDGET_API virtual ~widget();
	WIDGET_API void set_alignment(std::string alignment);
	WIDGET_API void set_spacing(int top, int bottom, int left, int right);
	WIDGET_API void set_border_spacing(int top, int bottom, int left, int right);
	WIDGET_API void set_vertical_border(char border);
	WIDGET_API void set_horizontal_border(char border);
	WIDGET_API void set_corner_border(char border);
	WIDGET_API void set_highlight_character(char character);
	WIDGET_API void set_width_multiplier(float multiplier);
	WIDGET_API void set_spacing_width_multipliers(float left_multiplier, float right_multiplier);
	WIDGET_API void set_border_spacing_width_multipliers(float left_multiplier, float right_multiplier);
	WIDGET_API void add_border(bool border);
	WIDGET_API void use_spacing_width_multipliers(bool use);
	WIDGET_API void set_selectable(bool selectable);
	WIDGET_API bool is_selectable();
	WIDGET_API void get_spacing(int& top, int& bottom, int& left, int& right);
	WIDGET_API void get_border_spacing(int& top, int& bottom, int& left, int& right);
	WIDGET_API char get_vertical_border();
	WIDGET_API char get_horizontal_border();
	WIDGET_API char get_corner_border();
	WIDGET_API char get_highlight_character();
	WIDGET_API float get_width_multiplier();
	WIDGET_API void get_spacing_width_multipliers(float& left_multiplier, float& right_multiplier);
	WIDGET_API void get_border_spacing_width_multipliers(float& left_multiplier, float& right_multiplier);
	WIDGET_API unsigned int get_width(bool include_spacing=false);
	WIDGET_API unsigned int get_height(bool include_spacing=false);
	WIDGET_API int get_x_origin();
	WIDGET_API int get_y_origin();
	WIDGET_API int get_widget_type();
	WIDGET_API std::string get_output();
	WIDGET_API std::string get_displayed_output();
	WIDGET_API std::string get_alignment();
	WIDGET_API int start_logging(const std::string& file_path);
	WIDGET_API void stop_logging();
	WIDGET_API int reset_logging(const std::string& file_path);
	operator int() { return item.id; }
protected:
	void set_output_to_frame(const std::string& text, bool mark_stale = true);
	void set_widget_type(int type);
	bool frame_stale();
	void mark_frame_as_stale();
	void frame_display();
	bool dec_enabled();
	bool color_enabled();
	void set_index_colors(const std::vector<format_tools::index_format>& index_colors);
	std::vector<format_tools::index_format> get_index_colors();
	std::vector<format_tools::index_format> get_displayed_index_colors();
	std::vector<format_tools::index_format> dec_format(std::string& format_content, unsigned int line_length=0);
	int get_default_foreground_color();
	int get_default_background_color();
	void widget_display(std::vector<std::string> output_lines, bool can_use_dec = false, bool can_use_color = false, const std::vector<format_tools::index_format>& colors = {});
	void set_line_constraint(bool line_constraint);
	void set_column_constraint(bool column_constraint);
	void set_displayed_lines(unsigned int displayed_lines);
	void set_line_subtraction_from_terminal_height(unsigned int line_subtraction_from_terminal_height);
	void set_line_compression_amount(unsigned int line_compression_amount);
	void set_top_line(unsigned int top_line);
	void set_left_column(unsigned int left_column);
	void get_displayed_output(std::vector<std::string>& displayed_output);
	void get_displayed_output(std::vector<std::string>& displayed_output, std::vector<format_tools::index_format>& colors);
	bool get_line_constraint();
	bool get_column_constraint();
	unsigned int get_displayed_lines();
	unsigned int get_line_subtraction_from_terminal_height();
	unsigned int get_line_compression_amount();
	unsigned int get_top_line();
	unsigned int get_left_column();
	unsigned int get_lines_count(bool only_displayed = true);
	unsigned int get_columns_count();
	void set_line_character(char character, unsigned int line, unsigned int character_index);
	void update_lines();
	unsigned int get_line_length(unsigned int line);
	void insert_character_in_output(unsigned int index, char character);
	void erase_character_in_output(unsigned int index);
	unsigned int get_output_length();
	void dynamically_adjust_displayed_lines();
	void bound_top_line();
	void display_entire_frame();

#ifdef __linux__
	void dec_print(const std::string& input);
#endif
	logger log;
private:
	frame *parent_frame;
	frame::widget_info item;
};