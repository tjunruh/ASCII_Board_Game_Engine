# board_metadata API

board_metadata is an object that contains data that is mapped to a tile of the board or mapped globally to the entire board. Metadata can be both set and retrieved. When ascii_board loads a board config, metadata in the config will be loaded into a board_metadata object. A pointer to the board_metadata object can then be retrieved from ascii_board. If a project using ASCII_Board_Game_Engine needs to migrate to a different graphics engine, but the logic should be retained, the board metadata object can be exported by executing the export_metadata.sh script from linux command line or Git Bash on Windows. The .cpp and .h files needed for the metadata object will be in the exported_metadata folder at the top level of this repository.

```
int get_int_metadata(int row, int column, const std::string& name)
float get_float_metadata(int row, int column, const std::string& name)
std::string get_string_metadata(int row, int column, const std::string& name)
int get_int_metadata(const std::string& name)
float get_float_metadata(const std::string& name)
std::string get_string_metadata(const std::string& name)
void insert_int_metadata(int row, int column, const std::string& name, int metadata)
void insert_float_metadata(int row, int column, const std::string& name, float metadata)
void insert_string_metadata(int row, int column, const std::string& name, const std::string& metadata)
void insert_int_metadata(const std::string& name, int metadata)
void insert_float_metadata(const std::string& name, float metadata)
void insert_string_metadata(const std::string& name, const std::string& name)
void insert_tile_metadata(const metadata_tile& tile)
void clear_metadata()
int get_last_status()
```

---
# Function Descriptions
---
## get_int_metadata
**int get_int_metadata(int row, int column, const std::string& name)**

```
Description:
returns integer tile metadata value identified by row, column, and name

Parameters:
int row - row of tile the metadata defines
int column - column of the tile the metadata defines
const std::string& name - name of the metadata parameter

Return value:
int - integer metadata
```

---
## get_float_metadata
**float get_float_metadata(int row, int column, const std::string& name)**

```
Description:
returns float tile metadata value identified by row, column, and name

Parameters:
int row - row of tile the metadata defines
int column - column of the tile the metadata defines
const std::string& name - name of the metadata parameter

Return value:
float - float metadata
```

---
## get_string_metadata
**std::string get_string_metadata(int row, int column, const std::string& name)**

```
Description:
returns string tile metadata value identified by row, column, and name

Parameters:
int row - row of tile the metadata defines
int column - column of the tile the metadata defines
const std::string& name - name of the metadata parameter

Return value:
std::string - string metadata
```

---
## get_int_metadata
**int get_int_metadata(const std::string& name)**

```
Description:
returns integer map metadata value identified by name

Parameters:
const std::string& name - name of the metadata parameter

Return value:
int - int metadata
```

---
## get_float_metadata
**float get_float_metadata(const std::string& name)**

```
Description:
returns float map metadata value identified by name

Parameters:
const std::string& name - name of the metadata parameter

Return value:
float - float metadata
```

---
## get_string_metadata
**std::string get_string_metadata(const std::string& name)**

```
Description:
returns std::string map metadata value identified by name

Parameters:
const std::string& name - name of the metadata parameter

Return value:
std::string - string metadata
```

## insert_int_metadata
**void insert_int_metadata(int row, int column, const std::string& name, int metadata)**

```
Description:
inserts integer metadata that will be identified by name for a tile at row and column (data retrieved using get_int_metadata)

Parameters:
int row - row of tile the metadata defines
int column - column of the tile the metadata defines
const std::string& name - name of the metadata parameter
int metadata - integer metadata value
```

## insert_float_metadata
**void insert_float_metadata(int row, int column, const std::string& name, float metadata)**

```
Description:
inserts float metadata that will be identified by name for a tile at row and column (data retrieved using get_float_metadata)

Parameters:
int row - row of tile the metadata defines
int column - column of the tile the metadata defines
const std::string& name - name of the metadata parameter
float metadata - float metadata value
```

## insert_string_metadata
**void insert_string_metadata(int row, int column, const std::string& name, const std::string& metadata)**

```
Description:
inserts string metadata that will be identified by name for a tile at row and column (data retrieved using get_string_metadata)

Parameters:
int row - row of tile the metadata defines
int column - column of the tile the metadata defines
const std::string& name - name of the metadata parameter
std::string metadata - string metadata value
```

## insert_int_metadata
**void insert_int_metadata(const std::string& name, int metadata)**

```
Description:
inserts integer metadata that will be identified by name for the whole board (data retrieved using get_int_metadata)

Parameters:
const std::string& name - name of the metadata parameter
int metadata - integer metadata value
```

## insert_float_metadata
**void insert_float_metadata(const std::string& name, float metadata)**

```
Description:
inserts float metadata that will be identified by name for the whole board (data retrieved using get_float_metadata)

Parameters:
const std::string& name - name of the metadata parameter
float metadata - float metadata value
```

## insert_string_metadata
**void insert_string_metadata(const std::string& name, const std::string& name)**

```
Description:
inserts string metadata that will be identified by name for the whole board (data retrieved using get_string_metadata)

Parameters:
const std::string& name - name of the metadata parameter
string metadata - string metadata value
```

## insert_tile_metadata
**void insert_tile_metadata(const metadata_tile& tile)**

```
Description:
inserts already populated metadata structure for a tile

Parameters:
const metadata_tile& tile - populated metadata for a tile
```

## clear_metadata
**void clear_metadata()**

```
Description:
clears all metadata from the object
```

## get_last_status
**int get_last_status()**

```
Description:
returns the status from the last function executed

int - status (SUCCESS (0) if successful or ELEMENT_NOT_FOUND (3) if name does not exist in map or tile defined by row and column)
```

---
# Member Structure Descriptions
---
## struct metadata_container
```
Values:
std::unordered_map<std::string, int> int_data
std::unordered_map<std::string, float> float_data
std::unordered_map<std::string, std::string> string_data

Value Descriptions:
std::unordered_map<std::string, int> int_data - map container for integer metadata
std::unordered_map<std::string, float> float_data - map container for float metadata
std::unordered_map<std::string, std::string> string_data - map container for string metadata
```

---
## struct metadata_tile
```
Values:
int row = 0
int column = 0
metadata_container metadata

Value Descriptions:
int row - row of tile
int column = column of tile
metadata_container metadata - metadata of tile
```
