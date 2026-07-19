# menu API

menu is a widget that displays options/items that can be selected by the user. Note that menu is derived from the **widget** base class so that the widget's public member functions also apply to menu. Public member functions of the **menu** class include:

# Functions
- [menu(frame* parent, const std::string& special_operation="none", int lines_count=0, bool start_logging=false, const std::string& logging_file_path="menu.log")](#menu)
- [int append_item(const std::string& item)](#append_item)
- [int remove_item(const std::string& item)](#remove_item)
- [void remove_all_items()](#remove_all_items)
- [void set_lines_count(int lines_count)](#set_lines_count)
- [int append_item_label(const std::string& item, const std::string& label)](#append_item_label)
- [int set_item_label(const std::string& item, unsigned int column, const std::string& label)](#set_item_label)
- [void use_top_row_as_heading(bool heading)](#use_top_row_as_heading)
- [void set_cursor(char cursor)](#set_cursor)
- [char get_cursor()](#get_cursor)
- [void set_cursor_index(unsigned int index)](#set_cursor_index)
- [unsigned int get_cursor_index()](#get_cursor_index)
- [menu::item_structure get_cursor_item_data()](#get_cursor_item_data)
- [int get_item_label(const std::string& item, unsigned int column, std::string& label)](#get_item_label)
- [void set_controls(std::vector\<int\> select, int up, int down, int left, int right, int quit)](#set_controls)
- [void set_controls(controls* centralized_controls)](#set_controls-1)
- [void get_controls(std::vector\<int\>& select, int& up, int& down, int& left, int& right, int& quit)](#get_controls)
- [void set_separater_characters(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char)](#set_separater_characters)
- [void get_separater_characters(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char)](#get_separater_characters)
- [void get_selection(std::string& selection, int& key_stroke)](#get_selection)
- [void enable_quit(bool enable)](#enable_quit)
- [void display()](#display)
- [void build()](#build)
- [void separate_items(bool separate)](#separate_items)
- [std::vector\<menu::item_structure\> get_menu_item_data()](#get_menu_item_data)

# Member structures
- [item_structure](#struct-item_structure)

---
# Function Descriptions
---
## menu
**menu(frame\* parent, const std::string& special_operation="none", int lines_count=0, bool start_logging=false, const std::string& logging_file_path="menu.log")**

**Description:**

the constructor of the class responsible for adding the widget to a parent frame and initializing logging

**Parameters:**
1. frame* **parent** - the frame that the menu should be placed in
2. const std::string& **special_operation** - optional parameter used to define how the menu widget should be placed in the frame (leaving blank will result in the widget being placed to the right of the last widget, "new line" will result in the widget being placed below on a new line, and "merge" will result in the widget being placed below the last widget but still in the same row)
3. int **lines_count** - number of lines to be displayed in the menu at a time (if 0, there is no limit and if negative, the number of lines will be dynamically determined based on total number of lines in the console minus the negative value)
4. bool **start_logging** - if set to true, a log file will be created where logs from menu member functions will be listed
5. const std::string& **logging_file_path** - set the absolute or relative path to the logging file (if not specified, the log file will be created as menu.log)

---
## append_item
**int append_item(const std::string& item)**

**Description:**

append item to the bottom of the menu

**Parameters:**
1. const std::string& **item** - title of the item to be appended to the bottom of the menu

**Return value:**

int - status code that is either DUPLICATE_ELEMENT or SUCCESS

---
## remove_item
**int remove_item(const std::string& item)**

**Description:**

removes item from menu

**Parameters:**
1. const std::string& **item** - item to remove from menu

**Return value:**

int - status code that is either ELEMENT_NOT_FOUND or SUCCESS

---
## remove_all_items
**void remove_all_items()**

**Description:**

removes all items from menu

---
## set_lines_count
**void set_lines_count(int lines_count)**

**Description:**

sets the maximum number of lines displayed in the menu at once (if 0, there is no limit and if negative, the number of lines will be dynamically determined based on total number of lines in the console minus the negative value)

**Parameters:**
1. int **lines_count** - maximum number of items displayed in the menu at once

---
## append_item_label
**int append_item_label(const std::string& item, const std::string& label)**

**Description:**

add a label to item in menu by appending to right most side of the menu row

**Parameters:**
1. const std::string& **item** - already existing item in the menu to add a label to
2. const std::string& **label** - contents of the label to be added to the item

**Return value:**

int - status code that is either ELEMENT_NOT_FOUND or SUCCESS

---
## set_item_label
**int set_item_label(const std::string& item, unsigned int column, const std::string& label)**

**Description:**

sets the label of item in menu at specified column position of labels

**Parameters:**
1. const std::string& **item** - already existing item in the menu to set a label
2. unsigned int **column** - column of row labels where the label should be set
3. const std::string& **label** - contents of the label to be set

**Return value:**

int - status code that is either ELEMENT_NOT_FOUND or SUCCESS

---
## use_top_row_as_heading
**void use_top_row_as_heading(bool heading)**

**Description:**

causes the top row of menu to be used as a heading or not (top row as heading means it cannot be selected and it will not be deleted when calling remove_all_items function)

**Parameters:**
1. bool **heading** - top row of menu will be used as heading when true and not used as heading when false (false is the default behavior)

---
## set_cursor
**void set_cursor(char cursor)**

**Description:**

set the character used to designate which menu item is highlighted

**Parameters:**
1. char **cursor** - character that should be used to highlight elements in menu

---
## get_cursor
**char get_cursor()**

**Description:**

get the character used to designate which menu item is highlighted

**Return value:**

char - character that is being used to highlight elements in menu

---
## set_cursor_index
**void set_cursor_index(unsigned int index)**

**Description:**

set which item row index of the menu is selected (selected item will have cursor visibly placed beside it)

**Parameters:**
1. unsigned int **index** - item row index of menu to have cursor placed beside

---
## get_cursor_index
**unsigned int get_cursor_index()**

**Description:**

returns the item row index of menu where the cursor is

**Return value:**

unsigned int - item row index of menu where the cursor is

---
## get_cursor_item_data
**menu::item_structure get_cursor_item_data()**

**Description:**

returns all data in row of menu where the cursor is located

**Return value:**

menu::item_structure - data in row of menu where the cursor is located

---
## get_item_label
**int get_item_label(const std::string& item, unsigned int column, std::string& label)**

**Description:**

retrieves the label of item at specified column

**Parameters:**
1. const std::string& **item** - already existing item in the menu to get the label contents of
2. unsigned int **column** - column of row labels where the label should be retrieved
3. std::string& **label** - will contain contents of the label if retrieved successfully

**Return value:**

int - status code that will be SUCCESS if successful, ELEMENT_NOT_FOUND if item does not exist, and INVALID_INDEX if column does not exist

---
## set_controls
**void set_controls(std::vector\<int\> select, int up, int down, int left, int right, int quit)**

**Description:**

defines the buttons used to select menu items, move the highlight character up and down, scroll left and right if menu is larger than display space, and quit the menu without selecting an item

**Parameters:**
1. std::vector\<int\> **select** - ascii code(s) defining keystroke to select an item
2. int **up** - ascii code defining keystroke to highlight item one row up
3. int **down** - ascii code defining keystroke to highlight item one row down
4. int **left** - ascii code defining keystroke to scroll left
5. int **right** - ascii code defining keystroke to scroll right
6. int **quit** - ascii code defining keystroke to exit selection

---
## set_controls
**void set_controls(controls\* centralized_controls)**

**Description:**

set controls by providing a pointer to a controls object (up, down, left, right, and quit controls will be defined by controls object using the control_names defined in the control_names namespace. select defined by setting select_keys with set_select_keys controls member function)

**Parameters:**
1. controls\* **centralized_controls** - pointer to an external controls object structure managing input mappings

---
## get_controls
**void get_controls(std::vector\<int\>& select, int& up, int& down, int& left, int& right, int& quit)**

**Description:**

get the buttons used to select menu items, move the highlight character up and down, scroll left and right if menu is larger than display space, and quit the menu without selecting an item

**Parameters:**
1. std::vector\<int\>& **select** - ascii code(s) defining keystroke to select an item
2. int& **up** - ascii code defining keystroke to highlight item one row up
3. int& **down** - ascii code defining keystroke to highlight item one row down
4. int& **left** - ascii code defining keystroke to scroll left
5. int& **right** - ascii code defining keystroke to scroll right
6. int& **quit** - ascii code defining keystroke to exit selection

---
## set_separater_characters
**void set_separater_characters(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char)**

**Description:**

set the characters being used to draw the boundaries between item and label elements in the menu

**Parameters:**
1. char **horizontal_char** - character being used to build the horizontal separaters between items and labels
2. char **vertical_char** - character being used to build the vertical separaters between items and labels
3. char **intersection_char** - character being used at the intersection of horizontal and separaters
4. char **endpoint_char** - character being used at endpoints of the horizontal and vertical separaters

---
## get_separater_characters
**void get_separater_characters(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char)**

**Description:**

get the characters being used to draw the boundaries between item and label elements in the menu

**Parameters:**
1. char& **horizontal_char** - character being used to build the horizontal separaters between items and labels
2. char& **vertical_char** - character being used to build the vertical separaters between items and labels
3. char& **intersection_char** - character being used at the intersection of horizontal and separaters
4. char& **endpoint_char** - character being used at endpoints of the horizontal and vertical separaters

---
## get_selection
**void get_selection(std::string& selection, int& key_stroke)**

**Description:**

blocking function that allows the user to select a menu item and then reports the name of the item selected and the keystroke used to select it

**Parameters:**
1. std::string& **selection** - item selected
2. int& **key_stroke** - keystroke used to select item

---
## enable_quit
**void enable_quit(bool enable)**

**Description:**

enables or disables user to exit menu without selecting anything

**Parameters:**
1. bool **enable** - will cause user to be able to exit the menu without selecting anthing if set to true, and will force the user to select something to exit the menu if set to false (false is the default behavior)

---
## display
**void display()**

**Description:**

displays the latest state of the menu on the frame by only updating the menu and not the entire frame

---
## build
**void build()**

**Description:**

builds the menu and updates the latest state of the menu to the frame

---
## separate_items
**void separate_items(bool separate)**

**Description:**

enable or disable drawing separaters between items and labels

**Parameters:**
1. bool **separate** - enables drawing separaters when true and disables drawing separaters when false

---
## get_menu_item_data
**std::vector\<menu::item_structure\> get_menu_item_data()**

**Description:**

returns all data in the menu

**Return value:**

std::vector\<menu::item_structure\> - vector containing menu data per row of menu

---
# Member Structure Descriptions
---
## struct item_structure

**Values:**

1. std::string **item** = "";
2. std::vector\<std::string\> **labels**;

**Value descriptions:**

1. std::string **item** - item of menu for a particular row
2. std::vector\<std::string\> **labels** - labels of menu for a particular row