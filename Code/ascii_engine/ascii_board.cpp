#include "ascii_board.h"
#include "../file_manager/file_manager.h"
#include "../validate_map_config/validate_map_config.h"
#include <iostream>

ascii_board::ascii_board(std::string path, int& status)
{
	validate_map_config validator;
	status = UNDEFINED;
	std::string board_config = "";
	int file_status = file_manager::read_file(path, board_config);
	if (file_status == 1)
	{
		status = INVALID_PATH;
		return;
	}

	int validation_status = validator.validate(board_config, true);
	if (validation_status == 1)
	{
		status = INVALID_CONFIG;
		return;
	}

	std::string array_dimension_field = "";
	std::string action_tiles_field = "";

	board = validator.get_map(board_config);
	array_dimension_field = validator.get_map_dimension_field(board_config);
	action_tiles_field = validator.get_map_action_tiles_field(board_config);

	validator.get_array_dimensions(array_dimension_field, max_rows, max_columns);

	initialize_tiles(max_rows, max_columns);
	set_tile_ranges(action_tiles_field);
	remove_inactive_tiles();
	set_tile_default_values();

	status = SUCCESS;
}

int ascii_board::clear_tile(int row, int column)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if ((action_tiles[i].array_row == row) && (action_tiles[i].array_column == column))
		{
			action_tiles[i].value = action_tiles[i].default_value;
			status = SUCCESS;
			break;
		}
	}
	return status;
}

void ascii_board::clear_tiles()
{
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		action_tiles[i].value = action_tiles[i].default_value;
	}
}

int ascii_board::set_tile(int row, int column, std::string value, char ignore_character)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if ((action_tiles[i].array_row == row) && (action_tiles[i].array_column == column))
		{
			if (value.length() == get_value_length(action_tiles[i]))
			{
				for (int j = 0; j < get_value_length(action_tiles[i]); j++)
				{
					if (((value[j] != ignore_character) && (ignore_character == '\0')))
					{
						(action_tiles[i].value)[j] = value[j];
					}
				}
				status = SUCCESS;
			}
			else
			{
				status = INVALID_INDEX;
			}
		}
	}
	return status;
}

int ascii_board::set_tile(tile_configuration configuration)
{
	int status = UNDEFINED;
	int action_tile_index = get_action_tile_index(configuration.row, configuration.column);
	if (action_tile_index != -1)
	{
		if (get_value_length(action_tiles[action_tile_index]) == configuration.value.length())
		{
			status = SUCCESS;
			for (int i = 0; i < get_value_length(action_tiles[action_tile_index]); i++)
			{
				if (((configuration.value[i] != configuration.ignore_character) || (configuration.ignore_character == '\0')))
				{
					(action_tiles[action_tile_index].value)[i] = (configuration.value)[i];
				}
			}
		}
		else
		{
			status = INVALID_INDEX;
		}
	}
	else
	{
		status = ELEMENT_NOT_FOUND;
	}
	return status;
}

int ascii_board::set_row(int row, std::string value, char ignore_character)
{
	int status = SUCCESS;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (action_tiles[i].array_row == row)
		{
			if (get_value_length(action_tiles[i]) == value.length())
			{
				for (int j = 0; j < get_value_length(action_tiles[i]); j++)
				{
					if (((value[j] != ignore_character) || (ignore_character == '\0')))
					{
						(action_tiles[i].value)[j] = value[j];
					}
				}
			}
			else
			{
				status = INVALID_INDEX;
				break;
			}
		}
	}
	return status;
}

int ascii_board::set_row(tile_configuration configuration)
{
	int status = SUCCESS;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (action_tiles[i].array_row == configuration.row)
		{
			if (get_value_length(action_tiles[i]) == configuration.value.length())
			{
				for (int j = 0; j < get_value_length(action_tiles[i]); j++)
				{
					if (((configuration.value[j] != configuration.ignore_character) || (configuration.ignore_character == '\0')))
					{
						(action_tiles[i].value)[j] = configuration.value[j];
					}
				}
			}
			else
			{
				status = INVALID_INDEX;
				break;
			}
		}
	}
	return status;
}

int ascii_board::set_column(int column, std::string value, char ignore_character)
{
	int status = SUCCESS;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (action_tiles[i].array_column == column)
		{
			if (get_value_length(action_tiles[i]) == value.length())
			{
				for (int j = 0; j < get_value_length(action_tiles[i]); j++)
				{
					if (((value[j] != ignore_character) || (ignore_character == '\0')))
					{
						(action_tiles[i].value)[j] = value[j];
					}
				}
			}
			else
			{
				status = INVALID_INDEX;
				break;
			}
		}
	}
	return status;
}

int ascii_board::set_column(tile_configuration configuration)
{
	int status = SUCCESS;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (action_tiles[i].array_column == configuration.column)
		{
			if (get_value_length(action_tiles[i]) == configuration.value.length())
			{
				for (int j = 0; j < get_value_length(action_tiles[i]); j++)
				{
					if (((configuration.value)[j] != configuration.ignore_character) || (configuration.ignore_character == '\0'))
					{
						(action_tiles[i].value)[j] = configuration.value[j];
					}
				}
			}
			else
			{
				status = INVALID_INDEX;
				break;
			}
		}
	}
	return status;
}

int ascii_board::set_all(std::string value, char ignore_character)
{
	int status = SUCCESS;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (get_value_length(action_tiles[i]) == value.length())
		{
			for (int j = 0; j < get_value_length(action_tiles[i]); j++)
			{
				if ((value[j] != ignore_character) || (ignore_character == '\0'))
				{
					(action_tiles[i].value)[j] = value[j];
				}
			}
		}
		else
		{
			status = INVALID_INDEX;
			break;
		}
	}
	return status;
}

int ascii_board::set_all(tile_configuration configuration)
{
	int status = SUCCESS;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (get_value_length(action_tiles[i]) == configuration.value.length())
		{
			for (int j = 0; j < get_value_length(action_tiles[i]); j++)
			{
				if (((configuration.value)[j] != configuration.ignore_character) || (configuration.ignore_character == '\0'))
				{
					(action_tiles[i].value)[j] = configuration.value[j];
				}
			}
		}
		else
		{
			status = INVALID_INDEX;
			break;
		}
	}
	return status;
}
int ascii_board::set_tile_character(int row, int column, char character, int character_index)
{
	int status = ELEMENT_NOT_FOUND;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if ((action_tiles[i].array_row == row) && (action_tiles[i].array_column == column))
		{
			if ((character_index >= 0) && (character_index < get_value_length(action_tiles[i])))
			{
				(action_tiles[i].value)[character_index] = character;
				status = SUCCESS;
			}
			else
			{
				status = INVALID_INDEX;
			}
		}
	}
	return status;
}

std::string ascii_board::get_tile(int row, int column)
{
	std::string tile = "";
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if ((action_tiles[i].array_row == row) && (action_tiles[i].array_column == column))
		{
			tile = action_tiles[i].value;
		}
	}
	return tile;
}

char ascii_board::get_tile_character(int row, int column, int character_index)
{
	char character = ' ';
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if ((action_tiles[i].array_row == row) && (action_tiles[i].array_column == column) && (character_index > 0) && (character_index < get_value_length(action_tiles[i])))
		{
			character = (action_tiles[i].value)[character_index];
		}
	}
	return character;
}

std::string ascii_board::get_board()
{
	update_board();
	return board;
}

int ascii_board::add_configuration(board_configuration configuration)
{
	int status = UNDEFINED;
	if (!configuration_present(configuration.name_id) && !duplicate_point_present(configuration))
	{
		if (configuration_indexing_acceptable(configuration))
		{
			board_configurations.push_back(configuration);
			status = SUCCESS;
		}
		else
		{
			status = INVALID_INDEX;
		}
	}
	else
	{
		status = DUPLICATE_ELEMENT;
	}

	return status;
}

int ascii_board::activate_configuration(int row, int column, std::string name_id)
{
	int status = UNDEFINED;
	int config_index = -1;
	int config_tile_index = -1;
	config_index = get_board_config_index(name_id);
	config_tile_index = get_tile_config_index(name_id, row, column);

	if ((config_index != -1) && (config_tile_index != -1))
	{
		status = set_tile(board_configurations[config_index].tile_configurations[config_tile_index]);
	}
	else
	{
		status = ELEMENT_NOT_FOUND;
	}
	return status;
}

int ascii_board::activate_configuration(std::string name_id)
{
	int status = UNDEFINED;
	int config_index = -1;
	config_index = get_board_config_index(name_id);
	if (config_index != -1)
	{
		for (unsigned int i = 0; i < board_configurations[config_index].tile_configurations.size(); i++)
		{
			if ((board_configurations[config_index].tile_configurations[i].row != -1) && (board_configurations[config_index].tile_configurations[i].column != -1))
			{
				status = set_tile(board_configurations[config_index].tile_configurations[i]);
			}
			else if ((board_configurations[config_index].tile_configurations[i].row == -1) && (board_configurations[config_index].tile_configurations[i].column == -1))
			{
				status = set_all(board_configurations[config_index].tile_configurations[i]);
			}
			else if (board_configurations[config_index].tile_configurations[i].column == -1)
			{
				status = set_row(board_configurations[config_index].tile_configurations[i]);
			}
			else if (board_configurations[config_index].tile_configurations[i].row == -1)
			{
				status = set_column(board_configurations[config_index].tile_configurations[i]);
			}
			
			if (status != SUCCESS)
			{
				break;
			}
		}
	}
	else
	{
		status = ELEMENT_NOT_FOUND;
	}
	return status;
}

int ascii_board::get_number_of_columns()
{
	return max_columns;
}

int ascii_board::get_number_of_rows()
{
	return max_rows;
}

void ascii_board::initialize_tiles(int rows, int columns)
{
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			action_tile tile;
			tile.array_row = row;
			tile.array_column = column;
			action_tiles.push_back(tile);
		}
	}
}

void ascii_board::set_tile_ranges(std::string content)
{
	int parameter = 0;
	char parenthesis = ' ';
	bool range_end = false;
	std::string array_row = "";
	std::string array_column = "";
	std::string map_start_row = "";
	std::string map_stop_row = "";
	std::string map_start_column = "";
	std::string map_stop_column = "";
	for (unsigned int i = 0; i < content.length(); i++)
	{
		if ((content[i] == '(') || (content[i] == ')'))
		{
			parenthesis = content[i];
		}

		if (content[i] == ',')
		{
			parameter++;
			range_end = false;
		}

		if (content[i] == ')')
		{
			parameter = 0;
			if (map_stop_row == "")
			{
				map_stop_row = map_start_row;
			}

			if (map_stop_column == "")
			{
				map_stop_column = map_start_column;
			}
			set_tile_range(stoi(array_row), stoi(array_column), stoi(map_start_row), stoi(map_stop_row), stoi(map_start_column), stoi(map_stop_column));
			array_row = "";
			array_column = "";
			map_start_row = "";
			map_stop_row = "";
			map_start_column = "";
			map_stop_column = "";
		}

		if (content[i] == '-')
		{
			range_end = true;
		}

		if(isdigit(content[i]))
		{
			if (parameter == 0)
			{
				if (range_end)
				{
					map_stop_row = map_stop_row + content[i];
				}
				else
				{
					map_start_row = map_start_row + content[i];
				}
			}
			else if (parameter == 1)
			{
				if (range_end)
				{
					map_stop_column = map_stop_column + content[i];
				}
				else
				{
					map_start_column = map_start_column + content[i];
				}
			}
			else if (parameter == 2)
			{
				array_row = array_row + content[i];
			}
			else if (parameter == 3)
			{
				array_column = array_column + content[i];
			}
		}
	}
}

void ascii_board::remove_inactive_tiles()
{
	int elements = action_tiles.size() - 1;

	for (int i = elements; i >= 0; i--)
	{
		if ((action_tiles[i].board_start_row == -1) || (action_tiles[i].board_stop_row == -1) || (action_tiles[i].board_start_column == -1) || (action_tiles[i].board_stop_column == -1))
		{
			action_tiles.erase(action_tiles.begin() + i);
		}
	}
}

void ascii_board::set_tile_range(int array_row, int array_column, int board_start_row, int board_stop_row, int board_start_column, int board_stop_column)
{
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if ((action_tiles[i].array_row == array_row) && (action_tiles[i].array_column == array_column))
		{
			action_tiles[i].board_start_row = board_start_row;
			action_tiles[i].board_stop_row = board_stop_row;
			action_tiles[i].board_start_column = board_start_column;
			action_tiles[i].board_stop_column = board_stop_column;
			break;
		}
	}
}

void ascii_board::set_tile_default_values()
{
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		action_tiles[i].default_value = get_board_section(action_tiles[i].board_start_row, action_tiles[i].board_stop_row, action_tiles[i].board_start_column, action_tiles[i].board_stop_column);
		action_tiles[i].value = action_tiles[i].default_value;
	}
}

std::string ascii_board::get_board_section(int start_row, int stop_row, int start_column, int stop_column)
{
	int row = 0;
	int column = 0;
	std::string section = "";
	for (unsigned int i = 0; i < board.length(); i++)
	{
		if ((row >= start_row) && (row <= stop_row) && (column >= start_column) && (column <= stop_column))
		{
			section = section + board[i];
		}

		if (board[i] == '\n')
		{
			row++;
			column = 0;
		}
		else
		{
			column++;
		}
	}

	return section;
}

void ascii_board::update_board()
{
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		int row = 0;
		int column = 0;
		int value_position = 0;
		for (unsigned int j = 0; j < board.length(); j++)
		{
			if ((row >= action_tiles[i].board_start_row) && (row <= action_tiles[i].board_stop_row) && (column >= action_tiles[i].board_start_column) && (column <= action_tiles[i].board_stop_column))
			{
				if (value_position < get_value_length(action_tiles[i]))
				{
					board[j] = (action_tiles[i].value)[value_position];
					value_position++;
				}
			}

			if (board[j] == '\n')
			{
				row++;
				column = 0;
			}
			else
			{
				column++;
			}
		}
	}
}

int ascii_board::get_value_length(action_tile tile)
{
	int width = 0;
	int height = 0;

	width = tile.board_stop_column - tile.board_start_column + 1;
	height = tile.board_stop_row - tile.board_stop_row + 1;

	int length = width * height;

	return length;
}

bool ascii_board::configuration_present(std::string name_id)
{
	bool duplicate = false;
	for (unsigned int i = 0; i < board_configurations.size(); i++)
	{
		if (board_configurations[i].name_id == name_id)
		{
			duplicate = true;;
		}
	}
	return duplicate;
}

board_configuration ascii_board::get_configuration(std::string name_id)
{
	board_configuration configuration;
	for (unsigned int i = 0; i < board_configurations.size(); i++)
	{
		if (board_configurations[i].name_id == name_id)
		{
			configuration = board_configurations[i];
			break;
		}
	}
	return configuration;
}

bool ascii_board::duplicate_point_present(board_configuration configuration)
{
	bool duplicate_found = false;
	for (unsigned int i = 0; i < configuration.tile_configurations.size(); i++)
	{
		for (unsigned int j = (i + 1); j < configuration.tile_configurations.size(); j++)
		{
			if ((configuration.tile_configurations[i].row == configuration.tile_configurations[j].row) && (configuration.tile_configurations[i].column == configuration.tile_configurations[j].column))
			{
				duplicate_found = true;
				break;
			}
		}
	}
	return duplicate_found;
}

bool ascii_board::configuration_indexing_acceptable(board_configuration configuration)
{
	bool acceptability = true;
	for (unsigned int i = 0; i < configuration.tile_configurations.size(); i++)
	{
		if ((configuration.tile_configurations[i].row < -1) || (configuration.tile_configurations[i].column < -1) || (configuration.tile_configurations[i].row >= max_rows) || (configuration.tile_configurations[i].column >= max_columns))
		{
			acceptability = false;
			break;
		}

		for (unsigned int j = 0; j < action_tiles.size(); j++)
		{
			if (((configuration.tile_configurations[i].row == -1) || (configuration.tile_configurations[i].row == action_tiles[j].array_row)) && ((configuration.tile_configurations[i].column == -1) || (configuration.tile_configurations[i].column == action_tiles[j].array_column)))
			{
				if (configuration.tile_configurations[i].value.length() != get_value_length(action_tiles[j]))
				{
					acceptability = false;
					break;
				}
			}
		}
	}
	return acceptability;
}

int ascii_board::get_action_tile_index(int row, int column)
{
	int index = -1;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if ((action_tiles[i].array_row == row) && (action_tiles[i].array_column == column))
		{
			index = i;
			break;
		}
	}
	return index;
}

int ascii_board::get_board_config_index(std::string name_id)
{
	int index = -1;
	for (unsigned int i = 0; i < board_configurations.size(); i++)
	{
		if (board_configurations[i].name_id == name_id)
		{
			index = i;
			break;
		}
	}
	return index;
}

int ascii_board::get_tile_config_index(std::string name_id, int row, int column)
{
	int board_config_index = get_board_config_index(name_id);
	int index = -1;
	if (board_config_index != -1)
	{
		for (unsigned int i = 0; i < board_configurations[board_config_index].tile_configurations.size(); i++)
		{
			if ((board_configurations[board_config_index].tile_configurations[i].row == row) && (board_configurations[board_config_index].tile_configurations[i].column == column))
			{
				index = i;
				break;
			}
		}
	}
	return index;
}