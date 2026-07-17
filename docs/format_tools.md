# format_tools API

format_tools includes functions providing the ability to perform fromatting operations on strings and vectors of strings. There primary task is to be used by other classes in ASCII_Board_Game_Engine, but they are made available to use in an API also. Functions in the format_tools namespace include:

```
std::vector<std::string> split_string(std::string str, char split_character)
void cut_word(const std::string& word, unsigned int length, std::string& first_section, std::string& second_section)
std::string get_spacing(unsigned int length, char space_char)
std::string fill_line(std::string input, unsigned int length, std::string alignment)
std::vector<std::string> fill_lines(std::vector<std::string> input, unsigned int length, std::string alignment)
std::vector<std::string> add_lines(std::vector<std::string> lines, unsigned int number_of_added_lines, unsigned int line_length)
std::string fuse_columns_into_row(text_column data, unsigned int& lines)
std::vector<std::string> get_lines(const std::string& output_string)
std::vector<std::string> get_lines(const std::string& content, unsigned int width, unsigned int current_position=0)
std::string get_string(const std::vector<std::string>& lines)
std::vector<std::string> remove_trailing_whitespace(const std::vector<std::string>& lines)
void remove_newline_characters(std::string& text)
int calculate_flag_number(const std::vector<index_format>& index_colors, int index)
bool index_found(const std::vector<index_format>& index_colors, int index)
std::vector<index_format> combine(const std::vector<index_format>& format_1, const std::vector<index_format>& format_2)
bool present(const std::vector<index_format>& main_format, const std::vector<index_format>& check_format)
std::vector<content_format> convert(std::vector<index_format> index_vec, const std::string& content)
std::vector<index_format> convert(std::vector<coordinate_format> coordinate_vec, int width)
std::vector<coordinate_format> convert(const std::vector<index_format>& index_vec, const std::vector<std::string>& lines)
std::vector<int> set_flags(std::vector<index_format>& index_colors, std::string& content, char flag)
std::vector<std::string> remove_flags(const std::vector<index_format>& index_colors, std::vector<int> ignore_flags, std::vector<std::string> lines, char flag)
void convert_flags(std::vector<coordinate_format>& coordinate_colors, const std::vector<index_format>& index_colors, std::vector<int> ignore_flags, std::vector<std::string>& lines, char flag)
std::vector<content_format> fit_to_width(const std::vector<content_format>& content_vec, unsigned int width)
std::vector<std::string> remove_newline_characters(std::vector<std::string> lines)
std::vector<std::string> add_newline_characters(std::vector<std::string> lines)
unsigned int get_first_line_length(const std::string& content)
std::string get_color_name(int color)
std::vector<index_format> shift_index(std::vector<index_format> index_colors, int shift_amount)
std::vector<index_format> build_color_for_value(const std::string& value, char ignore_character, int foreground_format, int background_format, bool bold, bool include_spaces = false)
int get_color_line(const index_format& color, const std::vector<std::string>& lines)
bool format_empty(const common_format& format)
unsigned int compress(unsigned int value, unsigned int compression, unsigned int& remainder)
unsigned int expand(unsigned int value, unsigned int expansion, unsigned int remainder)
```

Structures provided in the format_tools namespace include:

```
struct common_format
{
	int foreground_format = none;
	int background_format = none;
	bool bold = false;
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
```

---
# Function Descriptions
---
## split_string
**std::vector<std::string> split_string(std::string str, char split_character)**
```
Description:
split string into sections separated by a specified character

Parameters:
std::string str - string to be split
char split_character - character that should indicate where the string should be split

Return value:
std::vector<std::string> - vector of strings that have been split from input string (note that the split_character is included in the vector between every split)
```

---
## cut_word
**void cut_word(const std::string& word, unsigned int length, std::string& first_section, std::string& second_section)**
```
Description:
cuts string into two sections at specified point in the string

Parameters:
const std::string& word - input string that should be split into two sections
unsigned int length - length of the first section extracted from input string
std::string& first_section - output string extracted from beginning of first string
std::string& second_section - output string extracted from the remainder of the input string
```

---
## get_spacing
**std::string get_spacing(unsigned int length, char space_char)**
```
Description:
creates a string of specified length composed of a single type of character

Parameters:
unsigned int length - length that the created spacer should be
char space_char - character that should be used to create the spacer

Return value:
std::string - spacer composed of specified character and specified length
```

---
## fill_line
**std::string fill_line(std::string input, unsigned int length, std::string alignment)**
```
Description:
fills string with spaces either at beginning of string, end of string, or both according to alignment to reach specified length (Note that newline characters should be removed from input string before using this function)

Parameters:
std::string input - input string to be filled with spaces
unsigned int length - length that output string should be
std::string alignment - alignment of output string ("right", "left", or "center")

Return value:
std::string - filled string according to length and alignment
```

---
## fill_lines
**std::vector<std::string> fill_lines(std::vector<std::string> input, unsigned int length, std::string alignment)**
```
Description:
fills multiple lines with spaces either at beginning of strings, end of strings, or both according to alignment to reach specified length (Note that newline characters should be removed from input lines before using this function)

Parameters:
std::vector<std::string> input - input lines that should be filled with spaces
unsigned int length - length that output lines should be
std::string alignment - alignment of output lines ("right, "left", "center", or "center block")

Return value:
std::vector<std::string> filled lines acoording to length and alignment
```

---
## add_lines
**std::vector<std::string> add_lines(std::vector<std::string> lines, unsigned int number_of_added_lines, unsigned int line_length)**
```
Description:
appends lines full of spaces to end of input vector

Parameters:
std::vector<std::string> lines - input lines that should have empty lines appended to
unsigned int number_of_added_lines - number of lines full of spaces that should be appended to the end of the input lines
unsinged int line_length - length that the appended lines should be

Return value:
std::vector<std::string> - input lines plus empty lines appended to the end
```

---
## fuse_columns_into_row
**std::string fuse_columns_into_row(text_column data, unsigned int& lines)**
```
Description:
fuses lines from different columns together to form a single row of lines (shorter columns will be filled out with empty lines of length specified in text_column structure)

Parameters:
text_column data - text_column structure containing vector of lines and vector of lengths of each column of lines
unsigned int& lines - returned number of lines in longest column

Return value:
std::string - string generated from fusing columns together
```

---
## get_lines
**std::vector<std::string> get_lines(const std::string& output_string)**
```
Description:
converts string into vector of strings by creating a new string in the vector after every '\n' character in the input string

Parameters:
const std::string& output_string - input string that should be parsed into lines

Return value:
std::vector<std::string> - lines parsed from input string
```

---
## get_lines
**std::vector<std::string> get_lines(const std::string& content, unsigned int width, unsigned int current_position=0)**
```
Description:
parses input string into lines of specified width with exception of first line optionally starting at a index greater than 0 and less than width

Parameters:
const std::string& content - input string that should be parsed into lines
unsigned int width - length that lines should be
unsinged int current_position - position where the string should start being parsed into the first line (should be less than width)

Return value
std::vector<std::string> - lines parsed from input string
```

---
## get_string
**std::string get_string(const std::vector<std::string>& lines)**
```
Description:
wraps lines in vector into string

Parameters:
const std::vector<std::string>& lines - vector of strings or lines that should be wrapped around into a single string

Return value:
std::string - string created by wrapping lines into single string
```

---
## remove_trailing_whitespace
**std::vector<std::string> remove_trailing_whitespace(const std::vector<std::string>& lines)**
```
Description:
removes any spaces at the end of lines or empty lines full of spaces appended to end of vector (will not remove '\n' characters at the end of lines containing text

Parameters:
const std::vector<std::string>& lines - input lines to have trailing whitespace removed

Return value:
std::vector<std::string> - vector removed of trailing whitespace
```

---
## remove_newline_characters
**void remove_newline_characters(std::string& text)**
```
Description:
removes all '\n' characters from string

Parameters:
std::string& text - string to have all '\n' characters removed from
```

---
## calculate_flag_number
**int calculate_flag_number(const std::vector<index_format>& index_colors, int index)**
```
Description:
counts the number of index_format structures in vector with index less than specified index

Parameters:
const std::vector<index_format>& index_colors - vector of index_format structures to be analyzed
int index - index defining benchmark to count number of strucutres with index less than

Return value:
int - number of structures in vector with index less than specified index
```

---
## index_found
**bool index_found(const std::vector<index_format>& index_colors, int index)**
```
Description:
determines if any structures in vector have specified index

Parameters:
const std::vector<index_format>& index_colors - vector containing index_format structures to be analyzed
int index - index to compare with indexes of index_format structures in vector

Return value:
bool - true if index found and false if not found
```

---
## combine
**std::vector<index_format> combine(const std::vector<index_format>& format_1, const std::vector<index_format>& format_2)**
```
Description:
combines two vectors for index_format structures into one vector sorted from lowest index to highest index (if the two vectors have any structures with equal indexes, the two structures are merged into a single structure with true and non-none values are kept

Parameters:
const std::vector<index_format>& format_1 - first vector of index_format structures
const std::vector<index_format>& format_2 - second vector of index_format_structures

Return value:
std::vector<index_format> - combined vector sorted from lowest index to highest index
```

---
## present
**bool present(const std::vector<index_format>& main_format, const std::vector<index_format>& check_format)**
```
Description:
returns true if all element from check_format are present in main_format (will ignore elements in check_format that have no color and are not bold)

Parameters:
const std::vector<index_format>& main_format - vector of index_format structures to be searched
const std::vector<index_format>& check_format - vector of index_format structures defining elements to be searched for in main_format

Return value:
bool - true if all elements from check_format are in main_format and false otherwise (will ignore elements in check_format that have no color and are not bold)
```

---
## convert
**std::vector<content_format> convert(std::vector<index_format> index_vec, const std::string& content)**
```
Description:
convert vector of index_format structures into vector of content_format structures

Parameters:
std::vector<index_format> index_vec - vector of index_format structures to be converted
const std::string& content - content to have content parsed from based on indexes provided in index_format structures and stored in content_format structures

Return value:
std::vector<content_format> - vector of content_format structures generated from input index_vec and content
```

---
## convert
**std::vector<index_format> convert(std::vector<coordinate_format> coordinate_vec, int width)**
```
Description:
convert vector of coordinate_format structures into vector of index_format structures

Parameters:
std::vector<coordinate_format> coordinate_vec - vector of coordinate_format structures to be converted
int width - width of lines (used to accuratly convert two dimensional coordinates into one dimensional indexes (the assumption is made that all lines are of the same length))

Return value:
std::vector<index_format> - vector of index_format structures generated from input coordinate_vec and width
```

---
## convert
**std::vector<coordinate_format> convert(const std::vector<index_format>& index_vec, const std::vector<std::string>& lines)**
```
Description:
convert vector of index_format structures into vector of coordinate_format structures

Parameters:
const std::vector<index_format>& index_vec - vector of index_format structures to be converted
const std::vector<std::string>& lines - lines cooresponding to index_vec used to convert one dimensional indexes in index_vec into two dimensional coordinates to populate a coordinate_format structure

Return value:
std::vector<coordinate_format> - vector of coordinate_format structures generated from input index_vec and lines
```

---
## set_flags
**std::vector<int> set_flags(std::vector<index_format>& index_colors, std::string& content, char flag)**
```
Description:
inject flag character into content string at indexes specified by index_format structures in index_colors

Parameters:
std::vector<index_format>& index_colors - vector of index_format structures used to determine where flags should be placed in content string and then store existing character for later flag conversion
std::string& content - string to have flags injected into at specified indexes according to index_format structures in index_colors vector
char flag - character to be used as flag injected into content string

Return value:
std::vector<int> - indexes where chosen flag character already existed in content string before having the flag character injected
```

---
## remove_flags
**std::vector<std::string> remove_flags(const std::vector<index_format>& index_colors, std::vector<int> ignore_flags, std::vector<std::string> lines, char flag)**
```
Description:
remove flags characters injected by set_flags function

Parameters:
const std::vector<index_format>& index_colors - vector of index_format structures used to determine where flags should be removed and replaced with stored character
std::vector<int> ignore_flags - indexes where chosen flag character already existed in content string before having the flag character injected (returned by set_flags function)
char flag - character be understood as the flag character that should be removed

Return value:
std::vector<std::string> - processed lines with the flag character removed
```

---
## convert_flags
**void convert_flags(std::vector<coordinate_format>& coordinate_colors, const std::vector<index_format>& index_colors, std::vector<int> ignore_flags, std::vector<std::string>& lines, char flag)**
```
Description:
converts vector of index_format structures into vector of coordinate_format structures using flags injected into a string that was then converted to vector of lines

Parameters:
std::vector<coordinate_format>& coordinate_colors - vector of coordinate_format structures created from index_colors and lines injected with flag characters
const std::vector<index_format>& index_vec - vector of index_format structures containing the flag replacement that should be used in place of flags that will be removed
std::vector<int> ignore_flags - indexes where the flag in lines should not be replaced or used to generate a coordinate_format structure
std::vector<std::string>& lines - lines containing flags used to generate coordinate_colors vector (flags will be replaced with original characters)
char flag - character to be used as flag in lines
```

---
## fit_to_width
**std::vector<content_format> fit_to_width(const std::vector<content_format>& content_vec, unsigned int width)**
```
Description:
break vector of content_format structures into more structure elements so that content in strucures does not cross index at multiples of specified width

Parameters:
const std::vector<content_format>& content_vec - vector of content_format structures to be split into more structures
unsigned int width - width defining multiples that content in content_vec should not cross within a single structure

Return value:
std::vector<content_format> - vector of content_format structures that has been split so that content in a single structure does not cross and index that is a multiple of width
```

---
## remove_newline_characters
**std::vector<std::string> remove_newline_characters(std::vector<std::string> lines)**
```
Description:
if the last character in a line is '\n' it will be removed

Parameters:
std::vector<std::string> lines - vector of strings that should have '\n' character removed from each line

Return value:
std::vector<std::string> - lines that have had '\n' character removed from the end of each line
```

---
## add_newline_characters
**std::vector<std::string> add_newline_characters(std::vector<std::string> lines)**
```
Description:
add '\n' character to the end of each line in vector of strings

Parameters:
std::vector<std::string> lines - lines to have a '\n' character added to the end of each line

Return value:
std::vector<std::string> - lines that have had '\n' character added to the end of each line
```

---
## get_first_line_length
**unsigned int get_first_line_length(const std::string& content)**
```
Description:
retrieves the length of the first line in string (the first line is the string until the first '\n' character)

Parameters:
const std::string& content - string to have the length of its first line calculated

Return value:
unsigned int - length of first line in string
```

---
## get_color_name
**std::string get_color_name(int color)**
```
Description:
returns a string that is the name of a color code

Parameters:
int color - the color code of a color (it is best to use color codes defined in format_tools)

Return value:
std::string - name of the color
```

---
## shift_index
**std::vector<index_format> shift_index(std::vector<index_format> index_colors, int shift_amount)**
```
Description:
shifts index of all index_format structures in vector by specified amount

Parameters:
std::vector<index_format> index_colors - vector of index_format structures to have their indexes shifted by specified amount
int shift_amount - amount to shift indexes (positive to shift right and negative to shift left)

return value:
std::vector<index_format> - vector of index_format structures that have had their indexes shifted
```

---
## build_color_for_value
**std::vector<index_format> build_color_for_value(const std::string& value, char ignore_character, int foreground_format, int background_format, bool bold, bool include_spaces = false)**
```
Description:
builds a vector of index_format structures that fit a string value exactly by placing the color only on characters in the value that are neither ignore characters nor spaces (the color will be applied to spaces also if include_spaces is set to true)

Parameters:
const std::string& value - string value to have a color fit to
char ignore_character - character in the value indicating places where the color should not be applied
int foreground_format - color code defining the color to be applied to the foreground
int background_format - color code defining the color to be applied to the background
bool bold - makes the foreground be brighter if set to true
bool include_spaces - will apply the color to spaces if set to true

Return value:
std::vector<index_format> - vector of index_format structures defining the color fit to the value
```

---
## get_color_line
**int get_color_line(const index_format& color, const std::vector<std::string>& lines)**
```
Description:
returns the line number that the color is on

Parameters:
const index_format& color - color to have its line found
const std::vector<std::string>& lines - lines to be analyzed to find the line the color is located on

Return value:
int - line the color is located on (-1 if the line could not be found)
```

---
## format_empty
**bool format_empty(const common_format& format)**
```
Description:
indicates if the format is empty (default value) or not

Parameters:
const common_format& format - format to be analyzed and determined if it is empty or not

Return value:
bool - true if the format is empty and false if it is not empty
```

---
## compress
**unsigned int compress(unsigned int value, unsigned int compression, unsigned int& remainder)**
```
Description:
divides value by compression amount and stores remainder

Parameters:
unsigned int value - value to be compressed
unsigned int compression - variable to divide value by
unsigned int& remainder - remainder resulting from dividing value by compression

Return value:
unsigned int - compressed value (input value divided by compression and rounded down)
```

---
## expand
**unsigned int expand(unsigned int value, unsigned int expansion, unsigned int remainder)**
```
Description:
multiplis value by expansion and adds remainder

Parameters:
unsigned int value - value to be expanded
unsigned int expansion - variable to multiply value by
unsigned int remainder - remainder that should be added to value after multiplication

Return value:
unsigned int - expanded value (input value multiplied by expansion and added to remainder)
```

---
# Structure descriptions
---
## common_format
```
Values:
int foreground_format = none
int background_format = none
bool bold = false
bool dec = false

Value descriptions:
int foreground_format - integer code designating color of foreground on terminal (use color codes defined in format_tools)
int background_format - integer code designating color of background on terminal (use color codes defined in format_tools)
bool bold - if set to true, foreground color will become brighter
bool dec - if set to true, characters should be interpreted as dec line drawing characters
```

---
## index_format
```
Values:
int index = 0
common_format format
char flag_replacement = ' '

Value descriptions:
int index - index in string where format should be activated until overridden by another format
common_format format - structure defining colors and dec line drawing character activation
char flag_replacement - value used to store character about to be replaced by a flag character
```

---
## content_format
```
Values:
std::string content = ""
common_format format

Value descriptions:
std::string content - string that should have format applied to when printed to terminal
common_format format - structure defining colors and dec line drawing character activation
```

---
## coordinate_format
```
Values:
int x_position = 0
int y_position = 0
common_format format

Value description:
int x_position - x coordinate in string of lines where format should be activated until overridden by another format
int y_position - y coordinate in string of lines where format should be activated until overriddent by another format
common_format format - structure defining colors and dec line drawing character activation
```

---
## test_column
```
Values:
std::vector<std::vector<std::string>> text
std::vector<unsigned int> width

Value description:
std::vector<std::vector<std::string>> text - vector of columns of text with each column containing lines of text
std::vector<unsigned int> width - width of lines in each column
```

---
# Color codes
```
Windows:
const int black = 30
const int red = 31
const int green = 32
const int yellow = 33
const int blue = 34
const int magenta = 35
const int cyan = 36
const int white = 37
const int none = 38

Linux:
const int black = 0
const int red = 1
const int green = 2
const int yellow = 3
const int blue = 4
const int magenta = 5
const int cyan = 6
const int white = 7
const int none = 8
```

---
# Alignment keywords
```
const std::string right_alignment_keyword = "right"
const std::string left_alignment_keyword = "left"
const std::string center_alignment_keyword = "center"
const std::string center_block_alignment_keyword = "center block"
```

---
# Color Tags
---
```
<black_foreground>
<red_foreground>
<green_foreground>
<yellow_foreground>
<blue_foreground>
<magenta_foreground>
<cyan_foreground>
<white_foreground>

<black_background>
<red_background>
<green_background>
<yellow_background>
<blue_background>
<magenta_background>
<cyan_background>
<white_background>

<no_color>
```