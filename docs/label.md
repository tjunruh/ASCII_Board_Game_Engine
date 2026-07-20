# label API

label is a widget that displays non-editable text that can be formatted and positioned within a frame. Note that label is derived from the **widget** base class so that the widget's public member functions also apply to label. Public member functions of the **label** class include:

# Functions
- [label(frame* parent, const std::string& special_operation = "none", int lines_count = 0, bool start_logging=false, const std::string& logging_file_path="label.log")](#label)
- [void set_output(const std::string& output)](#set_output)
- [void set_colors(std::vector<format_tools::index_format> colors)](#set_colors)
- [std::vector<format_tools::index_format> get_colors()](#get_colors)
- [std::vector<format_tools::index_format> get_displayed_colors()](#get_displayed_colors)
- [void display()](#display)
- [int scroll()](#scroll)
- [void scroll_up(unsigned int amount = 1, bool render = true)](#scroll_up)
- [void scroll_down(unsigned int amount = 1, bool render = true)](#scroll_down)
- [void scroll_left(unsigned int amount = 1, bool render = true)](#scroll_left)
- [void scroll_right(unsigned int amount = 1, bool render = true)](#scroll_right)
- [void set_controls(int up, int down, int left, int right, int quit)](#set_controls)
- [void set_controls(controls* centralized_controls)](#set_controls-1)
- [void get_controls(int& up, int& down, int& left, int& right, int& quit)](#get_controls)
- [void set_lines_count(int lines_count)](#set_lines_count)
- [void enable_word_wrap(bool enable)](#enable_word_wrap)

---
# Function Descriptions
---
## label
**label(frame\* parent, const std::string& special_operation = "none", int lines_count = 0, bool start_logging=false, const std::string& logging_file_path="label.log")**

**Description:**

the constructor of the class responsible for adding the widget to a parent frame and initializing logging

**Parameters:**
1. frame\* **parent** - the frame that the label should be placed in
2. std::string **special_operation** - optional parameter used to define how the label widget should be placed in the frame (leaving blank will result in the widget being placed to the right of the last widget, "new line" will result in the widget being placed below on a new line, and "merge" will result in the widget being placed below the last widget but still in the same row)
3. int **lines_count** - optional parameter used to set number of lines in the label (if 0, there is no limit and if negative, the number of lines will be dynamically determined based on total number of lines in the console minus the negative value)
4. bool **start_logging** - if set to true, a log file will be created where logs from label member functions will be listed
5. std::string **logging_file_path** - set the absolute or relative path to the logging file (if not specified, the log file will be created as label.log)

---
## set_output
**void set_output(const std::string& output)**

**Description:**

sets the text inside the label (colors can be set by embedding color tags in the text (tags are listed at the bottom of format_tools documentation))

**Parameters:**
1. const std::string& **output** - text that should be displayed in the label

---
## set_colors
**void set_colors(std::vector\<format_tools::index_format\> colors)**

**Description:**

sets colors of text in the label (color specified at index will continue until another color is specified and colors will not be set if index in color is less than zero or longer than the length of the text in the label)

**Parameters:**
1. const std::vector\<format_tools::index_format\>& **colors** - vector of colors to apply to text in the label (look at format_tools for reference to index_format structure)

---
## get_colors
**std::vector\<format_tools::index_format\> get_colors()**

**Description:**

get colors currently being applied to text in label

**Return value:**

std::vector\<format_tools::index_format\> - colors currently being applied to text in label

---
## get_displayed_colors
**std::vector\<format_tools::index_format\> get_displayed_colors()**

**Description:**

get only the colors currently being displayed on the text in the label

**Return value:**

std::vector\<format_tools::index_format\> - colors currently being displayed on the text in the label

---
## display
**void display()**

**Description:**

displays the latest state of the label on the frame by only updating the label and not the entire frame

---
## scroll
**int scroll()**

**Description:**

enables the user to have the label scroll up and down using the up and down keys

**Return value**

int - last keystroke before the function exited

---
## scroll_up
**void scroll_up(unsigned int amount = 1, bool render = true)**

**Description:**

programmatically moves the label up specified amount of lines

**Parameters:**
1. unsigned int **amount** - number of lines to scroll up (will stop at 0 if too many)
2. bool **render** - the scroll operation will immediately be rendered if true, otherwise it will not be drawn until the next display call

---
## scroll_down
**void scroll_down(unsigned int amount = 1, bool render = true)**

**Description:**

programmatically moves the label down specified amount of lines

**Parameters:**
1. unsigned int **amount** - number of lines to scroll down (will stop at number of lines in label if too many)
2. bool **render** - the scroll operation will immediately be rendered if true, otherwise it will not be drawn until the next display call

---
## scroll_left
**void scroll_left(unsigned int amount = 1, bool render = true)**

**Description:**

programmatically moves the label left specified amount of columns

**Parameters:**
1. unsigned int **amount** - number of columns to scroll left (will stop at 0 if too many)
2. bool **render** - the scroll operation will immediately be rendered if true, otherwise it will not be drawn until the next display call

---
## scroll_right
**void scroll_right(unsigned int amount = 1, bool render = true)**

**Description:**

programmatically moves the label right specified amount of columns

**Parameters:**
1. unsigned int **amount** - number of columns to scroll right (will stop at number of columns in label if too many)
2. bool **render** - the scroll operation will immediately be rendered if true, otherwise it will not be drawn until the next display call

---
## set_controls
**void set_controls(int up, int down, int left, int right, int quit)**

**Description:**

defines the buttons used to scroll up and down, and quit scrolling the label

**Parameters:**
1. int **up** - ascii code defining keystroke to scroll up
2. int **down** - ascii code defining keystroke to scroll down
3. int **left** - ascii code defining keystroke to scroll left
4. int **right** - ascii code defining keystroke to scroll right
5. int **quit** - ascii code defining keystroke to exit label

---
## set_controls
**void set_controls(controls\* centralized_controls)**

**Description:**

set controls by providing a pointer to a controls object (up, down, left, right, and quit controls will be defined by controls object using the control_names defined in the control_names namespace)

**Parameters:**
1. controls\* **centralized_controls** - pointer to controls object

---
## get_controls
**void get_controls(int& up, int& down, int& left, int& right, int& quit)**

**Description:**

gets the buttons used to scroll up and down, and quit scrolling the label

**Parameters:**
1. int& **up** - ascii code defining keystroke to scroll up
2. int& **down** - ascii code defining keystroke to scroll down
3. int& **left** - ascii code defining keystroke to scroll left
4. int& **right** - ascii code defining keystroke to scroll right
5. int& **quit** - ascii code defining keystroke to exit label

---
## set_lines_count
**void set_lines_count(int lines_count)**

**Description:**

sets the number of lines in the label

**Parameters:**
1. int **lines_count** - number of lines in the label (if 0, there is no limit and if negative, the number of lines will be dynamically determined based on total number of lines in the console minus the negative value)

---
## enable_word_wrap
**void enable_word_wrap(bool enable)**

**Description:**

enables word wrap when set to true and sets the label to cut off lines instead when set to false (is set to true by default when the label widget is created)

**Parameters:**
1. bool **enable** - enables word wrap when set to true and disables it when set to false