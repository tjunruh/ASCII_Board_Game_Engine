#pragma once
#include <unordered_map>
#include <vector>
#include "../ascii_engine/error_codes.h"

#ifdef _WIN32
#ifdef BOARD_METADATA_EXPORTS
#define BOARD_METADATA_API __declspec(dllexport)
#else
#define BOARD_METADATA_API __declspec(dllimport)
#endif
#elif __linux__
#define BOARD_METADATA_API
#endif

class board_metadata
{
public:
	struct metadata_container
	{
		std::unordered_map<std::string, int> int_data;
		std::unordered_map<std::string, float> float_data;
		std::unordered_map<std::string, std::string> string_data;
	};

	struct metadata_tile
	{
		int row = 0;
		int column = 0;
		metadata_container metadata;
	};

	BOARD_METADATA_API int get_int_metadata(int row, int column, const std::string& metadata_name);
	BOARD_METADATA_API float get_float_metadata(int row, int column, const std::string& metadata_name);
	BOARD_METADATA_API std::string get_string_metadata(int row, int column, const std::string& metadata_name);
	BOARD_METADATA_API int get_int_metadata(const std::string& metadata);
	BOARD_METADATA_API float get_float_metadata(const std::string& metadata);
	BOARD_METADATA_API std::string get_string_metadata(const std::string& metadata);
	BOARD_METADATA_API void insert_int_metadata(int row, int column, const std::string& name, int metadata);
	BOARD_METADATA_API void insert_float_metadata(int row, int column, const std::string& name, float metadata);
	BOARD_METADATA_API void insert_string_metadata(int row, int column, const std::string& name, const std::string& metadata);
	BOARD_METADATA_API void insert_int_metadata(const std::string& name, int metadata);
	BOARD_METADATA_API void insert_float_metadata(const std::string& name, float metadata);
	BOARD_METADATA_API void insert_string_metadata(const std::string& name, const std::string& metadata);
	BOARD_METADATA_API void insert_tile_metadata(const metadata_tile& tile);
	BOARD_METADATA_API void clear_metadata();
	BOARD_METADATA_API int get_last_status();

private:
	metadata_container map_metadata;
	std::vector<metadata_tile> tile_metadata;
	int last_status = UNDEFINED;
};