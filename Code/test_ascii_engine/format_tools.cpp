#include "pch.h"
#ifdef __linux__
#include <gtest/gtest.h>
#endif
#ifdef _WIN32
#include "../ascii_engine/format_tools.h"
#elif __linux__
#include <ascii_engine/format_tools.h>
#endif

#include <string>
#include <vector>

class format_tools_test : public testing::Test
{
protected:
	void format_equivalent_test(std::vector<format_tools::index_format> correct_answer, std::vector<format_tools::index_format> test_format, int test_num)
	{
		correct_answer = format_tools::sort(correct_answer);
		test_format = format_tools::sort(test_format);
		ASSERT_EQ(test_format.size(), correct_answer.size()) << "Test num: " + std::to_string(test_num) + "\ncorrect_answer vector and test_colors vector have different lengths.";
		for (unsigned int i = 0; i < correct_answer.size(); i++)
		{
			EXPECT_EQ(test_format[i].index, correct_answer[i].index) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
			EXPECT_EQ(test_format[i].format.background_format, correct_answer[i].format.background_format) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
			EXPECT_EQ(test_format[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
			EXPECT_EQ(test_format[i].format.dec, correct_answer[i].format.dec) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
		}
	}

	void format_equivalent_test(std::vector<format_tools::coordinate_format> correct_answer, std::vector<format_tools::coordinate_format> test_format, int test_num)
	{
		correct_answer = format_tools::sort(correct_answer);
		test_format = format_tools::sort(test_format);
		ASSERT_EQ(test_format.size(), correct_answer.size()) << "Test num: " + std::to_string(test_num) + "\ncorrect_answer vector and test_colors vector have different lengths.";
		for (unsigned int i = 0; i < correct_answer.size(); i++)
		{
			EXPECT_EQ(test_format[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
			EXPECT_EQ(test_format[i].format.background_format, correct_answer[i].format.background_format) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
			EXPECT_EQ(test_format[i].x_position, correct_answer[i].x_position) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
			EXPECT_EQ(test_format[i].y_position, correct_answer[i].y_position) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
			EXPECT_EQ(test_format[i].format.dec, correct_answer[i].format.dec) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
		}
	}

	void format_equivalent_test(std::vector<format_tools::content_format> correct_answer, std::vector<format_tools::content_format> test_format, int test_num)
	{
		ASSERT_EQ(test_format.size(), correct_answer.size()) << "Test num: " + std::to_string(test_num) + "\ncorrect_answer vector and test_colors vector have different lengths.";
		for (unsigned int i = 0; i < correct_answer.size(); i++)
		{
			EXPECT_EQ(test_format[i].content, correct_answer[i].content) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
			EXPECT_EQ(test_format[i].format.background_format, correct_answer[i].format.background_format) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
			EXPECT_EQ(test_format[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
			EXPECT_EQ(test_format[i].format.dec, correct_answer[i].format.dec) << "Test num: " + std::to_string(test_num) + "\nIndex of colors not equivalent: " + std::to_string(i);
		}
	}
};

TEST_F(format_tools_test, split_string)
{
	std::string test_string = "This is my test string. It should be split into words.";
	std::vector<std::string> segmented_string = format_tools::split_string(test_string, ' ');
	std::vector<std::string> correct_answer = { "This", " ", "is", " ", "my", " ", "test", " ", "string.", " ", "It", " ", "should", " ", "be", " ", "split", " ", "into", " " , "words." };
	ASSERT_EQ(segmented_string.size(), correct_answer.size()) << "Vector created from splitting string is wrong length";
	for (unsigned int i = 0; i < segmented_string.size(); i++)
	{
		EXPECT_EQ(segmented_string[i], correct_answer[i]) << "Vector created from splitting string is wrong at index " << i;
	}
}

TEST_F(format_tools_test, cut_word)
{
	std::string long_word = "longword";
	std::string first_section = "";
	std::string second_section = "";
	format_tools::cut_word(long_word, 4, first_section, second_section);
	EXPECT_EQ(first_section, "long");
	EXPECT_EQ(second_section, "word");
	format_tools::cut_word(long_word, 100, first_section, second_section);
	EXPECT_EQ(first_section, "longword");
	EXPECT_EQ(second_section, "");
	format_tools::cut_word(long_word, -1, first_section, second_section);
	EXPECT_EQ(first_section, "longword");
	EXPECT_EQ(second_section, "");
}

TEST_F(format_tools_test, get_spacing)
{
	std::string spacing = format_tools::get_spacing(25, ' ');
	std::string correct_answer = "";
	for (unsigned int i = 0; i < 25; i++)
	{
		correct_answer = correct_answer + " ";
	}
	EXPECT_EQ(spacing, correct_answer);
	spacing = format_tools::get_spacing(7, '<');
	correct_answer = "";
	for (unsigned int i = 0; i < 7; i++)
	{
		correct_answer = correct_answer + '<';
	}
	EXPECT_EQ(spacing, correct_answer);
}

TEST_F(format_tools_test, fill_line)
{
	std::string test_string = "This sentence is 36 characters long.";
	std::string filled_string = format_tools::fill_line(test_string, 50, format_tools::left_alignment_keyword);
	std::string correct_answer = test_string;
	for (unsigned int i = 0; i < 14; i++)
	{
		correct_answer = correct_answer + " ";
	}
	EXPECT_EQ(filled_string, correct_answer);

	filled_string = format_tools::fill_line(test_string, 51, format_tools::center_alignment_keyword);
	correct_answer = test_string;
	for (unsigned int i = 0; i < 7; i++)
	{
		correct_answer = " " + correct_answer;
	}

	for (unsigned int i = 0; i < 8; i++)
	{
		correct_answer = correct_answer + " ";
	}
	EXPECT_EQ(filled_string, correct_answer);

	filled_string = format_tools::fill_line(test_string, 50, format_tools::right_alignment_keyword);
	correct_answer = test_string;
	for (unsigned int i = 0; i < 14; i++)
	{
		correct_answer = " " + correct_answer;
	}
	EXPECT_EQ(filled_string, correct_answer);

	filled_string = format_tools::fill_line(test_string, 50, "jibberish");
	correct_answer = test_string;
	EXPECT_EQ(filled_string, correct_answer);

	filled_string = format_tools::fill_line(test_string, 1, format_tools::left_alignment_keyword);
	correct_answer = test_string;
	EXPECT_EQ(filled_string, correct_answer);
}

TEST_F(format_tools_test, fill_lines)
{
	std::vector<std::string> test_lines;
	for (unsigned int i = 10; i < 36; i++)
	{
		std::string line = "This is sentence number " + std::to_string(i);
		test_lines.push_back(line);
	}

	std::vector<std::string> filled_lines = format_tools::fill_lines(test_lines, 50, format_tools::left_alignment_keyword);
	std::vector<std::string> correct_answer = test_lines;
	for (unsigned int i = 0; i < 25; i++)
	{
		for (unsigned int j = 0; j < 24; j++)
		{
			correct_answer[i] = correct_answer[i] + " ";
		}
	}

	for (unsigned int i = 0; i < 25; i++)
	{
		EXPECT_EQ(filled_lines[i], correct_answer[i]) << "left";
	}

	filled_lines = format_tools::fill_lines(test_lines, 51, format_tools::center_alignment_keyword);
	correct_answer = test_lines;
	for (unsigned int i = 0; i < 25; i++)
	{
		for (unsigned int j = 0; j < 12; j++)
		{
			correct_answer[i] = " " + correct_answer[i];
		}

		for (unsigned int j = 0; j < 13; j++)
		{
			correct_answer[i] = correct_answer[i] + " ";
		}
	}

	for (unsigned int i = 0; i < 25; i++)
	{
		EXPECT_EQ(filled_lines[i], correct_answer[i]) << "center";
	}

	filled_lines = format_tools::fill_lines(test_lines, 50, format_tools::right_alignment_keyword);
	correct_answer = test_lines;
	for (unsigned int i = 0; i < 25; i++)
	{
		for (unsigned int j = 0; j < 24; j++)
		{
			correct_answer[i] = " " + correct_answer[i];
		}
	}

	for (unsigned int i = 0; i < 25; i++)
	{
		EXPECT_EQ(filled_lines[i], correct_answer[i]) << "right";
	}

	filled_lines = format_tools::fill_lines(test_lines, 50, "jibberish");
	correct_answer = test_lines;

	for (unsigned int i = 0; i < 25; i++)
	{
		EXPECT_EQ(filled_lines[i], correct_answer[i]) << "jibberish";
	}

	filled_lines = format_tools::fill_lines(test_lines, 1, format_tools::left_alignment_keyword);
	correct_answer = test_lines;

	for (unsigned int i = 0; i < 25; i++)
	{
		EXPECT_EQ(filled_lines[i], correct_answer[i]) << "short left";
	}

	filled_lines = format_tools::fill_lines(test_lines, 1, format_tools::center_block_alignment_keyword);
	correct_answer = test_lines;

	for (unsigned int i = 0; i < 25; i++)
	{
		EXPECT_EQ(filled_lines[i], correct_answer[i]) << "short center block";
	}

	test_lines[0] = test_lines[0] + "longer line.";
	filled_lines = format_tools::fill_lines(test_lines, 51, format_tools::center_block_alignment_keyword);
	correct_answer = test_lines;
	for (unsigned int i = 0; i < 6; i++)
	{
		correct_answer[0] = " " + correct_answer[0];
	}

	for (unsigned int i = 0; i < 7; i++)
	{
		correct_answer[0] = correct_answer[0] + " ";
	}

	for (unsigned int i = 1; i < 25; i++)
	{
		for (unsigned int j = 0; j < 6; j++)
		{
			correct_answer[i] = " " + correct_answer[i];
		}

		for (unsigned int j = 0; j < 19; j++)
		{
			correct_answer[i] = correct_answer[i] + " ";
		}
	}

	for (unsigned int i = 0; i < 25; i++)
	{
		EXPECT_EQ(filled_lines[i], correct_answer[i]) << "center block";
	}
}

TEST_F(format_tools_test, add_lines)
{
	std::vector<std::string> lines;
	std::string line = "This is a test line.";
	lines.push_back(line);
	std::vector<std::string> correct_answer = lines;
	lines = format_tools::add_lines(lines, 9, lines[0].length());
	std::string line_spacer = "";
	for (unsigned int i = 0; i < lines[0].length(); i++)
	{
		line_spacer = line_spacer + " ";
	}
	
	for (unsigned int i = 0; i < 9; i++)
	{
		correct_answer.push_back(line_spacer);
	}
	
	ASSERT_EQ(lines.size(), correct_answer.size());

	for (unsigned int i = 0; i < lines.size(); i++)
	{
		EXPECT_EQ(lines[i], correct_answer[i]);
	}
}

TEST_F(format_tools_test, fuse_columns_into_row)
{
	std::vector<std::string> lines1 = {
		"1 ",
		"2 ",
		"3 ",
		"4 ",
		"5 ",
		"6 ",
		"7 ",
		"8 ",
		"9 ",
		"10",
		"  "
	};

	std::vector<std::string> lines2 = {
		"1 ",
		"2 ",
		"3 ",
		"4 ",
		"5 ",
		"6 ",
		"7 ",
		"8 ",
		"9 ",
		"10",
		"11"
	};

	std::string correct_answer = 
		"1 1 \n"
		"2 2 \n"
		"3 3 \n"
		"4 4 \n"
		"5 5 \n"
		"6 6 \n"
		"7 7 \n"
		"8 8 \n"
		"9 9 \n"
		"1010\n"
		"  11\n";

	unsigned int correct_number_of_lines = 11;
	format_tools::text_column column;
	column.text.push_back(lines1);
	column.width.push_back(2);
	column.text.push_back(lines2);
	column.width.push_back(2);

	unsigned int number_of_lines = 0;
	std::string fused_columns = format_tools::fuse_columns_into_row(column, number_of_lines);
	EXPECT_EQ(number_of_lines, correct_number_of_lines);
	EXPECT_EQ(fused_columns, correct_answer);
}

TEST_F(format_tools_test, get_lines)
{
	std::string test_string = "1 1 \n"
		"2 2 \n"
		"3 3 \n"
		"4 4 \n"
		"5 5 \n"
		"6 6 \n"
		"7 7 \n"
		"8 8 \n"
		"9 9 \n"
		"1010\n"
		"  11\n";

	std::vector<std::string> correct_answer = {
		"1 1 \n",
		"2 2 \n",
		"3 3 \n",
		"4 4 \n",
		"5 5 \n",
		"6 6 \n",
		"7 7 \n",
		"8 8 \n",
		"9 9 \n",
		"1010\n",
		"  11\n"
	};

	std::vector<std::string> lines = format_tools::get_lines(test_string);
	EXPECT_EQ(lines, correct_answer);
}

TEST_F(format_tools_test, get_lines_without_newline_character)
{
	std::string test_string = "1 1 "
		"2 2 "
		"3 3 "
		"4 4 "
		"5 5 "
		"6 6 "
		"7 7 "
		"8 8 "
		"9 9 "
		"1010"
		"  11";

	std::vector<std::string> correct_answer = {
		"1 1 ",
		"2 2 ",
		"3 3 ",
		"4 4 ",
		"5 5 ",
		"6 6 ",
		"7 7 ",
		"8 8 ",
		"9 9 ",
		"1010",
		"  11"
	};

	std::vector<std::string> lines = format_tools::get_lines(test_string, 4);
	EXPECT_EQ(lines, correct_answer);

	test_string = "1 "
		"2 2 "
		"3 3 "
		"4 4 "
		"5 5 "
		"6 6 "
		"7 7 "
		"8 8 "
		"9 9 "
		"1010"
		"  11";

	correct_answer = {
		"1 ",
		"2 2 ",
		"3 3 ",
		"4 4 ",
		"5 5 ",
		"6 6 ",
		"7 7 ",
		"8 8 ",
		"9 9 ",
		"1010",
		"  11"
	};

	lines = format_tools::get_lines(test_string, 4, 2);
	EXPECT_EQ(lines, correct_answer);
}

TEST_F(format_tools_test, get_string)
{
	std::vector<std::string> test_vector = {
		"1 1 ",
		"2 2 ",
		"3 3 ",
		"4 4 ",
		"5 5 ",
		"6 6 ",
		"7 7 ",
		"8 8 ",
		"9 9 ",
		"1010",
		"  11"
	};

	std::string correct_answer = "1 1 "
		"2 2 "
		"3 3 "
		"4 4 "
		"5 5 "
		"6 6 "
		"7 7 "
		"8 8 "
		"9 9 "
		"1010"
		"  11";

	std::string created_string = format_tools::get_string(test_vector);
	EXPECT_EQ(created_string, correct_answer);
}

TEST_F(format_tools_test, remove_trailing_whitespace)
{
	std::vector<std::string> test_vector = {
		"1 1 ",
		"2 2 ",
		"3 3 ",
		"4 4 ",
		"5 5 ",
		"6 6 ",
		"7 7 ",
		"8 8 ",
		"9 9 ",
		"1010",
		"  11"
		"    "
		"    "
	};

	std::vector<std::string> correct_answer = {
		"1 1",
		"2 2",
		"3 3",
		"4 4",
		"5 5",
		"6 6",
		"7 7",
		"8 8",
		"9 9",
		"1010",
		"  11"
	};

	std::vector<std::string> lines = format_tools::remove_trailing_whitespace(test_vector);
	EXPECT_EQ(lines, correct_answer);

	test_vector = {
		"1 1 \n",
		"2 2 \n",
		"3 3 \n",
		"4 4 \n",
		"5 5 \n",
		"6 6 \n",
		"7 7 \n",
		"8 8 \n",
		"9 9 \n",
		"1010\n",
		"  11\n",
		"    \n",
		"    \n"
	};

	correct_answer = {
		"1 1\n",
		"2 2\n",
		"3 3\n",
		"4 4\n",
		"5 5\n",
		"6 6\n",
		"7 7\n",
		"8 8\n",
		"9 9\n",
		"1010\n",
		"  11\n"
	};

	lines = format_tools::remove_trailing_whitespace(test_vector);
	EXPECT_EQ(lines, correct_answer);
}

TEST_F(format_tools_test, mask_string)
{
	std::string test_string =
		"1 1 \n"
		"2 2 \n"
		"3 3 \n"
		"4 4 \n"
		"5 5 \n"
		"6 6 \n"
		"7 7 \n"
		"8 8 \n"
		"9 9 \n"
		"1010\n"
		"  11\n";

	std::string previous_test_string =
		"1 1 1 \n"
		"2 2 2 \n"
		"3 3 3 \n"
		"4 4 4 \n"
		"5 5 5 \n"
		"6 6 6 \n"
		"7 7 7 \n"
		"8 8 8 \n"
		"9 9 9 \n"
		"1010\n"
		"1111\n"
		"1212\n"
		"1313\n";

	std::string correct_answer =
		"1 1  \n"
		"2 2  \n"
		"3 3  \n"
		"4 4  \n"
		"5 5  \n"
		"6 6  \n"
		"7 7  \n"
		"8 8  \n"
		"9 9  \n"
		"1010\n"
		"  11\n"
		"    \n"
		"    \n";

	format_tools::mask_string(test_string, previous_test_string);
	EXPECT_EQ(test_string, correct_answer);
}

TEST_F(format_tools_test, remove_newline_characters_string)
{
	std::string test_string =
		"1 1  \n"
		"2 2  \n"
		"3 3  \n"
		"4 4  \n"
		"5 5  \n"
		"6 6  \n"
		"7 7  \n"
		"8 8  \n"
		"9 9  \n"
		"1010\n"
		"  11\n"
		"    \n"
		"    \n";

	std::string correct_answer = 
		"1 1  "
		"2 2  "
		"3 3  "
		"4 4  "
		"5 5  "
		"6 6  "
		"7 7  "
		"8 8  "
		"9 9  "
		"1010"
		"  11"
		"    "
		"    ";
	
	format_tools::remove_newline_characters(test_string);
	EXPECT_EQ(test_string, correct_answer);
}

TEST_F(format_tools_test, sort_index)
{
	format_tools::common_format format;
	std::vector<format_tools::index_format> index_vec = {
		{5, format, ' '},
		{4, format, ' '},
		{3, format, ' '},
		{2, format, ' '},
		{1, format, ' '},
		{25, format, ' '},
		{0, format, ' '},
		{10, format, ' '},
		{9, format, ' '},
		{8, format, ' '},
		{7, format, ' '},
		{6, format, ' '},
	};
	
	std::vector<format_tools::index_format> correct_answer = {
		{0, format, ' '},
		{1, format, ' '},
		{2, format, ' '},
		{3, format, ' '},
		{4, format, ' '},
		{5, format, ' '},
		{6, format, ' '},
		{7, format, ' '},
		{8, format, ' '},
		{9, format, ' '},
		{10, format, ' '},
		{25, format, ' '},
	};

	format_equivalent_test(correct_answer, format_tools::sort(index_vec), 0);
}

TEST_F(format_tools_test, sort_coordinate)
{
	format_tools::common_format format;
	std::vector<format_tools::coordinate_format> coordinate_vec = {
		{5, 2, format},
		{4, 1, format},
		{3, 5, format},
		{2, 2, format},
		{1, 4, format},
		{25, 5, format},
		{0, 4, format},
		{10, 3, format},
		{9, 3, format},
		{8, 6, format},
		{7, 0, format},
		{6, 6, format},
	};

	std::vector<format_tools::coordinate_format> correct_answer = {
		{7, 0, format},
		{4, 1, format},
		{2, 2, format},
		{5, 2, format},
		{9, 3, format},
		{10, 3, format},
		{0, 4, format},
		{1, 4, format},
		{3, 5, format},
		{25, 5, format},
		{6, 6, format},
		{8, 6, format},
	};

	format_equivalent_test(correct_answer, format_tools::sort(coordinate_vec), 0);
}

TEST_F(format_tools_test, calculate_flag_number)
{
	format_tools::common_format format;
	std::vector<format_tools::index_format> index_vec = {
		{0, format, ' '},
		{1, format, ' '},
		{2, format, ' '},
		{3, format, ' '},
		{4, format, ' '},
		{5, format, ' '},
		{6, format, ' '},
		{7, format, ' '},
		{8, format, ' '},
		{9, format, ' '},
		{10, format, ' '},
		{25, format, ' '},
	};

	int correct_answer = 11;
	int flag_number = format_tools::calculate_flag_number(index_vec, 15);
	EXPECT_EQ(flag_number, correct_answer);

	index_vec = {
		{5, format, ' '},
		{4, format, ' '},
		{3, format, ' '},
		{2, format, ' '},
		{1, format, ' '},
		{25, format, ' '},
		{0, format, ' '},
		{10, format, ' '},
		{9, format, ' '},
		{8, format, ' '},
		{7, format, ' '},
		{6, format, ' '},
	};

	correct_answer = 5;
	flag_number = format_tools::calculate_flag_number(index_vec, 15);
	EXPECT_EQ(flag_number, correct_answer);
}

TEST_F(format_tools_test, index_found)
{
	format_tools::common_format format;
	std::vector<format_tools::index_format> index_vec = {
		{5, format, ' '},
		{4, format, ' '},
		{3, format, ' '},
		{2, format, ' '},
		{1, format, ' '},
		{25, format, ' '},
		{0, format, ' '},
		{10, format, ' '},
		{9, format, ' '},
		{8, format, ' '},
		{7, format, ' '},
		{6, format, ' '},
	};

	bool correct_answer = true;
	bool index_found = format_tools::index_found(index_vec, 25);
	EXPECT_EQ(index_found, correct_answer);

	correct_answer = false;
	index_found = format_tools::index_found(index_vec, 13);
	EXPECT_EQ(index_found, correct_answer);
}

TEST_F(format_tools_test, combine)
{
	format_tools::common_format empty_format;
	std::vector<format_tools::index_format> index_vec1 = {
		{5, empty_format, ' '},
		{4, empty_format, ' '},
		{3, empty_format, ' '},
		{2, empty_format, ' '},
		{1, empty_format, ' '},
		{25, empty_format, ' '},
		{0, empty_format, ' '},
		{10, empty_format, ' '},
		{9, empty_format, ' '},
		{8, empty_format, ' '},
		{7, empty_format, ' '},
		{6, empty_format, ' '}
	};

	format_tools::common_format full_format;
	full_format.background_format = format_tools::white;
	full_format.foreground_format = format_tools::black;
	full_format.dec = true;
	std::vector<format_tools::index_format> index_vec2 = {
		{15, full_format, ' '},
		{14, full_format, ' '},
		{13, full_format, ' '},
		{12, full_format, ' '},
		{11, full_format, ' '},
		{24, full_format, ' '},
		{22, full_format, ' '},
		{20, full_format, ' '},
		{19, full_format, ' '},
		{18, full_format, ' '},
		{17, full_format, ' '},
		{16, full_format, ' '}
	};

	std::vector<format_tools::index_format> correct_answer = {
		{0, empty_format, ' '},
		{1, empty_format, ' '},
		{2, empty_format, ' '},
		{3, empty_format, ' '},
		{4, empty_format, ' '},
		{5, empty_format, ' '},
		{6, empty_format, ' '},
		{7, empty_format, ' '},
		{8, empty_format, ' '},
		{9, empty_format, ' '},
		{10, empty_format, ' '},
		{11, full_format, ' '},
		{12, full_format, ' '},
		{13, full_format, ' '},
		{14, full_format, ' '},
		{15, full_format, ' '},
		{16, full_format, ' '},
		{17, full_format, ' '},
		{18, full_format, ' '},
		{19, full_format, ' '},
		{20, full_format, ' '},
		{22, full_format, ' '},
		{24, full_format, ' '},
		{25, empty_format, ' '}
	};

	format_equivalent_test(correct_answer, format_tools::combine(index_vec1, index_vec2), 0);

	index_vec2 = {
		{15, full_format, ' '},
		{14, full_format, ' '},
		{13, full_format, ' '},
		{12, full_format, ' '},
		{11, full_format, ' '},
		{25, full_format, ' '},
		{22, full_format, ' '},
		{10, full_format, ' '},
		{19, full_format, ' '},
		{18, full_format, ' '},
		{17, full_format, ' '},
		{16, full_format, ' '}
	};

	correct_answer = {
		{0, empty_format, ' '},
		{1, empty_format, ' '},
		{2, empty_format, ' '},
		{3, empty_format, ' '},
		{4, empty_format, ' '},
		{5, empty_format, ' '},
		{6, empty_format, ' '},
		{7, empty_format, ' '},
		{8, empty_format, ' '},
		{9, empty_format, ' '},
		{10, full_format, ' '},
		{11, full_format, ' '},
		{12, full_format, ' '},
		{13, full_format, ' '},
		{14, full_format, ' '},
		{15, full_format, ' '},
		{16, full_format, ' '},
		{17, full_format, ' '},
		{18, full_format, ' '},
		{19, full_format, ' '},
		{22, full_format, ' '},
		{25, full_format, ' '}
	};

	format_equivalent_test(correct_answer, format_tools::combine(index_vec1, index_vec2), 1);
}

TEST_F(format_tools_test, present)
{
	format_tools::common_format empty_format;

	format_tools::common_format full_format;
	full_format.background_format = format_tools::white;
	full_format.foreground_format = format_tools::black;
	full_format.bold = true;

	format_tools::common_format foreground_format;
	foreground_format.foreground_format = format_tools::black;

	format_tools::common_format background_format;
	background_format.background_format = format_tools::white;

	format_tools::common_format bold_format;
	bold_format.bold = true;


	std::vector<format_tools::index_format> index_vec1 = {
		{0, empty_format, ' '},
		{1, empty_format, ' '},
		{2, empty_format, ' '},
		{3, empty_format, ' '},
		{4, empty_format, ' '},
		{5, empty_format, ' '},
		{6, empty_format, ' '},
		{7, empty_format, ' '},
		{8, empty_format, ' '},
		{9, empty_format, ' '},
		{10, empty_format, ' '},
		{11, full_format, ' '},
		{12, full_format, ' '},
		{13, full_format, ' '},
		{14, full_format, ' '},
		{15, full_format, ' '},
		{16, full_format, ' '},
		{17, full_format, ' '},
		{18, full_format, ' '},
		{19, full_format, ' '},
		{20, full_format, ' '},
		{22, full_format, ' '},
		{24, full_format, ' '},
		{25, empty_format, ' '}
	};

	std::vector<format_tools::index_format> index_vec2 = {
		{16, full_format, ' '},
		{14, full_format, ' '},
		{13, full_format, ' '},
		{12, full_format, ' '},
		{11, full_format, ' '},
		{24, full_format, ' '},
		{22, full_format, ' '},
		{20, full_format, ' '},
		{19, full_format, ' '},
		{18, full_format, ' '},
		{17, full_format, ' '},
		{16, full_format, ' '}
	};

	std::vector<format_tools::index_format> index_vec3 = {
		{0, empty_format, ' '},
		{1, empty_format, ' '},
		{2, empty_format, ' '},
		{3, empty_format, ' '},
		{4, empty_format, ' '},
		{5, empty_format, ' '},
		{6, empty_format, ' '},
		{7, empty_format, ' '},
		{8, empty_format, ' '},
		{9, empty_format, ' '},
		{10, empty_format, ' '},
		{21, empty_format, ' '},
	};

	std::vector<format_tools::index_format> index_vec4 = {
		{0, full_format, ' '}
	};

	std::vector<format_tools::index_format> index_vec5 = {
		{0, foreground_format, ' '}
	};

	std::vector<format_tools::index_format> index_vec6 = {
		{0, background_format, ' '}
	};

	std::vector<format_tools::index_format> index_vec7 = {
		{0, bold_format, ' '}
	};

	EXPECT_EQ(true, format_tools::present(index_vec1, index_vec2));
	EXPECT_EQ(false, format_tools::present(index_vec1, index_vec3));
	EXPECT_EQ(true, format_tools::present(index_vec4, index_vec5));
	EXPECT_EQ(true, format_tools::present(index_vec4, index_vec6));
	EXPECT_EQ(true, format_tools::present(index_vec4, index_vec7));
}

TEST_F(format_tools_test, get_min_format_index)
{
	format_tools::common_format empty_format;
	std::vector<format_tools::index_format> index_vec1 = {
		{5, empty_format, ' '},
		{4, empty_format, ' '},
		{3, empty_format, ' '},
		{2, empty_format, ' '},
		{1, empty_format, ' '},
		{25, empty_format, ' '},
		{0, empty_format, ' '},
		{10, empty_format, ' '},
		{9, empty_format, ' '},
		{8, empty_format, ' '},
		{7, empty_format, ' '},
		{6, empty_format, ' '}
	};

	int correct_answer = 6;
	int min_index = format_tools::get_min_format_index(index_vec1);
	EXPECT_EQ(min_index, correct_answer);
}

TEST_F(format_tools_test, convert_index_to_content)
{
	// vanilla case
	std::string test_string = 
		"1 1 "
		"2 2 "
		"3 3 "
		"4 4 "
		"5 5 "
		"6 6 "
		"7 7 "
		"8 8 "
		"9 9 "
		"1010"
		"  11";

	format_tools::common_format full_format;
	full_format.background_format = format_tools::white;
	full_format.foreground_format = format_tools::black;
	full_format.dec = true;
	std::vector<format_tools::index_format> index_vec = {
		{0, full_format, ' '},
		{4, full_format, ' '},
		{8, full_format, ' '},
		{12, full_format, ' '},
		{16, full_format, ' '},
		{20, full_format, ' '},
		{24, full_format, ' '},
		{28, full_format, ' '},
		{32, full_format, ' '},
		{36, full_format, ' '},
		{40, full_format, ' '}
	};

	std::vector<format_tools::content_format> correct_answer = {
		{"1 1 ", full_format},
		{"2 2 ", full_format},
		{"3 3 ", full_format},
		{"4 4 ", full_format},
		{"5 5 ", full_format},
		{"6 6 ", full_format},
		{"7 7 ", full_format},
		{"8 8 ", full_format},
		{"9 9 ", full_format},
		{"1010", full_format},
		{"  11", full_format}
	};

	format_equivalent_test(correct_answer, format_tools::convert(index_vec, test_string), 0);

	// out of order
	index_vec = {
		{4, full_format, ' '},
		{8, full_format, ' '},
		{12, full_format, ' '},
		{16, full_format, ' '},
		{20, full_format, ' '},
		{24, full_format, ' '},
		{0, full_format, ' '},
		{28, full_format, ' '},
		{32, full_format, ' '},
		{36, full_format, ' '},
		{40, full_format, ' '}
	};

	format_equivalent_test(correct_answer, format_tools::convert(index_vec, test_string), 1);

	// index out of range
	index_vec = {
		{0, full_format, ' '},
		{4, full_format, ' '},
		{8, full_format, ' '},
		{12, full_format, ' '},
		{16, full_format, ' '},
		{20, full_format, ' '},
		{24, full_format, ' '},
		{28, full_format, ' '},
		{32, full_format, ' '},
		{36, full_format, ' '},
		{40, full_format, ' '},
		{75, full_format, ' '}
	};

	format_equivalent_test(correct_answer, format_tools::convert(index_vec, test_string), 2);

	// 0 index missing
	format_tools::common_format empty_format;
	index_vec = {
		{4, full_format, ' '},
		{8, full_format, ' '},
		{12, full_format, ' '},
		{16, full_format, ' '},
		{20, full_format, ' '},
		{24, full_format, ' '},
		{28, full_format, ' '},
		{32, full_format, ' '},
		{36, full_format, ' '},
		{40, full_format, ' '}
	};

	correct_answer = {
		{"1 1 ", empty_format},
		{"2 2 ", full_format},
		{"3 3 ", full_format},
		{"4 4 ", full_format},
		{"5 5 ", full_format},
		{"6 6 ", full_format},
		{"7 7 ", full_format},
		{"8 8 ", full_format},
		{"9 9 ", full_format},
		{"1010", full_format},
		{"  11", full_format}
	};

	format_equivalent_test(correct_answer, format_tools::convert(index_vec, test_string), 3);
}

TEST_F(format_tools_test, convert_coordinate_to_index)
{
	format_tools::common_format empty_format;
	std::vector<format_tools::coordinate_format> coordinate_vec = {
		{0, 0, empty_format},
		{0, 1, empty_format},
		{0, 2, empty_format},
		{0, 3, empty_format},
		{0, 4, empty_format},
		{0, 5, empty_format},
		{0, 6, empty_format},
		{0, 7, empty_format},
		{0, 8, empty_format},
		{0, 9, empty_format},
		{0, 10, empty_format}
	};

	std::vector<format_tools::index_format> correct_answer = {
		{0, empty_format, ' '},
		{4, empty_format, ' '},
		{8, empty_format, ' '},
		{12, empty_format, ' '},
		{16, empty_format, ' '},
		{20, empty_format, ' '},
		{24, empty_format, ' '},
		{28, empty_format, ' '},
		{32, empty_format, ' '},
		{36, empty_format, ' '},
		{40, empty_format, ' '}
	};

	format_equivalent_test(correct_answer, format_tools::convert(coordinate_vec, 4), 0);
}

TEST_F(format_tools_test, convert_index_to_coordinate)
{
	format_tools::common_format empty_format;

	std::vector<format_tools::index_format> index_vec = {
		{0, empty_format, ' '},
		{4, empty_format, ' '},
		{8, empty_format, ' '},
		{12, empty_format, ' '},
		{16, empty_format, ' '},
		{20, empty_format, ' '},
		{24, empty_format, ' '},
		{28, empty_format, ' '},
		{32, empty_format, ' '},
		{36, empty_format, ' '},
		{40, empty_format, ' '}
	};

	std::vector<format_tools::coordinate_format> correct_answer = {
		{0, 0, empty_format},
		{0, 1, empty_format},
		{0, 2, empty_format},
		{0, 3, empty_format},
		{0, 4, empty_format},
		{0, 5, empty_format},
		{0, 6, empty_format},
		{0, 7, empty_format},
		{0, 8, empty_format},
		{0, 9, empty_format},
		{0, 10, empty_format}
	};

	std::vector<std::string> lines = {
		"1 1 ",
		"2 2 ",
		"3 3 ",
		"4 4 ",
		"5 5 ",
		"6 6 ",
		"7 7 ",
		"8 8 ",
		"9 9 ",
		"1010",
		"  11"
	};

	format_equivalent_test(correct_answer, format_tools::convert(index_vec, lines), 0);
}

TEST_F(format_tools_test, set_flags)
{
	std::string test_string =
		"1 1 "
		"2 2 "
		"3 3 "
		"4 4 "
		"5 5 "
		"6 6 "
		"7 7 "
		"8 8 "
		"9 9 "
		"1010"
		"  11";

	format_tools::common_format empty_format;
	std::vector<format_tools::index_format> index_vec = {
		{0, empty_format, ' '},
		{4, empty_format, ' '},
		{8, empty_format, ' '},
		{12, empty_format, ' '},
		{16, empty_format, ' '},
		{20, empty_format, ' '},
		{24, empty_format, ' '},
		{28, empty_format, ' '},
		{32, empty_format, ' '},
		{36, empty_format, ' '},
		{40, empty_format, ' '}
	};

	std::string correct_answer =
		"* 1 "
		"* 2 "
		"* 3 "
		"* 4 "
		"* 5 "
		"* 6 "
		"* 7 "
		"* 8 "
		"* 9 "
		"*010"
		"* 11";

	std::vector<char> correct_flag_replacements =
	{
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'1',
		' ',
	};

	format_tools::set_flags(index_vec, test_string, '*');
	ASSERT_EQ(index_vec.size(), correct_flag_replacements.size());
	for (unsigned int i = 0; i < index_vec.size(); i++)
	{
		EXPECT_EQ(index_vec[i].flag_replacement, correct_flag_replacements[i]) << "Index: " + std::to_string(i);
	}
	EXPECT_EQ(test_string, correct_answer);
}

TEST_F(format_tools_test, remove_flags)
{
	std::vector<std::string> test_lines =
	{
		"* 1 ",
		"* 2 ",
		"* 3 ",
		"* 4 ",
		"* 5 ",
		"* 6 ",
		"* 7 ",
		"* 8 ",
		"* 9 ",
		"*010",
		"* 11"
	};

	format_tools::common_format empty_format;
	std::vector<format_tools::index_format> index_vec = {
		{0, empty_format, '1'},
		{4, empty_format, '2'},
		{8, empty_format, '3'},
		{12, empty_format, '4'},
		{16, empty_format, '5'},
		{20, empty_format, '6'},
		{24, empty_format, '7'},
		{28, empty_format, '8'},
		{32, empty_format, '9'},
		{36, empty_format, '1'},
		{40, empty_format, ' '}
	};

	std::vector<std::string> correct_answer =
	{
		"1 1 ",
		"2 2 ",
		"3 3 ",
		"4 4 ",
		"5 5 ",
		"6 6 ",
		"7 7 ",
		"8 8 ",
		"9 9 ",
		"1010",
		"  11"
	};

	std::vector<int> ignore_flags;

	test_lines = format_tools::remove_flags(index_vec, ignore_flags, test_lines, '*');
	ASSERT_EQ(correct_answer.size(), test_lines.size());
	for (unsigned int i = 0; i < correct_answer.size(); i++)
	{
		EXPECT_EQ(correct_answer[i], test_lines[i]) << "Index: " + std::to_string(i);
	}

	test_lines =
	{
		"* 1 ",
		"* 2 ",
		"* 3 ",
		"* 4 ",
		"* 5 ",
		"* 6 ",
		"* 7 ",
		"* 8 ",
		"* 9 ",
		"*010",
		"* 11"
	};

	index_vec = {
		{0, empty_format, '1'},
		{4, empty_format, '2'},
		{8, empty_format, '3'},
		{12, empty_format, '4'},
		{20, empty_format, '6'},
		{24, empty_format, '7'},
		{28, empty_format, '8'},
		{32, empty_format, '9'},
		{36, empty_format, '1'},
		{40, empty_format, ' '}
	};

	correct_answer =
	{
		"1 1 ",
		"2 2 ",
		"3 3 ",
		"4 4 ",
		"* 5 ",
		"6 6 ",
		"7 7 ",
		"8 8 ",
		"9 9 ",
		"1010",
		"  11"
	};

	ignore_flags.push_back(4);

	test_lines = format_tools::remove_flags(index_vec, ignore_flags, test_lines, '*');
	ASSERT_EQ(correct_answer.size(), test_lines.size());
	for (unsigned int i = 0; i < correct_answer.size(); i++)
	{
		EXPECT_EQ(correct_answer[i], test_lines[i]) << "Index: " + std::to_string(i);
	}
}

TEST_F(format_tools_test, convert_flags)
{
	std::vector<std::string> lines = {
		"* 1 ",
		"* 2 ",
		"* 3 ",
		"* 4 ",
		"* 5 ",
		"* 6 ",
		"* 7 ",
		"* 8 ",
		"* 9 ",
		"*010",
		"* 11"
	};

	format_tools::common_format empty_format;
	std::vector<format_tools::index_format> index_vec = {
		{0, empty_format, '1'},
		{4, empty_format, '2'},
		{8, empty_format, '3'},
		{12, empty_format, '4'},
		{16, empty_format, '5'},
		{20, empty_format, '6'},
		{24, empty_format, '7'},
		{28, empty_format, '8'},
		{32, empty_format, '9'},
		{36, empty_format, '1'},
		{40, empty_format, ' '}
	};

	std::vector<int> ignore_flags;
	std::vector<format_tools::coordinate_format> coordinate_vec;
	std::vector<std::string> correct_lines = {
		"1 1 ",
		"2 2 ",
		"3 3 ",
		"4 4 ",
		"5 5 ",
		"6 6 ",
		"7 7 ",
		"8 8 ",
		"9 9 ",
		"1010",
		"  11"
	};

	std::vector<format_tools::coordinate_format> correct_coordinate_vec = {
		{0, 0, empty_format},
		{0, 1, empty_format},
		{0, 2, empty_format},
		{0, 3, empty_format},
		{0, 4, empty_format},
		{0, 5, empty_format},
		{0, 6, empty_format},
		{0, 7, empty_format},
		{0, 8, empty_format},
		{0, 9, empty_format},
		{0, 10, empty_format}
	};

	format_tools::convert_flags(coordinate_vec, index_vec, ignore_flags, lines, '*');
	format_equivalent_test(correct_coordinate_vec, coordinate_vec, 0);

	ASSERT_EQ(lines.size(), correct_lines.size());
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		EXPECT_EQ(lines[i], correct_lines[i]) << "Index: " + std::to_string(i);
	}

	lines = {
		"* 1 ",
		"* 2 ",
		"* 3 ",
		"* 4 ",
		"* 5*",
		"* 6 ",
		"* 7 ",
		"* 8 ",
		"* 9 ",
		"*010",
		"* 11"
	};

	correct_lines = {
		"1 1 ",
		"2 2 ",
		"3 3 ",
		"4 4 ",
		"5 5*",
		"6 6 ",
		"7 7 ",
		"8 8 ",
		"9 9 ",
		"1010",
		"  11"
	};

	ignore_flags.push_back(5);

	format_tools::convert_flags(coordinate_vec, index_vec, ignore_flags, lines, '*');
	format_equivalent_test(correct_coordinate_vec, coordinate_vec, 1);

	ASSERT_EQ(lines.size(), correct_lines.size());
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		EXPECT_EQ(lines[i], correct_lines[i]) << "Index: " + std::to_string(i);
	}
}

TEST_F(format_tools_test, fit_to_width)
{
	format_tools::common_format empty_format;
	format_tools::common_format full_format;
	full_format.background_format = format_tools::white;
	full_format.foreground_format = format_tools::black;
	full_format.dec = true;
	std::vector<format_tools::content_format> content_vec = {
		{"1 1 ", empty_format},
		{"2 2 ", full_format},
		{"3 3 ", empty_format},
		{"4 4 ", full_format},
		{"5 5 ", empty_format},
		{"6 6 ", full_format},
		{"7 7 ", empty_format},
		{"8 8 ", full_format},
		{"9 9 ", empty_format},
		{"1010", full_format},
		{"  11", empty_format}
	};

	std::vector<format_tools::content_format> correct_answer = {
		{"1 1", empty_format},
		{" ", empty_format},
		{"2 ", full_format},
		{"2 ", full_format},
		{"3", empty_format},
		{" 3 ", empty_format},
		{"4 4", full_format},
		{" ", full_format},
		{"5 ", empty_format},
		{"5 ", empty_format},
		{"6", full_format},
		{" 6 ", full_format},
		{"7 7", empty_format},
		{" ", empty_format},
		{"8 ", full_format},
		{"8 ", full_format},
		{"9", empty_format},
		{" 9 ", empty_format},
		{"101", full_format},
		{"0", full_format},
		{"  ", empty_format},
		{"11", empty_format}
	};

	format_equivalent_test(correct_answer, format_tools::fit_to_width(content_vec, 3), 0);
}

TEST_F(format_tools_test, remove_newline_characters_vector)
{
	std::vector<std::string> test_vector = {
		"1 1 \n",
		"2 2 \n",
		"3 3 \n",
		"4 4 \n",
		"5 5 \n",
		"6 6 \n",
		"7 7 \n",
		"8 8 \n",
		"9 9 \n",
		"1010\n",
		"  11\n",
		"    \n",
		"    \n"
	};

	std::vector<std::string> correct_answer = {
		"1 1 ",
		"2 2 ",
		"3 3 ",
		"4 4 ",
		"5 5 ",
		"6 6 ",
		"7 7 ",
		"8 8 ",
		"9 9 ",
		"1010",
		"  11",
		"    ",
		"    "
	};

	std::vector<std::string> cleaned_vector = format_tools::remove_newline_characters(test_vector);
	ASSERT_EQ(cleaned_vector.size(), correct_answer.size());
	for (unsigned int i = 0; i < cleaned_vector.size(); i++)
	{
		EXPECT_EQ(cleaned_vector[i], correct_answer[i]) << "Index: " + std::to_string(i);
	}

	test_vector = {
		"1 1 \n",
		"2 2 \n",
		"3 3 \n",
		"4 4 \n",
		"5 5 \n",
		"6 6 \n",
		"7 7 \n",
		"8 8 \n",
		"9 9 \n",
		"1010\n",
		"  11\n",
		"   \n ",
		"\n"
	};

	correct_answer = {
		"1 1 ",
		"2 2 ",
		"3 3 ",
		"4 4 ",
		"5 5 ",
		"6 6 ",
		"7 7 ",
		"8 8 ",
		"9 9 ",
		"1010",
		"  11",
		"   \n ",
		""
	};

	cleaned_vector = format_tools::remove_newline_characters(test_vector);
	ASSERT_EQ(cleaned_vector.size(), correct_answer.size());
	for (unsigned int i = 0; i < cleaned_vector.size(); i++)
	{
		EXPECT_EQ(cleaned_vector[i], correct_answer[i]) << "Index: " + std::to_string(i);
	}
}

TEST_F(format_tools_test, get_first_line_length)
{
	std::string test_string =
		"1 1 \n"
		"2 2 \n"
		"3 3 \n"
		"4 4 \n"
		"5 5 \n"
		"6 6 \n"
		"7 7 \n"
		"8 8 \n"
		"9 9 \n"
		"1010\n"
		"  11\n"
		"    \n"
		"    \n";

	unsigned int correct_answer = 5;
	unsigned int first_line_length = format_tools::get_first_line_length(test_string);
	EXPECT_EQ(first_line_length, correct_answer);

	test_string =
		"1 1 1 1 1 \n"
		"2 2 \n"
		"3 3 \n"
		"4 4 \n"
		"5 5 \n"
		"6 6 \n"
		"7 7 \n"
		"8 8 \n"
		"9 9 \n"
		"1010\n"
		"  11\n"
		"    \n"
		"    \n";

	correct_answer = 11;
	first_line_length = format_tools::get_first_line_length(test_string);
	EXPECT_EQ(first_line_length, correct_answer);
}

TEST_F(format_tools_test, shift_index)
{
	format_tools::common_format empty_format;
	std::vector<format_tools::index_format> colors =
	{
		{5, empty_format, ' '},
		{10, empty_format, ' '},
		{15, empty_format, ' '}
	};

	std::vector<format_tools::index_format> correct_answer_shift_right =
	{
		{7, empty_format, ' '},
		{12, empty_format, ' '},
		{17, empty_format, ' '}
	};

	std::vector<format_tools::index_format> correct_answer_shift_left =
	{
		{3, empty_format, ' '},
		{8, empty_format, ' '},
		{13, empty_format, ' '}
	};

	std::vector<format_tools::index_format> correct_answer_shift_left_far =
	{
		{3, empty_format, ' '},
		{8, empty_format, ' '}
	};


	format_equivalent_test(correct_answer_shift_right, format_tools::shift_index(colors, 2), 0);
	format_equivalent_test(correct_answer_shift_left, format_tools::shift_index(colors, -2), 1);
	format_equivalent_test(correct_answer_shift_left_far, format_tools::shift_index(colors, -7), 2);
}

TEST_F(format_tools_test, bound_colors)
{
	std::vector<std::string> lines =
	{
		"012",
		"345",
		"678",
		"910"
	};

	format_tools::common_format empty_format;
	format_tools::common_format green_foreground;
	format_tools::common_format green_background;
	green_foreground.foreground_format = format_tools::green;
	green_background.background_format = format_tools::green;

	std::vector<format_tools::coordinate_format> colors =
	{
		{1, 0, green_foreground},
		{0, 1, green_background},
		{2, 2, green_foreground}
	};

	std::vector<format_tools::coordinate_format> colors_answer =
	{
		{1, 0, green_foreground},
		{3, 0, empty_format},
		{0, 1, green_background},
		{3, 1, empty_format},
		{0, 2, green_background},
		{2, 2, green_foreground},
		{3, 2, empty_format},
		{0, 3, green_foreground},
		{3, 3, empty_format}
	};

	format_equivalent_test(colors_answer, format_tools::bound_colors(colors, lines), 0);
}

TEST_F(format_tools_test, build_color_for_value_test)
{
	std::string o_value = "**//'\\\\**"
						  "**|   |**"
						  "**\\\\.//**";

	std::string edge_value = "||     ||"
							 "||     ||"
							 "||     ||";

	std::string edge_value_2 = "||*****||"
							   "||*****||"
							   "||*****||";


	format_tools::common_format empty_color;
	format_tools::common_format green_foreground_color = { format_tools::green, format_tools::none, false, false };
	format_tools::common_format red_background_color = { format_tools::none, format_tools::red, false, false };
	format_tools::common_format green_foreground_red_background_color = { format_tools::green, format_tools::red, false, false };
	format_tools::common_format bold_green_foreground_color = { format_tools::green, format_tools::none, true, false };

	std::vector<format_tools::index_format> o_green_foreground_correct_answer =
	{
		{2, green_foreground_color, ' '},
		{7, empty_color, ' '},
		{11, green_foreground_color, ' '},
		{12, empty_color, ' '},
		{15, green_foreground_color, ' '},
		{16, empty_color, ' '},
		{20, green_foreground_color, ' '},
		{25, empty_color, ' '}
	};

	std::vector<format_tools::index_format> o_red_background_correct_answer =
	{
		{2, red_background_color, ' '},
		{7, empty_color, ' '},
		{11, red_background_color, ' '},
		{12, empty_color, ' '},
		{15, red_background_color, ' '},
		{16, empty_color, ' '},
		{20, red_background_color, ' '},
		{25, empty_color, ' '}
	};

	std::vector<format_tools::index_format> o_green_foreground_red_background_correct_answer =
	{
		{2, green_foreground_red_background_color, ' '},
		{7, empty_color, ' '},
		{11, green_foreground_red_background_color, ' '},
		{12, empty_color, ' '},
		{15, green_foreground_red_background_color, ' '},
		{16, empty_color, ' '},
		{20, green_foreground_red_background_color, ' '},
		{25, empty_color, ' '}
	};

	std::vector<format_tools::index_format> o_bold_green_foreground_correct_answer =
	{
		{2, bold_green_foreground_color, ' '},
		{7, empty_color, ' '},
		{11, bold_green_foreground_color, ' '},
		{12, empty_color, ' '},
		{15, bold_green_foreground_color, ' '},
		{16, empty_color, ' '},
		{20, bold_green_foreground_color, ' '},
		{25, empty_color, ' '}
	};

	std::vector<format_tools::index_format> o_green_foreground_include_spaces_correct_answer =
	{
		{2, green_foreground_color, ' '},
		{7, empty_color, ' '},
		{11, green_foreground_color, ' '},
		{16, empty_color, ' '},
		{20, green_foreground_color, ' '},
		{25, empty_color, ' '}
	};

	std::vector<format_tools::index_format> edge_green_foreground_correct_answer =
	{
		{0, green_foreground_color, ' '},
		{2, empty_color, ' '},
		{7, green_foreground_color, ' '},
		{11, empty_color, ' '},
		{16, green_foreground_color, ' '},
		{20, empty_color, ' '},
		{25, green_foreground_color, ' '}
	};

	std::vector<format_tools::index_format> edge_green_foreground_include_spaces_correct_answer =
	{
		{0, green_foreground_color, ' '}
	};

	format_equivalent_test(o_green_foreground_correct_answer, format_tools::build_color_for_value(o_value, '*', format_tools::green, format_tools::none, false), 0);
	format_equivalent_test(o_red_background_correct_answer, format_tools::build_color_for_value(o_value, '*', format_tools::none, format_tools::red, false), 1);
	format_equivalent_test(o_green_foreground_red_background_correct_answer, format_tools::build_color_for_value(o_value, '*', format_tools::green, format_tools::red, false), 2);
	format_equivalent_test(o_bold_green_foreground_correct_answer, format_tools::build_color_for_value(o_value, '*', format_tools::green, format_tools::none, true), 3);
	format_equivalent_test(o_green_foreground_include_spaces_correct_answer, format_tools::build_color_for_value(o_value, '*', format_tools::green, format_tools::none, false, true), 4);
	format_equivalent_test(edge_green_foreground_correct_answer, format_tools::build_color_for_value(edge_value, '*', format_tools::green, format_tools::none, false), 5);
	format_equivalent_test(edge_green_foreground_include_spaces_correct_answer, format_tools::build_color_for_value(edge_value, '*', format_tools::green, format_tools::none, false, true), 6);
	format_equivalent_test(edge_green_foreground_correct_answer, format_tools::build_color_for_value(edge_value_2, '*', format_tools::green, format_tools::none, false), 7);
	format_equivalent_test(edge_green_foreground_correct_answer, format_tools::build_color_for_value(edge_value_2, '*', format_tools::green, format_tools::none, false, true), 8);
}

TEST_F(format_tools_test, empty_format_test)
{
	format_tools::common_format empty_format;
	format_tools::common_format foreground_format = { format_tools::green, format_tools::none, false, false };
	format_tools::common_format background_format = { format_tools::none, format_tools::green, false, false };
	format_tools::common_format bold_format = { format_tools::none, format_tools::none, true, false };
	format_tools::common_format dec_format = { format_tools::none, format_tools::none, false, true };

	EXPECT_EQ(true, format_tools::format_empty(empty_format));
	EXPECT_EQ(false, format_tools::format_empty(foreground_format));
	EXPECT_EQ(false, format_tools::format_empty(background_format));
	EXPECT_EQ(false, format_tools::format_empty(bold_format));
	EXPECT_EQ(false, format_tools::format_empty(dec_format));
}

TEST_F(format_tools_test, compress)
{
	unsigned int value = 17;
	unsigned int remainder = 0;

	unsigned int correct_compressed_value = 5;
	unsigned int correct_remainder = 2;

	unsigned int compressed_value = format_tools::compress(value, 3, remainder);

	EXPECT_EQ(compressed_value, correct_compressed_value);
	EXPECT_EQ(remainder, correct_remainder);

	correct_compressed_value = 17;
	correct_remainder = 0;

	remainder = 0;

	compressed_value = format_tools::compress(value, 0, remainder);

	EXPECT_EQ(compressed_value, correct_compressed_value);
	EXPECT_EQ(remainder, correct_remainder);
}

TEST_F(format_tools_test, expand)
{
	unsigned int value = 5;
	unsigned int remainder = 2;

	unsigned int correct_expanded_value = 17;

	unsigned int expanded_value = format_tools::expand(value, 3, remainder);

	EXPECT_EQ(expanded_value, correct_expanded_value);

	correct_expanded_value = 5;

	expanded_value = format_tools::expand(value, 0, remainder);

	EXPECT_EQ(expanded_value, correct_expanded_value);
}