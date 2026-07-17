# text_box API

text_box is a widget that allows the user to write and edit text. Note that text_box is derived from the **widget** base class so that the widget's public member functions also apply to text_box. Public member functions of the **text_box** class include:

```
text_box(frame* parent, std::string special_operation = "none", int lines_count = 1, bool start_logging = false, std::string logging_file_path="text_box.log")
unsigned int write()
void set_max_characters(int characters)
void clear()
std::string get_text()
void set_lines_count(int lines_count)
```

---
# Function Descriptions
---
## text_box
**text_box(frame\* parent, std::string special_operation = "none", int lines_count = 1, bool start_logging = false, std::string logging_file_path="text_box.log")**
```
Parameters:
frame* parent - the frame that the text box should be placed in
std::string special_operation - optional parameter used to define how the text box widget should be placed in the frame (leaving blank will result in the widget being placed to the right of the last widget, "new line" will result in the widget being placed below on a new line, and "merge" will result in the widget being placed below the last widget but still in the same row)
int lines_count - number of lines that should be displayed at a time in the text box (if negative, the number of lines will be dynamically determined based on total number of lines in the console minus the negative value)
bool start_logging - if set to true, a log file will be created where logs from tex box member functions will be listed
std::string logging_file_path - set the absolute or relative path to the logging file (if not specified, the log file will be created as text_box.log)
```

---
## write
**unsigned int write()**
```
Description:
blocks and allows the user to write and edit text in the text box

Return value:
unsigned int - the ascii code defining the keystroke used to exit the write function
```

---
## set_max_characters
**void set_max_characters(int characters)**
```
Description:
defines the maximum number of characters that can be written in the text box (if set to a negative value, there is no limit)

Parameters:
int characters - maximum number of characters that can be written in the text box
```

---
## clear
**void clear()**
```
Description:
removes all text from the text box
```

---
## get_text
**std::string get_text()**
```
Description:
returns text that is in the text box

Return value:
std::string - text currently in the text box
```

---
## set_lines_count
**void set_lines_count(int lines_count)**
```
Description:
sets the number of lines in the text box

Parameters:
int lines_count - number of lines in the text box (if negative, the number of lines will be dynamically determined based on total number of lines in the console minus the negative value)
```