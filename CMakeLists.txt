cmake_minimum_required(VERSION 3.10)
project(ascii_engine)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build examples programs" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Static libraries used by multiple executables/libraries
add_subdirectory(Code/file_manager)
add_subdirectory(Code/board_config_field_parser)
add_subdirectory(Code/validate_board_config) # this is also an executable

# Executables
add_subdirectory(Code/build_board_config)
add_subdirectory(Code/action_tile_pattern_maker)

# Ascii engine library
add_subdirectory(Code/ascii_engine)

if(BUILD_TESTS)
   enable_testing()
   add_subdirectory(Code/test_ascii_engine)
endif()
