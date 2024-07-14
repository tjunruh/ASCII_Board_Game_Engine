#include <gtest/gtest.h>

#include <iostream>

#include "ascii_engine/ascii_io.h"

TEST(ascii_io, set_cursor)
{
   int x = 5, y = 10;
   ascii_io::ncurses_init();

   ascii_io::move_curser_to_position(x, y);
  
   int getx = 0, gety = 0;
   ascii_io::get_curser_position(getx, gety);
   ascii_io::ncurses_end();

   EXPECT_EQ(x, getx);
   EXPECT_EQ(y, gety);

}

TEST(ascii_io, move_cursor_down)
{
   ascii_io::ncurses_init();
   ascii_io::move_curser_to_position(1, 1);
   ascii_io::move_curser_down(1);

   int getx = 0, gety = 0;
   ascii_io::get_curser_position(getx, gety);
   ascii_io::ncurses_end();

   EXPECT_EQ(1, getx);
   EXPECT_EQ(2, gety);
   
}

TEST(ascii_io, move_cursor_up)
{
   ascii_io::ncurses_init();
   ascii_io::move_curser_to_position(1, 1);
   ascii_io::move_curser_up(1);

   int getx = 0, gety = 0;
   ascii_io::get_curser_position(getx, gety);
   ascii_io::ncurses_end();

   EXPECT_EQ(1, getx);
   EXPECT_EQ(0, gety);
}

TEST(ascii_io, move_cursor_left)
{
   ascii_io::ncurses_init();
   ascii_io::move_curser_to_position(1, 1);
   ascii_io::move_curser_left(1);

   int getx = 0, gety = 0;
   ascii_io::get_curser_position(getx, gety);
   ascii_io::ncurses_end();
   
   EXPECT_EQ(0, getx); 
   EXPECT_EQ(1, gety);
}

TEST(ascii_io, move_cursor_right)
{
   ascii_io::ncurses_init();
   ascii_io::move_curser_to_position(1, 1);
   ascii_io::move_curser_right(1);

   int getx = 0, gety = 0;
   ascii_io::get_curser_position(getx, gety);
   ascii_io::ncurses_end();

   EXPECT_EQ(2, getx);
   EXPECT_EQ(1, gety);
}

TEST(ascii_io, terminal_size_nonzero)
{
   ascii_io::ncurses_init();

   int max_x = 0, max_y = 0;
   ascii_io::get_terminal_size(max_x, max_y);

   ascii_io::ncurses_end();

   EXPECT_NE(0, max_x);
   EXPECT_NE(0, max_y);
}
