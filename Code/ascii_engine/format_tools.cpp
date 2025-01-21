#include "../ascii_engine_dll_files/pch.h"
#include "format_tools.h"

#ifdef __linux__
#include <algorithm>
#endif

std::vector<std::string> format_tools::split_string(std::string str, char split_character)
{
	std::string section = "";
	std::vector<std::string> sections;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == split_character)
		{
			sections.push_back(section);
			if (section != std::string(1, split_character))
			{
				sections.push_back(std::string(1, split_character));
			}
			section = "";
		}
		else
		{
			section = section + str[i];
		}
	}

	if (section != "")
	{
		sections.push_back(section);
	}

	return sections;
}

void format_tools::cut_word(const std::string& word, unsigned int length, std::string& first_section, std::string& second_section)
{
	first_section = "";
	second_section = "";
	if (length > word.length())
	{
		length = word.length();
	}

	for (unsigned int i = 0; i < length; i++)
	{
		first_section = first_section + word[i];
	}

	for (unsigned int i = length; i < word.length(); i++)
	{
		second_section = second_section + word[i];
	}
}

std::string format_tools::get_spacing(unsigned int length, char space_char)
{
	std::string spacing = "";
	for (unsigned int i = 0; i < length; i++)
	{
		spacing = spacing + space_char;
	}
	return spacing;
}

std::string format_tools::fill_line(std::string input, unsigned int length, std::string alignment)
{
	if (alignment == left_alignment_keyword)
	{
		while (input.length() < length)
		{
			input = input + " ";
		}
	}
	else if (alignment == center_alignment_keyword)
	{
		bool begin = true;
		while (input.length() < length)
		{
			if (begin)
			{
				input = input + " ";
				begin = false;
			}
			else
			{
				input.insert(0, " ");
				begin = true;
			}
		}
	}
	else if (alignment == right_alignment_keyword)
	{
		while (input.length() < length)
		{
			input.insert(0, " ");
		}
	}

	return input;
}

std::vector<std::string> format_tools::fill_lines(std::vector<std::string> input, unsigned int length, std::string alignment)
{
	unsigned int largest_width = 0;
	if (alignment == center_block_alignment_keyword)
	{
		for (unsigned int i = 0; i < input.size(); i++)
		{
			if (input[i].length() > largest_width)
			{
				largest_width = input[i].length();
			}
		}

		for (unsigned int i = 0; i < input.size(); i++)
		{
			input[i] = input[i] + get_spacing(largest_width - input[i].length(), ' ');
			input[i] = fill_line(input[i], length, center_alignment_keyword);
		}
	}
	else
	{
		for (unsigned int i = 0; i < input.size(); i++)
		{
			input[i] = fill_line(input[i], length, alignment);
		}
	}
	return input;
}

std::vector<std::string> format_tools::add_lines(std::vector<std::string> lines, unsigned int number_of_added_lines, unsigned int line_length)
{
	std::string line = get_spacing(line_length, ' ');
	for (unsigned int i = 0; i < number_of_added_lines; i++)
	{
		lines.push_back(line);
	}
	return lines;
}

std::string format_tools::fuse_columns_into_row(text_column data, unsigned int& lines)
{
	std::string row = "";
	unsigned int max_length = 0;
	for (unsigned int column = 0; column < data.text.size(); column++)
	{
		if (data.text[column].size() > max_length)
		{
			max_length = data.text[column].size();
		}
	}
	lines = max_length;

	for (unsigned int column = 0; column < data.text.size(); column++)
	{
		data.text[column] = format_tools::add_lines(data.text[column], max_length - data.text[column].size(), data.width[column]);
	}

	for (unsigned int line = 0; line < max_length; line++)
	{
		for (unsigned int column = 0; column < data.text.size(); column++)
		{
			row = row + (data.text[column])[line];
		}
		row = row + "\n";
	}
	return row;
}

std::vector<std::string> format_tools::get_lines(const std::string& output_string)
{
	std::vector<std::string> output_lines;
	std::string line = "";
	for (unsigned int i = 0; i < output_string.length(); i++)
	{
		line = line + output_string[i];
		if (output_string[i] == '\n')
		{
			output_lines.push_back(line);
			line = "";
		}
	}
	if (line != "")
	{
		output_lines.push_back(line);
	}
	return output_lines;
}

std::vector<std::string> format_tools::get_lines(const std::string& content, unsigned int width, unsigned int current_position)
{
	std::vector<std::string> lines;
	std::string line = "";
	for (unsigned int i = 0; i < content.length(); i++)
	{
		line = line + content[i];
		if (lines.size() == 0)
		{
			if (line.length() >= (width - current_position))
			{
				lines.push_back(line);
				line = "";
			}
		}
		else if (line.length() >= width)
		{
			lines.push_back(line);
			line = "";
		}
	}
	if (line != "")
	{
		lines.push_back(line);
	}
	return lines;
}

std::string format_tools::get_string(const std::vector<std::string>& lines)
{
	std::string output_string = "";
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		output_string = output_string + lines[i];
	}
	return output_string;
}

std::vector<std::string> format_tools::remove_trailing_whitespace(const std::vector<std::string>& lines)
{
	std::vector<std::string> updated_lines;
	std::string line = "";
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		line = lines[i];

		unsigned int line_length = line.length() - 1;
		for (int j = line_length; j >= 0; j--)
		{
			if (line[j] == ' ')
			{
				line.erase(j, 1);
			}
			else if (line[j] != '\n')
			{
				break;
			}
		}
		if ((line != "\n") && (line != ""))
		{
			updated_lines.push_back(line);
		}
	}
	return updated_lines;
}

void format_tools::mask_string(std::string& output, const std::string& old_output)
{
	std::vector<std::string> new_output_lines = get_lines(output);
	std::vector<std::string> old_output_lines = remove_trailing_whitespace(get_lines(old_output));
	for (unsigned int i = 0; i < old_output_lines.size(); i++)
	{
		if (i < new_output_lines.size())
		{
			if (old_output_lines[i].length() > new_output_lines[i].length())
			{
				while ((old_output_lines[i].length() - new_output_lines[i].length()) != 0)
				{
					new_output_lines[i].insert(new_output_lines[i].length() - 2, " ");
				}
			}
		}
		else
		{
			std::string spacer = get_spacing(old_output_lines[i].length() - 1, ' ');
			spacer = spacer + "\n";
			new_output_lines.push_back(spacer);
		}
	}

	output = "";
	for (unsigned int i = 0; i < new_output_lines.size(); i++)
	{
		output = output + new_output_lines[i];
	}
}

void format_tools::remove_newline_characters(std::string& text)
{
	int text_length = (int)(text.length() - 1);
	for (int i = text_length; i >= 0; i--)
	{
		if (text[i] == '\n')
		{
			text.erase(i, 1);
		}
	}
}

std::vector<format_tools::index_format> format_tools::sort(std::vector<index_format>& index_colors)
{
	std::vector<index_format> sorted_format;
	unsigned int combined_format_length = index_colors.size();
	for (unsigned int i = 0; i < combined_format_length; i++)
	{
		int index = get_min_format_index(index_colors);
		sorted_format.push_back(index_colors[index]);
		index_colors.erase(index_colors.begin() + index);
	}
	return sorted_format;
}

std::vector<format_tools::coordinate_format> format_tools::sort(std::vector<coordinate_format>& coordinate_colors)
{
	std::vector<coordinate_format> sorted_format;
	unsigned int length = coordinate_colors.size();
	for (unsigned int i = 0; i < length; i++)
	{
		int index = get_min_format_index(coordinate_colors);
		sorted_format.push_back(coordinate_colors[index]);
		coordinate_colors.erase(coordinate_colors.begin() + index);
	}
	return sorted_format;
}

int format_tools::calculate_flag_number(const std::vector<index_format>& index_colors, int index)
{
	int number = 0;
	for (unsigned int i = 0; i < index_colors.size(); i++)
	{
		if (index_colors[i].index < index)
		{
			number++;
		}
		else
		{
			break;
		}
	}
	return number;
}

bool format_tools::index_found(const std::vector<index_format>& index_colors, int index)
{
	bool found = false;
	for (unsigned int i = 0; i < index_colors.size(); i++)
	{
		if (index_colors[i].index == index)
		{
			found = true;
			break;
		}
	}
	return found;
}

std::vector<format_tools::index_format> format_tools::combine(const std::vector<index_format>& format_1, const std::vector<index_format>& format_2)
{
	std::vector<index_format> combined_format;
	std::vector<index_format> sorted_format;

	for (unsigned int i = 0; i < format_1.size(); i++)
	{
		combined_format.push_back(format_1[i]);
	}

	for (unsigned int i = 0; i < format_2.size(); i++)
	{
		combined_format.push_back(format_2[i]);
	}

	int length = (int)combined_format.size() - 1;
	for (int i = length; i >= 0; i--)
	{
		for (unsigned int j = ((unsigned int)i + 1); j < combined_format.size(); j++)
		{
			if (combined_format[i].index == combined_format[j].index)
			{
				if (combined_format[j].format.dec)
				{
					combined_format[i].format.dec = true;
				}

				if (combined_format[j].format.bold)
				{
					combined_format[i].format.bold = true;
				}

				if (combined_format[i].format.foreground_format == format_tools::none)
				{
					combined_format[i].format.foreground_format = combined_format[j].format.foreground_format;
				}

				if (combined_format[i].format.background_format == format_tools::none)
				{
					combined_format[i].format.background_format = combined_format[j].format.background_format;
				}

				combined_format.erase(combined_format.begin() + j);
			}
		}
	}

	sorted_format = sort(combined_format);
	return sorted_format;
}

int format_tools::get_min_format_index(const std::vector<index_format>& format_vec)
{
	int min_vec_index = 0;
	int min_index = 0;
	if (format_vec.size() > 0)
	{
		min_vec_index = 0;
		min_index = format_vec[min_vec_index].index;
		for (unsigned int i = 1; i < format_vec.size(); i++)
		{
			if (format_vec[i].index < min_index)
			{
				min_vec_index = i;
				min_index = format_vec[min_vec_index].index;
			}
		}
	}
	return min_vec_index;
}

int format_tools::get_min_format_index(const std::vector<coordinate_format>& format_vec)
{
	int min_vec_index = 0;
	int min_x = 0;
	int min_y = 0;
	if (format_vec.size() > 0)
	{
		min_vec_index = 0;
		min_x = format_vec[min_vec_index].x_position;
		min_y = format_vec[min_vec_index].y_position;
		for (unsigned int i = 1; i < format_vec.size(); i++)
		{
			if (format_vec[i].y_position < min_y)
			{
				min_vec_index = i;
				min_x = format_vec[min_vec_index].x_position;
				min_y = format_vec[min_vec_index].y_position;
			}
			else if ((format_vec[i].y_position == min_y) && (format_vec[i].x_position < min_x))
			{
				min_vec_index = i;
				min_x = format_vec[min_vec_index].x_position;
				min_y = format_vec[min_vec_index].y_position;
			}
		}
	}
	return min_vec_index;
}

std::vector<format_tools::content_format> format_tools::convert(std::vector<index_format> index_vec, const std::string& content)
{
	unsigned int index_vec_position = 0;
	unsigned int content_position = 0;
	content_format converted_format;
	std::vector<content_format> content_vec;
	index_vec = sort(index_vec);
	if ((index_vec.size() > 0) && (index_vec[0].index > 0))
	{
		converted_format.format.foreground_format = none;
		converted_format.format.background_format = none;
		converted_format.format.dec = false;
		for (int i = 0; i < index_vec[0].index; i++)
		{
			converted_format.content = converted_format.content + content[content_position];
			content_position++;
			if (content_position > content.length())
			{
				break;
			}
		}
		content_vec.push_back(converted_format);
		converted_format.content = "";
	}

	if (index_vec.size() > 0)
	{
		converted_format.format = index_vec[index_vec_position].format;
	}

	while (content_position < content.length())
	{
		if (((index_vec_position + 1) < index_vec.size()) && ((int)content_position == index_vec[index_vec_position + 1].index))
		{
			index_vec_position++;
			content_vec.push_back(converted_format);
			converted_format.format = index_vec[index_vec_position].format;
			converted_format.content = content[content_position];
		}
		else
		{
			converted_format.content = converted_format.content + content[content_position];
		}
		content_position++;
	}

	if (converted_format.content != "")
	{
		content_vec.push_back(converted_format);
	}
	return content_vec;
}

std::vector<format_tools::index_format> format_tools::convert(const std::vector<coordinate_format>& coordinate_vec, int width)
{
	index_format converted_format;
	std::vector<index_format> index_vec;
	for (unsigned int i = 0; i < coordinate_vec.size(); i++)
	{
		converted_format.format = coordinate_vec[i].format;
		converted_format.index = (coordinate_vec[i].y_position * width) + coordinate_vec[i].x_position;
		index_vec.push_back(converted_format);
	}
	return index_vec;
}

std::vector<format_tools::coordinate_format> format_tools::convert(const std::vector<index_format>& index_vec, const std::vector<std::string>& lines)
{
	coordinate_format converted_format;
	std::vector<coordinate_format> coordinate_vec;
	int index = 0;
	for (unsigned int i = 0; i < index_vec.size(); i++)
	{
		for (unsigned int j = 0; j < lines.size(); j++)
		{
			if ((int)(index + lines[j].length()) <= index_vec[i].index)
			{
				index = index + lines[j].length();
				converted_format.y_position++;
			}
			else
			{
				converted_format.x_position = index_vec[i].index - index;
				converted_format.format = index_vec[i].format;
				coordinate_vec.push_back(converted_format);
				converted_format.x_position = 0;
				converted_format.y_position = 0;
				index = 0;
				break;
			}
		}
	}
	return coordinate_vec;
}

std::vector<int> format_tools::set_flags(std::vector<index_format>& index_colors, std::string& content, char flag)
{
	index_colors = sort(index_colors);
	std::vector<int> ignore_flags;
	int flags_found = 0;
	for (unsigned int i = 0; i < content.length(); i++)
	{
		if ((content[i] == flag) && !index_found(index_colors, i))
		{
			ignore_flags.push_back(flags_found + calculate_flag_number(index_colors, i));
			flags_found++;
		}
	}

	for (unsigned int i = 0; i < index_colors.size(); i++)
	{
		if ((index_colors[i].index >= 0) && (index_colors[i].index < (int)content.length()))
		{
			index_colors[i].flag_replacement = content[index_colors[i].index];
			content[index_colors[i].index] = flag;
		}
	}
	return ignore_flags;
}

void format_tools::convert_flags(std::vector<coordinate_format>& coordinate_colors, const std::vector<index_format>& index_colors, std::vector<int> ignore_flags, std::vector<std::string>& lines, char flag)
{
	coordinate_colors.clear();
	coordinate_format converted_format;
	for (unsigned int i = 0; i < index_colors.size(); i++)
	{
		converted_format.format = index_colors[i].format;
		coordinate_colors.push_back(converted_format);
	}

	unsigned int color_index = 0;
	unsigned int flag_characters_found = 0;
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		for (unsigned int j = 0; j < lines[i].length(); j++)
		{
			if ((lines[i])[j] == flag)
			{
				if (std::count(ignore_flags.begin(), ignore_flags.end(), flag_characters_found) == 0)
				{
					if (color_index < coordinate_colors.size())
					{
						coordinate_colors[color_index].y_position = i;
						coordinate_colors[color_index].x_position = j;
						(lines[i])[j] = index_colors[color_index].flag_replacement;
						color_index++;
					}
					else
					{
						return;
					}
				}
				flag_characters_found++;
			}
		}
	}
}

std::vector<format_tools::content_format> format_tools::fit_to_width(const std::vector<content_format>& content_vec, unsigned int width)
{
	std::vector<content_format> updated_vec;
	unsigned int length = 0;
	for (unsigned int i = 0; i < content_vec.size(); i++)
	{
		if ((length + content_vec[i].content.length()) >= width)
		{
			std::vector<std::string> lines = get_lines(content_vec[i].content, width, length);
			for (unsigned int j = 0; j < lines.size(); j++)
			{
				content_format temp;
				temp.content = lines[j];
				temp.format = content_vec[i].format;
				updated_vec.push_back(temp);
				length = length + lines[j].length();
				if (length >= width)
				{
					length = 0;
				}
			}
		}
		else
		{
			updated_vec.push_back(content_vec[i]);
			length = length + content_vec[i].content.length();
		}
	}
	return updated_vec;
}

std::vector<std::string> format_tools::remove_newline_characters(std::vector<std::string> lines)
{
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		if ((lines[i].length() > 0) && (lines[i].back() == '\n'))
		{
			lines[i].erase((lines[i].length() - 1), 1);
		}
	}
	return lines;
}

std::vector<std::string> format_tools::add_newline_characters(std::vector<std::string> lines)
{
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		if ((lines[i].length() > 0) && (lines[i].back() != '\n'))
		{
			lines[i] = lines[i] + '\n';
		}
	}
	return lines;
}

unsigned int format_tools::get_first_line_length(const std::string& content)
{
	unsigned int width = 0;
	for (unsigned int i = 0; i < content.length(); i++)
	{
		width++;
		if (content[i] == '\n')
		{
			break;
		}
	}
	return width;
}

std::string format_tools::get_color_name(int color)
{
	std::string name = "";
	for (unsigned int i = 0; i < color_string_map.size(); i++)
	{
		if (color_string_map[i].color == color)
		{
			name = color_string_map[i].name;
		}
	}
	return name;
}

std::vector<format_tools::index_format> format_tools::shift_index(std::vector<index_format> index_colors, int shift_amount)
{
	int length = index_colors.size() - 1;
	for (int i = length; i >= 0; i--)
	{
		index_colors[i].index = index_colors[i].index + shift_amount;
		if (index_colors[i].index < 0)
		{
			index_colors.erase(index_colors.begin() + i);
		}
	}
	return index_colors;
}

std::vector<format_tools::coordinate_format> format_tools::bound_colors(std::vector<coordinate_format> colors, const std::vector<std::string>& lines)
{
	if (colors.size() > 0)
	{
		colors = sort(colors);
		coordinate_format last_color = colors[0];
		unsigned int colors_length = colors.size();
		for (unsigned int i = 0; i < colors_length; i++)
		{
			bool non_empty_format = ((last_color.format.foreground_format != format_tools::none) || (last_color.format.background_format != format_tools::none) || last_color.format.bold);
			if ((colors[i].y_position != last_color.y_position) && non_empty_format)
			{
				coordinate_format cap_format;
				cap_format.y_position = last_color.y_position;
				cap_format.x_position = lines[last_color.y_position].length();
				colors.push_back(cap_format);
				coordinate_format wrap_format;
				wrap_format.format = last_color.format;
				wrap_format.x_position = 0;

				for (int j = last_color.y_position + 1; j < colors[i].y_position; j++)
				{
					wrap_format.y_position = j;
					colors.push_back(wrap_format);
					cap_format.x_position = lines[colors[j].y_position].length();
					cap_format.y_position = j;
					colors.push_back(cap_format);
				}
				
				if (colors[i].x_position != 0)
				{
					wrap_format.y_position = colors[i].y_position;
					colors.push_back(wrap_format);
				}
			}

			non_empty_format = ((colors[i].format.foreground_format != format_tools::none) || (colors[i].format.background_format != format_tools::none) || colors[i].format.bold);
			if ((i == colors_length - 1) && non_empty_format)
			{
				coordinate_format cap_format;
				cap_format.y_position = colors[i].y_position;
				cap_format.x_position = lines[colors[i].y_position].length();
				colors.push_back(cap_format);
				coordinate_format wrap_format;
				wrap_format.format = colors[i].format;
				wrap_format.x_position = 0;

				for (unsigned int j = colors[i].y_position + 1; j < lines.size(); j++)
				{
					wrap_format.y_position = j;
					colors.push_back(wrap_format);
					cap_format.x_position = lines[colors[j].y_position].length();
					cap_format.y_position = j;
					colors.push_back(cap_format);
				}
			}
			last_color = colors[i];
		}
	}
	
	return colors;
}