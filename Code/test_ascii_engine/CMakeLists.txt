find_package(Threads REQUIRED)

include(FetchContent)
FetchContent_Declare(
   googletest
   URL https://github.com/google/googletest/releases/download/v1.18.0/googletest-1.18.0.tar.gz
   URL_HASH SHA256=6e3191c1455468b3fc35a417fb565c1c5071aee1b7e7f85e30cf48a98d37d8b5
   DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

if(NOT TARGET gtest)
   find_package(GTest REQUIRED)
endif()

add_executable(test_ascii_engine)
target_sources(test_ascii_engine
   PRIVATE
      ascii_board.cpp
      ascii_io.cpp
      console.cpp
      controls.cpp
      format_tools.cpp
      frame.cpp
      label.cpp
      main.cpp
      menu.cpp
      pch.cpp
      widget.cpp

)

target_include_directories(test_ascii_engine
   PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIRECTORY}
)

target_precompile_headers(test_ascii_engine
   PRIVATE
      pch.h
)

target_link_libraries(test_ascii_engine
   PRIVATE
      ascii_engine
      Threads::Threads
      gtest
)

add_custom_command(
   TARGET test_ascii_engine POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_directory
   ${CMAKE_CURRENT_SOURCE_DIR}/test_configs
   $<TARGET_FILE_DIR:test_ascii_engine>/Code/build/test_configs
   COMMENT "Copying test configs to build directory"
)

add_test(
   NAME test_ascii_engine
   COMMAND test_ascii_engine --gtest_filter=-ascii_io.*
)

set_tests_properties(test_ascii_engine PROPERTIES
   ENVIRONMENT "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}"
   WORKING_DIRECTORY ${PROJECT_ROOT}
   TIMEOUT 120
)
