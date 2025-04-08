#pragma once
#include <string>
#include <vector>
#include "ascii_io.h"
#include "widget_types.h"
#include "format_tools.h"
#include "logger.h"
#include "dec_formatter.h"

#ifdef _WIN32
#ifdef FRAME_EXPORTS
#define FRAME_API __declspec(dllexport)
#else
#define FRAME_API __declspec(dllimport)
#endif
#elif __linux__
#define FRAME_API
#endif

class frame
{
public:
	friend class widget;
	friend class spacer;
	FRAME_API frame(bool start_logger=false, const std::string& logging_file_path="frame.log");
	FRAME_API void display();
	FRAME_API bool stale();
	FRAME_API void set_controls(int select, int quit, int up, int down, int left, int right);
	FRAME_API void get_controls(int& select, int& quit, int& up, int& down, int& left, int& right);
	FRAME_API int get_selection();
	FRAME_API void set_spacer_character(char character);
	FRAME_API char get_spacer_character();
	FRAME_API void enable_dec(bool enable);
	FRAME_API bool dec_enabled();
	FRAME_API void enable_color(bool enable);
	FRAME_API bool color_enabled();
	FRAME_API void set_dec_format_characters(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char);
	FRAME_API void get_dec_format_characters(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char);
	FRAME_API void set_default_background_color(int color);
	FRAME_API void set_default_foreground_color(int color);
	FRAME_API int get_default_background_color();
	FRAME_API int get_default_foreground_color();
	FRAME_API void use_fake_console_dimensions();
	FRAME_API void use_true_console_dimensions();
	FRAME_API void set_fake_console_width(int width);
	FRAME_API void set_fake_console_height(int height);
	FRAME_API std::string get_frame_output();
	FRAME_API int start_logging(const std::string& file_path);
	FRAME_API void stop_logging();
	FRAME_API int reset_logging(const std::string& file_path);

private:
	dec_formatter dec;
	struct widget_info
	{
		int id = -1;
		std::string output = "";
		int row = 0;
		int column = 0;
		std::string alignment = "left";
		int top_spacing = 0;
		int bottom_spacing = 0;
		int right_spacing = 0;
		int left_spacing = 0;
		float right_width_multiplier = 0.0;
		float left_width_multiplier = 0.0;
		int top_border_spacing = 0;
		int bottom_border_spacing = 0;
		int right_border_spacing = 0;
		int left_border_spacing = 0;
		float right_border_width_multiplier = 0.0;
		float left_border_width_multiplier = 0.0;
		bool add_border = false;
		bool use_spacing_width_multipliers = false;
		char highlight_character = '#';
		char vertical_border = '|';
		char horizontal_border = '-';
		char corner_border = '.';
		int widget_type = WIDGET;
		int x_origin = -1;
		int y_origin = -1;
		unsigned int lines_count = 0;
		int level = 0;
		float width_multiplier = 1.0;
		bool selectable = false;
		unsigned int top_line = 0;
		unsigned int displayed_lines = 0;
		unsigned int line_subtraction_from_terminal_height = 0;
		unsigned int line_compression_amount = 0;
		unsigned int left_column = 0;
		bool line_constraint = false;
		bool column_constraint = false;
		bool line_edited = false;
		std::vector<format_tools::coordinate_format> coordinate_colors;
		std::vector<format_tools::index_format> index_colors;
		std::vector<std::string> lines;
	};

	const std::string special_operation_new_line = "new line";
	const std::string special_operation_merge = "merge";
	const std::string special_operation_none = "none";
	int add_widget();
	int set_position(int id, int row, int column, int level);
	int append(int id, const std::string& special_operation="none");
	int set_output(int id, const std::string& output, bool mark_frame_stale);
	int set_alignment(int id, const std::string& alignment);
	int set_spacing(int id, int top, int bottom, int left, int right);
	int set_border_spacing(int id, int top, int bottom, int left, int right);
	int set_widget_type(int id, int type);
	int set_vertical_border(int id, char border);
	int set_horizontal_border(int id, char border);
	int set_corner_border(int id, char border);
	int set_highlight_character(int id, char character);
	int set_x_origin(int id, int x_origin);
	int set_y_origin(int id, int y_origin);
	int set_lines_count(int id, unsigned int lines_count);
	int set_width_multiplier(int id, float multiplier);
	int set_spacing_width_multipliers(int id, float left_multiplier, float right_multiplier);
	int set_border_spacing_width_multipliers(int id, float left_multiplier, float right_multiplier);
	int set_selectable(int id, bool selectable);
	int set_coordinate_colors(int id, std::vector<format_tools::coordinate_format> coordinate_colors);
	int set_index_colors(int id, std::vector<format_tools::index_format> index_colors);
	int set_line_constraint(int id, bool line_constraint);
	int set_top_line(int id, unsigned int top_line);
	int set_column_constraint(int id, bool column_constraint);
	int set_left_column(int id, unsigned int left_column);
	int set_displayed_lines(int id, unsigned int displayed_lines);
	int set_line_subtraction_from_terminal_height(int id, unsigned int line_subtraction_from_terminal_height);
	int set_line_compression_amount(int id, unsigned int line_compression_amount);
	int set_lines(int id, const std::vector<std::string>& lines);
	int set_line_character(int id, char character, unsigned int line, unsigned int character_index);
	int set_line_edited(int id, bool line_edited);
	int add_border(int id, bool border);
	int use_spacing_width_multipliers(int id, bool use);
	void highlight(int row, int column, int level);
	void unhighlight(int row, int column, int level);
	void keep_point_in_console_bounds(int& x, int& y);
	bool widget_exists(int id);
	bool widget_exists(int row, int column);
	int get_levels(int row, int column);
	int get_lines_count(int id, unsigned int& lines_count, bool only_displayed=true);
	int get_x_origin(int id, int& x_origin);
	int get_y_origin(int id, int& y_origin);
	int get_alignment(int id, std::string& allignment);
	int get_spacing(int id, int& top, int& bottom, int& left, int& right);
	int get_border_spacing(int id, int& top, int& bottom, int& left, int& right);
	int get_vertical_border(int id, char& border);
	int get_horizontal_border(int id, char& border);
	int get_corner_border(int id, char& border);
	int get_highlight_character(int id, char& highlight_character);
	int get_width_multiplier(int id, float& multiplier);
	int get_spacing_width_multipliers(int id, float& left_multiplier, float& right_multiplier);
	int get_border_spacing_width_multipliers(int id, float& left_multiplier, float& right_multiplier);
	int get_selectability(int id, bool& selectable);
	int get_top_line(int id, unsigned int& top_line);
	int get_left_column(int id, unsigned int& left_column);
	int get_displayed_lines(int id, unsigned int& displayed_lines);
	int get_line_subtraction_from_terminal_height(int id, unsigned int& line_subtraction_from_terminal_height);
	int get_line_compression_amount(int id, unsigned int& line_compression_amount);
	float get_greatest_width_multiplier_at_coordinate(int row, int column);
	float get_width_weight(const widget_info& item, float multiplier);
	int get_index_colors(int id, std::vector<format_tools::index_format>& index_colors);
	int get_line_constraint(int id, bool& line_constraint);
	int get_column_constraint(int id, bool& column_constraint);
	int get_line_length(int id, unsigned int line, unsigned int& length);
	int generate_widget_id();
	std::vector<int> get_row_ids(int row);
	std::vector<std::vector<int>> sort_row_ids(std::vector<int> ids);
	int get_min_column_index(const std::vector<widget_info>& widget_vec);
	int get_min_level_index(const std::vector<widget_info>& widget_vec);
	bool in_range(int value, int begin, int end);
	int get_output(int id, std::string& output);
	int get_widget(int id, widget_info& return_value);
	int get_widget(int row, int column, int level, widget_info& return_value);
	unsigned int get_widget_width(const widget_info& item, bool include_spacing);
	unsigned int get_greatest_widget_width_at_coordinate(const widget_info& item, bool include_spacing);
	int get_widget_width(int id, unsigned int& width, bool include_spacing);
	unsigned int get_widget_height(const widget_info& item, bool include_spacing);
	int get_widget_height(int id, unsigned int& width, bool include_spacing);
	void constrain_lines(const widget_info& item, std::vector<std::string>& widget_lines);
	void constrain_colors(const widget_info& item, std::vector<format_tools::coordinate_format>& colors);
	void update_widget_output_from_lines(widget_info& item);
	std::vector<std::string> build_core_widget_lines(widget_info& item);
	std::vector<std::string> build_widget_lines(int id);
	int get_displayed_output(int id, std::vector<std::string>& displayed_output);
	int get_displayed_colors(int id, std::vector<format_tools::index_format>& colors);
	bool element_exists(const std::vector<int>& storage, int element);
	unsigned int get_total_rows();
	unsigned int get_columns_in_row(int row);
	std::string generate_frame_output();
	void set_widget_origins();
	void translate_coordinate_colors_to_frame();
	bool is_selectable(int row, int column, int level);
	bool is_selectable(int id);
	bool initialize_selection(int& row, int& column, int& level);
	bool get_nearest_selectable_in_row(int& row, int& column, int& level, widget_info item, int search_row);
	void up_handle(int& selected_row, int& selected_column, int& selected_level);
	void down_handle(int& selected_row, int& selected_column, int& selected_level);
	void right_handle(int& selected_row, int& selected_column, int& selected_level);
	void left_handle(int& selected_row, int& selected_column, int& selected_level);
	void generate_border(const widget_info& item, std::vector<std::string>& lines);
	bool only_widget_at_coordinate(const widget_info& item);
	void mark_as_stale();
	int insert_character_in_output(int id, unsigned int index, char character);
	int erase_character_in_output(int id, unsigned int index);
	int get_output_length(int id, unsigned int& length);
	void bound_top_line(widget_info& item);
	void dynamically_adjust_displayed_lines(widget_info& item);
	std::vector<format_tools::index_format> dec_format(std::string& format_content, unsigned int line_length=0);

#ifdef __linux__
	void dec_print(const std::string& input);
#endif

	std::vector<widget_info> widgets;
	int _select = ascii_io::enter;
	int _up = ascii_io::up;
	int _down = ascii_io::down;
	int _right = ascii_io::right;
	int _left = ascii_io::left;
	int _quit = ascii_io::q;
	int append_row = 0;
	int append_column = -1;
	int append_level = 0;
	bool display_stale = true;
	std::vector<unsigned int> row_heights;
	logger log;
	char spacer_character = '-';
	bool _dec_enabled = false;
	bool _color_enabled = false;
	bool _use_fake_console_dimensions = false;
	int _fake_console_width = 0;
	int _fake_console_height = 0;
	int default_foreground_color = format_tools::white;
	int default_background_color = format_tools::black;
	std::vector<format_tools::coordinate_format> color_regions;
	int terminal_x = -1;
	int terminal_y = -1;
	int previous_x = -2;
	int previous_y = -2;
#ifdef WIN32
	std::string previous_output = "";
#endif
};
