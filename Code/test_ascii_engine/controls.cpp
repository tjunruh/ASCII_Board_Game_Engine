#include "pch.h"
#ifdef __linux__
#include <gtest/gtest.h>
#endif
#ifdef _WIN32
#include "../ascii_engine/controls.h"
#include "../ascii_engine/error_codes.h"
#include "../file_manager/file_manager.h"
#elif __linux__
#include <ascii_engine/controls.h>
#include <ascii_engine/error_codes.h>
#include <ascii_engine/file_manager.h>
#endif

#include <vector>
#include <utility>

constexpr const char* FILE_NAME = "test_file";

constexpr const char* BIND_NAME = "test";
constexpr int BIND_KEY = 15;

constexpr const char* BIND_NAME_A = "forward";
constexpr int BIND_KEY_A = 60;

constexpr const char* BIND_NAME_B = "left";
constexpr int BIND_KEY_B =  70;

constexpr const char* BIND_NAME_C = "right";
constexpr int BIND_KEY_C = 80;

constexpr const char* BIND_NAME_D = "backward";
constexpr int BIND_KEY_D = 90;

class controls_test : public testing::Test
{
protected:

   const std::vector<std::pair<std::string, int>> KEY_TEST
   {
      {BIND_NAME_A, BIND_KEY_A},
      {BIND_NAME_B, BIND_KEY_B},
      {BIND_NAME_C, BIND_KEY_C},
      {BIND_NAME_D, BIND_KEY_D}
   };

   controls_test()
   {
      single_controls.bind(BIND_NAME, BIND_KEY);

      multiple_controls.bind(BIND_NAME_A, BIND_KEY_A);
      multiple_controls.bind(BIND_NAME_B, BIND_KEY_B);
      multiple_controls.bind(BIND_NAME_C, BIND_KEY_C);
      multiple_controls.bind(BIND_NAME_D, BIND_KEY_D);
   }

   ~controls_test(){}

   controls empty_controls;
   controls single_controls;
   controls multiple_controls;
};

TEST_F(controls_test, bind)
{

   int result = 0;

   result = empty_controls.bind(BIND_NAME, BIND_KEY);
   EXPECT_EQ(result, SUCCESS);

   result = empty_controls.bind(BIND_NAME, 0);
   EXPECT_EQ(result, DUPLICATE_ELEMENT);

   int key = empty_controls.get_key(BIND_NAME);
   EXPECT_EQ(key, BIND_KEY);
}

TEST_F(controls_test, force_bind)
{
    multiple_controls.force_bind(BIND_NAME_D, BIND_KEY_A);
    int result = multiple_controls.get_key(BIND_NAME_D);
    EXPECT_EQ(result, BIND_KEY_A);
}

TEST_F(controls_test, unbind)
{
   int result = 0;

   result = single_controls.unbind(BIND_NAME);
   EXPECT_EQ(result, SUCCESS);

   result = single_controls.unbind(BIND_NAME);
   EXPECT_EQ(result, ELEMENT_NOT_FOUND);
}

TEST_F(controls_test, get_key)
{
   int key = 0;

   for ( const auto& test : KEY_TEST )
   {
      key = multiple_controls.get_key(test.first);
      EXPECT_EQ(key, test.second);
   }

}

TEST_F(controls_test, save_and_load)
{
    multiple_controls.set_select_keys({ ascii_io::enter, ascii_io::DEL });
   int result = multiple_controls.save_controls({FILE_NAME});
   ASSERT_EQ(result, SUCCESS);

   controls ascii_controls;
   result = ascii_controls.load_controls({FILE_NAME});
   EXPECT_EQ(result, SUCCESS);

   for ( const auto& test : KEY_TEST )
   {
      int key = ascii_controls.get_key(test.first);
      EXPECT_EQ(key, test.second);
   }

   std::vector<int> select_keys = multiple_controls.get_select_keys();
   EXPECT_EQ(select_keys.size(), 2);
   EXPECT_EQ(select_keys[0], ascii_io::enter);
   EXPECT_EQ(select_keys[1], ascii_io::DEL);

   file_manager::delete_file(FILE_NAME);
}

