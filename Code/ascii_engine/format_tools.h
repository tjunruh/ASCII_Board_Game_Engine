#pragma once
#include <string>
#include <vector>

#ifdef _WIN32
#ifdef FORMAT_TOOLS_EXPORTS
#define FORMAT_TOOLS_API __declspec(dllexport)
#else
#define FORMAT_TOOLS_API __declspec(dllimport)
#endif
#elif __linux__
#define FORMAT_TOOLS_API
#endif

namespace format_tools
{

#ifdef _WIN32
	const int black = 30;
	const int red = 31;
	const int green = 32;
	const int yellow = 33;
	const int blue = 34;
	const int magenta = 35;
	const int cyan = 36;
	const int white = 37;
	const int none = 38;
#elif __linux__
	const int black = 0;
	const int red = 1;
	const int green = 2;
	const int yellow = 3;
	const int blue = 4;
	const int magenta = 5;
	const int cyan = 6;
	const int white = 7;
	const int none = 8;
#endif
	const std::vector<int> colors = { black, red, green, yellow, blue, magenta, cyan, white };
	const std::vector<char> invalid_characters = { '\n', '\a', '\b', '\f', '\r', '\t', '\v', '\0' };

	struct common_format
	{
		int foreground_format = none;
		int background_format = none;
		bool dec = false;
	};

	struct index_format
	{
		int index = 0;
		common_format format;
		char flag_replacement = ' ';
	};

	struct content_format
	{
		std::string content = "";
		common_format format;
	};

	struct coordinate_format
	{
		int x_position = 0;
		int y_position = 0;
		common_format format;
	};

	struct text_column
	{
		std::vector<std::vector<std::string>> text;
		std::vector<unsigned int> width;
	};

	const std::string right_alignment_keyword = "right";
	const std::string left_alignment_keyword = "left";
	const std::string center_alignment_keyword = "center";
	const std::string center_block_alignment_keyword = "center block";
	FORMAT_TOOLS_API std::vector<std::string> split_string(std::string str, char split_character);
	FORMAT_TOOLS_API void cut_word(const std::string& word, unsigned int length, std::string& first_section, std::string& second_section);
	FORMAT_TOOLS_API std::string get_spacing(unsigned int length, char space_char);
	FORMAT_TOOLS_API std::string fill_line(std::string input, unsigned int length, std::string alignment);
	FORMAT_TOOLS_API std::vector<std::string> fill_lines(std::vector<std::string> input, unsigned int length, std::string alignment);
	FORMAT_TOOLS_API std::vector<std::string> add_lines(std::vector<std::string> lines, unsigned int number_of_added_lines, unsigned int line_length);
	FORMAT_TOOLS_API std::string fuse_columns_into_row(text_column data, unsigned int& lines);
	FORMAT_TOOLS_API std::vector<std::string> get_lines(const std::string& output_string);
	FORMAT_TOOLS_API std::vector<std::string> get_lines(const std::string& content, unsigned int width, unsigned int current_position=0);
	FORMAT_TOOLS_API std::string get_string(const std::vector<std::string>& lines);
	FORMAT_TOOLS_API std::vector<std::string> remove_trailing_whitespace(const std::vector<std::string>& lines);
	FORMAT_TOOLS_API void mask_string(std::string& new_string, const std::string& old_string);
	FORMAT_TOOLS_API void remove_newline_characters(std::string& text);
	FORMAT_TOOLS_API std::vector<index_format> sort(std::vector<index_format>& index_colors);
	FORMAT_TOOLS_API int calculate_flag_number(const std::vector<index_format>& index_colors, int index);
	FORMAT_TOOLS_API bool index_found(const std::vector<index_format>& index_colors, int index);
	FORMAT_TOOLS_API std::vector<index_format> combine(const std::vector<index_format>& format_1, const std::vector<index_format>& format_2);
	FORMAT_TOOLS_API int get_min_format_index(const std::vector<index_format>& format_vec);
	FORMAT_TOOLS_API std::vector<content_format> convert(std::vector<index_format> index_vec, const std::string& content);
	FORMAT_TOOLS_API std::vector<index_format> convert(const std::vector<coordinate_format>& coordinate_vec, int width);
	FORMAT_TOOLS_API std::vector<coordinate_format> convert(const std::vector<index_format>& index_vec, const std::vector<std::string>& lines);
	FORMAT_TOOLS_API std::vector<int> set_flags(std::vector<index_format>& index_colors, std::string& content, char flag);
	FORMAT_TOOLS_API void convert_flags(std::vector<coordinate_format>& coordinate_colors, const std::vector<index_format>& index_colors, std::vector<int> ignore_flags, std::vector<std::string>& lines, char flag);
	FORMAT_TOOLS_API std::vector<content_format> fit_to_width(const std::vector<content_format>& content_vec, unsigned int width);
	FORMAT_TOOLS_API std::vector<std::string> remove_newline_characters(std::vector<std::string> lines);
	FORMAT_TOOLS_API std::vector<std::string> add_newline_characters(std::vector<std::string> lines);
	FORMAT_TOOLS_API unsigned int get_first_line_length(const std::string& content);
}