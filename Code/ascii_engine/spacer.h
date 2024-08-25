#pragma once
#include <string>
#include "frame.h"

#ifdef _WIN32
#ifdef SPACER_EXPORTS
#define SPACER_API __declspec(dllexport)
#else
#define SPACER_API __declspec(dllimport)
#endif
#endif

void spacer(frame* parent, float multiplier, std::string special_operation="none", bool start_logging=false, std::string logging_file_path="spacer.log");