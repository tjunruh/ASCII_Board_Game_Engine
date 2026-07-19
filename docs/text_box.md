# text_box API

text_box is a widget that allows the user to write and edit text. Note that text_box is derived from the **widget** base class so that the widget's public member functions also apply to text_box. Public member functions of the **text_box** class include:

# Functions
- [text_box(frame* parent, std::string special_operation = "none", int lines_count = 1, bool start_logging = false, std::string logging_file_path="text_box.log")](#text_box)
- [unsigned int write()](#write)
- [void set_max_characters(int characters)](#set_max_characters)
- [void clear()](#clear)
- [std::string get_text()](#get_text)
- [void set_lines_count(int lines_count)](#set_lines_count)

---
# Function Descriptions
---
## text_box
**text_box(frame\* parent, std::string special_operation = "none", int lines_count = 1, bool start_logging = false, std::string logging_file_path="text_box.log")**

**Description:**

the constructor of the class responsible for adding the widget to a parent frame and initializing logging

**Parameters:**
1. frame* **parent** - the frame that the text box should be placed in
2. std::string **special_operation** - optional parameter used to define how the text box widget should be placed in the frame (leaving blank will result in the widget being placed to the right of the last widget, "new line" will result in the widget being placed below on a new line, and "merge" will result in the widget being placed below the last widget but still in the same row)
3. int **lines_count** - number of lines that should be displayed at a time in the text box (if negative, the number of lines will be dynamically determined based on total number of lines in the console minus the negative value)
4. bool **start_logging** - if set to true, a log file will be created where logs from tex box member functions will be listed
5. std::string **logging_file_path** - set the absolute or relative path to the logging file (if not specified, the log file will be created as text_box.log)

---
## write
**unsigned int write()**

**Description:**

blocks and allows the user to write and edit text in the text box

**Return value:**

unsigned int - the ascii code defining the keystroke used to exit the write function

---
## set_max_characters
**void set_max_characters(int characters)**

**Description:**

defines the maximum number of characters that can be written in the text box (if set to a negative value, there is no limit)

**Parameters:**
1. int **characters** - maximum number of characters that can be written in the text box

---
## clear
**void clear()**

**Description:**

removes all text from the text box

---
## get_text
**std::string get_text()**

**Description:**

returns text that is in the text box

**Return value:**

std::string - text currently in the text box

---
## set_lines_count
**void set_lines_count(int lines_count)**

**Description:**

sets the number of lines in the text box

**Parameters:**
1. int **lines_count** - number of lines in the text box (if negative, the number of lines will be dynamically determined based on total number of lines in the console minus the negative value)