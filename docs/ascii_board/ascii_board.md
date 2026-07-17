# ascii_board API

ascii_board is a widget that loads a board configuration and can be customized to configure each tile on the board as desired. Note that ascii_board is derived from the **widget** base class so that the widget's public member functions also apply to ascii_board. Public member functions of the **ascii_board** class include:

```
ascii_board(frame* parent, const std::string& path, const std::string& name_id, const std::string& special_operation = "none", int lines_count = 0, bool start_logging=false, const std::string& logging_file_path="ascii_board.log")
void clear_tile(int row, int column)
void clear_row(int row)
void clear_column(int column)
void clear_all()
std::string get_tile(int row, int column)
void set_tile(int row, int column, std::string value)
char get_tile_character(int row, int column, unsigned int character_index)
std::string get_board()
std::vector<format_tools::index_format> get_colors()
void get_board_and_colors(std::string& game_board, std::vector<format_tools::index_format>& colors)
void add_configuration(board_configuration configuration)
void add_configuration(const std::string& name_id, int row, int column, const std::string& value, char ignore_character)
void add_configuration(const std::string& name_id, int row, int column, const std::string& value, char ignore_character, const std::vector<format_tools::index_format>& colors)
void add_configuration(const std::string& name_id, int row, int column, const std::string& value, char ignore_character, int foreground_format, int background_format, bool bold, bool include_spaces = false)
void activate_configuration(const std::string& name_id, int row, int column)
void activate_configuration(const std::string& name_id)
void deactivate_configuration(const std::string& name_id, int row, int column)
void deactivate_configuration(const std::string& name_id)
std::string load_configuration(const std::string& path)
void load_configuration(const std::string& path, const std::string& name_id, int row, int column, char ignore_character)
void load_configuration(const std::string& path, const std::string& name_id, int row, int column, char ignore_character, const std::vector<format_tools::index_format>& colors)
void load_configuration(const std::string& path, const std::string& name_id, int row, int column, char ignore_character, int foreground_format, int background_format, bool bold, bool include_spaces = false)
void set_sub_configuration_color(const std::string& name_id, const std::string& value_match, const std::vector<format_tools::index_format>& colors)
int get_number_of_columns()
int get_number_of_rows()
void display()
void build()
action_tile get_action_tile(int row, int column)
bool configuration_activated(const std::string& name_id, int row, int column)
void modify_configuration(const std::string& target_name_id, const std::string& modification_name_id)
int load_board_translation(const std::string& name_id, const std::string& path, bool load_metadata = false)
void use_translation(const std::string& name_id, bool swap_metadata = false)
void set_lines_count(int lines_count)
void set_top_display_index(unsigned int index)
void set_left_display_index(unsigned int index)
void scroll_up(unsigned int amount=1)
void scroll_down(unsigned int amount=1)
void scroll_left(unsigned int amount=1)
void scroll_right(unsigned int amount=1)
void bring_tile_into_view(int row, int column, int top_padding = 0, int bottom_padding = 0, int left_padding = 0, int right_padding = 0)
board_metadata* get_metadata();
```

Non-member structures provided in the header file include:

```
struct tile_configuration
{
	int row = -2;
	int column = -2;
	std::string value = "";
	char ignore_character = '\0';
	std::vector<format_tools::index_format> colors;
};

struct board_configuration
{
	std::string name_id;
	std::vector<tile_configuration> tile_configurations;
};
```

Member public structures provided by the ascii_board class include:
```
struct action_tile_board_section
{
	int board_start_row = -1;
	int board_stop_row = -1;
	int board_start_column = -1;
	int board_stop_column = -1;
};

struct sub_tile_configuration
{
	std::string name_id = "";
	std::string value = "";
	char ignore_character = '\0';
};
	
struct action_tile
{
	int array_row = -1;
	int array_column = -1;
	std::vector<action_tile_board_section> board_section;
	std::string default_value = "";
	std::string value = "";
	std::vector<format_tools::index_format> colors;
	std::vector<sub_tile_configuration> activated_configs;
};
```

---
# Function Descriptions
---
## ascii_board
**ascii_board(frame\* parent, const std::string& path, const std::string& name_id, const std::string& special_operation = "none", int lines_count = 0, bool start_logging=false, const std::string& logging_file_path="ascii_board.log")**

```
Description:
the constructor of the class responsible for loading the board configuration, adding the board widget to a parent frame, and initialize logging

Parameters:
frame* parent - the frame that the board should be placed in
const std::string& path - absolute or relative path to the board configuration file (the board configuration file is generated using build_board_config
const std::string& name_id - name to uniquely identify default board incase board translation are used
const std::string& special_operation - optional parameter used to define how the ascii_board widget should be placed in the frame (leaving blank will result in the widget being placed to the right of the last widget, "new line" will result in the widget being placed below on a new line, and "merge" will result in the widget being placed below the last widget but still in the same row)
int lines_count - number of lines to be displayed in the console at a time (if 0, there is no limit and if negative, the number of lines will be dynamically determined based on total number of lines in the console minus the negative value)
bool start_logging - if set to true, a log file will be created where logs from ascii_board member functions will be listed
const std::string& logging_file_path - set the absolute or relative path to the logging file (if not specified, the log file will be created as ascii_board.log)
```

---
## clear_tile
**void clear_tile(int row, int column)**

```
Description:
sets the tile at specified row and column of the board back to its default state

Parameters:
int row - row coordinate where the tile should be cleared
int column - column coordinate where the tile should be cleared
```

---
## clear_row
**void clear_row(int row)**

```
Description:
sets all tiles on specified row of the board back to their default states

Parameters:
int row - row coordinate where all tiles should be cleared
```

---
## clear_column
**void clear_column(int column)**

```
Description:
sets all tiles on specified column of the board back to their default states

Parameters:
int column - column coordinate where all tiles should be cleared
```

---
## clear_all
**void clear_all()**

```
Description:
sets all tiles of the board back to their default states
```

---
## get_tile
**std::string get_tile(int row, int column)**

```
Description:
returns the value of tile at specified coordinate

Parameters:
int row - row coordinate of tile that should have its value returned
int column - column coordinate of tile that should have its value returned

Return value:
std::string - value of the tile at specified coordinate
```

---
## set_tile
**set_tile(int row, int column, std::string value)**
```
Description:
Sets the tile at row and column to value (value can be shorter than the size of the tile but not larger)(colors can be set by embedding color tags in the text (tags are listed at the bottom of format_tools documentation))

Parameters:
int row - row coordinate of tile that should have its value set
int column - column coordinate of tile that should have its value set
std::string - value that the tile should contain
```

---
## get_tile_character
**char get_tile_character(int row, int column, unsigned int character_index)**

```
Description:
returns the character of tile at specified coordinate

Parameters:
int row - row coordinate where all tiles should be set to desired value
int column - column coordinate where all tiles should be set to desired value
unsigned int character_index - character's index of board tile's value

Return value:
char - character at specified coordinates
```

---
## get_board
**std::string get_board()**

```
Description:
generates and then returns the board

Return value:
std::string - the board
```

---
## get_colors
**std::vector<format_tools::index_format> get_colors()**
```
Description:
returns colors currently applied to the board

Return value:
std::vector<format_tools::index_format> - vector of all colors currently displayed on the board (look at format_tools for reference to index_format structure)
```

---
## get_board_and_colors
**void get_board_and_colors(std::string& game_board, std::vector<format_tools::index_format>& colors)**
```
Description:
retrieves the board and colors at the same time

Parameters:
std::string& game_board - value to hold the returned board
std::vector<format_tools::index_format>& colors - value to hold the returned colors currently applied to the board
```

---
## add_configuration
**void add_configuration(board_configuration configuration)**

```
Description:
adds board configuration as a structure to ascii_board's data

Parameters:
board_configuration configuration - structure holding the board configuration's data
```

---
## add_configuration
**void add_configuration(const std::string& name_id, int row, int column, const std::string& value, char ignore_character)**

```
Description:
adds board configuration as parameters to ascii_board's data

Parameters:
const std::string& name_id - name that also acts as the id of the configuration
int row - row on the board where the configuration should apply (setting to -1 makes configuration apply to all rows)
int column - column on the board where the configuration should apply (setting to -1 makes configuration apply to all columns)
const std::string& value - value that board tile should be set to when configuration is activated
char ignore_character - defines character in value that should be ignored: whatever is in the tile already at the indexes of ignore characters should remain unchanged
```

---
## add_configuration
**void add_configuration(const std::string& name_id, int row, int column, const std::string& value, char ignore_character, const std::vector<format_tools::index_format>& colors)**

```
Description:
adds board configuration as parameters to ascii_board's data and includes colors in parameters

Parameters:
const std::string& name_id - name that also acts as the id of the configuration
int row - row on the board where the configuration should apply (setting to -1 makes configuration apply to all rows)
int column - column on the board where the configuration should apply (setting to -1 makes configuration apply to all columns)
const std::string& value - value that board tile should be set to when configuration is activated
char ignore_character - defines character in value that should be ignored: whatever is in the tile already at the indexes of ignore characters should remain unchanged
const std::vector<format_tools::index_format& colors - vector of index_format structures providing the ability to change the foreground and background colors of tile beginning at specified index of the tile's string
```

---
## add_configuration
**void add_configuration(const std::string& name_id, int row, int column, const std::string& value, char ignore_character, int foreground_format, int background_format, bool bold, bool include_spaces = false)**

```
Description:
adds board configuration as parameters to ascii_board's data and includes an uniform color

Parameters:
const std::string& name_id - name that also acts as the id of the configuration
int row - row on the board where the configuration should apply (setting to -1 makes configuration apply to all rows)
int column - column on the board where the configuration should apply (setting to -1 makes configuration apply to all columns)
const std::string& value - value that board tile should be set to when configuration is activated
char ignore_character - defines character in value that should be ignored: whatever is in the tile already at the indexes of ignore characters should remain unchanged
int foreground_format - color code defining the color to be applied to the foreground
int background_format - color code defining the color to be applied to the background
bool bold - makes the foreground be brighter if set to true
bool include_spaces - will apply the color to spaces if set to true
```

---
## activate_configuration
**void activate_configuration(const std::string& name_id, int row, int column)**

```
Description:
sets the board tile at specified row and column to value of configuration defined by name_id

Parameters:
const std::string& name_id - name that also acts as the id of the configuration
int row - row on the board where the configuration should apply (setting to -1 makes configuration apply to all rows)
int column - column on the board where the configuration should apply (setting to -1 makes configuration apply to all columns)
```

---
## activate_configuration
**void activate_configuration(const std::string& name_id)**

```
Description:
sets the board tiles everywhere where the configuration applies to value of configuration defined by name_id

Parameters:
const std::string& name_id - name that also acts as the id of the configuration
```

---
## deactivate_configuration
**void deactivate_configuration(const std::string& name_id, int row, int column)**

```
Description:
sets the board tile at specified row and column to default value except for character positions where the configuration value has ignore characters

Parameters:
const std::string& name_id - name that also acts as the id of the configuration
int row - row on the board where the configuration should apply (setting to -1 makes configuration apply to all rows)
int column - column on the board where the configuration should apply (setting to -1 makes configuration apply to all columns)
```

---
## deactivate_configuration
**void deactivate_configuration(const std::string& name_id)**

```
Description:
sets all board tiles to default value except for character positions where the configuration value has ignore characters

Parameters:
const std::string& name_id - name that also acts as the id of the configuration
```

---
## load_configuration
**std::string load_configuration(const std::string& path)**

```
Description:
loads a configuration's value from a file at specified path

Parameters:
const std::string& path - absolute or relative path to the file containing a configuration's value

Return value:
std::string - configuration's value loaded from file
```

---
## load_configuration
**void load_configuration(const std::string& path, const std::string& name_id, int row, int column, char ignore_character)**

```
Description:
loads a configuration's value from a file at specified path and immediatly adds the configuration using parameters into ascci_board's data

Parameters:
const std::string& path - absolute or relative path to the file containing a configuration's value
const std::string& name_id - name that also acts as the id of the configuration
int row - row on the board where the configuration should apply (setting to -1 makes configuration apply to all rows)
int column - column on the board where the configuration should apply (setting to -1 makes configuration apply to all columns)
char ignore_character - defines character in value that should be ignored: whatever is in the tile already at the indexes of ignore characters should remain unchanged
```

---
## load_configuration
**void load_configuration(const std::string& path, const std::string& name_id, int row, int column, char ignore_character, const std::vector<format_tools::index_format>& colors)**

```
Description:
loads a configuration's value from a file at specified path and immediatly adds the configuration using parameters into ascci_board's data and includes colors in parameters

Parameters:
const std::string& path - absolute or relative path to the file containing a configuration's value
const std::string& name_id - name that also acts as the id of the configuration
int row - row on the board where the configuration should apply (setting to -1 makes configuration apply to all rows)
int column - column on the board where the configuration should apply (setting to -1 makes configuration apply to all columns)
char ignore_character - defines character in value that should be ignored: whatever is in the tile already at the indexes of ignore characters should remain unchanged
const std::vector<format_tools::index_format& colors - vector of index_format structures providing the ability to change the foreground and background colors of tile beginning at specified index of the tile's string
```

---
## load_configuration
**void load_configuration(const std::string& path, const std::string& name_id, int row, int column, char ignore_character, int foreground_format, int background_format, bool bold, bool include_spaces = false)**

```
Description:
loads a configuration's value from a file at specified path and immediatly adds the configuration using parameters into ascii_board's data and includes uniform color in parameters

Parameters:
const std::string& path - absolute or relative path to the file containing a configuration's value
const std::string& name_id - name that also acts as the id of the configuration
int row - row on the board where the configuration should apply (setting to -1 makes configuration apply to all rows)
int column - column on the board where the configuration should apply (setting to -1 makes configuration apply to all columns)
char ignore_character - defines character in value that should be ignored: whatever is in the tile already at the indexes of ignore characters should remain unchanged
int foreground_format - color code defining the color to be applied to the foreground
int background_format - color code defining the color to be applied to the background
bool bold - makes the foreground be brighter if set to true
bool include_spaces - will apply the color to spaces if set to true
```

---
## set_sub_configuration_color
**void set_sub_configuration_color(const std::string& name_id, const std::string& value_match, const std::vector<format_tools::index_format>& colors)**
```
Description:
set color on the portion of a configuration identified by name_id and with a value that matches value_match

Parameters:
const std::string& name_id - the name identifying the configuration to have its color set
const std::string& value_math - only portions of the configuration that have this value match will have their color set
const std::vector<format_tools::index_format>& colors - colors to be set
```

---
## get_number_of_columns
**int get_number_of_columns()**

```
Description:
returns the number of columns in the board

Return value:
int - number of columns in the board
```

---
## get_number_of_rows
**int get_number_of_rows()**

```
Description:
returns the number of rows in the board

Return value:
int - number of columns in the board
```

---
## display
**void display()**

```
Description:
displays the latest state of the board on the frame by only updating the board and not the entire frame
```

---
## build
**void build()**
```
Description:
builds the board and updates the latest state of the board to the frame
```

---
## get_action_tile
**action_tile get_action_tile(int row, int column)**

```
Description:
returns the action tile data structure of the tile at specified row and column

Parameters:
int row - row coordinate where the action_tile data structure should be retrieved
int column - column coordinate where the action_tile data structure should be retrieved
```

---
## configuration_activated
**bool configuration_activated(const std::string& name_id, int row, int column)**

```
Description:
indicates if a configuration is activated on an action tile of the board (a configuration will only be considered activated if all characters in the configuration are found on the specified action tile)

Parameters:
const std::string& name_id - name of the configuration to look for on the action tile
int row - row coordinate of the action tile to look for the configuration
int column - column coordinate of the action tile to look for the configuration

Return value:
bool - true if configuration is activated and false if configuration is not activated
```

---
## modify_configuration
**void modify_configuration(const std::string& target_name_id, const std::string& modification_name_id)**
```
Description:
search for tiles where configurations identified by target_name_id are activated and activate configuration identified by modification_name_id on those action tiles (a configuration will only be considered activated if all characters in the configuration are found on the specified action tile)

Parameters:
const std::string& target_name_id - name of the configuration to be searched for where it is activated on the board
const std::string& modification_name_id - name of the configuration to be activated on action tiles where the configuration identified by target_name_id is activated
```

---
## load_board_translation
**int load_board_translation(const std::string& name_id, const std::string& path, bool load_metadata = false)**
```
Description:
loads a board configuration from file at specified path and will be identified by name_id (translations are useful to display the board in different orientations so the board can be displayed for different player's views)

Parameters:
const std::string& name_id - name identifing the translation
const std::string& path - absolute or relative path to the file containing a board configuration
bool load_metadata - will attempt to load metadata from the board config file if set to true, otherwise, metadata will not be loaded

Return value:
int - status that will be:
      SUCCESS if loaded successfully
      INVALID_PATH if the configuration cannot be loaded at specified path
      INVALID_CONFIG if the configuration is invalid
      INVALID_LENGTH if the dimensions of the array or the number of action tiles defined in the board config do not match that of the original board config loaded in the constructor
      ELEMENT_NOT_FOUND if an action tile in the translation is defined to be at an array coordinate not defined by an action tile in the original board configuration loaded in the constructor
```

---
## use_translation
**void use_translation(const std::string& name_id, bool swap_metadata = false)**
```
Description:
activates a loaded translation and moves action tiles as they are to be at new locations defined by the translation (translations are useful to display the board in different orientations so the board can be displayed for different player's views)

Parameters:
const std::string& name_id - name identifing the translation to be used
bool swap_metadata - will swap current metadata with the metadata of the new translation if true, otherwise, it will keep the current metadata
```

---
## set_lines_count
**void set_lines_count(int lines_count)**
```
Description:
sets the maximum number of lines displayed in the console at once (if 0, there is no limit and if negative, the number of lines will be dynamically determined based on total number of lines in the console minus the negative value)

Parameters:
unsigned int lines_count - number of lines displayed in the console at once
```

---
## set_top_display_index
**void set_top_display_index(unsigned int index)**
```
Description:
sets the index defining the top visible line of the board (will do nothing if the line index is larger than total lines in board minus displayable lines)

Parameters:
unsigned int index - index defining the top visible line of the board
```

---
## set_left_display_index
**void set_left_display_index(unsigned int index)**
```
Description:
sets the index defining the left visible column of the board (will do nothing if the column index is larger than the total columns in the board minus displayable columns)

Parameters:
unsigned int index - index defining the left visible column of the board
```

---
## scroll_up
**void scroll_up(unsigned int amount=1)**
```
Description:
programatically moves the board up specified amount of lines

Parameters:
unsigned int amount - number of lines to scroll up (will do nothing if it would otherwise scroll beyond top side of board)
```

---
## scroll_down
**void scroll_down(unsigned int amount=1)**
```
Description:
programatically moves the board down specified amount of lines

Parameters:
unsigned int amount - number of lines to scroll down (will do nothing if it would otherwise scroll beyond bottom side of board)
```

---
## scroll_left
**void scroll_left(unsigned int amount=1)**
```
Description:
programatically moves the board left specified amount of columns

Parameters:
unsigned int amount - number of columns to scroll left (will do nothing if it would otherwise scroll beyond left side of board)
```

---
## scroll_right
**void scroll_down(unsigned int amount=1)**
```
Description:
programatically moves the board right specified amount of columns

Parameters:
unsigned int amount - number of columns to scroll right (will do nothing if it would otherwise scroll beyond right side of board)
```

---
## bring_tile_into_view
**void bring_tile_into_view(int row, int column, int top_padding = 0, int bottom_padding = 0, int left_padding = 0, int right_padding = 0)**
```
Description:
Ensures that the tile specified by row and column will be visible next time the board is displayed assuming the board is large enough to display the tile completely

Parameters:
int row - row of tile that should be visible next time board is displayed
int column - column of the tile that should be visible next time board is displayed
int top_padding - minimum number of lines that should be shown above the tile
int bottom_padding - minimum number of lines that should be shown below the tile
int left_padding - minimum number of columns (characters) that should be displayed to the left of the tile
int right_padding - minimum number of columns (characters) that should be displayed to the right of the tile
```

---
## get_metadata
**board_metadata\* get_metadata()**
```
Description:
returns board metadata object pointer to access board metadata loaded from board config

Retrun value:
board_metadata* - board metadata object containing all metadata loaded from board config and updated when new config is loaded
```

---
# Non-member Structure Descriptions
---
## struct tile_configuration
```
Values:
int row = -2;
int column = -2;
std::string value = "";
char ignore_character = '\0';
std::vector<format_tools::index_format> colors;

Value descriptions:
int row - row coordinate where the tile should be set to desired value
int column - column coordinate where the tile should be set to desired value
std::string value - value that the tile should be set to
char ignore_character - defines character in value that should be ignored: whatever is in the tile already at the indexes of ignore characters should remain unchanged
const std::vector<format_tools::index_format& colors - vector of index_format structures providing the ability to change the foreground and background colors of tile beginning at specified index of the tile's string
```

---
## struct board_configuration
```
Values:
std::string name_id
std::vector<tile_configuration> tile_configurations

Value descriptions:
std::string name_id - name that also acts as the id of the configuration
std::vector<tile_configuration> tile_configurations - vector of tile configurations that should all be identified with the same name_id
```

---
# Member Structure Descriptions
---
## struct action_tile_board_section
```
Values:
int board_start_row = -1;
int board_stop_row = -1;
int board_start_column = -1;
int board_stop_column = -1;

Value descriptions:
int board_start_row - the row in the '\n' separated string holding the board where the tile begins
int board_stop_row - the row in the '\n' separated string holding the board where the tile ends
int board_start_column - the column in the '\n' separated string holding the board where the tile begins
int board_stop_column - the column in the '\n' separated string holding the board where the tile ends
```

## struct sub_tile_configuration
```
Values:
std::string name_id = "";
std::string value = "";
char ignore_character = '\0';

Value descriptions:
std::string name_id - name of the configuration
std::string value - actual string value of the configuration
char ignore_character - character indicating locations in the value that are not set in the configuration
```

## struct action_tile
```
Values:
int array_row = -1;
int array_column = -1;
std::vector<action_tile_board_section> board_section;
std::string default_value = "";
std::string value = "";
std::vector<format_tools::index_format> colors;
std::vector<sub_tile_configuration> activated_configs;

Value descriptions:
int array_row - row index defining the position of the tile in the board
int array_column - column index defining the position of the tile in the board
std::vector<action_tile_board_section> board_section - vector of structures defining where the tile is located in the board string
std::string default_value - the value of the tile when the board was first loaded from the configuration file
std::string value - value that the tile is currently set to
std::vector<format_tools::index_format> colors - vector of index_format structures defining the current foreground and background colors of tile
std::vector<sub_tile_configuration> activated_configs - vector of structures stating what configurations are activated on the tile
```