#pragma once
#include <string>

#ifdef _WIN32
#ifdef BOARD_CONFIG_FIELD_TITLES_EXPORTS
#define BOARD_CONFIG_FIELD_TITLES_API __declspec(dllexport)
#else
#define BOARD_CONFIG_FIELD_TITLES_API __declspec(dllimport)
#endif
#elif __linux__
#define BOARD_CONFIG_FIELD_TITLES_API
#endif


namespace board_config_field_titles
{
	const std::string board_begin = "** board begin **";
	const std::string board_end = "** board end **";
	const std::string array_dimensions_field = "** Define Dimensions of 2D Array Containing Action Tiles (Rows, Columns) **\n";
	const std::string array_dimensions_begin = "** array dimensions begin **";
	const std::string array_dimensions_initialization = "(,)\n";
	const std::string array_dimensions_end = "** array dimensions end **";
	const std::string action_tile_field = "** Define Actions Tiles (Map Row Range, Map Column Range, Array Row, Array Column) **\n";
	const std::string action_tiles_begin = "** action tiles begin **";
	const std::string action_tile_initialization = "(,,,)\n  .\n  .\n  .\n";
	const std::string action_tiles_end = "** action tiles end **";
	const std::string metadata_field = "** Define Metadata - Global: (Key, Value) Action Tile Specific: {(Key, Value), (Key, Value), (Key, Value)...} - value can be integer, float, or string (string must be enclosed in quotation marks).\nNote that two key value pairs in each curly bracket block must be used to define the row and column of action tile the metadata is related to **\n";
	const std::string metadata_begin = "** metadata begin **";
	const std::string metadata_initialization = "Global:\n(Key, Value)\n(Key, Value)\n\nAction Tile Specific:\n{\n   (row, 0)\n   (column, 0)\n   (Key, Value)\n   (Key, Value)\n}\n\n{\n   (row, 0)\n   (column, 0)\n   (Key, Value)\n   (Key, Value)\n}\n  .\n  .\n  .\n";
	const std::string metadata_end = "** metadata end **";
}