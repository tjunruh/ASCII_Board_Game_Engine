#include "pch.h"
#ifdef __linux__
#include <gtest/gtest.h>
#endif

int main(int argc, char **argv)
{
   testing::InitGoogleTest(&argc, argv);   
   return RUN_ALL_TESTS();
}
