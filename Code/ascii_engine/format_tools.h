#pragma once
#include <string>
#include <vector>

namespace format_tools
{
	struct text_column
	{
		std::vector<std::vector<std::string>> text;
		std::vector<unsigned int> width;
	};
	const std::string right_alignment_keyword = "right";
	const std::string left_alignment_keyword = "left";
	const std::string center_alignment_keyword = "center";
	std::vector<std::string> split_string(std::string str, char split_character);
	void cut_word(const std::string& word, unsigned int length, std::string& first_section, std::string& second_section);
	std::string get_spacing(unsigned int length, char space_char);
	std::string fill_line(std::string input, unsigned int length, std::string allignment);
	std::vector<std::string> add_lines(std::vector<std::string> lines, unsigned int number_of_added_lines, unsigned int line_length);
	std::string fuse_columns_into_row(text_column data, unsigned int& lines);
	std::vector<std::string> get_lines(const std::string& output_string);
	std::vector<std::string> remove_trailing_whitespace(const std::vector<std::string>& lines);
	void mask_string(std::string& new_string, const std::string& old_string);
	void remove_newline_characters(std::string& text);
}