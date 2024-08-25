#pragma once
#include <string>

#ifdef _WIN32
#ifdef FILE_MANAGER_EXPORTS
#define FILE_MANAGER_API __declspec(dllexport)
#else
#define FILE_MANAGER_API __declspec(dllimport)
#endif
#endif

namespace file_manager
{
	int write_file(std::string file_path, std::string content);
	int read_file(std::string file_path, std::string& extracted_content);
	int append_to_file(std::string file_path, std::string content);
	std::string extract_path(std::string path_with_file);
	std::string extract_file(std::string path_with_file);
	std::string remove_extension(std::string path_with_extension);
}