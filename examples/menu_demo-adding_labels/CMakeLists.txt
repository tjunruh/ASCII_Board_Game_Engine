cmake_minimum_required(VERSION 3.16)
project(menu_demo-adding_labels)

# Set this to where your ascii_engine is installed
set(ASCII_ENGINE_INSTALL_ROOT "${CMAKE_SOURCE_DIR}/../../build/install")
include(cmake/import_ascii_engine_from_install.cmake)

add_executable(menu_demo-adding_labels)
target_sources(menu_demo-adding_labels
   PRIVATE
      menu_demo-adding_labels.cpp
)

target_link_libraries(menu_demo-adding_labels PRIVATE ascii_engine::ascii_engine)

