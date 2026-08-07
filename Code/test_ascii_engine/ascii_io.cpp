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
   ascii_io::clear_screen_on_init_and_end(false);
   ascii_io::ascii_engine_init();
   int original_x = 0;
   int original_y = 0;
   ascii_io::get_cursor_position(original_x, original_y);
   int x = 5, y = 10;
   ascii_io::move_cursor_to_position(x, y);
  
   int getx = 0, gety = 0;
   ascii_io::get_cursor_position(getx, gety);
   ascii_io::move_cursor_to_position(original_x, original_y);

   EXPECT_EQ(x, getx);
   EXPECT_EQ(y, gety);
   ascii_io::ascii_engine_end();
}

TEST(ascii_io, move_cursor_down)
{
   ascii_io::clear_screen_on_init_and_end(false);
   ascii_io::ascii_engine_init();
   int original_x = 0;
   int original_y = 0;
   ascii_io::get_cursor_position(original_x, original_y);
   ascii_io::move_cursor_to_position(1, 1);
   ascii_io::move_cursor_down(1);

   int getx = 0, gety = 0;
   ascii_io::get_cursor_position(getx, gety);
   ascii_io::move_cursor_to_position(original_x, original_y);

   EXPECT_EQ(1, getx);
   EXPECT_EQ(2, gety);
   ascii_io::ascii_engine_end();
}

TEST(ascii_io, move_cursor_up)
{
   ascii_io::clear_screen_on_init_and_end(false);
   ascii_io::ascii_engine_init();
   int original_x = 0;
   int original_y = 0;
   ascii_io::get_cursor_position(original_x, original_y);
   ascii_io::move_cursor_to_position(1, 1);
   ascii_io::move_cursor_up(1);

   int getx = 0, gety = 0;
   ascii_io::get_cursor_position(getx, gety);
   ascii_io::move_cursor_to_position(original_x, original_y);

   EXPECT_EQ(1, getx);
   EXPECT_EQ(0, gety);
   ascii_io::ascii_engine_end();
}

TEST(ascii_io, move_cursor_left)
{
   ascii_io::clear_screen_on_init_and_end(false);
   ascii_io::ascii_engine_init();
   int original_x = 0;
   int original_y = 0;
   ascii_io::get_cursor_position(original_x, original_y);
   ascii_io::move_cursor_to_position(1, 1);
   ascii_io::move_cursor_left(1);

   int getx = 0, gety = 0;
   ascii_io::get_cursor_position(getx, gety);
   ascii_io::move_cursor_to_position(original_x, original_y);
   
   EXPECT_EQ(0, getx); 
   EXPECT_EQ(1, gety);
   ascii_io::ascii_engine_end();
}

TEST(ascii_io, move_cursor_right)
{
   ascii_io::clear_screen_on_init_and_end(false);
   ascii_io::ascii_engine_init();
   int original_x = 0;
   int original_y = 0;
   ascii_io::get_cursor_position(original_x, original_y);
   ascii_io::move_cursor_to_position(1, 1);
   ascii_io::move_cursor_right(1);

   int getx = 0, gety = 0;
   ascii_io::get_cursor_position(getx, gety);
   ascii_io::move_cursor_to_position(original_x, original_y);

   EXPECT_EQ(2, getx);
   EXPECT_EQ(1, gety);
   ascii_io::ascii_engine_end();
}

TEST(ascii_io, terminal_size_nonzero)
{
   ascii_io::clear_screen_on_init_and_end(false);
   ascii_io::ascii_engine_init();
   int max_x = 0, max_y = 0;
   ascii_io::get_terminal_size(max_x, max_y);

   EXPECT_NE(0, max_x);
   EXPECT_NE(0, max_y);
   ascii_io::ascii_engine_end();
}
