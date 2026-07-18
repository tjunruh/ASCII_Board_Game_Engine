# board_metadata API

board_metadata is an object that contains data that is mapped to a tile of the board or mapped globally to the entire board. Metadata can be both set and retrieved. When ascii_board loads a board config, metadata in the config will be loaded into a board_metadata object. A pointer to the board_metadata object can then be retrieved from ascii_board. If a project using ASCII_Board_Game_Engine needs to migrate to a different graphics engine, but the logic should be retained, the board metadata object can be exported by executing the export_metadata.sh script from linux command line or Git Bash on Windows. The .cpp and .h files needed for the metadata object will be in the exported_metadata folder at the top level of this repository.

# Functions
- [int get_int_metadata(int row, int column, const std::string& name)](#get_int_metadata)
- [float get_float_metadata(int row, int column, const std::string& name)](#get_float_metadata)
- [std::string get_string_metadata(int row, int column, const std::string& name)](#get_string_metadata)
- [int get_int_metadata(const std::string& name)](#get_int_metadata-1)
- [float get_float_metadata(const std::string& name)](#get_float_metadata-1)
- [std::string get_string_metadata(const std::string& name)](#get_string_metadata-1)
- [void insert_int_metadata(int row, int column, const std::string& name, int metadata)](#insert_int_metadata)
- [void insert_float_metadata(int row, int column, const std::string& name, float metadata)](#insert_float_metadata)
- [void insert_string_metadata(int row, int column, const std::string& name, const std::string& metadata)](#insert_string_metadata)
- [void insert_int_metadata(const std::string& name, int metadata)](#insert_float_metadata-1)
- [void insert_float_metadata(const std::string& name, float metadata)](#insert_float_metadata-1)
- [void insert_string_metadata(const std::string& name, const std::string& name)](#insert_string_metadata-1)
- [void insert_tile_metadata(const metadata_tile& tile)](#insert_tile_metadata)
- [void clear_metadata()](#clear_metadata)
- [int get_last_status()](#get_last_status)

# Member structures
- [metadata_container](#struct-metadata_container)
- [metadata_tile](#struct-metadata_tile)

---
# Function Descriptions
---
## get_int_metadata
**int get_int_metadata(int row, int column, const std::string& name)**

**Description:**

returns integer tile metadata value identified by row, column, and name

**Parameters:**
1. int **row** - row of tile the metadata defines
2. int **column** - column of the tile the metadata defines
3. const std::string& **name** - name of the metadata parameter

**Return value:**

int - integer metadata

---
## get_float_metadata
**float get_float_metadata(int row, int column, const std::string& name)**

**Description:**

returns float tile metadata value identified by row, column, and name

**Parameters:**
1. int **row** - row of tile the metadata defines
2. int **column** - column of the tile the metadata defines
3. const std::string& **name** - name of the metadata parameter

**Return value:**

float - float metadata

---
## get_string_metadata
**std::string get_string_metadata(int row, int column, const std::string& name)**

**Description:**

returns string tile metadata value identified by row, column, and name

**Parameters:**
1. int **row** - row of tile the metadata defines
2. int **column** - column of the tile the metadata defines
3. const std::string& **name** - name of the metadata parameter

**Return value:**

std::string - string metadata

---
## get_int_metadata
**int get_int_metadata(const std::string& name)**

**Description:**

returns integer map metadata value identified by name

**Parameters:**
1. const std::string& **name** - name of the metadata parameter

**Return value:**

int - int metadata

---
## get_float_metadata
**float get_float_metadata(const std::string& name)**

**Description:**

returns float map metadata value identified by name

**Parameters:**
1. const std::string& **name** - name of the metadata parameter

**Return value:**

float - float metadata

---
## get_string_metadata
**std::string get_string_metadata(const std::string& name)**

**Description:**

returns std::string map metadata value identified by name

**Parameters:**
1. const std::string& **name** - name of the metadata parameter

**Return value:**

std::string - string metadata

## insert_int_metadata
**void insert_int_metadata(int row, int column, const std::string& name, int metadata)**

**Description:**

inserts integer metadata that will be identified by name for a tile at row and column (data retrieved using get_int_metadata)

**Parameters:**
1. int **row** - row of tile the metadata defines
2. int **column** - column of the tile the metadata defines
3. const std::string& **name** - name of the metadata parameter
4. int **metadata** - integer metadata value

## insert_float_metadata
**void insert_float_metadata(int row, int column, const std::string& name, float metadata)**

**Description:**

inserts float metadata that will be identified by name for a tile at row and column (data retrieved using get_float_metadata)

**Parameters:**
1. int **row** - row of tile the metadata defines
2. int **column** - column of the tile the metadata defines
3. const std::string& **name** - name of the metadata parameter
4. float **metadata** - float metadata value

## insert_string_metadata
**void insert_string_metadata(int row, int column, const std::string& name, const std::string& metadata)**

**Description:**

inserts string metadata that will be identified by name for a tile at row and column (data retrieved using get_string_metadata)

**Parameters:**
1. int **row** - row of tile the metadata defines
2. int **column** - column of the tile the metadata defines
3. const std::string& **name** - name of the metadata parameter
4. std::string **metadata** - string metadata value

## insert_int_metadata
**void insert_int_metadata(const std::string& name, int metadata)**

**Description:**

inserts integer metadata that will be identified by name for the whole board (data retrieved using get_int_metadata)

**Parameters:**
1. const std::string& **name** - name of the metadata parameter
2. int **metadata** - integer metadata value

## insert_float_metadata
**void insert_float_metadata(const std::string& name, float metadata)**

**Description:**

inserts float metadata that will be identified by name for the whole board (data retrieved using get_float_metadata)

**Parameters:**
1. const std::string& **name** - name of the metadata parameter
2. float **metadata** - float metadata value

## insert_string_metadata
**void insert_string_metadata(const std::string& name, const std::string& name)**

**Description:**

inserts string metadata that will be identified by name for the whole board (data retrieved using get_string_metadata)

**Parameters:**
1. const std::string& **name** - name of the metadata parameter
2. string **metadata** - string metadata value

## insert_tile_metadata
**void insert_tile_metadata(const metadata_tile& tile)**

**Description:**

inserts already populated metadata structure for a tile

**Parameters:**
1. const metadata_tile& **tile** - populated metadata for a tile

## clear_metadata
**void clear_metadata()**

**Description:**

clears all metadata from the object

## get_last_status
**int get_last_status()**

**Description:**

returns the status from the last function executed

**Return value:**

int - status (SUCCESS (0) if successful or ELEMENT_NOT_FOUND (3) if name does not exist in map or tile defined by row and column)

---
# Member Structure Descriptions
---
## struct metadata_container

**Values:**

1. std::unordered_map\<std::string, int\> **int_data**
2. std::unordered_map\<std::string, float\> **float_data**
3. std::unordered_map\<std::string, std::string\> **string_data**

**Value Descriptions:**

1. std::unordered_map\<std::string, int\> **int_data** - map container for integer metadata
2. std::unordered_map\<std::string, float\> **float_data** - map container for float metadata
3. std::unordered_map\<std::string, std::string\> **string_data** - map container for string metadata

---
## struct metadata_tile

**Values:**

1. int **row** = 0
2. int **column** = 0
3. metadata_container **metadata**

**Value Descriptions:**

1. int **row** - row of tile
2. int **column** = column of tile
3. metadata_container **metadata** - metadata of tile
