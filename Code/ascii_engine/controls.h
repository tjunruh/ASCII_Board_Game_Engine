#pragma once
#include <string>
#include <vector>
#include <map>
#include "ascii_io.h"
#include "error_codes.h"

class controls
{
public:
	/*
	* control name can be any name of developers choosing so long as
	* it is not duplicate. Key is to be a key defined in ascii_io.
	* 
	* Function should store binding in control_mapping
	* 
	* return either SUCCESS or DUPLICATE_ELEMENT from error_codes.h
	*/
	int bind(std::string control_name, const int key);

	/*
	* Control name can be any name of developers choosing. Search
	* control map for control name. If found, delete it and return
	* SUCCESS. Otherwise, return ELEMENT_NOT_FOUND
	*/
	int unbind(std::string control_name);

	/*
	* control_name can be any name of developers choosing. Search
	* control map for control name. Return the value to the key
	* in control_mapping. If not found, return ascii_io::undefined
	*/
	const int get_key(std::string control_name);

	/*
	* Load a file containing controls and populate control_mapping.
	* file_manager.h contains code that can be used to load a file.
	* Determine a way to parse the file content.
	* JSON is an option or you can make
	* a custom parser. However, whatever direction we take should
	* be used for everything including loading game state.
	* 
	* return SUCCESS if successful load, INVALID_PATH if file not 
	* found, or INVALID_CONFIG if parsing error.
	*/
	int load_controls(std::string file_path);

	/*
	* Save information from control_mapping to file at file_path
	* location. file_manager.h contains a function for saving
	* a string. JSON can be a method of making the information
	* savable. However, whatever direction we take should
	* be used for everything including saving game state.
	* 
	* return SUCCESS if saved or INVALID_PATH if failure.
	*/
	int save_controls(std::string file_path);

private:
	std::map<std::string, const int> control_mapping;
};