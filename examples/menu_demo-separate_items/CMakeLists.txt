cmake_minimum_required(VERSION 3.16)
project(menu_demo-separate_items)

# Set this to where your ascii_engine is installed
set(ASCII_ENGINE_INSTALL_ROOT "${CMAKE_SOURCE_DIR}/../../build/install")
include(cmake/import_ascii_engine_from_install.cmake)

add_executable(menu_demo-separate_items)
target_sources(menu_demo-separate_items
   PRIVATE
      menu_demo-separate_items.cpp
)

target_link_libraries(menu_demo-separate_items PRIVATE ascii_engine::ascii_engine)

