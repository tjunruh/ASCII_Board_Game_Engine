#pragma once
#include <string>

namespace board_config_field_titles
{
	const std::string board_begin = "** board begin **\n";
	const std::string board_end = "** board end **\n\n\n";
	const std::string array_dimensions_field = "** Define Dimensions of 2D Array Containing Action Tiles (Rows, Columns) **\n";
	const std::string array_dimensions_begin = "** array dimensions begin **\n";
	const std::string array_dimensions_initialization = "(,)\n";
	const std::string array_dimensions_end = "** array dimensions end **\n\n\n";
	const std::string action_tile_field = "** Define Actions Tiles (Map Row Range, Map Column Range, Array Row, Array Column) **\n";
	const std::string action_tiles_begin = "** action tiles begin **\n";
	const std::string action_tile_initialization = "(,,,)\n  .\n  .\n  .\n";
	const std::string action_tiles_end = "** action tiles end **\n\n\n";
}