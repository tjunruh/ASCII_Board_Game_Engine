#pragma once
#include <string>

#ifdef _WIN32
#ifdef FILE_MANAGER_EXPORTS
#define FILE_MANAGER_API __declspec(dllexport)
#else
#define FILE_MANAGER_API __declspec(dllimport)
#endif
#elif __linux__
#define FILE_MANAGER_API
#endif

namespace file_manager
{
	FILE_MANAGER_API int write_file(std::string file_path, std::string content);
	FILE_MANAGER_API int read_file(std::string file_path, std::string& extracted_content);
	FILE_MANAGER_API int append_to_file(std::string file_path, std::string content);
	FILE_MANAGER_API int delete_file(std::string file_path);
	FILE_MANAGER_API std::string extract_path(std::string path_with_file);
	FILE_MANAGER_API std::string extract_file(std::string path_with_file);
	FILE_MANAGER_API std::string remove_extension(std::string path_with_extension);
}