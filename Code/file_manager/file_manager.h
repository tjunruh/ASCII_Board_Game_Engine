#pragma once
#include <string>

namespace file_manager
{
	int write_file(std::string file_path, std::string content);
	int read_file(std::string file_path, std::string& extracted_content);
	std::string extract_path(std::string path_with_file);
	std::string extract_file(std::string path_with_file);
	std::string remove_extension(std::string path_with_extension);
}