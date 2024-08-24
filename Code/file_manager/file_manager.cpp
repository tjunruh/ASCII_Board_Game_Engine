#include "file_manager.h"
#include <fstream>

int file_manager::write_file(std::string file_path, std::string content)
{
	int status = 1;
	std::ofstream file(file_path);
	if (file.is_open()) {
		file << content << std::endl;
		status = 0;
		file.close();
	}
	else {
		status = 1;
	}
	return status;
}

int file_manager::read_file(std::string file_path, std::string& extracted_content)
{
	std::ifstream file(file_path);
	extracted_content = "";
	int status = 1;

	if (file.is_open()) {
		char letter[1];
		while (!file.eof()) {
			file.read(letter, 1);
			extracted_content = extracted_content + letter[0];
		}
		extracted_content.erase((extracted_content.length() - 1), 1);
		file.close();
		status = 0;
	}
	else {
		extracted_content = "";
		status = 1;
	}
	return status;
}

int file_manager::append_to_file(std::string file_path, std::string content)
{
	int status = 1;
	std::ofstream file(file_path, std::ios_base::app);
	if (file.is_open()) {
		file << content << std::endl;
		status = 0;
		file.close();
	}
	else {
		status = 1;
	}
	return status;
}

std::string file_manager::extract_path(std::string path_with_file)
{
#ifdef WIN32
	char path_seperator = '\\';
#elif __linux__
	char path_seperator = '/';
#endif
	std::string path = "";
	bool path_seperator_encountered = false;
	for (int i = (path_with_file.length() - 1); i >= 0; i--)
	{
		if (path_with_file[i] == path_seperator)
		{
			path_seperator_encountered = true;
		}

		if (path_seperator_encountered)
		{
			path.insert(0, std::string(1, path_with_file[i]));
		}
	}
	return path;
}

std::string file_manager::extract_file(std::string path_with_file)
{
#ifdef WIN32
	char path_seperator = '\\';
#elif __linux__
	char path_seperator = '/';
#endif
	std::string file = "";
	for (int i = (path_with_file.length() - 1); i >= 0; i--)
	{
		if (path_with_file[i] == path_seperator)
		{
			break;
		}
		file.insert(0, std::string(1, path_with_file[i]));
	}
	return file;
}

std::string file_manager::remove_extension(std::string path_with_extension)
{
	std::string file = "";
	for (unsigned int i = 0; i < path_with_extension.length(); i++)
	{
		if (path_with_extension[i] == '.')
		{
			break;
		}
		file = file + path_with_extension[i];
	}
	return file;
}
