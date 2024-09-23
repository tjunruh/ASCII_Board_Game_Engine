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

TEST_F(format_tools_test, sort)
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

	index_vec = format_tools::sort(index_vec);
	ASSERT_EQ(index_vec.size(), correct_answer.size());
	for (unsigned int i = 0; i < index_vec.size(); i++)
	{
		EXPECT_EQ(index_vec[i].index, correct_answer[i].index) << "Index: " + std::to_string(i);
		EXPECT_EQ(index_vec[i].flag_replacement, correct_answer[i].flag_replacement) << "Index: " + std::to_string(i);
		EXPECT_EQ(index_vec[i].format.background_format, correct_answer[i].format.background_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(index_vec[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(index_vec[i].format.dec, correct_answer[i].format.dec) << "Index: " + std::to_string(i);
	}
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

	std::vector<format_tools::index_format> combined_vec = format_tools::combine(index_vec1, index_vec2);
	ASSERT_EQ(combined_vec.size(), correct_answer.size());
	for (unsigned int i = 0; i < combined_vec.size(); i++)
	{
		EXPECT_EQ(combined_vec[i].index, correct_answer[i].index) << "Index: " + std::to_string(i);
		EXPECT_EQ(combined_vec[i].flag_replacement, correct_answer[i].flag_replacement) << "Index: " + std::to_string(i);
		EXPECT_EQ(combined_vec[i].format.background_format, correct_answer[i].format.background_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(combined_vec[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(combined_vec[i].format.dec, correct_answer[i].format.dec) << "Index: " + std::to_string(i);
	}

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

	combined_vec = format_tools::combine(index_vec1, index_vec2);
	ASSERT_EQ(combined_vec.size(), correct_answer.size());
	for (unsigned int i = 0; i < combined_vec.size(); i++)
	{
		EXPECT_EQ(combined_vec[i].index, correct_answer[i].index) << "Index: " + std::to_string(i);
		EXPECT_EQ(combined_vec[i].flag_replacement, correct_answer[i].flag_replacement) << "Index: " + std::to_string(i);
		EXPECT_EQ(combined_vec[i].format.background_format, correct_answer[i].format.background_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(combined_vec[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(combined_vec[i].format.dec, correct_answer[i].format.dec) << "Index: " + std::to_string(i);
	}
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

	std::vector<format_tools::content_format> content_vec = format_tools::convert(index_vec, test_string);
	ASSERT_EQ(content_vec.size(), correct_answer.size());
	for (unsigned int i = 0; i < content_vec.size(); i++)
	{
		EXPECT_EQ(content_vec[i].content, correct_answer[i].content) << "Index: " + std::to_string(i);
		EXPECT_EQ(content_vec[i].format.background_format, correct_answer[i].format.background_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(content_vec[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(content_vec[i].format.dec, correct_answer[i].format.dec) << "Index: " + std::to_string(i);
	}

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

	content_vec = format_tools::convert(index_vec, test_string);
	ASSERT_EQ(content_vec.size(), correct_answer.size());
	for (unsigned int i = 0; i < content_vec.size(); i++)
	{
		EXPECT_EQ(content_vec[i].content, correct_answer[i].content) << "Index: " + std::to_string(i);
		EXPECT_EQ(content_vec[i].format.background_format, correct_answer[i].format.background_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(content_vec[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(content_vec[i].format.dec, correct_answer[i].format.dec) << "Index: " + std::to_string(i);
	}

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

	content_vec = format_tools::convert(index_vec, test_string);
	ASSERT_EQ(content_vec.size(), correct_answer.size());
	for (unsigned int i = 0; i < content_vec.size(); i++)
	{
		EXPECT_EQ(content_vec[i].content, correct_answer[i].content) << "Index: " + std::to_string(i);
		EXPECT_EQ(content_vec[i].format.background_format, correct_answer[i].format.background_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(content_vec[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(content_vec[i].format.dec, correct_answer[i].format.dec) << "Index: " + std::to_string(i);
	}

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

	content_vec = format_tools::convert(index_vec, test_string);
	ASSERT_EQ(content_vec.size(), correct_answer.size());
	for (unsigned int i = 0; i < content_vec.size(); i++)
	{
		EXPECT_EQ(content_vec[i].content, correct_answer[i].content) << "Index: " + std::to_string(i);
		EXPECT_EQ(content_vec[i].format.background_format, correct_answer[i].format.background_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(content_vec[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(content_vec[i].format.dec, correct_answer[i].format.dec) << "Index: " + std::to_string(i);
	}
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

	std::vector<format_tools::index_format> converted_vec = format_tools::convert(coordinate_vec, 4);
	ASSERT_EQ(converted_vec.size(), correct_answer.size());
	for (unsigned int i = 0; i < converted_vec.size(); i++)
	{
		EXPECT_EQ(converted_vec[i].index, correct_answer[i].index) << "Index: " + std::to_string(i);
		EXPECT_EQ(converted_vec[i].flag_replacement, correct_answer[i].flag_replacement) << "Index: " + std::to_string(i);
		EXPECT_EQ(converted_vec[i].format.background_format, correct_answer[i].format.background_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(converted_vec[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(converted_vec[i].format.dec, correct_answer[i].format.dec) << "Index: " + std::to_string(i);
	}
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
		

	std::vector<format_tools::coordinate_format> converted_vec = format_tools::convert(index_vec, lines);
	ASSERT_EQ(converted_vec.size(), correct_answer.size());
	for (unsigned int i = 0; i < converted_vec.size(); i++)
	{
		EXPECT_EQ(converted_vec[i].x_position, correct_answer[i].x_position) << "Index: " + std::to_string(i);
		EXPECT_EQ(converted_vec[i].y_position, correct_answer[i].y_position) << "Index: " + std::to_string(i);
		EXPECT_EQ(converted_vec[i].format.background_format, correct_answer[i].format.background_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(converted_vec[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(converted_vec[i].format.dec, correct_answer[i].format.dec) << "Index: " + std::to_string(i);
	}
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
	ASSERT_EQ(coordinate_vec.size(), correct_coordinate_vec.size());
	for (unsigned int i = 0; i < coordinate_vec.size(); i++)
	{
		EXPECT_EQ(coordinate_vec[i].x_position, correct_coordinate_vec[i].x_position) << "Index: " + std::to_string(i);
		EXPECT_EQ(coordinate_vec[i].y_position, correct_coordinate_vec[i].y_position) << "Index: " + std::to_string(i);
		EXPECT_EQ(coordinate_vec[i].format.background_format, correct_coordinate_vec[i].format.background_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(coordinate_vec[i].format.foreground_format, correct_coordinate_vec[i].format.foreground_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(coordinate_vec[i].format.dec, correct_coordinate_vec[i].format.dec) << "Index: " + std::to_string(i);
	}
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
	ASSERT_EQ(coordinate_vec.size(), correct_coordinate_vec.size());
	for (unsigned int i = 0; i < coordinate_vec.size(); i++)
	{
		EXPECT_EQ(coordinate_vec[i].x_position, correct_coordinate_vec[i].x_position) << "Index: " + std::to_string(i);
		EXPECT_EQ(coordinate_vec[i].y_position, correct_coordinate_vec[i].y_position) << "Index: " + std::to_string(i);
		EXPECT_EQ(coordinate_vec[i].format.background_format, correct_coordinate_vec[i].format.background_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(coordinate_vec[i].format.foreground_format, correct_coordinate_vec[i].format.foreground_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(coordinate_vec[i].format.dec, correct_coordinate_vec[i].format.dec) << "Index: " + std::to_string(i);
	}
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

	std::vector<format_tools::content_format> modified_vec = format_tools::fit_to_width(content_vec, 3);
	ASSERT_EQ(modified_vec.size(), correct_answer.size());
	for (unsigned int i = 0; i < modified_vec.size(); i++)
	{
		EXPECT_EQ(modified_vec[i].content, correct_answer[i].content) << "Index: " + std::to_string(i);
		EXPECT_EQ(modified_vec[i].format.background_format, correct_answer[i].format.background_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(modified_vec[i].format.foreground_format, correct_answer[i].format.foreground_format) << "Index: " + std::to_string(i);
		EXPECT_EQ(modified_vec[i].format.dec, correct_answer[i].format.dec) << "Index: " + std::to_string(i);
	}
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