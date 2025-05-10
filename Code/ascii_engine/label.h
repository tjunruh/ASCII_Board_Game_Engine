#pragma once
#include <string>
#include <vector>
#include "frame.h"
#include "widget.h"
#include "format_tools.h"
#include "ascii_io.h"
#include <unordered_map>

#ifdef _WIN32
#ifdef LABEL_EXPORTS
#define LABEL_API __declspec(dllexport)
#else
#define LABEL_API __declspec(dllimport)
#endif
#elif __linux__
#define LABEL_API
#endif

class label : public widget
{
public:
	LABEL_API label(frame* parent, const std::string& special_operation = "none", unsigned int lines_count = 0, bool start_logging=false, const std::string& logging_file_path="label.log");
	LABEL_API void set_output(std::string output);
	LABEL_API void set_colors(std::vector<format_tools::index_format> colors);
	LABEL_API std::vector<format_tools::index_format> get_colors();
	LABEL_API std::vector<format_tools::index_format> get_displayed_colors();
	LABEL_API void display();
	LABEL_API void scroll();
	LABEL_API void scroll_up(unsigned int amount = 1, bool render=true);
	LABEL_API void scroll_down(unsigned int amount = 1, bool render=true);
	LABEL_API void set_controls(int up, int down, int quit);
	LABEL_API void get_controls(int& up, int& down, int& quit);
	LABEL_API void set_lines_count(unsigned int lines_count);
private:
	std::vector<format_tools::index_format> convert_color_tags(std::string& content);
	int _up = ascii_io::up;
	int _down = ascii_io::down;
	int _quit = ascii_io::q;

	const std::unordered_map<std::string, int> foreground_color_tags =
	{
		{"<black_foreground>", format_tools::black},
		{"<red_foreground>", format_tools::red},
		{"<green_foreground>", format_tools::green},
		{"<yellow_foreground>", format_tools::yellow},
		{"<blue_foreground>", format_tools::blue},
		{"<magenta_foreground>", format_tools::magenta},
		{"<cyan_foreground>", format_tools::cyan},
		{"<white_foreground>", format_tools::white},
		{"<no_color>", format_tools::none}
	};

	const std::unordered_map<std::string, int> background_color_tags =
	{
		{"<black_background>", format_tools::black},
		{"<red_background>", format_tools::red},
		{"<green_background>", format_tools::green},
		{"<yellow_background>", format_tools::yellow},
		{"<blue_background>", format_tools::blue},
		{"<magenta_background>", format_tools::magenta},
		{"<cyan_background>", format_tools::cyan},
		{"<white_background>", format_tools::white},
		{"<no_color>", format_tools::none}
	};
};
