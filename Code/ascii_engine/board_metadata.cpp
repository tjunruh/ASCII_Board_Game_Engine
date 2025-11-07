#include "../ascii_engine_dll_files/pch.h"
#include "board_metadata.h"

int board_metadata::get_int_metadata(int row, int column, const std::string& metadata_name)
{
	int value = 0;
	last_status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < tile_metadata.size(); i++)
	{
		if (tile_metadata[i].row == row && tile_metadata[i].column == column)
		{
			auto element = tile_metadata[i].metadata.int_data.find(metadata_name);
			if (element != tile_metadata[i].metadata.int_data.end())
			{
				last_status = SUCCESS;
				value = element->second;
			}
			break;
		}
	}

	return value;
}

float board_metadata::get_float_metadata(int row, int column, const std::string& metadata_name)
{
	float value = 0.0;
	last_status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < tile_metadata.size(); i++)
	{
		if (tile_metadata[i].row == row && tile_metadata[i].column == column)
		{
			auto element = tile_metadata[i].metadata.float_data.find(metadata_name);
			if (element != tile_metadata[i].metadata.float_data.end())
			{
				last_status = SUCCESS;
				value = element->second;
			}
			break;
		}
	}

	return value;
}

std::string board_metadata::get_string_metadata(int row, int column, const std::string& metadata_name)
{
	std::string value = "";
	last_status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < tile_metadata.size(); i++)
	{
		if (tile_metadata[i].row == row && tile_metadata[i].column == column)
		{
			auto element = tile_metadata[i].metadata.string_data.find(metadata_name);
			if (element != tile_metadata[i].metadata.string_data.end())
			{
				last_status = SUCCESS;
				value = element->second;
			}
			break;
		}
	}

	return value;
}

int board_metadata::get_int_metadata(const std::string& metadata_name)
{
	int value = 0;
	last_status = ELEMENT_NOT_FOUND;
	auto element = map_metadata.int_data.find(metadata_name);
	if (element != map_metadata.int_data.end())
	{
		last_status = SUCCESS;
		value = element->second;
	}

	return value;
}

float board_metadata::get_float_metadata(const std::string& metadata_name)
{
	float value = 0.0;
	last_status = ELEMENT_NOT_FOUND;
	auto element = map_metadata.float_data.find(metadata_name);
	if (element != map_metadata.float_data.end())
	{
		last_status = SUCCESS;
		value = element->second;
	}

	return value;
}

std::string board_metadata::get_string_metadata(const std::string& metadata_name)
{
	std::string value = "";
	last_status = ELEMENT_NOT_FOUND;
	auto element = map_metadata.string_data.find(metadata_name);
	if (element != map_metadata.string_data.end())
	{
		last_status = SUCCESS;
		value = element->second;
	}

	return value;
}

void board_metadata::insert_int_metadata(int row, int column, const std::string& name, int metadata)
{
	bool tile_exists = false;
	for (unsigned int i = 0; i < tile_metadata.size(); i++)
	{
		if (tile_metadata[i].row == row && tile_metadata[i].column == column)
		{
			tile_metadata[i].metadata.int_data.insert({ name, metadata });
			tile_exists = true;
			break;
		}
	}

	if (!tile_exists)
	{
		metadata_tile tile;
		tile.row = row;
		tile.column = column;
		tile.metadata.int_data.insert({ name, metadata });
		tile_metadata.push_back(tile);
	}
}

void board_metadata::insert_float_metadata(int row, int column, const std::string& name, float metadata)
{
	bool tile_exists = false;
	for (unsigned int i = 0; i < tile_metadata.size(); i++)
	{
		if (tile_metadata[i].row == row && tile_metadata[i].column == column)
		{
			tile_metadata[i].metadata.float_data.insert({ name, metadata });
			tile_exists = true;
			break;
		}
	}

	if (!tile_exists)
	{
		metadata_tile tile;
		tile.row = row;
		tile.column = column;
		tile.metadata.float_data.insert({ name, metadata });
		tile_metadata.push_back(tile);
	}
}

void board_metadata::insert_string_metadata(int row, int column, const std::string& name, const std::string& metadata)
{
	bool tile_exists = false;
	for (unsigned int i = 0; i < tile_metadata.size(); i++)
	{
		if (tile_metadata[i].row == row && tile_metadata[i].column == column)
		{
			tile_metadata[i].metadata.string_data.insert({ name, metadata });
			tile_exists = true;
			break;
		}
	}

	if (!tile_exists)
	{
		metadata_tile tile;
		tile.row = row;
		tile.column = column;
		tile.metadata.string_data.insert({ name, metadata });
		tile_metadata.push_back(tile);
	}
}

void board_metadata::insert_tile_metadata(const metadata_tile& tile)
{
	last_status = SUCCESS;
	bool exists = false;
	for (unsigned int i = 0; i < tile_metadata.size(); i++)
	{
		if (tile_metadata[i].row == tile.row && tile_metadata[i].column == tile.column)
		{
			exists = true;
			last_status = DUPLICATE_ELEMENT;
			break;
		}
	}

	if (!exists)
	{
		tile_metadata.push_back(tile);
	}
}

void board_metadata::insert_int_metadata(const std::string& name, int metadata)
{
	map_metadata.int_data.insert({ name, metadata });
}

void board_metadata::insert_float_metadata(const std::string& name, float metadata)
{
	map_metadata.float_data.insert({ name, metadata });
}

void board_metadata::insert_string_metadata(const std::string& name, const std::string& metadata)
{
	map_metadata.string_data.insert({ name, metadata });
}

void board_metadata::clear_metadata()
{
	tile_metadata.clear();
	map_metadata.int_data.clear();
	map_metadata.float_data.clear();
	map_metadata.string_data.clear();
}

int board_metadata::get_last_status()
{
	return last_status;
}