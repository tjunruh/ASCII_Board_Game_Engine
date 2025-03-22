#include "../ascii_engine_dll_files/pch.h"
#include "ascii_io.h"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#elif __linux__
#include <ncurses.h>
#include <memory>
#include <chrono>
#include <thread>
#include "format_tools.h"
#endif

#ifdef __linux__
std::string system_call_with_feedback(const char* command)
{
	char buffer[128];
	std::string result = "";
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
	if (pipe)
	{
		while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr)
		{
			result = result + buffer;
		}
	}
	return result;
}
#endif

int maximize_terminal()
{
	int status = 0;
#ifdef _WIN32
	ShowWindow(GetForegroundWindow(), SW_MAXIMIZE);
#elif __linux__
	status = system("which wmctrl > /dev/null");
	if (status == 0)
	{
		std::string window_id = system_call_with_feedback("xprop -root | awk \'/_NET_ACTIVE_WINDOW\\(WINDOW\\)/{print $NF}\'");
		if (window_id.length() > 0)
		{
			window_id.erase(window_id.length() - 1);
		}
		std::string maximize_command = "wmctrl -ir " + window_id + " -b add,maximized_vert,maximized_horz";
		status = system(maximize_command.c_str());
	}
	else
	{
		status = system("which xdotool > /dev/null");
		if (status == 0)
		{
			std::string window_id = system_call_with_feedback("xprop -root | awk \'/_NET_ACTIVE_WINDOW\\(WINDOW\\)/{print $NF}\'");
			if (window_id.length() > 0)
			{
				window_id.erase(window_id.length() -1);
			}
			std::string place_command = "xdotool windowmove " + window_id + " 0 0";
			std::string maximize_command = "xdotool windowsize " + window_id + " 100% 100%";
			status = system(place_command.c_str());
			status |= system(maximize_command.c_str());
		}
	}
#endif
	return status;
}

void ascii_io::print(const std::string& output) {
#ifdef _WIN32
	std::cout << output;
#elif __linux__
	printw(output.c_str());
	refresh();
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
		nodelay(stdscr, true);
		int secondary_input = 0;
		while (true)
		{
			secondary_input = getch();
			if (secondary_input == ERR)
			{
				break;
			}
			input = input + secondary_input;
		}
		nodelay(stdscr, false);
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
	y = y - 1;
	x = x - 1;
#endif
}

void ascii_io::get_cursor_position(int& x, int& y)
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

void ascii_io::hide_cursor()
{
#ifdef _WIN32
	print("\x1b[?25l");
#elif __linux__
   curs_set(0);
#endif
}

void ascii_io::show_cursor()
{
#ifdef _WIN32
	print("\x1b[?25h");
#elif __linux__
   curs_set(1);
#endif
}

void ascii_io::move_cursor_up(unsigned int amount)
{
#ifdef _WIN32
	print("\x1b[" + std::to_string(amount) + "A");
#elif __linux__
   int x = 0, y = 0;
   get_cursor_position(x, y);
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

void ascii_io::move_cursor_down(unsigned int amount)
{
#ifdef _WIN32
	print("\x1b[" + std::to_string(amount) + "B");
#elif __linux__
   int max_x = 0, max_y = 0;
   get_terminal_size(max_x, max_y);

   int x = 0, y = 0;
   get_cursor_position(x, y);

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

void ascii_io::move_cursor_right(unsigned int amount)
{
#ifdef _WIN32
	print("\x1b[" + std::to_string(amount) + "C");
#elif __linux__
   int max_x = 0, max_y = 0;
   get_terminal_size(max_x, max_y);

   int x = 0, y = 0;
   get_cursor_position(x, y);
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

void ascii_io::move_cursor_left(unsigned int amount)
{
#ifdef _WIN32
	print("\x1b[" + std::to_string(amount) + "D");
#elif __linux__
   int x = 0, y = 0;
   get_cursor_position(x, y);
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

void ascii_io::move_cursor_to_position(unsigned int x, unsigned int y)
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

void ascii_io::set_color(int foreground, int background, bool bold)
{
#ifdef _WIN32
	if (bold)
	{
		print("\x1b[1m");
	}
	else
	{
		print("\x1b[22m");
	}
	print("\x1b[" + std::to_string(foreground) + "m");
	print("\x1b[" + std::to_string(background + 10) + "m");
#elif __linux__
	if (bold)
	{
		attron(A_BOLD);
	}
	else
	{
		attroff(A_BOLD);
	}
	attron(COLOR_PAIR(get_color_id(foreground, background)));
#endif
}

std::string ascii_io::get_key_name(int key)
{
	std::string name = "";
	for (unsigned int i = 0; i < key_string_map.size(); i++)
	{
		if (key == key_string_map[i].key)
		{
			name = key_string_map[i].name;
		}
	}
	return name;
}

void ascii_io::ascii_engine_init(bool maximize)
{
	if (maximize)
	{
		maximize_terminal();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
#ifdef _WIN32
	fit_console_buffer_to_screen();
#elif __linux__
	ncurses_init();
#endif
}

void ascii_io::ascii_engine_end()
{
#ifdef __linux__
	ncurses_end();
#endif
}

#ifdef _WIN32
void ascii_io::enable_dec()
{
	print("\x1b(0");
}

void ascii_io::disable_dec()
{
	print("\x1b(B");
}

void ascii_io::fit_console_buffer_to_screen()
{
	bool success = false;
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
	buffer_info.dwSize.Y = 1;
	do
	{
		success = SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), buffer_info.dwSize);
		buffer_info.dwSize.Y++;
	} while (!success);
}
#endif

#ifdef __linux__
void ascii_io::ncurses_init()
{
   initscr();
   raw();
   noecho();
   cbreak();
   colors_init();
}

void ascii_io::colors_init()
{
	start_color();
	initialize_colors();
}

void ascii_io::ncurses_end()
{
   endwin();
}

int ascii_io::get_color_id(int foreground, int background)
{
	int most_significant_bit = 1 << 7;
	int background_bits = (7 & background) << 4;
	int foreground_bits = 7 & foreground;

	return (most_significant_bit | background_bits | foreground_bits);
}

void ascii_io::initialize_colors()
{
	int color_id = 0;

	for (unsigned int background = 0; background < format_tools::colors.size(); background++) 
	{
		for (unsigned int foreground = 0; foreground < format_tools::colors.size(); foreground++) 
		{
			color_id = get_color_id((int)format_tools::colors[foreground], (int)format_tools::colors[background]);
			init_pair(color_id, (int)format_tools::colors[foreground], (int)format_tools::colors[background]);
		}
	}
}
#endif
