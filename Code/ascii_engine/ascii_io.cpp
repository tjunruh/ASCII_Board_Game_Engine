#include "../ascii_engine_dll_files/pch.h"
#include "ascii_io.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#include "../../external_libraries/json.hpp"
#include <tchar.h>
#include "../file_manager/file_manager.h"
#include <unordered_map>
#elif __linux__
#include <ncurses.h>
#include <memory>
#include "format_tools.h"
#include <termios.h>
#include <sys/ioctl.h>
#endif

int console_zoom_amount = 0;
bool left_mouse_held_down = false;
bool right_mouse_held_down = false;

#ifdef _WIN32
bool shift_held_down = false;
const std::string console_settings_path = "\\AppData\\Local\\Packages\\Microsoft.WindowsTerminal_8wekyb3d8bbwe\\LocalState\\";
const std::string console_settings_file = "settings.json";
const int default_font_size = 12;
bool keep_cursor_shown = false;
DWORD original_console_mode;

const std::unordered_map<int, const int> key_mapping =
{
	{8, ascii_io::backspace},
	{13, ascii_io::enter},
	{27, ascii_io::ESC},
	{32, ascii_io::space},
	{33, ascii_io::page_up},
	{34, ascii_io::page_down},
	{35, ascii_io::end},
	{36, ascii_io::home},
	{37, ascii_io::left},
	{38, ascii_io::up},
	{39, ascii_io::right},
	{40, ascii_io::down},
	{45, ascii_io::insert},
	{46, ascii_io::DEL},
	{48, ascii_io::zero},
	{49, ascii_io::one},
	{50, ascii_io::two},
	{51, ascii_io::three},
	{52, ascii_io::four},
	{53, ascii_io::five},
	{54, ascii_io::six},
	{55, ascii_io::seven},
	{56, ascii_io::eight},
	{57, ascii_io::nine},
	{65, ascii_io::a},
	{66, ascii_io::b},
	{67, ascii_io::c},
	{68, ascii_io::d},
	{69, ascii_io::e},
	{70, ascii_io::f},
	{71, ascii_io::g},
	{72, ascii_io::h},
	{73, ascii_io::i},
	{74, ascii_io::j},
	{75, ascii_io::k},
	{76, ascii_io::l},
	{77, ascii_io::m},
	{78, ascii_io::n},
	{79, ascii_io::o},
	{80, ascii_io::p},
	{81, ascii_io::q},
	{82, ascii_io::r},
	{83, ascii_io::s},
	{84, ascii_io::t},
	{85, ascii_io::u},
	{86, ascii_io::v},
	{87, ascii_io::w},
	{88, ascii_io::x},
	{89, ascii_io::y},
	{90, ascii_io::z},
	{186, ascii_io::semi_colon},
	{187, ascii_io::equal},
	{188, ascii_io::comma},
	{189, ascii_io::minus},
	{190, ascii_io::period},
	{191, ascii_io::forward_slash},
	{192, ascii_io::back_quote},
	{219, ascii_io::begin_bracket},
	{221, ascii_io::end_bracket},
	{220, ascii_io::pipe},
	{222, ascii_io::single_quotation}
};

const std::unordered_map<int, const int> key_mapping_with_shift =
{
	{8, ascii_io::backspace},
	{13, ascii_io::enter },
	{27, ascii_io::ESC},
	{32, ascii_io::space},
	{33, ascii_io::page_up},
	{34, ascii_io::page_down},
	{35, ascii_io::end},
	{36, ascii_io::home},
	{37, ascii_io::left},
	{38, ascii_io::up},
	{39, ascii_io::right},
	{40, ascii_io::down},
	{45, ascii_io::insert},
	{46, ascii_io::DEL},
	{48, ascii_io::end_parentheses},
	{49, ascii_io::exclamation},
	{50, ascii_io::at_sign},
	{51, ascii_io::pound},
	{52, ascii_io::dollar},
	{53, ascii_io::percent},
	{54, ascii_io::caret},
	{55, ascii_io::ampersand},
	{56, ascii_io::asterisk},
	{57, ascii_io::begin_parentheses},
	{65, ascii_io::A},
	{66, ascii_io::B},
	{67, ascii_io::C},
	{68, ascii_io::D},
	{69, ascii_io::E},
	{70, ascii_io::F},
	{71, ascii_io::G},
	{72, ascii_io::H},
	{73, ascii_io::I},
	{74, ascii_io::J},
	{75, ascii_io::K},
	{76, ascii_io::L},
	{77, ascii_io::M},
	{78, ascii_io::N},
	{79, ascii_io::O},
	{80, ascii_io::P},
	{81, ascii_io::Q},
	{82, ascii_io::R},
	{83, ascii_io::S},
	{84, ascii_io::T},
	{85, ascii_io::U},
	{86, ascii_io::V},
	{87, ascii_io::W},
	{88, ascii_io::X},
	{89, ascii_io::Y},
	{90, ascii_io::Z},
	{186, ascii_io::colon},
	{187, ascii_io::plus},
	{188, ascii_io::less_than},
	{189, ascii_io::underscore},
	{190, ascii_io::greater_than},
	{191, ascii_io::question},
	{192, ascii_io::tilde},
	{219, ascii_io::begin_curly_bracket},
	{221, ascii_io::end_curly_bracket},
	{220, ascii_io::backslash},
	{222, ascii_io::double_quotation}
};

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
	addstr(output.c_str());
	refresh();
#endif
}

int ascii_io::getchar()
{
	int input = undefined;
#ifdef _WIN32
	INPUT_RECORD input_record;
	DWORD unused_number_of_events_read;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(handle, ENABLE_MOUSE_INPUT);
	if (keep_cursor_shown)
	{
		keep_cursor_shown = false;
	}
	else
	{
		hide_cursor();
	}

	do
	{
		ReadConsoleInput(handle, &input_record, 1, &unused_number_of_events_read);
		if (input_record.EventType == KEY_EVENT)
		{
			if (((KEY_EVENT_RECORD&)input_record.Event).bKeyDown)
			{
				if (input_record.Event.KeyEvent.wVirtualKeyCode == 16)
				{
					shift_held_down = true;
				}
				else
				{
					input = input_record.Event.KeyEvent.wVirtualKeyCode;
					if (shift_held_down)
					{
						auto map = key_mapping_with_shift.find(input);
						if (map == key_mapping_with_shift.end())
						{
							input = undefined;
						}
						else
						{
							input = map->second;
						}
					}
					else
					{
						auto map = key_mapping.find(input);
						if (map == key_mapping.end())
						{
							input = undefined;
						}
						else
						{
							input = map->second;
						}
					}
				}
			}
			else if (input_record.Event.KeyEvent.wVirtualKeyCode == 16)
			{
				shift_held_down = false;
			}
		}
		else if (input_record.EventType == MOUSE_EVENT)
		{
			if (input_record.Event.MouseEvent.dwEventFlags == MOUSE_WHEELED)
			{
				short scrollDelta = HIWORD(input_record.Event.MouseEvent.dwButtonState);
				if (scrollDelta > 0) {
					input = scroll_up;
				}
				else if (scrollDelta < 0) {
					input = scroll_down;
				}
				else
				{
					input = undefined;
				}
			}
			else if (input_record.Event.MouseEvent.dwEventFlags == 0)
			{
				if (!left_mouse_held_down && input_record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					input = mouse_left_pressed;
					left_mouse_held_down = true;
				}
				else if (left_mouse_held_down && input_record.Event.MouseEvent.dwButtonState == 0)
				{
					input = mouse_left_released;
					left_mouse_held_down = false;
				}
				else if (!right_mouse_held_down && input_record.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
				{
					input = mouse_right_pressed;
					right_mouse_held_down = true;
				}
				else if (right_mouse_held_down && input_record.Event.MouseEvent.dwButtonState == 0)
				{
					input = mouse_right_released;
					right_mouse_held_down = false;
				}
				else if (input_record.Event.MouseEvent.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED)
				{
					input = mouse_middle;
				}
				else
				{
					input = undefined;
				}
			}
			else if (left_mouse_held_down)
			{
				input = mouse_moved;
			}
			else
			{
				input = undefined;
			}
		}
	} while (input == undefined);
#elif __linux__
	do
	{
		input = getch();

		if (input == KEY_MOUSE)
		{
			MEVENT event;
			if (getmouse(&event) == OK)
			{
				if (event.bstate & BUTTON1_PRESSED)
				{
					input = mouse_left_pressed;
					left_mouse_held_down = true;
				}
				else if (event.bstate & BUTTON1_RELEASED)
				{
					input = mouse_left_released;
					left_mouse_held_down = false;
				}
				else if (event.bstate & BUTTON2_CLICKED)
				{
					input = mouse_middle;
				}
				else if (event.bstate & BUTTON3_PRESSED)
				{
					input = mouse_right_pressed;
				}
				else if (event.bstate & BUTTON3_RELEASED)
				{
					input = mouse_right_released;
				}
				else if (event.bstate & BUTTON4_PRESSED)
				{
					input = scroll_up;
				}
				else if (event.bstate & BUTTON5_PRESSED)
				{
					input = scroll_down;
				}
				else if (left_mouse_held_down && (event.bstate & REPORT_MOUSE_POSITION))
				{
					input = mouse_moved;
				}
				else
				{
					input = undefined;
				}
			}
		}
	} while (input == undefined);
#endif

	return input;
}

int ascii_io::getchar(int& mouse_x_position, int& mouse_y_position)
{
	int input = undefined;
#ifdef _WIN32
	INPUT_RECORD input_record;
	DWORD unused_number_of_events_read;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(handle, ENABLE_MOUSE_INPUT);
	if (keep_cursor_shown)
	{
		keep_cursor_shown = false;
	}
	else
	{
		hide_cursor();
	}

	do
	{
		ReadConsoleInput(handle, &input_record, 1, &unused_number_of_events_read);
		if (input_record.EventType == KEY_EVENT)
		{
			if (((KEY_EVENT_RECORD&)input_record.Event).bKeyDown)
			{
				if (input_record.Event.KeyEvent.wVirtualKeyCode == 16)
				{
					shift_held_down = true;
				}
				else
				{
					input = input_record.Event.KeyEvent.wVirtualKeyCode;
					if (shift_held_down)
					{
						auto map = key_mapping_with_shift.find(input);
						if (map == key_mapping_with_shift.end())
						{
							input = undefined;
						}
						else
						{
							input = map->second;
						}
					}
					else
					{
						auto map = key_mapping.find(input);
						if (map == key_mapping.end())
						{
							input = undefined;
						}
						else
						{
							input = map->second;
						}
					}
				}
			}
			else if (input_record.Event.KeyEvent.wVirtualKeyCode == 16)
			{
				shift_held_down = false;
			}
		}
		else if (input_record.EventType == MOUSE_EVENT)
		{
			if (input_record.Event.MouseEvent.dwEventFlags == MOUSE_WHEELED)
			{
				short scrollDelta = HIWORD(input_record.Event.MouseEvent.dwButtonState);
				if (scrollDelta > 0) {
					input = scroll_up;
				}
				else if (scrollDelta < 0) {
					input = scroll_down;
				}
				else
				{
					input = undefined;
				}
			}
			else if (input_record.Event.MouseEvent.dwEventFlags == 0)
			{
				if (!left_mouse_held_down && input_record.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
				{
					input = mouse_left_pressed;
					left_mouse_held_down = true;
				}
				else if (left_mouse_held_down && input_record.Event.MouseEvent.dwButtonState == 0)
				{
					input = mouse_left_released;
					left_mouse_held_down = false;
				}
				else if (!right_mouse_held_down && input_record.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
				{
					input = mouse_right_pressed;
					right_mouse_held_down = true;
				}
				else if (right_mouse_held_down && input_record.Event.MouseEvent.dwButtonState == 0)
				{
					input = mouse_right_released;
					right_mouse_held_down = false;
				}
				else if (input_record.Event.MouseEvent.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED)
				{
					input = mouse_middle;
				}
				else
				{
					input = undefined;
				}
			}
			else if (left_mouse_held_down)
			{
				input = mouse_moved;
			}
			else
			{
				input = undefined;
			}

			mouse_x_position = input_record.Event.MouseEvent.dwMousePosition.X;
			mouse_y_position = input_record.Event.MouseEvent.dwMousePosition.Y;
		}
	} while (input == undefined);
#elif __linux__
	do
	{
		input = getch();

		if (input == KEY_MOUSE)
		{
			MEVENT event;
			if (getmouse(&event) == OK)
			{
				if (event.bstate & BUTTON1_PRESSED)
				{
					input = mouse_left_pressed;
					left_mouse_held_down = true;
				}
				else if (event.bstate & BUTTON1_RELEASED)
				{
					input = mouse_left_released;
					left_mouse_held_down = false;
				}
				else if (event.bstate & BUTTON2_CLICKED)
				{
					input = mouse_middle;
				}
				else if (event.bstate & BUTTON3_PRESSED)
				{
					input = mouse_right_pressed;
				}
				else if (event.bstate & BUTTON3_RELEASED)
				{
					input = mouse_right_released;
				}
				else if (event.bstate & BUTTON4_PRESSED)
				{
					input = scroll_up;
				}
				else if (event.bstate & BUTTON5_PRESSED)
				{
					input = scroll_down;
				}
				else if (left_mouse_held_down && (event.bstate & REPORT_MOUSE_POSITION))
				{
					input = mouse_moved;
				}
				else
				{
					input = undefined;
				}

				mouse_x_position = event.x;
				mouse_y_position = event.y;
			}
		}
	} while (input == undefined);
#endif

	return input;
}

int ascii_io::wait_for_keystroke(std::vector<int> keystroke_options)
{
	int input = ascii_io::undefined;
	do
	{
		input = getchar();
	} while (std::count(keystroke_options.begin(), keystroke_options.end(), input) == 0);

	return input;
}

int ascii_io::wait_for_keystroke(std::vector<int> keystroke_options, int& mouse_x_position, int& mouse_y_position)
{
	int input = ascii_io::undefined;
	do
	{
		input = getchar(mouse_x_position, mouse_y_position);
	} while(std::count(keystroke_options.begin(), keystroke_options.end(), input) == 0);

	return input;
}

void ascii_io::clear() {
#ifdef _WIN32
	system("cls");
#elif __linux__
	erase();
#endif
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

	if ( y < 0 )
	{
		y = 0;
	}

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

	if ( y >= max_y )
	{
		y = max_y - 1;
	}

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

	if ( x >= max_x )
	{
		x = max_x - 1;
	}

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

	if ( x < 0 )
	{
		x = 0;
	}

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
	move(y, x);
	refresh();
#endif
}

int ascii_io::zoom_in(unsigned int amount, unsigned int wait_milliseconds)
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
		free(raw_home_directory);
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
					font_size = font_size + 1;
					console_zoom_amount = console_zoom_amount + 1;
				}
				console_settings["profiles"]["defaults"]["fontSize"] = font_size;
			}
			else
			{
				int font_size = default_font_size;
				for (unsigned int i = 0; i < amount; i++)
				{
					font_size = font_size + 1;
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
	free(raw_home_directory);
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
	std::this_thread::sleep_for(std::chrono::milliseconds(wait_milliseconds));
#ifdef __linux__
	winsize ws;
	ioctl(0, TIOCGWINSZ, &ws);
	resizeterm(ws.ws_row, ws.ws_col);
#endif
	return status;
}

int ascii_io::zoom_out(unsigned int amount, unsigned int wait_milliseconds)
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
		free(raw_home_directory);
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
					if ((font_size - 1) >= 0)
					{
						font_size = font_size - 1;
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
					if ((font_size - 1) > 0)
					{
						font_size = font_size - 1;
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
	free(raw_home_directory);
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
	std::this_thread::sleep_for(std::chrono::milliseconds(wait_milliseconds));
#ifdef __linux__
	winsize ws;
	ioctl(0, TIOCGWINSZ, &ws);
	resizeterm(ws.ws_row, ws.ws_col);
#endif
	return status;
}

int ascii_io::zoom_to_level(int level, unsigned int wait_milliseconds)
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
		free(raw_home_directory);
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
			int font_size = default_font_size + level * 1;
			if (font_size < 0)
			{
				font_size = 0;
			}

			console_settings["profiles"]["defaults"]["fontSize"] = font_size;
			console_zoom_amount = level;
			status = file_manager::write_file(home_directory + console_settings_path + console_settings_file, console_settings.dump(3));
		}
		else
		{
			status = 1;
		}
	}
	free(raw_home_directory);
#elif __linux__

	if (level > console_zoom_amount)
	{
		status = zoom_in(level - console_zoom_amount);
	}
	else if (level < console_zoom_amount)
	{
		status = zoom_out(console_zoom_amount - level);
	}
#endif
	std::this_thread::sleep_for(std::chrono::milliseconds(wait_milliseconds));
#ifdef __linux__
	winsize ws;
	ioctl(0, TIOCGWINSZ, &ws);
	resizeterm(ws.ws_row, ws.ws_col);
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

bool ascii_io::is_dragging()
{
	return left_mouse_held_down;
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
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &original_console_mode);
	fit_console_buffer_to_screen();
	DWORD mode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT;
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hInput, mode);
#elif __linux__
	ncurses_init();
#endif
	hide_cursor();
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
			free(raw_home_directory);
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
		free(raw_home_directory);
	}

	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(hInput, original_console_mode);
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
	show_cursor();
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

void ascii_io::keep_cursor_shown_in_getchar()
{
	keep_cursor_shown = true;
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
	keypad(stdscr, TRUE);
	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
	mouseinterval(0);
	printf("\033[?1003h\n");
}

void ascii_io::colors_init()
{
	start_color();
	initialize_colors();
}

void ascii_io::ncurses_end()
{
	printf("\033[?1003l\n");
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

void ascii_io::guarantee_clear_on_next_display()
{
	clearok(stdscr, true);
}
#endif
