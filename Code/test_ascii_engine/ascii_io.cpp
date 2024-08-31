#include "pch.h"
#ifdef __linux__
#include <gtest/gtest.h>
#endif

#include <iostream>

#ifdef _WIN32
#include "../ascii_engine/ascii_io.h"
#elif __linux__
#include "ascii_engine/ascii_io.h"
#endif

TEST(ascii_io, set_cursor)
{
   int x = 5, y = 10;
#ifdef __linux__
   ascii_io::ncurses_init();
#endif

   ascii_io::move_curser_to_position(x, y);
  
   int getx = 0, gety = 0;
   ascii_io::get_curser_position(getx, gety);
#ifdef __linux
   ascii_io::ncurses_end();
#endif

   EXPECT_EQ(x, getx);
   EXPECT_EQ(y, gety);

}

TEST(ascii_io, move_cursor_down)
{
#ifdef __linux__
   ascii_io::ncurses_init();
#endif
   ascii_io::move_curser_to_position(1, 1);
   ascii_io::move_curser_down(1);

   int getx = 0, gety = 0;
   ascii_io::get_curser_position(getx, gety);
#ifdef __linux__
   ascii_io::ncurses_end();
#endif

   EXPECT_EQ(1, getx);
   EXPECT_EQ(2, gety);
   
}

TEST(ascii_io, move_cursor_up)
{
#ifdef __linux__
   ascii_io::ncurses_init();
#endif
   ascii_io::move_curser_to_position(1, 1);
   ascii_io::move_curser_up(1);

   int getx = 0, gety = 0;
   ascii_io::get_curser_position(getx, gety);
#ifdef __linux__
   ascii_io::ncurses_end();
#endif

   EXPECT_EQ(1, getx);
   EXPECT_EQ(0, gety);
}

TEST(ascii_io, move_cursor_left)
{
#ifdef __linux__
   ascii_io::ncurses_init();
#endif
   ascii_io::move_curser_to_position(1, 1);
   ascii_io::move_curser_left(1);

   int getx = 0, gety = 0;
   ascii_io::get_curser_position(getx, gety);
#ifdef __linux__
   ascii_io::ncurses_end();
#endif
   
   EXPECT_EQ(0, getx); 
   EXPECT_EQ(1, gety);
}

TEST(ascii_io, move_cursor_right)
{
#ifdef __linux__
   ascii_io::ncurses_init();
#endif
   ascii_io::move_curser_to_position(1, 1);
   ascii_io::move_curser_right(1);

   int getx = 0, gety = 0;
   ascii_io::get_curser_position(getx, gety);
#ifdef __linux__
   ascii_io::ncurses_end();
#endif

   EXPECT_EQ(2, getx);
   EXPECT_EQ(1, gety);
}

TEST(ascii_io, terminal_size_nonzero)
{
#ifdef __linux__
   ascii_io::ncurses_init();
#endif

   int max_x = 0, max_y = 0;
   ascii_io::get_terminal_size(max_x, max_y);
#ifdef __linux__
   ascii_io::ncurses_end();
#endif

   EXPECT_NE(0, max_x);
   EXPECT_NE(0, max_y);
}
