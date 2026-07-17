# menu API

menu is a widget that displays options/items that can be selected by the user. Note that menu is derived from the **widget** base class so that the widget's public member functions also apply to menu. Public member functions of the **menu** class include:

```
menu(frame* parent, const std::string& special_operation="none", int lines_count=0, bool start_logging=false, const std::string& logging_file_path="menu.log")
int append_item(const std::string& item)
int remove_item(const std::string& item)
void remove_all_items()
void set_lines_count(int lines_count)
int append_item_label(const std::string& item, const std::string& label)
int set_item_label(const std::string& item, unsigned int column, const std::string& label)
void use_top_row_as_heading(bool heading)
void set_cursor(char cursor)
char get_cursor()
void set_cursor_index(unsigned int index)
unsigned int get_cursor_index()
menu::item_structure get_cursor_item_data()
int get_item_label(const std::string& item, unsigned int column, std::string& label)
void set_controls(std::vector<int> select, int up, int down, int left, int right, int quit)
void set_controls(controls* centralized_controls)
void get_controls(std::vector<int>& select, int& up, int& down, int& left, int& right, int& quit)
void set_separater_characters(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char)
void get_separater_characters(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char)
void get_selection(std::string& selection, int& key_stroke)
void enable_quit(bool enable)
void display()
void build()
void separate_items(bool separate)
std::vector<menu::item_structure> get_menu_item_data()
```

Structures provided in the menu class include:

```
struct item_structure
{
   std::string item = "";
   std::vector<std::string> labels;
};
```

---
# Function Descriptions
---
## menu
**menu(frame\* parent, const std::string& special_operation="none", int lines_count=0, bool start_logging=false, const std::string& logging_file_path="menu.log")**
```
Description:
the constructor of the class responsible for adding the widget to a parent frame and initializing logging

Parameters:
frame* parent - the frame that the menu should be placed in
const std::string& special_operation - optional parameter used to define how the menu widget should be placed in the frame (leaving blank will result in the widget being placed to the right of the last widget, "new line" will result in the widget being placed below on a new line, and "merge" will result in the widget being placed below the last widget but still in the same row)
int lines_count - number of lines to be displayed in the menu at a time (if 0, there is no limit and if negative, the number of lines will be dynamically determined based on total number of lines in the console minus the negative value)
bool start_logging - if set to true, a log file will be created where logs from menu member functions will be listed
const std::string& logging_file_path - set the absolute or relative path to the logging file (if not specified, the log file will be created as menu.log)
```

---
## append_item
**int append_item(const std::string& item)**
```
Description:
append item to the bottom of the menu

Parameters:
const std::string& item - title of the item to be appended to the bottom of the menu

Return value:
int - status code that is either DUPLICATE_ELEMENT or SUCCESS
```

---
## remove_item
**int remove_item(const std::string& item)**
```
Description:
removes item from menu

Parameters:
const std::string& item - item to remove from menu

Return value:
int - status code that is either ELEMENT_NOT_FOUND or SUCCESS
```

---
## remove_all_items
**void remove_all_items()**
```
Description:
removes all items from menu
```

---
## set_lines_count
**void set_lines_count(int lines_count)**
```
Description:
sets the maximum number of lines displayed in the menu at once (if 0, there is no limit and if negative, the number of lines will be dynamically determined based on total number of lines in the console minus the negative value)

Parameters:
unsigned int lines_count - maximum number of items displayed in the menu at once
```

---
## append_item_label
**int append_item_label(const std::string& item, const std::string& label)**
```
Description:
add a label to item in menu by appending to right most side of the menu row

Parameters:
const std::string& item - already existing item in the menu to add a label to
const std::string& label - contents of the label to be added to the item

Return value:
int - status code that is either ELEMENT_NOT_FOUND or SUCCESS
```

---
## set_item_label
**int set_item_label(const std::string& item, unsigned int column, const std::string& label)**
```
Description:
sets the label of item in menu at specified column posiiton of labels

Parameters:
const std::string& item - already existing item in the menu to set a label
unsigned int column - column of row labels where the label should be set
const std::string& label - contents of the label to be set

Return value:
int - status code that is either ELEMENT_NOT_FOUND or SUCCESS
```

---
## use_top_row_as_heading
**void use_top_row_as_heading(bool heading)**
```
Description:
causes the top row of menu to be used as a heading or not (top row as heading means it cannot be selected and it will not be deleted when calling remove_all_items function)

Parameters:
bool heading - top row of menu will be used as heading when true and not used as heading when false (false is the default behavior)
```

---
## set_cursor
**void set_cursor(char cursor)**
```
Description:
set the character used to designate which menu item is highlighted

Parameters:
char cursor - character that should be used to highlight elements in menu
```

---
## get_cursor
**char get_cursor()**
```
Description:
get the character used to designate which menu item is highlighted

Return value:
char - character that is being used to highlight elements in menu
```

---
## set_cursor_index
**void set_cursor_index(unsigned int index)**
```
Description:
set which item row index of the menu is selected (selected item will have cursor visibly placed beside it)

Parameters:
unsigned int index - item row index of menu to have cursor placed beside
```

---
## get_cursor_index
**unsigned int get_cursor_index()**
```
Description:
returns the item row index of menu where the cursor is

Return value:
unsigned int - item row index of menu where the cursor is
```

---
## get_cursor_item_data()
**menu::item_structure get_cursor_item_data()**

```
Description:
returns all data in row of menu where the cursor is located

Return value:
menu::item_structure - data in row of menu where the cursor is located
```

---
## get_item_label
**int get_item_label(const std::string& item, unsigned int column, std::string& label)**

```
Description:
retrieves the label of item at specified column

Parameters:
const std::string& item - already existing item in the menu to get the label contents of
unsigned int column - column of row labels where the label should be retrieved
std::string& label - will contain contents of the label if retrieved successfully

Return value:
int - status code that will be SUCCESS if successful, ELEMENT_NOT_FOUND if item does not exist, and INVALID_INDEX if column does not exist
```

---
## set_controls
**void set_controls(std::vector<int> select, int up, int down, int left, int right, int quit)**
```
Description:
defines the buttons used to select menu items, move the highlight character up and down, scroll left and right if menu is larger than display space, and quit the menu without selecting an item

Parameters:
std::vector<int> select - ascii code(s) defining keystroke to select an item
int quit - ascii code defining keystroke to exit selection
int up - ascii code defining keystroke to highlight item one row up
int down - ascii code defining keystroke to highlight item one row down
int left - ascii code defining keystroke to scroll left
int right - ascii code defining keystroke to scroll right
```

---
## set_controls
**void set_controls(controls\* centralized_controls)**
```
Description:
set controls by providing a pointer to a controls object (up, down, left, right, and quit controls will be defined by controls object using the control_names defined in the control_names namespace. select defined by setting select_keys with set_select_keys controls member function)
```

---
## get_controls
**void get_controls(std::vector<int>& select, int& up, int& down, int& quit)**
```
Description:
get the buttons used to select menu items, move the highlight character up and down, scroll left and right if menu is larger than display space, and quit the menu without selecting an item

Parameters:
std::vector<int>& select - ascii code(s) defining keystroke to select an item
int& quit - ascii code defining keystroke to exit selection
int& up - ascii code defining keystroke to highlight item one row up
int& down - ascii code defining keystroke to highlight item one row down
int& left - ascii code defining keystroke to scroll left
int& right - ascii code defining keystroke to scroll right
```

---
## set_separater_characters
**void set_separater_characters(char horizontal_char, char vertical_char, char intersection_char, char endpoint_char)**
```
Description:
set the characters being used to draw the boundaries between item and label elements in the menu

Parameters:
char horizontal_char - character being used to build the horizontal separaters between items and labels
char vertical_char - character being used to build the vertical separaters between items and labels
char intersection_char - character being used at the intersection of horizontal and separaters
char endpoint_char - character being used at endpoints of the horizontal and vertical separaters
```

---
## get_separater_characters
**void get_separater_characters(char& horizontal_char, char& vertical_char, char& intersection_char, char& endpoint_char)**
```
Description:
get the characters being used to draw the boundaries between item and label elements in the menu

Parameters:
char& horizontal_char - character being used to build the horizontal separaters between items and labels
char& vertical_char - character being used to build the vertical separaters between items and labels
char& intersection_char - character being used at the intersection of horizontal and separaters
char& endpoint_char - character being used at endpoints of the horizontal and vertical separaters
```

---
## get_selection
**void get_selection(std::string& selection, int& key_stroke)**
```
Description:
blocking function that allows the user to select a menu item and then reports the name of the item selected and the keystroke used to select it

Parameters:
std::string& selection - item selected
int& key_stroke - keystroke used to select item
```

---
## enable_quit
**void enable_quit(bool enable)**
```
Description:
enables or disables user to exit menu without selecting anything

Parameters:
bool enable - will cause user to be able to exit the menu without selecting anthing if set to true, and will force the user to select something to exit the menu if set to false (false is the default behavior)
```

---
## display
**void display()**
```
Description:
displays the latest state of the menu on the frame by only updating the menu and not the entire frame
```

---
## build
**void build()**
```
Description:
builds the menu and updates the latest state of the menu to the frame
```

---
## separate_items
**void separate_items(bool separate)**
```
Description:
enable or disable drawing separaters between items and labels

Parameters:
bool separate - enables drawing separaters when true and disables drawing separaters when false
```

---
## get_menu_item_data
**std::vector<menu::item_structure> get_menu_item_data()**
```
Description:
returns all data in the menu

Return value:
std::vector<menu::item_structure> - vector containing menu data per row of menu
```

---
# Structure descriptions
---
## item_structure
```
Values:
std::string item = ""
std::vector<std::string> labels

Value descriptions:
std::string item - item of menu for a particular row
std::vector<std::string> labels - labels of menu for a particular row
```