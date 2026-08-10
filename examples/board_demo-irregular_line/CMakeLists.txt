add_executable(board_demo-irregular_line)
target_sources(board_demo-irregular_line
   PRIVATE
      board_demo-irregular_line.cpp
)

target_link_libraries(board_demo-irregular_line
   PRIVATE
      libascii_engine
)

if (MSVC)
   target_compile_options(board_demo-irregular_line PRIVATE /W4)
else()
   target_compile_options(board_demo-irregular_line PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_custom_command(
   TARGET board_demo-irregular_line
   COMMAND ${CMAKE_COMMAND} -E copy_directory
   ${CMAKE_CURRENT_SOURCE_DIR}/board_configs
   $<TARGET_FILE_DIR:board_demo-irregular_line>/board_configs
   COMMENT "Copying board configs to build directory"
)
