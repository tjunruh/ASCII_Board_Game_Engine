#include "ascii_io.h"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#elif __linux__
#include <ncurses.h>
#endif

void ascii_io::print(const std::string& output) {
#ifdef _WIN32
	std::cout << output;
#elif __linux__
	printw(output.c_str());
#endif
}

int ascii_io::getchar() {
	int input = 0;
#ifdef _WIN32
	input = _getch();
#elif __linux__
	input = getch();
	if (input == 27) {
		input = getch();
		input = getch();
	}
#endif

	return input;
}

void ascii_io::clear() {
#ifdef _WIN32
	system("cls");
#elif __linux__
	erase();
#endif
}

void ascii_io::reset() {
#ifdef _WIN32
	print("\x1b[1;1H");
#elif __linux__
	erase();
#endif
}

std::string ascii_io::getline() {
#ifdef _WIN32
	std::string input = "";
	std::getline(std::cin, input);
#elif __linux__
	echo();
	char raw_input[160];
	std::string input;
	getnstr(raw_input, 160);
	input = raw_input;
	noecho();
#endif
	return input;
}

void ascii_io::get_terminal_size(int &x, int &y)
{
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO size_info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &size_info);
	x = size_info.dwSize.X;
	y = size_info.dwSize.Y;
#elif __linux__
	getmaxyx(stdscr, x, y);
#endif
}

void ascii_io::hide_curser()
{
	print("\x1b[?25l");
}