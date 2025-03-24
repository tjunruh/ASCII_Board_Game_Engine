#include "../ascii_engine_dll_files/pch.h"
#include "ascii_io.h"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#include "../../external_libraries/json.hpp"
#include <tchar.h>
#include "../file_manager/file_manager.h"
#elif __linux__
#include <ncurses.h>
#include <memory>
#include <chrono>
#include <thread>
#include "format_tools.h"
#endif

int console_zoom_amount = 0;

#ifdef _WIN32
const std::string console_settings_path = "\\AppData\\Local\\Packages\\Microsoft.WindowsTerminal_8wekyb3d8bbwe\\LocalState\\";
const std::string console_settings_file = "settings.json";
const int default_font_size = 12;
const int font_size_increment = 2;

std::string convert_LPTSTR_to_string(LPTSTR lptstr)
{
#ifdef UNICODE
	int size = WideCharToMultiByte(CP_UTF8, 0, lptstr, -1, nullptr, 0, nullptr, nullptr);
	if (size == 0)
	{
		return "";
	}
	std::string result(size, 0);
	WideCharToMultiByte(CP_UTF8, 0, lptstr, -1, &result[0], size, nullptr, nullptr);
	result.pop_back();
	return result;
#else
	return std::string(lptstr);
#endif
}
#elif __linux__
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

int ascii_io::zoom_in(unsigned int amount)
{
	int status = 0;
#ifdef _WIN32
	LPTSTR raw_home_directory;
	const unsigned int buffer_size = 4096;

	raw_home_directory = (LPTSTR)malloc(buffer_size * sizeof(TCHAR));
	if (NULL == raw_home_directory)
	{
		status = 1;
		return status;
	}

	DWORD return_value = GetEnvironmentVariable(TEXT("userprofile"), raw_home_directory, buffer_size);
	if (return_value == buffer_size || return_value == 0)
	{
		status = 1;
		return status;
	}
	std::string home_directory = convert_LPTSTR_to_string(raw_home_directory);
	std::string content = "";
	status = file_manager::read_file(home_directory + console_settings_path + console_settings_file, content);
	if (status == 0)
	{
		nlohmann::json console_settings = nlohmann::json::parse(content, nullptr, false);
		if (console_settings.contains("profiles") && console_settings["profiles"].contains("defaults"))
		{
			if (console_settings["profiles"]["defaults"].contains("fontSize") && console_settings["profiles"]["defaults"]["fontSize"].is_number())
			{
				int font_size = console_settings["profiles"]["defaults"]["fontSize"].template get<int>();
				for (unsigned int i = 0; i < amount; i++)
				{
					font_size = font_size + font_size_increment;
					console_zoom_amount = console_zoom_amount + 1;
				}
				console_settings["profiles"]["defaults"]["fontSize"] = font_size;
			}
			else
			{
				int font_size = default_font_size;
				for (unsigned int i = 0; i < amount; i++)
				{
					font_size = font_size + font_size_increment;
					console_zoom_amount = console_zoom_amount + 1;
				}
				console_settings["profiles"]["defaults"]["fontSize"] = font_size;
			}
			status = file_manager::write_file(home_directory + console_settings_path + console_settings_file, console_settings.dump(3));
		}
		else
		{
			status = 1;
		}
	}
#elif __linux__
	status = system("which xdotool > /dev/null");
	if (status == 0)
	{
		for (unsigned int i = 0; i < amount; i++)
		{
			status = system("xdotool key Ctrl+plus");
			console_zoom_amount = console_zoom_amount + 1;
		}
	}
#endif
	return status;
}

int ascii_io::zoom_out(unsigned int amount)
{
	int status = 0;
#ifdef _WIN32
	LPTSTR raw_home_directory;
	const unsigned int buffer_size = 4096;

	raw_home_directory = (LPTSTR)malloc(buffer_size * sizeof(TCHAR));
	if (NULL == raw_home_directory)
	{
		status = 1;
		return status;
	}

	DWORD return_value = GetEnvironmentVariable(TEXT("userprofile"), raw_home_directory, buffer_size);
	if (return_value == buffer_size || return_value == 0)
	{
		status = 1;
		return status;
	}
	std::string home_directory = convert_LPTSTR_to_string(raw_home_directory);
	std::string content = "";
	status = file_manager::read_file(home_directory + console_settings_path + console_settings_file, content);
	if (status == 0)
	{
		nlohmann::json console_settings = nlohmann::json::parse(content, nullptr, false);
		if (console_settings.contains("profiles") && console_settings["profiles"].contains("defaults"))
		{
			if (console_settings["profiles"]["defaults"].contains("fontSize") && console_settings["profiles"]["defaults"]["fontSize"].is_number())
			{
				int font_size = console_settings["profiles"]["defaults"]["fontSize"].template get<int>();
				for (unsigned int i = 0; i < amount; i++)
				{
					if ((font_size - font_size_increment) > 0)
					{
						font_size = font_size - font_size_increment;
						console_zoom_amount = console_zoom_amount - 1;
					}
					else
					{
						break;
					}
				}
				console_settings["profiles"]["defaults"]["fontSize"] = font_size;
			}
			else
			{
				int font_size = default_font_size;
				for (unsigned int i = 0; i < amount; i++)
				{
					if ((font_size - font_size_increment) > 0)
					{
						font_size = font_size - font_size_increment;
						console_zoom_amount = console_zoom_amount - 1;
					}
					else
					{
						break;
					}
				}
				console_settings["profiles"]["defaults"]["fontSize"] = font_size;
			}
			status = file_manager::write_file(home_directory + console_settings_path + console_settings_file, console_settings.dump(3));
		}
		else
		{
			status = 1;
		}
	}
#elif __linux__
	status = system("which xdotool > /dev/null");
	if (status == 0)
	{
		for (unsigned int i = 0; i < amount; i++)
		{
			status = system("xdotool key Ctrl+minus");
			console_zoom_amount = console_zoom_amount - 1;
		}
	}
#endif
	return status;
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
#ifdef __linux__
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
#endif
	}
#ifdef _WIN32
	fit_console_buffer_to_screen();
#elif __linux__
	ncurses_init();
#endif
}

void ascii_io::ascii_engine_end()
{
#ifdef _WIN32
	if (console_zoom_amount != 0)
	{
		LPTSTR raw_home_directory;
		const unsigned int buffer_size = 4096;

		raw_home_directory = (LPTSTR)malloc(buffer_size * sizeof(TCHAR));
		if (NULL == raw_home_directory)
		{
			return;
		}

		DWORD return_value = GetEnvironmentVariable(TEXT("userprofile"), raw_home_directory, buffer_size);
		if (return_value == buffer_size || return_value == 0)
		{
			return;
		}
		std::string home_directory = convert_LPTSTR_to_string(raw_home_directory);
		std::string content = "";
		int status = file_manager::read_file(home_directory + console_settings_path + console_settings_file, content);
		if (status == 0)
		{
			nlohmann::json console_settings = nlohmann::json::parse(content, nullptr, false);
			if (console_settings.contains("profiles") && console_settings["profiles"].contains("defaults") && console_settings["profiles"]["defaults"].contains("fontSize"))
			{
				console_settings["profiles"]["defaults"].erase("fontSize");
				status = file_manager::write_file(home_directory + console_settings_path + console_settings_file, console_settings.dump(3));
			}
		}
	}
#elif __linux__
	if (console_zoom_amount > 0)
	{
		zoom_out(console_zoom_amount);
	}
	else if(console_zoom_amount < 0)
	{
		zoom_in(console_zoom_amount * -1);
	}
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
