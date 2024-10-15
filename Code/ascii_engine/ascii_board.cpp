#include "../ascii_engine_dll_files/pch.h"
#include "ascii_board.h"
#include "../file_manager/file_manager.h"
#include "../validate_board_config/validate_board_config.h"
#include "../board_config_field_parser/board_config_field_parser.h"
#include "error_codes.h"
#include "format_tools.h"

#ifdef __linux__
#include <algorithm>
#endif

ascii_board::ascii_board(frame* parent, std::string path, std::string name_id, std::string special_operation, bool start_logging, std::string logging_file_path) : widget(parent, special_operation)
{
	if (start_logging)
	{
		int logger_status = log.start_widget_logging(logging_file_path, BOARD);
		if (logger_status != 0)
		{
			ascii_io::clear();
			ascii_io::print("ascii_board initialization: Invalid logger path.\nPress any button to continue.");
			ascii_io::getchar();
		}
	}
	log.log_begin("ascii_board::ascii_board");
	validate_board_config validator;
	int status = UNDEFINED;
	std::string board_config = "";
	int file_status = file_manager::read_file(path, board_config);
	if (file_status == 1)
	{
		status = INVALID_PATH;
		log.log_status(status, "ascii_board::ascii_board");
		return;
	}
	std::string validation_debug_log = "";
	int validation_status = validator.validate(board_config, validation_debug_log);
	if (validation_status == 1)
	{
		status = INVALID_CONFIG;
		log.log_status(status, "ascii_board::ascii_board");
		log.log_comment(validation_debug_log);
		return;
	}

	std::string array_dimension_field = "";
	std::string action_tiles_field = "";
	board_config_field_parser parser;
	board = parser.get_board(board_config);
	array_dimension_field = parser.get_dimension_field(board_config);
	action_tiles_field = parser.get_action_tiles_field(board_config);

	parser.get_array_dimensions(array_dimension_field, max_rows, max_columns);

	board_translation translation;
	translation.name_id = name_id;
	translation.board = board;

	initialize_tiles(max_rows, max_columns, translation.action_tile_skeletons);
	set_tile_ranges(action_tiles_field, translation.action_tile_skeletons);
	remove_inactive_tiles(translation.action_tile_skeletons);
	set_tile_default_values(board, translation.action_tile_skeletons);
	board_translations.push_back(translation);
	for (unsigned int i = 0; i < translation.action_tile_skeletons.size(); i++)
	{
		action_tile tile;
		tile.array_row = translation.action_tile_skeletons[i].array_row;
		tile.array_column = translation.action_tile_skeletons[i].array_column;
		tile.board_start_row = translation.action_tile_skeletons[i].board_start_row;
		tile.board_stop_row = translation.action_tile_skeletons[i].board_stop_row;
		tile.board_start_column = translation.action_tile_skeletons[i].board_start_column;
		tile.board_stop_column = translation.action_tile_skeletons[i].board_stop_column;
		tile.default_value = translation.action_tile_skeletons[i].default_value;
		tile.value = translation.action_tile_skeletons[i].default_value;
		action_tiles.push_back(tile);
	}
	set_widget_type(BOARD);
	selectable();
	status = SUCCESS;
	log.log_status(status, "ascii_board::ascii_board");
	log.log_comment(validation_debug_log);
	log.log_end("ascii_board::ascii_board");
}

void ascii_board::clear_tile(int row, int column)
{
	int status = INVALID_INDEX;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if ((action_tiles[i].array_row == row) && (action_tiles[i].array_column == column))
		{
			action_tiles[i].value = action_tiles[i].default_value;
			action_tiles[i].colors.clear();
			action_tiles[i].activated_configs.clear();
			status = SUCCESS;
			break;
		}
	}

	log.log_status(status, "ascii_board::clear_tile");
}

void ascii_board::clear_all()
{
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		action_tiles[i].value = action_tiles[i].default_value;
		action_tiles[i].colors.clear();
		action_tiles[i].activated_configs.clear();
	}
}

void ascii_board::clear_row(int row)
{
	int status = INVALID_INDEX;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (action_tiles[i].array_row == row)
		{
			action_tiles[i].value = action_tiles[i].default_value;
			action_tiles[i].colors.clear();
			action_tiles[i].activated_configs.clear();
			status = SUCCESS;
		}
	}

	log.log_status(status, "ascii_board::clear_row");
}

void ascii_board::clear_column(int column)
{
	int status = INVALID_INDEX;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (action_tiles[i].array_column == column)
		{
			action_tiles[i].value = action_tiles[i].default_value;
			action_tiles[i].colors.clear();
			action_tiles[i].activated_configs.clear();
			status = SUCCESS;
		}
	}

	log.log_status(status, "ascii_board::clear_column");
}

void ascii_board::set_tile(int row, int column, std::string value, char ignore_character)
{
	int status = UNDEFINED;
	int action_tile_index = get_action_tile_index(row, column);
	if (action_tile_index != -1)
	{
		if (value.length() == get_value_length(action_tiles[action_tile_index]))
		{
			for (unsigned int i = 0; i < get_value_length(action_tiles[action_tile_index]); i++)
			{
				if (((value[i] != ignore_character) || (ignore_character == '\0')))
				{
					(action_tiles[action_tile_index].value)[i] = value[i];
				}
			}
			status = SUCCESS;
		}
		else
		{
			status = INVALID_LENGTH;
		}
	}
	else
	{
		status = INVALID_INDEX;
	}
	
	log.log_status(status, "ascii_board::set_tile");
}

void ascii_board::set_tile(int row, int column, std::string value, char ignore_character, const std::vector<format_tools::index_format>& colors)
{
	int status = UNDEFINED;
	int action_tile_index = get_action_tile_index(row, column);
	if (action_tile_index != -1)
	{
		if (value.length() == get_value_length(action_tiles[action_tile_index]))
		{
			for (unsigned int i = 0; i < get_value_length(action_tiles[action_tile_index]); i++)
			{
				if (((value[i] != ignore_character) || (ignore_character == '\0')))
				{
					(action_tiles[action_tile_index].value)[i] = value[i];
				}
			}
			action_tiles[action_tile_index].colors = colors;
			status = SUCCESS;
		}
		else
		{
			status = INVALID_LENGTH;
		}
	}
	else
	{
		status = INVALID_INDEX;
	}

	log.log_status(status, "ascii_board::set_tile");
}

void ascii_board::set_tile(tile_configuration configuration, bool activate, std::string name_id)
{
	int status = UNDEFINED;
	int action_tile_index = get_action_tile_index(configuration.row, configuration.column);
	if (action_tile_index != -1)
	{
		if (get_value_length(action_tiles[action_tile_index]) == configuration.value.length())
		{
			status = SUCCESS;
			for (unsigned int i = 0; i < get_value_length(action_tiles[action_tile_index]); i++)
			{
				if (((configuration.value[i] != configuration.ignore_character) || (configuration.ignore_character == '\0')))
				{
					if (activate)
					{
						(action_tiles[action_tile_index].value)[i] = (configuration.value)[i];
					}
					else
					{
						(action_tiles[action_tile_index].value)[i] = (action_tiles[action_tile_index].default_value)[i];
					}
				}
			}

			if (activate)
			{
				action_tiles[action_tile_index].colors = configuration.colors;
			}
			else
			{
				action_tiles[action_tile_index].colors.clear();
			}

			sub_tile_configuration temp_sub_config;
			temp_sub_config.name_id = name_id;
			temp_sub_config.value = configuration.value;
			temp_sub_config.ignore_character = configuration.ignore_character;
			action_tiles[action_tile_index].activated_configs.push_back(temp_sub_config);
			trim_activated_configs(action_tiles[action_tile_index].activated_configs, action_tiles[action_tile_index].value);
		}
		else
		{
			status = INVALID_LENGTH;
		}
	}
	else
	{
		status = INVALID_INDEX;
	}
	
	log.log_status(status, "ascii_board::set_tile");
}

void ascii_board::set_row(int row, std::string value, char ignore_character)
{
	int status = INVALID_INDEX;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (action_tiles[i].array_row == row)
		{
			status = SUCCESS;
			if (get_value_length(action_tiles[i]) == value.length())
			{
				for (unsigned int j = 0; j < get_value_length(action_tiles[i]); j++)
				{
					if (((value[j] != ignore_character) || (ignore_character == '\0')))
					{
						(action_tiles[i].value)[j] = value[j];
					}
				}
			}
			else
			{
				log.log_status(INVALID_LENGTH, "ascii_board::set_row");
			}
		}
	}
	
	log.log_status(status, "ascii_board::set_row");
}

void ascii_board::set_row(int row, std::string value, char ignore_character, const std::vector<format_tools::index_format>& colors)
{
	int status = INVALID_INDEX;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (action_tiles[i].array_row == row)
		{
			status = SUCCESS;
			if (get_value_length(action_tiles[i]) == value.length())
			{
				for (unsigned int j = 0; j < get_value_length(action_tiles[i]); j++)
				{
					if (((value[j] != ignore_character) || (ignore_character == '\0')))
					{
						(action_tiles[i].value)[j] = value[j];
					}
				}
				action_tiles[i].colors = colors;
			}
			else
			{
				log.log_status(INVALID_LENGTH, "ascii_board::set_row");
			}
		}
	}

	log.log_status(status, "ascii_board::set_row");
}

void ascii_board::set_row(tile_configuration configuration, bool activate, std::string name_id)
{
	int status = INVALID_INDEX;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (action_tiles[i].array_row == configuration.row)
		{
			status = SUCCESS;
			if (get_value_length(action_tiles[i]) == configuration.value.length())
			{
				for (unsigned int j = 0; j < get_value_length(action_tiles[i]); j++)
				{
					if (((configuration.value[j] != configuration.ignore_character) || (configuration.ignore_character == '\0')))
					{
						if (activate)
						{
							(action_tiles[i].value)[j] = configuration.value[j];
						}
						else
						{
							(action_tiles[i].value)[j] = (action_tiles[i].default_value)[j];
						}
					}
				}

				if (activate)
				{
					action_tiles[i].colors = configuration.colors;
				}
				else
				{
					action_tiles[i].colors.clear();
				}

				sub_tile_configuration temp_sub_config;
				temp_sub_config.name_id = name_id;
				temp_sub_config.value = configuration.value;
				temp_sub_config.ignore_character = configuration.ignore_character;
				action_tiles[i].activated_configs.push_back(temp_sub_config);
				trim_activated_configs(action_tiles[i].activated_configs, action_tiles[i].value);
			}
			else
			{
				log.log_status(INVALID_LENGTH, "ascii_board::set_row");
			}
		}
	}
	
	log.log_status(status, "ascii_board::set_row");
}

void ascii_board::set_column(int column, std::string value, char ignore_character)
{
	int status = INVALID_INDEX;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (action_tiles[i].array_column == column)
		{
			status = SUCCESS;
			if (get_value_length(action_tiles[i]) == value.length())
			{
				for (unsigned int j = 0; j < get_value_length(action_tiles[i]); j++)
				{
					if (((value[j] != ignore_character) || (ignore_character == '\0')))
					{
						(action_tiles[i].value)[j] = value[j];
					}
				}
			}
			else
			{
				log.log_status(INVALID_LENGTH, "ascii_board::set_column");
			}
		}
	}
	
	log.log_status(status, "ascii_board::set_column");
}

void ascii_board::set_column(int column, std::string value, char ignore_character, const std::vector<format_tools::index_format>& colors)
{
	int status = INVALID_INDEX;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (action_tiles[i].array_column == column)
		{
			status = SUCCESS;
			if (get_value_length(action_tiles[i]) == value.length())
			{
				for (unsigned int j = 0; j < get_value_length(action_tiles[i]); j++)
				{
					if (((value[j] != ignore_character) || (ignore_character == '\0')))
					{
						(action_tiles[i].value)[j] = value[j];
					}
				}
				action_tiles[i].colors = colors;
			}
			else
			{
				log.log_status(INVALID_LENGTH, "ascii_board::set_column");
			}
		}
	}

	log.log_status(status, "ascii_board::set_column");
}

void ascii_board::set_column(tile_configuration configuration, bool activate, std::string name_id)
{
	int status = INVALID_INDEX;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (action_tiles[i].array_column == configuration.column)
		{
			status = SUCCESS;
			if (get_value_length(action_tiles[i]) == configuration.value.length())
			{
				for (unsigned int j = 0; j < get_value_length(action_tiles[i]); j++)
				{
					if (((configuration.value)[j] != configuration.ignore_character) || (configuration.ignore_character == '\0'))
					{
						if (activate)
						{
							(action_tiles[i].value)[j] = configuration.value[j];
						}
						else
						{
							(action_tiles[i].value)[j] = (action_tiles[i].default_value)[j];
						}
					}
				}

				if (activate)
				{
					action_tiles[i].colors = configuration.colors;
					
				}
				else
				{
					action_tiles[i].colors.clear();
				}

				sub_tile_configuration temp_sub_config;
				temp_sub_config.name_id = name_id;
				temp_sub_config.value = configuration.value;
				temp_sub_config.ignore_character = configuration.ignore_character;
				action_tiles[i].activated_configs.push_back(temp_sub_config);
				trim_activated_configs(action_tiles[i].activated_configs, action_tiles[i].value);
			}
			else
			{
				log.log_status(INVALID_LENGTH, "ascii_board::set_column");
			}
		}
	}
	
	log.log_status(status, "ascii_board::set_column");
}

void ascii_board::set_all(std::string value, char ignore_character)
{
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (get_value_length(action_tiles[i]) == value.length())
		{
			for (unsigned int j = 0; j < get_value_length(action_tiles[i]); j++)
			{
				if ((value[j] != ignore_character) || (ignore_character == '\0'))
				{
					(action_tiles[i].value)[j] = value[j];
				}
			}
		}
		else
		{
			log.log_status(INVALID_INDEX, "ascii_board::set_all");
		}
	}
	
	log.log_status(SUCCESS, "ascii_board::set_all");
}

void ascii_board::set_all(std::string value, char ignore_character, const std::vector<format_tools::index_format>& colors)
{
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (get_value_length(action_tiles[i]) == value.length())
		{
			for (unsigned int j = 0; j < get_value_length(action_tiles[i]); j++)
			{
				if ((value[j] != ignore_character) || (ignore_character == '\0'))
				{
					(action_tiles[i].value)[j] = value[j];
				}
				action_tiles[i].colors = colors;
			}
		}
		else
		{
			log.log_status(INVALID_INDEX, "ascii_board::set_all");
		}
	}

	log.log_status(SUCCESS, "ascii_board::set_all");
}

void ascii_board::set_all(tile_configuration configuration, bool activate, std::string name_id)
{
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if (get_value_length(action_tiles[i]) == configuration.value.length())
		{
			for (unsigned int j = 0; j < get_value_length(action_tiles[i]); j++)
			{
				if (((configuration.value)[j] != configuration.ignore_character) || (configuration.ignore_character == '\0'))
				{
					if (activate)
					{
						(action_tiles[i].value)[j] = configuration.value[j];
					}
					else
					{
						(action_tiles[i].value)[j] = (action_tiles[i].default_value)[j];
					}
				}
			}

			if (activate)
			{
				action_tiles[i].colors = configuration.colors;
			}
			else
			{
				action_tiles[i].colors.clear();
			}

			sub_tile_configuration temp_sub_config;
			temp_sub_config.name_id = name_id;
			temp_sub_config.value = configuration.value;
			temp_sub_config.ignore_character = configuration.ignore_character;
			action_tiles[i].activated_configs.push_back(temp_sub_config);
			trim_activated_configs(action_tiles[i].activated_configs, action_tiles[i].value);
		}
		else
		{
			log.log_status(INVALID_INDEX, "ascii_board::set_all");
		}
	}
	
	log.log_status(SUCCESS, "ascii_board::set_all");
}

void ascii_board::set_tile_character(int row, int column, char character, unsigned int character_index)
{
	int status = INVALID_INDEX;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if ((action_tiles[i].array_row == row) && (action_tiles[i].array_column == column))
		{
			if ((character_index >= 0) && (character_index < get_value_length(action_tiles[i])))
			{
				(action_tiles[i].value)[character_index] = character;
				status = SUCCESS;
			}
		}
	}
	
	log.log_status(status, "ascii_board::set_tile_character");
}

std::string ascii_board::get_tile(int row, int column)
{
	std::string tile = "";
	int status = INVALID_INDEX;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if ((action_tiles[i].array_row == row) && (action_tiles[i].array_column == column))
		{
			tile = action_tiles[i].value;
			status = SUCCESS;
		}
	}

	log.log_status(status, "ascii_board::get_tile");
	return tile;
}

char ascii_board::get_tile_character(int row, int column, unsigned int character_index)
{
	char character = ' ';
	int status = INVALID_INDEX;
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		if ((action_tiles[i].array_row == row) && (action_tiles[i].array_column == column) && (character_index > 0) && (character_index < get_value_length(action_tiles[i])))
		{
			character = (action_tiles[i].value)[character_index];
			status = SUCCESS;
		}
	}

	log.log_status(status, "ascii_board::get_tile_character");
	return character;
}

std::string ascii_board::get_board()
{
	update_board();
	return board;
}

void ascii_board::add_configuration(board_configuration configuration)
{
	int status = UNDEFINED;
	if (configuration.name_id == "")
	{
		status = INVALID_VALUE;
	}
	else if (!configuration_present(configuration.name_id) && !duplicate_point_present(configuration))
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

	log.log_status(status, "ascii_board::add_configuration");
}

void ascii_board::add_configuration(std::string name_id, int row, int column, std::string value, char ignore_character)
{
	board_configuration board_config;
	tile_configuration tile_config;
	board_config.name_id = name_id;
	tile_config.row = row;
	tile_config.column = column;
	tile_config.value = value;
	tile_config.ignore_character = ignore_character;
	board_config.tile_configurations.push_back(tile_config);
	add_configuration(board_config);
}

void ascii_board::add_configuration(std::string name_id, int row, int column, std::string value, char ignore_character, const std::vector<format_tools::index_format>& colors)
{
	board_configuration board_config;
	tile_configuration tile_config;
	board_config.name_id = name_id;
	tile_config.row = row;
	tile_config.column = column;
	tile_config.value = value;
	tile_config.ignore_character = ignore_character;
	tile_config.colors = colors;
	board_config.tile_configurations.push_back(tile_config);
	add_configuration(board_config);
}

void ascii_board::activate_configuration(std::string name_id, int row, int column)
{
	int config_index = get_board_config_index(name_id);
	int config_tile_index = get_tile_config_index(name_id, row, column);
	log.log_begin("ascii_board::activate_configuration");
	if ((config_index != -1) && (config_tile_index != -1))
	{
		tile_configuration temp_tile_config;
		temp_tile_config = board_configurations[config_index].tile_configurations[config_tile_index];
		temp_tile_config.row = row;
		temp_tile_config.column = column;
		if ((row != -1) && (column != -1))
		{
			set_tile(temp_tile_config, true, board_configurations[config_index].name_id);
		}
		else if ((row == -1) && (column == -1))
		{
			set_all(temp_tile_config, true, board_configurations[config_index].name_id);
		}
		else if (column == -1)
		{
			set_row(temp_tile_config, true, board_configurations[config_index].name_id);
		}
		else if (row == -1)
		{
			set_column(temp_tile_config, true, board_configurations[config_index].name_id);
		}
	}
	else if (config_index == -1)
	{
		log.log_status(ELEMENT_NOT_FOUND, "ascii_board::activate_configuration");
	}
	else
	{
		log.log_status(INVALID_INDEX, "ascii_board::activate_configuration");
	}
	
	log.log_end("ascii_board::activate_configuration");
}

void ascii_board::activate_configuration(std::string name_id)
{
	int config_index = get_board_config_index(name_id);
	log.log_begin("ascii_board::activate_configuration");
	if (config_index != -1)
	{
		for (unsigned int i = 0; i < board_configurations[config_index].tile_configurations.size(); i++)
		{
			log.log_comment("Activation for: " + board_configurations[config_index].tile_configurations[i].value);
			if ((board_configurations[config_index].tile_configurations[i].row != -1) && (board_configurations[config_index].tile_configurations[i].column != -1))
			{
				set_tile(board_configurations[config_index].tile_configurations[i], true, board_configurations[config_index].name_id);
			}
			else if ((board_configurations[config_index].tile_configurations[i].row == -1) && (board_configurations[config_index].tile_configurations[i].column == -1))
			{
				set_all(board_configurations[config_index].tile_configurations[i], true, board_configurations[config_index].name_id);
			}
			else if (board_configurations[config_index].tile_configurations[i].column == -1)
			{
				set_row(board_configurations[config_index].tile_configurations[i], true, board_configurations[config_index].name_id);
			}
			else if (board_configurations[config_index].tile_configurations[i].row == -1)
			{
				set_column(board_configurations[config_index].tile_configurations[i], true, board_configurations[config_index].name_id);
			}
		}
	}
	else
	{
		log.log_status(ELEMENT_NOT_FOUND, "ascii_board::activate_configuration");
	}

	log.log_end("ascii_board::activate_configuration");
}

void ascii_board::deactivate_configuration(std::string name_id, int row, int column)
{
	int config_index = get_board_config_index(name_id);
	int config_tile_index = get_tile_config_index(name_id, row, column);
	std::vector<format_tools::index_format> colors;
	log.log_begin("ascii_board::deactivate_configuration");
	if ((config_index != -1) && (config_tile_index != -1))
	{
		tile_configuration temp_tile_config;
		temp_tile_config = board_configurations[config_index].tile_configurations[config_tile_index];
		temp_tile_config.row = row;
		temp_tile_config.column = column;
		if ((row != -1) && (column != -1))
		{
			set_tile(temp_tile_config, false);
		}
		else if ((row == -1) && (column == -1))
		{
			set_all(temp_tile_config, false);
		}
		else if (column == -1)
		{
			set_row(temp_tile_config, false);
		}
		else if (row == -1)
		{
			set_column(temp_tile_config, false);
		}
	}
	else if (config_index == -1)
	{
		log.log_status(ELEMENT_NOT_FOUND, "ascii_board::deactivate_configuration");
	}
	else
	{
		log.log_status(INVALID_INDEX, "ascii_board::deactivate_configuration");
	}
	
	log.log_end("ascii_board::deactivate_configuration");
}

void ascii_board::deactivate_configuration(std::string name_id)
{
	int config_index = get_board_config_index(name_id);
	log.log_begin("ascii_board::deactivate_configuration");
	if (config_index != -1)
	{
		for (unsigned int i = 0; i < board_configurations[config_index].tile_configurations.size(); i++)
		{
			if ((board_configurations[config_index].tile_configurations[i].row != -1) && (board_configurations[config_index].tile_configurations[i].column != -1))
			{
				set_tile(board_configurations[config_index].tile_configurations[i], false);
			}
			else if ((board_configurations[config_index].tile_configurations[i].row == -1) && (board_configurations[config_index].tile_configurations[i].column == -1))
			{
				set_all(board_configurations[config_index].tile_configurations[i], false);
			}
			else if (board_configurations[config_index].tile_configurations[i].column == -1)
			{
				set_row(board_configurations[config_index].tile_configurations[i], false);
			}
			else if (board_configurations[config_index].tile_configurations[i].row == -1)
			{
				set_column(board_configurations[config_index].tile_configurations[i], false);
			}
		}
	}
	else
	{
		log.log_status(ELEMENT_NOT_FOUND, "ascii_board::deactivate_configuration");
	}
	
	log.log_end("ascii_board::deactivate_configuration");
}

std::string ascii_board::load_configuration(std::string path)
{
	std::string value = "";
	int file_status = file_manager::read_file(path, value);
	if (file_status == 1)
	{
		log.log_status(INVALID_PATH, "ascii_board::load_configuration");
		return "";
	}
	log.log_status(SUCCESS, "ascii_board::load_configuration");
	format_tools::remove_newline_characters(value);
	return value;
}

void ascii_board::load_configuration(std::string path, std::string name_id, int row, int column, char ignore_character)
{
	log.log_begin("ascii_board::load_configuration");
	std::string value = load_configuration(path);
	if (value == "")
	{
		return;
	}
	add_configuration(name_id, row, column, value, ignore_character);
	log.log_end("ascii_board::load_configuration");
}

void ascii_board::load_configuration(std::string path, std::string name_id, int row, int column, char ignore_character, const std::vector<format_tools::index_format>& colors)
{
	log.log_begin("ascii_board::load_configuration");
	std::string value = load_configuration(path);
	if (value == "")
	{
		return;
	}
	add_configuration(name_id, row, column, value, ignore_character, colors);
	log.log_end("ascii_board::load_configuration");
}

int ascii_board::get_number_of_columns()
{
	return max_columns;
}

int ascii_board::get_number_of_rows()
{
	return max_rows;
}

void ascii_board::display()
{
	unsigned int width = get_width();
	if (frame_stale())
	{
		sync();
		frame_display();
	}
	else if (dec_enabled() || color_enabled())
	{
		int x_origin = get_x_origin();
		int y_origin = get_y_origin();
		int cursor_x = 0;
		int cursor_y = 0;
		ascii_io::get_cursor_position(cursor_x, cursor_y);
		update_board();
		std::vector<format_tools::index_format> index_regions;
		std::vector<std::string> lines;
		std::string board_copy = board;
		if (color_enabled())
		{
			index_regions = board_colors;
			std::vector<int> ignore_flags = format_tools::set_flags(index_regions, board_copy, '*');
			lines = format_tools::get_lines(board_copy);
			lines = format_tools::remove_newline_characters(lines);
			lines = format_tools::fill_lines(lines, width, get_alignment());
			std::vector<format_tools::coordinate_format> coordinate_colors;
			format_tools::convert_flags(coordinate_colors, index_regions, ignore_flags, lines, '*');
			index_regions = format_tools::convert(coordinate_colors, width);
		}
		else
		{
			lines = format_tools::get_lines(board_copy);
			lines = format_tools::remove_newline_characters(lines);
			lines = format_tools::fill_lines(lines, width, get_alignment());
		}

		std::string adjusted_board = format_tools::get_string(lines);
		
		if (dec_enabled())
		{
			std::vector<format_tools::index_format> dec_regions = dec_format(adjusted_board, get_width());
			if (index_regions.size() > 0)
			{
				index_regions = format_tools::combine(index_regions, dec_regions);
			}
			else
			{
				index_regions = dec_regions;
			}
		}
		
		int line = 0;
		unsigned int line_length = 0;
		ascii_io::move_cursor_to_position(x_origin, y_origin);
		std::vector<format_tools::content_format> regions = format_tools::convert(index_regions, adjusted_board);
		regions = format_tools::fit_to_width(regions, width);
		for (unsigned int i = 0; i < regions.size(); i++)
		{
			int foreground_color = get_default_foreground_color();
			int background_color = get_default_background_color();
			if (std::count(format_tools::colors.begin(), format_tools::colors.end(), regions[i].format.foreground_format) != 0)
			{
				foreground_color = regions[i].format.foreground_format;
			}

			if (std::count(format_tools::colors.begin(), format_tools::colors.end(), regions[i].format.background_format) != 0)
			{
				background_color = regions[i].format.background_format;
			}

			ascii_io::set_color(foreground_color, background_color, regions[i].format.bold);

			if (regions[i].format.dec)
			{
#ifdef _WIN32
				ascii_io::enable_dec();
				ascii_io::print(regions[i].content);
#elif __linux__
				dec_print(regions[i].content);
#endif
			}
			else
			{
#ifdef _WIN32
				ascii_io::disable_dec();
#endif
				ascii_io::print(regions[i].content);
			}
			line_length = line_length + regions[i].content.length();
			if (line_length >= width)
			{
				line++;
				line_length = 0;
				ascii_io::move_cursor_to_position(x_origin, y_origin + line);
			}
		}
#ifdef _WIN32
		ascii_io::disable_dec();
#endif
		ascii_io::move_cursor_to_position(cursor_x, cursor_y);
	}
	else
	{
		int x_origin = get_x_origin();
		int y_origin = get_y_origin();
		int cursor_x = 0;
		int cursor_y = 0;
		ascii_io::get_cursor_position(cursor_x, cursor_y);
		update_board();
		std::vector<std::string> lines = format_tools::get_lines(board);
		lines = format_tools::remove_newline_characters(lines);
		lines = format_tools::fill_lines(lines, width, get_alignment());
		for (unsigned int i = 0; i < lines.size(); i++)
		{
			ascii_io::move_cursor_to_position(x_origin, y_origin + i);
			ascii_io::print(lines[i]);
		}
		ascii_io::move_cursor_to_position(cursor_x, cursor_y);
	}
}

void ascii_board::sync()
{
	update_board();
	set_output_to_frame(board);
	set_index_colors(board_colors);
}

ascii_board::action_tile ascii_board::get_action_tile(int row, int column)
{
	int index = get_action_tile_index(row, column);
	action_tile tile;
	if (index != -1)
	{
		tile = action_tiles[index];
		log.log_status(SUCCESS, "ascii_board::get_action_tile");
	}
	else
	{
		log.log_status(INVALID_INDEX, "ascii_board::get_action_tile");
	}
	return tile;
}

bool ascii_board::configuration_activated(std::string name_id, int row, int column)
{
	bool activated = false;
	int status = UNDEFINED;
	if ((row < 0 ) || (column < 0) || (row >= get_number_of_rows()) || (column >= get_number_of_columns()))
	{
		status = INVALID_INDEX;
	}
	else
	{
		status = ELEMENT_NOT_FOUND;
		for (unsigned int i = 0; i < action_tiles.size(); i++)
		{
			if ((action_tiles[i].array_row == row) && (action_tiles[i].array_column == column))
			{
				if (configuration_activated(action_tiles[i].activated_configs, name_id))
				{
					activated = true;
				}
				status = SUCCESS;
				break;
			}
		}
	}

	log.log_status(status, "ascii_board::configuration_activated");
	return activated;
}

void ascii_board::modify_configuration(std::string target_name_id, std::string modification_name_id)
{
	int status = UNDEFINED;
	if (!configuration_present(target_name_id) || !configuration_present(modification_name_id))
	{
		status = ELEMENT_NOT_FOUND;
	}
	else
	{
		status = SUCCESS;
		for (unsigned int i = 0; i < action_tiles.size(); i++)
		{
			if (configuration_activated(action_tiles[i].activated_configs, target_name_id))
			{
				activate_configuration(modification_name_id, action_tiles[i].array_row, action_tiles[i].array_column);
			}
		}
	}

	log.log_status(status, "ascii_board::modify_configuration");
}

int ascii_board::load_board_translation(std::string name_id, std::string path)
{
	log.log_begin("ascii_board::load_board_translation");
	board_translation translation;
	translation.name_id = name_id;
	log.log_begin("ascii_board::load_board_translation");
	validate_board_config validator;
	int status = UNDEFINED;
	std::string board_config = "";
	int file_status = file_manager::read_file(path, board_config);
	if (file_status == 1)
	{
		status = INVALID_PATH;
		log.log_status(status, "ascii_board::load_board_translation");
		return status;
	}
	std::string validation_debug_log = "";
	int validation_status = validator.validate(board_config, validation_debug_log);
	if (validation_status == 1)
	{
		status = INVALID_CONFIG;
		log.log_status(status, "ascii_board::load_board_translation");
		log.log_comment(validation_debug_log);
		return status;
	}

	std::string array_dimension_field = "";
	board_config_field_parser parser;
	array_dimension_field = parser.get_dimension_field(board_config);

	int number_of_rows = 0;
	int number_of_columns = 0;

	parser.get_array_dimensions(array_dimension_field, number_of_rows, number_of_columns);

	if ((number_of_rows != max_rows) || (number_of_columns != max_columns))
	{
		status = INVALID_LENGTH;
		log.log_status(status, "ascii_board::load_board_translation");
		return status;
	}

	std::string action_tiles_field = "";
	translation.board = parser.get_board(board_config);
	action_tiles_field = parser.get_action_tiles_field(board_config);
	initialize_tiles(number_of_rows, number_of_columns, translation.action_tile_skeletons);
	set_tile_ranges(action_tiles_field, translation.action_tile_skeletons);
	remove_inactive_tiles(translation.action_tile_skeletons);
	status = validate_translation(translation.action_tile_skeletons);
	if (status != SUCCESS)
	{
		log.log_status(status, "ascii_board::load_board_translation");
		return status;
	}
	set_tile_default_values(translation.board, translation.action_tile_skeletons);
	board_translations.push_back(translation);
	status = SUCCESS;
	log.log_comment(validation_debug_log);
	log.log_status(SUCCESS, "ascii_board::load_board_translation");
	log.log_end("ascii_board::load_board_translation");
}

void ascii_board::use_translation(std::string name_id)
{
	int status = ELEMENT_NOT_FOUND;
	board_translation translation;
	for (unsigned int i = 0; i < board_translations.size(); i++)
	{
		if (board_translations[i].name_id == name_id)
		{
			status = SUCCESS;
			translation = board_translations[i];
			break;
		}
	}

	if (status == SUCCESS)
	{
		for (unsigned int i = 0; i < translation.action_tile_skeletons.size(); i++)
		{
			for (unsigned int j = 0; j < action_tiles.size(); j++)
			{
				if ((translation.action_tile_skeletons[i].array_row == action_tiles[j].array_row) && (translation.action_tile_skeletons[i].array_column == action_tiles[j].array_column))
				{
					action_tiles[j].board_start_row = translation.action_tile_skeletons[i].board_start_row;
					action_tiles[j].board_stop_row = translation.action_tile_skeletons[i].board_stop_row;
					action_tiles[j].board_start_column = translation.action_tile_skeletons[i].board_start_column;
					action_tiles[j].board_stop_column = translation.action_tile_skeletons[i].board_stop_column;
					for (unsigned int k = 0; k < action_tiles[j].default_value.length(); k++)
					{
						if (action_tiles[j].value[k] == action_tiles[j].default_value[k])
						{
							action_tiles[j].value[k] = translation.action_tile_skeletons[i].default_value[k];
						}
					}
					action_tiles[j].default_value = translation.action_tile_skeletons[i].default_value;
				}
			}
		}
	}

	log.log_status(status, "ascii_board::use_translation");
}

void ascii_board::initialize_tiles(int rows, int columns, std::vector<action_tile_skeleton>& action_tile_skeletons)
{
	action_tile_skeletons.clear();
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			action_tile_skeleton tile;
			tile.array_row = row;
			tile.array_column = column;
			action_tile_skeletons.push_back(tile);
		}
	}
}

void ascii_board::set_tile_ranges(std::string content, std::vector<action_tile_skeleton>& action_tile_skeletons)
{
	int parameter = 0;
	bool range_end = false;
	std::string array_row = "";
	std::string array_column = "";
	std::string map_start_row = "";
	std::string map_stop_row = "";
	std::string map_start_column = "";
	std::string map_stop_column = "";
	for (unsigned int i = 0; i < content.length(); i++)
	{
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
			set_tile_range(stoi(array_row), stoi(array_column), stoi(map_start_row), stoi(map_stop_row), stoi(map_start_column), stoi(map_stop_column), action_tile_skeletons);
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

void ascii_board::remove_inactive_tiles(std::vector<action_tile_skeleton>& action_tile_skeletons)
{
	int elements = action_tile_skeletons.size() - 1;

	for (int i = elements; i >= 0; i--)
	{
		if ((action_tile_skeletons[i].board_start_row == -1) || (action_tile_skeletons[i].board_stop_row == -1) || (action_tile_skeletons[i].board_start_column == -1) || (action_tile_skeletons[i].board_stop_column == -1))
		{
			action_tile_skeletons.erase(action_tile_skeletons.begin() + i);
		}
	}
}

void ascii_board::set_tile_range(int array_row, int array_column, int board_start_row, int board_stop_row, int board_start_column, int board_stop_column, std::vector<action_tile_skeleton>& action_tile_skeletons)
{
	for (unsigned int i = 0; i < action_tile_skeletons.size(); i++)
	{
		if ((action_tile_skeletons[i].array_row == array_row) && (action_tile_skeletons[i].array_column == array_column))
		{
			action_tile_skeletons[i].board_start_row = board_start_row;
			action_tile_skeletons[i].board_stop_row = board_stop_row;
			action_tile_skeletons[i].board_start_column = board_start_column;
			action_tile_skeletons[i].board_stop_column = board_stop_column;
			break;
		}
	}
}

void ascii_board::set_tile_default_values(const std::string& board_reference, std::vector<action_tile_skeleton>& action_tile_skeletons)
{
	for (unsigned int i = 0; i < action_tile_skeletons.size(); i++)
	{
		action_tile_skeletons[i].default_value = get_board_section(board_reference, action_tile_skeletons[i].board_start_row, action_tile_skeletons[i].board_stop_row, action_tile_skeletons[i].board_start_column, action_tile_skeletons[i].board_stop_column);
	}
}

std::string ascii_board::get_board_section(const std::string& board_reference, int start_row, int stop_row, int start_column, int stop_column)
{
	int row = 0;
	int column = 0;
	std::string section = "";
	for (unsigned int i = 0; i < board_reference.length(); i++)
	{
		if ((row >= start_row) && (row <= stop_row) && (column >= start_column) && (column <= stop_column))
		{
			section = section + board_reference[i];
		}

		if (board_reference[i] == '\n')
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
	board_colors.clear();
	for (unsigned int i = 0; i < action_tiles.size(); i++)
	{
		int row = 0;
		int column = 0;
		unsigned int value_position = 0;
		bool color_active = false;
		for (unsigned int j = 0; j < board.length(); j++)
		{
			if ((row >= action_tiles[i].board_start_row) && (row <= action_tiles[i].board_stop_row) && (column >= action_tiles[i].board_start_column) && (column <= action_tiles[i].board_stop_column))
			{
				if (value_position < get_value_length(action_tiles[i]))
				{
					board[j] = (action_tiles[i].value)[value_position];
					for (unsigned int k = 0; k < action_tiles[i].colors.size(); k++)
					{
						if (action_tiles[i].colors[k].index == (int)value_position)
						{
							color_active = true;
							format_tools::index_format color = action_tiles[i].colors[k];
							color.index = j;
							board_colors.push_back(color);
						}
					}
					value_position++;
				}
			}
			else if (color_active)
			{
				format_tools::index_format color;
				color.index = j;
				color.format.foreground_format = format_tools::none;
				color.format.background_format = format_tools::none;
				board_colors.push_back(color);
				color_active = false;
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

unsigned int ascii_board::get_value_length(action_tile tile)
{
	unsigned int width = 0;
	unsigned int height = 0;

	width = (unsigned int)(tile.board_stop_column - tile.board_start_column + 1);
	height = (unsigned int)(tile.board_stop_row - tile.board_start_row + 1);

	unsigned int length = width * height;

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
		if (!action_tile_index_exists(configuration.tile_configurations[i].row, configuration.tile_configurations[i].column))
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

				for (unsigned int k = 0; k < configuration.tile_configurations[i].colors.size(); k++)
				{
					if ((configuration.tile_configurations[i].colors[k].index < 0) || configuration.tile_configurations[i].colors[k].index >= (int)get_value_length(action_tiles[j]))
					{
						acceptability = false;
						return acceptability;
					}
				}
			}
		}
	}
	return acceptability;
}

bool ascii_board::action_tile_index_exists(int row, int column)
{
	bool exists = false;
	if ((row == -1) && (column == -1))
	{
		exists = true;
	}
	else if (column == -1)
	{
		for (unsigned int i = 0; i < action_tiles.size(); i++)
		{
			if (action_tiles[i].array_row == row)
			{
				exists = true;
				break;
			}
		}
	}
	else if (row == -1)
	{
		for (unsigned int i = 0; i < action_tiles.size(); i++)
		{
			if (action_tiles[i].array_column == column)
			{
				exists = true;
				break;
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < action_tiles.size(); i++)
		{
			if ((action_tiles[i].array_row == row) && (action_tiles[i].array_column == column))
			{
				exists = true;
				break;
			}
		}
	}
	return exists;
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
	if ((board_config_index != -1) && action_tile_index_exists(row, column))
	{
		for (unsigned int i = 0; i < board_configurations[board_config_index].tile_configurations.size(); i++)
		{
			if (((board_configurations[board_config_index].tile_configurations[i].row == row) || (board_configurations[board_config_index].tile_configurations[i].row == -1)) && ((board_configurations[board_config_index].tile_configurations[i].column == column) || (board_configurations[board_config_index].tile_configurations[i].column == -1)))
			{
				index = i;
				break;
			}
		}
	}
	return index;
}

std::string ascii_board::fill_default_value_with_ignore_character(std::string config_value, std::string default_value, char ignore_character)
{
	if (config_value.length() == default_value.length())
	{
		for (unsigned int i = 0; i < config_value.length(); i++)
		{
			if (config_value[i] == ignore_character)
			{
				default_value[i] = ignore_character;
			}
		}
	}
	return default_value;
}

void ascii_board::trim_activated_configs(std::vector<sub_tile_configuration>& activated_configurations, std::string tile_value)
{
	for (int i = (activated_configurations.size() - 1); i >= 0; i--)
	{
		if (activated_configurations[i].value.length() == tile_value.length())
		{
			for (unsigned int j = 0; j < tile_value.length(); j++)
			{
				if ((activated_configurations[i].value[j] != activated_configurations[i].ignore_character) && (activated_configurations[i].value[j] != tile_value[j]))
				{
					activated_configurations.erase(activated_configurations.begin() + i);
					break;
				}
			}
		}
		else
		{
			log.log_comment("ascii_board::trim_activated_config: " + activated_configurations[i].value + " is not the same length as " + tile_value);
		}
		
	}
}

bool ascii_board::configuration_activated(std::vector<sub_tile_configuration> activated_configurations, std::string name_id)
{
	bool activated = false;
	for (unsigned int i = 0; i < activated_configurations.size(); i++)
	{
		if (activated_configurations[i].name_id == name_id)
		{
			activated = true;
		}
	}
	return activated;
}

int ascii_board::validate_translation(std::vector<action_tile_skeleton> action_tile_skeletons)
{
	int status = SUCCESS;
	if (action_tile_skeletons.size() != action_tiles.size())
	{
		status = INVALID_LENGTH;
		return status;
	}

	for (unsigned int i = 0; i < action_tile_skeletons.size(); i++)
	{
		bool action_tile_found = false;
		for (unsigned int j = 0; j < action_tiles.size(); j++)
		{
			if ((action_tile_skeletons[i].array_row == action_tiles[j].array_row) && (action_tile_skeletons[i].array_column == action_tiles[j].array_column))
			{
				action_tile_found = true;
				int skeleton_row_range = action_tile_skeletons[i].board_stop_row - action_tile_skeletons[i].board_start_row;
				int skeleton_column_range = action_tile_skeletons[i].board_stop_column - action_tile_skeletons[i].board_start_column;
				int tile_row_range = action_tiles[j].board_stop_row - action_tiles[j].board_start_row;
				int tile_column_range = action_tiles[j].board_stop_column - action_tiles[j].board_start_column;
				if ((skeleton_row_range != tile_row_range) || (skeleton_column_range != tile_column_range))
				{
					return INVALID_INDEX;
				}
			}
		}

		if (!action_tile_found)
		{
			return ELEMENT_NOT_FOUND;
		}
	}
}