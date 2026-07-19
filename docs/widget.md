# widget API

widget is the base class that all widget objects are derived from. Objects derived from widget are ascii_board, label, menu, and text_box. widget is not meant to be used by its self, but its functions are to be called from the derived classes. These functions include:

# Functions
- [widget(frame* parent, std::string special_operation="none")](#widget)
- [void set_alignment(std::string alignment)](#set_alignment)
- [void set_spacing(int top, int bottom, int left, int right)](#set_spacing)
- [void set_border_spacing(int top, int bottom, int left, int right)](#set_border_spacing)
- [void set_vertical_border(char border)](#set_vertical_border)
- [void set_horizontal_border(char border)](#set_horizontal_border)
- [void set_corner_border(char border)](#set_corner_border)
- [void set_highlight_character(char character)](#set_highlight_character)
- [void set_width_multiplier(float multiplier)](#set_width_multiplier)
- [void set_spacing_width_multipliers(float left_multiplier, float right_multiplier)](#set_spacing_width_multipliers)
- [void set_border_spacing_width_multipliers(float left_multiplier, float right_multiplier)](#set_border_spacing_width_multipliers)
- [void set_title(const std::string& title)](#set_title)
- [void add_border(bool border)](#add_border)
- [void use_spacing_width_multipliers(bool use)](#use_spacing_width_multipliers)
- [void set_selectable(bool selectable)](#set_selectable)
- [bool is_selectable()](#is_selectable)
- [void get_spacing(int& top, int& bottom, int& left, int& right)](#get_spacing)
- [void get_border_spacing(int& top, int& bottom, int& left, int& right)](#get_border_spacing)
- [char get_vertical_border()](#get_vertical_border)
- [char get_horizontal_border()](#get_horizontal_border)
- [char get_corner_border()](#get_corner_border)
- [char get_highlight_character()](#get_highlight_character)
- [float get_width_multiplier()](#get_width_multiplier)
- [void get_spacing_width_multipliers(float& left_multiplier, float& right_multiplier)](#get_spacing_width_multipliers)
- [void get_border_spacing_width_multipliers(float& left_multiplier, float& right_multiplier)](#get_border_spacing_width_multipliers)
- [std::string get_title()](#get_title)
- [unsigned int get_width(bool include_spacing=false)](#get_width)
- [unsigned int get_height(bool include_spacing=false)](#get_height)
- [int get_x_origin()](#get_x_origin)
- [int get_y_origin()](#get_y_origin)
- [int get_widget_type()](#get_widget_type)
- [std::string get_output()](#get_output)
- [std::string get_displayed_output()](#get_displayed_output)
- [std::string get_alignment()](#get_alignment)
- [int start_logging(const std::string& file_path)](#start_logging)
- [void stop_logging()](#stop_logging)
- [int reset_logging(const std::string& file_path)](#reset_logging)

---
# Function Descriptions
---
## widget
**widget(frame\* parent, std::string special_operation="none")**

**Description:**

the constructor of the class responsible for adding the widget to a parent frame

**Parameters:**
1. frame* **parent** - the frame that the widget should be placed in
2. std::string **special_operation** - optional parameter used to define how the widget should be placed in the frame (leaving blank will result in the widget being placed to the right of the last widget, "new line" will result in the widget being placed below on a new line, and "merge" will result in the widget being placed below the last widget but still in the same row)

---
## set_alignment
**void set_alignment(std::string alignment)**

**Description:**

sets the alignment of text inside the widget

**Parameters:**
1. std::string **alignment** - alignment of the widget's text ("left", "right", "center", or "center block")

---
## set_spacing
**void set_spacing(int top, int bottom, int left, int right)**

**Description:**

definies the number of spaces/lines that should be filled on the top, bottom, left, and right of the widget

**Parameters:**
1. int **top** - number of lines on the top of the widget
2. int **bottom** - number of lines on the bottom of the widget
3. int **left** - number of spaces on the left of the widget
4. int **right** - number of spaces on the right of the widget

---
## set_border_spacing
**void set_border_spacing(int top, int bottom, int left, int right)**

**Description:**

defines the number of spaces/lines that the border should be moved outward from the widget (the border spacing cannot exceed the widget's spacing set in set_spacing function)

**Parameters:**
1. int **top** - number of lines the border is moved up on the top side of widget
2. int **bottom** - number of lines the border is moved down on the bottom side of widget
3. int **left** - number of spaces the border is moved left on the left side of widget
4. int **right** - number of spaces the border is moved right on the right side of widget

---
## set_vertical_border
**void set_vertical_border(char border)**

**Description:**

defines the character used to draw the vertical section of the widget's border

**Parameters:**
1. char **border** - character that should be used to draw the vertical section of the widget's border

---
## set_horizontal_border
**void set_horizontal_border(char border)**

**Description:**

defines the character used to draw the horizontal section of the widget's border

**Parameters:**
1. char **border** - character that should be used to draw the horizontal section of the widget's border

---
## set_corner_border
**void set_corner_border(char border)**

**Description:**

defines the character used to draw the conrers of the widget's border

**Parameters:**
1. char **border** - character that should be used to draw the corners of the widget's border

---
## set_highlight_character
**void set_highlight_character(char character)**

**Description:**

defines the character used to indicate the widget is being highlighted by the user

**Parameters:**
1. char **character** - character that should be used to visually highlight the widget

---
## set_width_multiplier
**void set_width_multiplier(float multiplier)**

**Description:**

sets the multiplier used to dynamically determine the widget's width

**Parameters:**
1. float **multiplier** - used to determine the width of the widget as a percentage of the total terminal width (if there are three widgets in a row with multipliers of 1.0, 3.0, and 2.0, there widths would be 1/6, 3/6, and 2/6 of the total terminal width respectively)

---
## set_spacing_width_multipliers
**void set_spacing_width_multipliers(float left_multiplier, float right_multiplier)**

**Description:**

sets the multipliers used to dynamically determine the widget's left and right spacing width

**Parameters:**
1. float **left_multiplier** - used to determine the width of the widget's left spacing as a percent of the total terminal width (if there is only one widget in a row with left spacing multiplier, widget multiplier, and right spacing multiplier of 1.0, 3.0, and 2.0, there widths would be 1/6, 3/6, and 2/6 of the total terminal width respectively)
2. float **right_multiplier** - used to determine the width of the widget's right spacing as a percent of the total terminal width (if there is only one widget in a row with left spacing multiplier, widget multiplier, and right spacing multiplier of 1.0, 3.0, and 2.0, there widths would be 1/6, 3/6, and 2/6 of the total terminal width respectively)

---
## set_border_spacing_width_multipliers
**void set_border_spacing_width_multipliers(float left_multiplier, float right_multiplier)**

**Description:**

sets the multipliers used to dynamically determine the distance between the border and the left and right side of the widget (the mulipliers cannot be larger than the left and right spacing width multipliers)

**Parameters:**
1. float **left_multiplier** - used to determine the width of the widget's left spacing as a percent of the total terminal width (if the board multiplier is half of the spacing multiplier, the side border will be placed half way between the spacing width and the widget)
2. float **right_multiplier** - used to determine the width of the widget's right spacing as a percent of the total terminal width (if the board multiplier is half of the spacing multiplier, the side border will be placed half way between the spacing width and the widget)

---
## set_title
**void set_title(const std::string& title)**

**Description:**

sets text that will be displayed above the widget in the border if the widget has a border (title will not be displayed if the widget does not have a border)

**Parameters:**
1. const std::string& **title** - title to be displayed in border above widget

---
## add_border
**void add_border(bool border)**

**Description:**

causes a border to be drawn about the widget when being displayed if set to true or causes the border to be removed if set to false

**Parameters:**
1. bool **border** - draws border around widget if set to true and removes border from widget if set to false

---
## use_spacing_width_multipliers
**void use_spacing_width_multipliers(bool use)**

**Description:**

causes width multipliers to be used for dynamically setting spacing width and border width instead of using constant values

**Parameters:**
1. bool **use** - width multipliers are used when set to true and constant spacing values are used when set to false

---
## set_selectable
**void set_selectable(bool selectable)**

**Description:**

enables or disables the user to select the widget

**Parameters:**
1. bool **selectable** - enables the widget to be selectable by the user if true and disables the widget to be selectable by the user if false

---
## is_selectable
**bool is_selectable()**

**Description:**

indicates if the widget is selectable by the user

**Return value:**

bool - true if the widget is selectable and false if the widget is not selectable

---
## get_spacing
**void get_spacing(int& top, int& bottom, int& left, int& right)**

**Description:**

retrieves the widget's spacing used to define how many spaces/lines should be placed on the top, bottom, left, and right of the widget

**Parameters:**
1. int& **top** - number of lines on the top of the widget
2. int& **bottom** - number of lines on the bottom of the widget
3. int& **left** - number of spaces on the left of the widget
4. int& **right** - number of spaces on the right of the widget

---
## get_border_spacing
**void get_border_spacing(int& top, int& bottom, int& left, int& right)**

**Description:**

retrieves the widget's border spacing used to define how many spaces/lines the border should be moved away from the widget's top, bottom, left, and right

**Parameters:**
1. int& **top** - number of lines the border is moved up on the top side of widget
2. int& **bottom** - number of lines the border is moved down on the bottom side of widget
3. int& **left** - number of spaces the border is moved left on the left side of widget
4. int& **right** - number of spaces the border is moved right on the right side of widget

---
## get_vertical_border
**char get_vertical_border()**

**Description:**

returns the character used to draw the vertical section of the border

**Return value:**

char - character that is being used to draw the vertical section of the widget's border

---
## get_horizontal_border
**char get_horizontal_border()**

**Description:**

returns the character used to draw the horizontal section of the border

**Return value:**

char - character that is being used to draw the horizontal section of the widget's border

---
## get_corner_border
**char get_corner_border()**

**Description:**

returns the character used to draw the corners of the border

**Return value:**

char - character that is being used to draw the corners of the border

---
## get_highlight_character
**char get_highlight_character()**

**Description:**

returns the character used to highlight the widget

**Return value:**

char - character that is being used to highlight the widget

---
## get_width_multiplier
**float get_width_multiplier()**

**Description:**

returns the multiplier used to dynamically determine the widget's width

**Return value:**

float - multiplier used to determine the width of the widget as a percentage of the total terminal width (if there are three widgets in a row with multipliers of 1.0, 3.0, and 2.0, there widths would be 1/6, 3/6, and 2/6 of the total terminal width respectively)

---
## get_spacing_width_multipliers
**void get_spacing_width_multipliers(float& left_multiplier, float& right_multiplier)**

**Description:**

returns the multipliers used to dynamically determine the widget's left and right spacing

**Parameters:**
1. float& **left_multiplier** - used to determine the width of the widget's left spacing as a percent of the total terminal width (if there is only one widget in a row with left spacing multiplier, widget multiplier, and right spacing multiplier of 1.0, 3.0, and 2.0, there widths would be 1/6, 3/6, and 2/6 of the total terminal width respectively)
2. float& **right_multiplier** - used to determine the width of the widget's right spacing as a percent of the total terminal width (if there is only one widget in a row with left spacing multiplier, widget multiplier, and right spacing multiplier of 1.0, 3.0, and 2.0, there widths would be 1/6, 3/6, and 2/6 of the total terminal width respectively)

---
## get_border_spacing_width_multipliers
**void get_border_spacing_width_multipliers(float& left_multiplier, float& right_multiplier)**

**Description:**

returns the multipliers used to dynamically determine the distance between the border and the left or right side of the widget

**Parameters:**
1. float& **left_multiplier** - used to determine the width of the widget's left spacing as a percent of the total terminal width (if the board multiplier is half of the spacing multiplier, the side border will be placed half way between the spacing width and the widget)
2. float& **right_multiplier** - used to determine the width of the widget's right spacing as a percent of the total terminal width (if the board multiplier is half of the spacing multiplier, the side border will be placed half way between the spacing width and the widget)

---
## get_title
**std::string get_title()**

**Description:**

returns the widget's title

**Return value:**

std::string - widget's title

---
## get_width
**unsigned int get_width(bool include_spacing=false)**

**Description:**

returns the width of the widget (number of spaces)

**Parameters:**
1. bool **include_spacing** - includes border and spacing in the width when set to true

**Return value:**

unsigned int - width of widget

---
## get_height
**unsigned int get_height(bool include_spacing=false)**

**Description:**

returns the height of the widget (number of lines)

**Parameters:**
1. bool **include_spacing** - includes border and spacing in the height when set to true

**Return value:**

unsigned int - height of widget

---
## get_x_origin
**int get_x_origin()**

**Description:**

returns the x position in the terminal where the widget's text starts (top left corner)

**Return value:**

int - x position in the terminal where the widget's text starts

---
## get_y_origin
**int get_y_origin()**

**Description:**

returns the y position in the terminal where the widget's text starts (top left corner) (y position starts at top and moves down)

**Return value:**

int - y position in the terminal where the widget's text starts

---
## get_widget_type
**int get_widget_type()**

**Description:**

returns the type of widget (WIDGET, TEXTBOX, MENU, BOARD, or LABEL)

**Return value:**

int - code designating type of widget (look at widget_types.md for widget type codes)

---
## get_output
**std::string get_output()**

**Description:**

returns text in the widget

**Return value:**

std::string - text inside widget

---
## get_displayed_output
**std::string get_displayed_output()**

**Description:**

returns text currently being displayed in the widget

**Return value:**

std::string - only displayed text inside the widget

---
## get_alignment
**std::string get_alignment()**

**Description:**

returns the alignment of the widget used to align the widget's text

**Return value:**

std::string - alginment of the widget's text ("left", "right", "center" or "center block")

---
## start_logging
**int start_logging(const std::string& file_path)**

**Description:**

starts logging debug logs from widget to a file

**Parameters:**
1. const std::string& **file_path** - absolute or relative path to file that should have widget debug logs written to

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