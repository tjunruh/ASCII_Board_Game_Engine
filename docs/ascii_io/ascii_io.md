# ascii_io API

ascii_io includes functions providing the ability to perform input and output operations involving Windows and Linux consoles. Functions in the ascii_io namespace include:

```
void ascii_engine_init(bool maximize = false)
void ascii_engine_end()
void print(const std::string& output)
int getchar()
int wait_for_keystroke(std::vector<int> keystroke_options)
void clear()
void get_terminal_size(int& x, int& y)
void get_cursor_position(int& x, int& y)
void hide_cursor()
void show_cursor()
void move_cursor_up(unsigned int amount=1)
void move_cursor_down(unsigned int amount=1)
void move_cursor_right(unsigned int amount=1)
void move_cursor_left(unsigned int amount=1)
void move_cursor_to_position(unsigned int x, unsigned int y)
int zoom_in(unsigned int amount=1, unsigned int wait_milliseconds = 0)
int zoom_out(unsigned int amount=1, unsigned int wait_milliseconds = 0)
int zoom_to_level(int level, unsigned int wait_milliseconds = 0)
void set_color(int foreground, int background, bool bold = false)
std::string get_key_name(int key)
```

Linux specific functions:

```
void guarantee_clear_on_next_display()
```

---
## ascii_engine_init
**void ascii_engine_init(bool maximize = false)**
```
Description:
This function must be called at the beginning of the program to initialize ascii engine

Parameters:
bool maximize - maximizes the terminal to fill the whole screen (wmctrl (sudo apt install wmctrl) or xdotool (sudo apt install xdotool) must be installed for it to work on Linux systems)
```

---
## ascii_engine_end
**void ascii_engine_end()**
```
Description:
This function must be called at the end of the program to properly shutdown ascii engine
```

---
## print
**void print(const std::string& output)**
```
Description:
prints to the terminal at whatever position the cursor is at

Parameters:
const std::string& output - string to be printed
```

---
## getchar
**int getchar()**
```
Description:
blocks until user presses a key and returns the ascii value of the key pressed

return value:
int - ascii value of the key pressed
```

---
## wait_for_keystroke
**int wait_for_keystroke(std::vector<int> keystroke_options)**
```
Description:
blocks until user presses a key specified in keystroke_options

Parameters:
std::vector<int> keystroke_options - group of keystrokes that will break out of the block

Return value:
int - ascii value of the key that broke out of the block
```

---
## clear
**void clear()**
```
Description:
clears the console
```

---
## get_terminal_size
**void get_terminal_size(int& x, int& y)**
```
Description:
retrieves the terminal's height and width

Parameters:
int& x - value populated with the width of the terminal
int& y - value populated with the height of the terminal
```

---
## get_cursor_position
**void get_cursor_position(int& x, int& y)**
```
Description:
retrieves the cursor's x and y position

Parameters:
int& x - value populated with the x position of the cursor
int& y - value populated with the y position of the cursor
```

---
## hide_cursor
**void hide_cursor()**
```
Description:
hides the cursor from view on the terminal
```

---
## show_cursor
**void show_cursor()**
```
Description:
make the cursor visible on the terminal
```

---
## move_cursor_up
**void move_cursor_up(unsigned int amount=1)**
```
Description:
moves the cursor up by specified amount

Parameters:
unsigned int amount - number of positions the cursor should move up (defaults to one if no parameter included)
```

---
## move_cursor_down
**void move_cursor_down(unsigned int amount=1)**
```
Description:
moves the cursor down by specified amount

Parameters:
unsigned int amount - number of positions the cursor should move down (defaults to one if no parameter included)
```

---
## move_cursor_right
**void move_cursor_right(unsigned int amount=1)**
```
Description:
moves the cursor right by specified amount

Parameters:
unsigned int amount - number of positions the cursor should move right (defaults to one if no parameter included)
```

---
## move_cursor_left
**void move_cursor_left(unsigned int amount=1)**
```
Description:
moves the cursor left by specified amount

Parameters:
unsigned int amount - number of positions the cursor should move left (defaults to one if no parameter included)
```

---
## move_cursor_to_position
**void move_cursor_to_position(unsigned int x, unsigned int y)**
```
Description:
moves the cursor to specified position on the terminal

Parameters:
int x - x position where the cursor should be moved
int y - y position where the cursor should be moved
```

---
## zoom_in
**int zoom_in(unsigned int amount=1, unsigned int wait_milliseconds = 0)**
```
Description:
makes characters in the terminal larger (xdotool (sudo apt install xdotool) must be installed for it to work on Linux systems)

Parameters:
unsigned int amount - controls how much larger the characters will get
unsigned int wait_milliseconds - specifies amount of time in milliseconds to wait before moving on so as to allow the terminal some time to make the font size change

Return value:
int - 0 upon success and a different number upon failure
```

---
## zoom_out
**int zoom_out(unsigned int amount=1, unsigned int wait_milliseconds = 0)**
```
Description:
makes characters in the terminal smaller (xdotool (sudo apt install xdotool) must be installed for it to work on Linux systems)

Parameters:
unsigned int amount - controls how much smaller the characters will get
unsigned int wait_milliseconds - specifies amount of time in milliseconds to wait before moving on so as to allow the terminal some time to make the font size change

Return value:
int - 0 upon success and a different number upon failure
```

---
## zoom_to_level
**int zoom_to_level(int level, unsigned int wait_milliseconds = 0)**
```
Description:
zooms to desired level (0 is default, positive is zoomed in (larger characters), and negative is zoomed out (smaller characters))

Parameters:
int level - level to zoom to
unsigned int wait_milliseconds - specifies amount of time in milliseconds to wait before moving on so as to allow the terminal some time to make the font size change

Return value:
int - 0 upon success and a different number upon failure
```

---
## set_color
**void set_color(int foreground, int background, bool bold = false)**
```
Description:
sets the foreground and background of the terminal for any printing to the terminal that follows (setting bold to true will cause the foreground to become brighter)

Parameters:
int foreground - integer code defining the foreground color (format_tools has values containing the color codes i.e. format_tools::black)
int background - integer code defining the background color (format_tools has values containing the color codes i.e. format_tools::black)
bool bold - makes the foreground brighter when set to true
```

---
## get_key_name
**std::string get_key_name(int key)**
```
Description:
returns a string that is the name of the key represented by ascii code

Parameters:
int key - The ascii code of the key (it is best to use the ascii key codes defined in ascii_io)

Return value:
std::string - name of the ascii key
```

Linux specific functions:

---
## guarantee_clear_on_next_display
**void guarantee_clear_on_next_display()**
```
Description:
Use this function in cases (most likely where the terminal is zoomed out and a lot of text is being displayed) when a display call does not overwrite all of the previous frame
```

---
# Keyboard Codes
ascii_io contains constant values mapping keyboard buttons to corresponding ascii codes:

```
const int undefined = -1;
const int TAB = 9;
const int ESC = 27;
const int space = 32;
const int exclamation = 33;
const int double_quoatation = 34;
const int pound = 35;
const int dollar = 36;
const int percent = 37;
const int ampersand = 38;
const int single_quotation = 39;
const int begin_parentheses = 40;
const int end_parentheses = 41;
const int asterisk = 42;
const int plus = 43;
const int comma = 44;
const int minus = 45;
const int period = 46;
const int forward_slash = 47;
const int zero = 48;
const int one = 49;
const int two = 50;
const int three = 51;
const int four = 52;
const int five = 53;
const int six = 54;
const int seven = 55;
const int eight = 56;
const int nine = 57;
const int colon = 58;
const int semi_colon = 59;
const int less_than = 60;
const int equal = 61;
const int greater_than = 62;
const int question = 63;
const int at_sign = 64;
const int A = 65;
const int B = 66;
const int C = 67;
const int D = 68;
const int E = 69;
const int F = 70;
const int G = 71;
const int H = 72;
const int I = 73;
const int J = 74;
const int K = 75;
const int L = 76;
const int M = 77;
const int N = 78;
const int O = 79;
const int P = 80;
const int Q = 81;
const int R = 82;
const int S = 83;
const int T = 84;
const int U = 85;
const int V = 86;
const int W = 87;
const int X = 88;
const int Y = 89;
const int Z = 90;
const int begin_bracket = 91;
const int backslash = 92;
const int end_bracket = 93;
const int caret = 94;
const int underscore = 95;
const int back_quote = 96;
const int a = 97;
const int b = 98;
const int c = 99;
const int d = 100;
const int e = 101;
const int f = 102;
const int g = 103;
const int h = 104;
const int i = 105;
const int j = 106;
const int k = 107;
const int l = 108;
const int m = 109;
const int n = 110;
const int o = 111;
const int p = 112;
const int q = 113;
const int r = 114;
const int s = 115;
const int t = 116;
const int u = 117;
const int v = 118;
const int w = 119;
const int x = 120;
const int y = 121;
const int z = 122;
const int begin_curly_bracket = 123;
const int pipe = 124;
const int end_curly_bracket = 125;
const int tilde = 126;

Windows:
const int backspace = 8;
const int enter = 13;
const int right = 301;
const int left = 299;
const int up = 296;
const int down = 304;
const int DEL = 307;
const int insert = 306;
const int end = 303;
const int home = 295;
const int page_down = 305;
const int page_up = 297;

Linux:
const int backspace = 127;
const int enter = 10;
const int right = 185;
const int left = 186;
const int up = 183;
const int down = 184;
const int DEL = 295;
const int insert = 294;
const int end = 188;
const int home = 190;
const int page_down = 298;
const int page_up = 297;
```