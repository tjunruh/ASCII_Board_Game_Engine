#pragma once

#ifdef _WIN32
#ifdef WIDGET_TYPES_EXPORTS
#define WIDGET_TYPES_API __declspec(dllexport)
#else
#define WIDGET_TYPES_API __declspec(dllimport)
#endif
#elif __linux__
#define WIDGET_TYPES_API
#endif

#define WIDGET 0
#define TEXTBOX 1
#define MENU 2
#define BOARD 3
#define LABEL 4
#define FRAME 5