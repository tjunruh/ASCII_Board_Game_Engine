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
	if (input == 224)
	{
		input = input + _getch();
	}
#elif __linux__
	input = getch();
	if (input == 27) 
	{
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
	move_curser_to_position(0, 0);
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

void ascii_io::get_curser_position(int& x, int& y)
{
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO position_info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &position_info);
	x = position_info.dwCursorPosition.X;
	y = position_info.dwCursorPosition.Y;
#endif
}

void ascii_io::hide_curser()
{
#ifdef _WIN32
	print("\x1b[?25l");
#endif
}

void ascii_io::show_curser()
{
#ifdef _WIN32
	print("\x1b[?25h");
#endif
}

void ascii_io::move_curser_up(unsigned int amount)
{
#ifdef _WIN32
	print("\x1b[" + std::to_string(amount) + "A");
#endif
}

void ascii_io::move_curser_down(unsigned int amount)
{
#ifdef _WIN32
	print("\x1b[" + std::to_string(amount) + "B");
#endif
}

void ascii_io::move_curser_right(unsigned int amount)
{
#ifdef _WIN32
	print("\x1b[" + std::to_string(amount) + "C");
#endif
}

void ascii_io::move_curser_left(unsigned int amount)
{
#ifdef _WIN32
	print("\x1b[" + std::to_string(amount) + "D");
#endif
}

void ascii_io::move_curser_to_position(unsigned int x, unsigned int y)
{
#ifdef _WIN32
	x = x + 1;
	y = y + 1;
	print("\x1b[" + std::to_string(y) + ";" + std::to_string(x) + "H");
#endif
}