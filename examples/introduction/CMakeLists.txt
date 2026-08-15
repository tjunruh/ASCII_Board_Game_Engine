cmake_minimum_required(VERSION 3.16)
project(ascii_engine_introduction)

# Set this to where your ascii_engine is installed
set(ASCII_ENGINE_INSTALL_ROOT "${CMAKE_SOURCE_DIR}/../../build/install")
include(cmake/import_ascii_engine_from_install.cmake)

add_executable(introduction)
target_sources(introduction
   PRIVATE
      introduction.cpp
)

target_link_libraries(introduction PRIVATE ascii_engine::ascii_engine)

