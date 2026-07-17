# file_manager API

file_manager includes functions providing the ability to read and write files and perform basic operations on file paths. Functions in the file_manager namespace include:
```
int write_file(std::string file_path, std::string content)
int read_file(std::string file_path, std::string& extracted_content)
int append_to_file(std::string file_path, std::string content)
int delete_file(std::string file_path)
std::string extract_path(std::string path_with_file)
std::string extract_file(std::string path_with_file)
std::string remove_extension(std::string path_with_extension)
```

---
# Function Descriptions
---
## write_file
**int write_file(std::string file_path, std::string content)**
```
Description:
writes file at specified path to contain desired content

Parameters:
std::string file_path - absolute or relative path to file that should be written
std::string content - content that should be written in the file

Return value:
int - status code that will be 0 on success and 1 on failure
```

---
## read_file
**int read_file(std::string file_path, std::string& extracted_content)**
```
Description:
reads file at specified path and extracts its content

Parameters:
std::string file_path - absolute or relative path to file that should be read
std::string& extracted_content - extracted content from the file

Return value:
int - status code that will be 0 on success and 1 on failure
```

---
## append_to_file
**int append_to_file(std::string file_path, std::string content)**
```
Description:
appends content to the end of file at specified path

Parameters:
std::string file_path - absolute or relative path to file that should have content appended
std::string content - content that should be appended to the file

Return value:
int - status code that will be 0 on success and 1 on failure
```

---
## delete_file
**int delete_file(std::string file_path)**
```
Description:
deletes file at specified path

Parameters:
std::string file_path - absolute or relative path to file that should be deleted

Return value:
int - status code that will be 0 on success and 1 on failure
```

---
## extract_path
**std::string extract_path(std::string path_with_file)**
```
Description:
extracts the file path with the file removed from the path

Parameters:
std::string path_with_file - file path including the file

Return value:
std::string - the file path without the file
```

---
## extract_file
**std::string extract_file(std::string path_with_file)**
```
Description:
extracts the file from the file path

Parameters:
std::string path_with_file - file path including the path and file

Return value:
std::string - the file without the rest of the path
```

---
## remove_extension
**std::string remove_extension(std::string path_with_extension)**
```
Description:
removes the file extension from the file path

Parameters:
std::string path_with_extension - file path including extension in the form of .extension

Return value:
std::string - the file path without the file extension
```