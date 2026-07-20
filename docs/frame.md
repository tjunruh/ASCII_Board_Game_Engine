# frame API

frame is responsible for spacing widgets on the terminal and managing the data of all widgets. All widgets must have a parent frame.

# Functions
- [frame(bool start_logger=false, const std::string& logging_file_path="frame.log")](#frame)
- [int get_id()](#get_id)
- [void display()](#display)
- [bool stale()](#stale)
- [void set_controls(int select, int quit, int up, int down, int left, int right)](#set_controls)
- [void set_controls(controls\* centralized_controls)](#set_controls-1)
- [void get_controls(int& select, int& quit, int& up, int& down, int& left, int& right)](#get_controls)
- [void set_selection_exit_keys(const std::vector\<int\>& exit_keys)](#set_selection_exit_keys)
- [std::vector\<int\> get_selection_exit_keys()](#get_selection_exit_keys)
- [void set_selection(int selection)](#set_selection)
- [int get_selection()](#get_selection)
- [bool selection_exit_key_used()](#selection_exit_key_used)
- [void enable_dec(bool enable)](#enable_dec)
- [void use_light_dec_formatting(bool light_formatting)](#use_light_dec_formatting)
- [bool dec_enabled()](#dec_enabled)
- [void enable_color(bool enable)](#enable_color)
- [bool color_enabled()](#color_enabled)
- [void set_dec_format_characters(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char)](#set_dec_format_characters)
- [void get_dec_format_characters(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char)](#get_dec_format_characters)
- [void set_default_background_color(int color)](#set_default_background_color)
- [void set_default_foreground_color(int color)](#set_default_foreground_color)
- [int get_default_background_color()](#get_default_background_color)
- [int get_default_foreground_color()](#get_default_foreground_color)
- [void use_fake_console_dimensions(bool use)](#use_fake_console_dimensions)
- [void set_fake_console_width(int width)](#set_fake_console_width)
- [void set_fake_console_height(int height)](#set_fake_console_height)
- [std::string get_frame_output()](#get_frame_output)
- [int start_logging(const std::string& file_path)](#start_logging)
- [void stop_logging()](#stop_logging)
- [int reset_logging(const std::string& file_path)](#reset_logging)

---
# Function Descriptions
---
## frame
**frame(bool start_logger=false, const std::string& logging_file_path="frame.log")**

**Description:**

the constructor of the class where debug logging can be started if desired

**Parameters:**
1. bool **start_logger** - starts debug logging if set to true
2. const std::string& **logging_file_path** - absolute or relative path to file that should hold logging content

---
## get_id
**int get_id()**

**Description**

returns the id of the frame

**Return value:**

int - id of the frame

---
## display
**void display()**

**Description:**

displays the entire frame which includes all widgets that have the frame as their parent

---
## stale
**bool stale()**

**Description:**

returns true if the terminal size has changed and the frame has not been regenerated

**Return value:**

bool - true if the terminal size has changed and the frame has not been regenerated, false otherwise

---
## set_controls
**void set_controls(int select, int quit, int up, int down, int left, int right)**

**Description:**

defines buttons used to move up, down, left, right, select a widget, or exit in the get_selection function

**Parameters:**
1. int **select** - ascii code defining keystroke to select a widget
2. int **quit** - ascii code defining keystroke to exit selection
3. int **up** - ascii code defining keystroke to highlight widget one row up
4. int **down** - ascii code defining keystroke to highlight widget one row down
5. int **left** - ascii code defining keystroke to highlight widget one column left
6. int **right** - ascii code defining keystroke to highlight widget one column right

---
## set_controls
**void set_controls(controls\* centralized_controls)**

**Description:**

set controls by providing a pointer to a controls object (up, down, left, right, quit, and select controls will be defined by controls object using the control_names defined in the control_names namespace)

**Parameters:**
1. controls\* **centralized_controls** - pointer to controls object

---
## get_controls
**void get_controls(int& select, int& quit, int& up, int& down, int& left, int& right)**

**Description:**

retrieves the buttons used to move up, down, left, right, select a widget, or exit in the get_selection function

**Parameters:**
1. int& **select** - ascii code defining keystroke to select a widget
2. int& **quit** - ascii code defining keystroke to exit selection
3. int& **up** - ascii code defining keystroke to highlight widget one row up
4. int& **down** - ascii code defining keystroke to highlight widget one row down
5. int& **left** - ascii code defining keystroke to highlight widget one column left
6. int& **right** - ascii code defining keystroke to highlight widget one column right

---
## set_selection_exit_keys
**void set_selection_exit_keys(const std::vector\<int\>& exit_keys)**

**Description:**

defines what keys can be pressed to exit the get_selection function

**Parameters:**
1. const std::vector\<int\>& **exit_keys** - keys that can be used to exit the get_selection function

---
## get_selection_exit_keys
**std::vector\<int\> get_selection_exit_keys()**

**Description:**

returns the keys that can be pressed to exit the get_selection function

**Return value:**

std::vector\<int\> - keys that can be used to exit the get_selection function

---
## set_selection
**void set_selection(int selection)**

**Description:**

Sets which widget will be highlighted at the beginning next time get_selection is used

**Parameters:**
1. int **selection** - id of the widget that should be highlighted at the beginning next time get_selection is used

---
## get_selection
**int get_selection()**

**Description:**

blocking function that allows the user to select a widget and then returns the ID of the widget selected

**Return value:**

int - ID of selected widget (-1 if none are selected)

---
## selection_exit_key_used
**bool selection_exit_key_used()**

**Description:**

used to determine if an exit key was used to exit the get_selection function

**Return value:**

bool - true if an exit key was used to exit the get_selection function or false if a widget was selected to exit

---
## enable_dec
**void enable_dec(bool enable)**

**Description:**

enables or disables dec line drawing characters to be interpreted on the terminal when frame or child widgets display

**Parameters:**
1. bool **enable** - enables dec if true and disables dec if false

---
## use_light_dec_formatting
**void use_light_dec_formatting(bool light_formatting)**

**Description:**

vertical characters will not be converted to dec lines when in light dec formatting mode to reduce render time (light formatting is disabled by default)

**Parameters:**
1. bool **light_formatting** - enables light dec formatting if true and disables light dec formatting if false (only applies if dec formatting is enabled with enable_dec function)

---
## dec_enabled
**bool dec_enabled()**

**Description:**

indicates if dec line drawing is enabled or disabled for frame and child widgets

**Return value:**

bool - true if dec is enabled and false if dec is disabled

---
## enable_color
**void enable_color(bool enable)**

**Description:**

enables or disables color to be rendered when frame or child widgets display (only ascii_board uses color)

**Parameters:**
1. bool **enable** - enables color if true and disables color if false

---
## color_enabled
**bool color_enabled()**

**Description:**

indicates if color is enabled or disabled for frame and child widgets

**Return value:**

bool - true if color is enabled and false if color is disabled

---
## set_dec_format_characters
**void set_dec_format_characters(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char)**

**Description:**

sets characters to be searched for when dec is enabled to draw lines in place of connected dec format characters

**Parameters:**
1. char **horizontal_char** - character where a horizontal line should be rendered
2. char **vertical_char** - character where a vertical line should be rendered
3. char **intersection_char** - character where a + intersection of four points should be rendered
4. char **endpoint_char** - character where either two point or three point intersections should be rendered

---
## get_dec_format_characters
**void get_dec_format_characters(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char)**

**Description:**

gets characters to be searched for when dec is enabled to draw lines in place of connected dec format characters

**Parameters:**
1. char& **horizontal_char** - character where a horizontal line should be rendered
2. char& **vertical_char** - character where a vertical line should be rendered
3. char& **intersection_char** - character where a + intersection of four points should be rendered
4. char& **endpoint_char** - character where either two point or three point intersections should be rendered

---
## set_default_background_color
**void set_default_background_color(int color)**

**Description:**

when color is enabled, the default background color should be used whenever no other color is specified

**Parameters:**
1. int **color** - color code defining the color (color codes are provided in format_tools)

---
## set_default_foreground_color
**void set_default_foreground_color(int color)**

**Description:**

when color is enabled, the default foreground color (text) should be used whenever no other color is specified

**Parameters:**
1. int **color** - color code defining the color (color codes are provided in format_tools)

---
## get_default_background_color
**int get_default_background_color()**

**Description:**

returns the color code defining the default background color (color codes are provided in format_tools)

**Return value:**

int - color code defining the default background color

---
## get_default_foreground_color
**int get_default_foreground_color()**

**Description:**

returns the color code defining the default foreground color (text) (color codes are provided in format_tools)

**Return value:**

int - color code defining the default background color

---
## use_fake_console_dimensions
**void use_fake_console_dimensions(bool use)**

**Description:**

the frame can be configured to use console dimensions or fake dimensions to fit the frame content in

**Parameters:**
1. bool **use** - fake dimensions will be use if true and the actual console dimensions will be used if false (false by default)

---
## set_fake_console_width
**void set_fake_console_width(int width)**

**Description:**

used for testing purposes to artificially set the console's width when there is no console in use

---
## set_fake_console_height
**void set_fake_console_height(int height)**

**Description:**

used for testing purposes to artificially set the console's height when there is no console in use

---
## get_frame_output
**std::string get_frame_output()**

**Description:**

generates and then returns the frame output that would be printed to the terminal

**Return value:**

std::string - frame output that would be printed to the terminal

---
## start_logging
**int start_logging(const std::string& file_path)**

**Description:**

starts logging debug logs from frame to a file

**Parameters:**
1. const std::string& **file_path** - absolute or relative path to file that should have frame debug logs written to

**Return value:**

int - status code that is either INVALID_PATH or SUCCESS

---
## stop_logging
**void stop_logging()**

**Description:**

stops logging debug logs from frame to a file

---
## reset_logging
**int reset_logging(const std::string& file_path)**

**Description:**

erases file at specified path and then continues to log debug information to file

**Parameters:**
1. const std::string& **file_path** - absolute or relative path to file that should be erased and then continue to have log messages written to

**Return value:**

int - status code that is either INVALID_PATH or SUCCESS