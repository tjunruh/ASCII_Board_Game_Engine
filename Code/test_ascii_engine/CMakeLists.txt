find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

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

   PRIVATE
      FILE_SET test_ascii_engine_headers
      TYPE HEADERS
      FILES
         expected_display_data.h
         irregular_line_board_definitions.h
         multi_line_board_definitions.h
         single_line_board_definitions.h
)

target_precompile_headers(test_ascii_engine
   PRIVATE
      pch.h
)

target_link_libraries(test_ascii_engine
   PRIVATE
      libascii_engine
      Threads::Threads
      GTest::gtest
)

add_custom_command(
   TARGET test_ascii_engine POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_directory
   ${CMAKE_CURRENT_SOURCE_DIR}/test_configs
   $<TARGET_FILE_DIR:test_ascii_engine>/test_configs
   COMMENT "Copying test configs to build directory"
)

add_test(
   NAME test_ascii_engine
   COMMAND test_ascii_engine --gtest_filter=-ascii_io.*
)
