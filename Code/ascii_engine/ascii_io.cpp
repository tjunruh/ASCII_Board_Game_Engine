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
	getmaxyx(stdscr, y, x);
#endif
}

void ascii_io::get_curser_position(int& x, int& y)
{
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO position_info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &position_info);
	x = position_info.dwCursorPosition.X;
	y = position_info.dwCursorPosition.Y;
#elif __linux__
   getyx(stdscr, y, x);
#endif
}

void ascii_io::hide_curser()
{
#ifdef _WIN32
	print("\x1b[?25l");
#elif __linux__
   curs_set(0);
#endif
}

void ascii_io::show_curser()
{
#ifdef _WIN32
	print("\x1b[?25h");
#elif __linux__
   curs_set(1);
#endif
}

void ascii_io::move_curser_up(unsigned int amount)
{
#ifdef _WIN32
	print("\x1b[" + std::to_string(amount) + "A");
#elif __linux__
   int x = 0, y = 0;
   get_curser_position(x, y);
   y -= amount;

   // Basic bound snapping. move() will return error if outside range
   // NOTE: There is not need to check the upper bound since we are
   //    only decreasing the value
   if ( y < 0 )
   {
      y = 0;
   }

   // NOTE: move does not update the cursor until refresh() is called
   move(y, x);
   refresh();
#endif
}

void ascii_io::move_curser_down(unsigned int amount)
{
#ifdef _WIN32
	print("\x1b[" + std::to_string(amount) + "B");
#elif __linux__
   int max_x = 0, max_y = 0;
   get_terminal_size(max_x, max_y);

   int x = 0, y = 0;
   get_curser_position(x, y);

   y += amount;

  // Basic bound snapping. move() will return error if outside range
  // NOTE: There is not need to check the lower bound since we are
  //    only increasing
  if ( y >= max_y )
   {
      y = max_y - 1;
   }

   // NOTE: move does not update the cursor until refresh() is called
   move(y, x);
   refresh();
#endif
}

void ascii_io::move_curser_right(unsigned int amount)
{
#ifdef _WIN32
	print("\x1b[" + std::to_string(amount) + "C");
#elif __linux__
   int max_x = 0, max_y = 0;
   get_terminal_size(max_x, max_y);

   int x = 0, y = 0;
   get_curser_position(x, y);
   x += amount;

   // Basic bound snapping. move() will return error if outside range
   // NOTE: There is not need to check the lower bound since we are
   //    only increasing
   if ( x >= max_x )
   {
      x = max_x - 1;
   }

   // NOTE: move does not update the cursor until refresh() is called
   move(y, x);
   refresh();
#endif
}

void ascii_io::move_curser_left(unsigned int amount)
{
#ifdef _WIN32
	print("\x1b[" + std::to_string(amount) + "D");
#elif __linux__
   int x = 0, y = 0;
   get_curser_position(x, y);
   x -= amount;

   // Basic bound snapping. move() will return error if outside range
   // NOTE: There is not need to check the upper bound since we are
   //    only decreasing the value
   if ( x < 0 )
   {
      x = 0;
   }

   // NOTE: move does not update the cursor until refresh() is called
   move(y, x);
   refresh();
#endif
}

void ascii_io::move_curser_to_position(unsigned int x, unsigned int y)
{
#ifdef _WIN32
	x = x + 1;
	y = y + 1;
	print("\x1b[" + std::to_string(y) + ";" + std::to_string(x) + "H");
#elif __linux__
   // NOTE: move does not update the cursor until refresh() is called
   move(y, x);
   refresh();
#endif
}

#ifdef __linux__
void ascii_io::ncurses_init()
{
   initscr();
   raw();
   noecho();
   cbreak();
}

void ascii_io::ncurses_end()
{
   endwin();
}
#endif
