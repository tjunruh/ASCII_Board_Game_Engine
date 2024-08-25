#pragma once

#ifdef _WIN32
#ifdef ERROR_CODES_EXPORTS
#define ERROR_CODES_API __declspec(dllexport)
#else
#define ERROR_CODES_API __declspec(dllimport)
#endif
#endif

#define UNDEFINED -1
#define SUCCESS 0
#define INVALID_PATH 1
#define INVALID_CONFIG 2
#define ELEMENT_NOT_FOUND 3
#define INVALID_INDEX 4
#define DUPLICATE_ELEMENT 5
#define INVALID_VALUE 6
#define OPERATION_NOT_SUPPORTED 7