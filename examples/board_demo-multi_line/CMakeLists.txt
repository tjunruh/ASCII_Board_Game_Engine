cmake_minimum_required(VERSION 3.16)
project(board_demo-multi_line)

# Set this to where your ascii_engine is installed
set(ASCII_ENGINE_INSTALL_ROOT "${CMAKE_SOURCE_DIR}/../../build/install")
include(cmake/import_ascii_engine_from_install.cmake)

add_executable(board_demo-multi_line)
target_sources(board_demo-multi_line
   PRIVATE
      board_demo-multi_line.cpp
)

target_link_libraries(board_demo-multi_line PRIVATE ascii_engine::ascii_engine)

add_custom_command(POST_BUILD
   TARGET board_demo-multi_line
   COMMAND ${CMAKE_COMMAND} -E copy_directory
   ${CMAKE_CURRENT_SOURCE_DIR}/board_configs
   $<TARGET_FILE_DIR:board_demo-multi_line>/board_configs
   COMMENT "Copying board configs to build directory"
)
