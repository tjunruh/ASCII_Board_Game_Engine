#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "ascii_io.h"
#include "error_codes.h"

#ifdef _WIN32
#ifdef CONTROLS_EXPORTS
#define CONTROLS_API __declspec(dllexport)
#else
#define CONTROLS_API __declspec(dllimport)
#endif
#elif __linux__
#define CONTROLS_API
#endif

class controls
{
public:
	CONTROLS_API int bind(const std::string& control_name, const int key);
	CONTROLS_API int unbind(const std::string& control_name);
	CONTROLS_API int get_key(const std::string& control_name);
	CONTROLS_API int load_controls(const std::string& file_path);
	CONTROLS_API int save_controls(const std::string& file_path);
private:
	std::unordered_map<std::string, const int> control_mapping;
};
