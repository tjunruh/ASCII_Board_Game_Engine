cmake_minimum_required(VERSION 3.16)
project(label_demo)

# Set this to where your ascii_engine is installed
set(ASCII_ENGINE_INSTALL_ROOT "${CMAKE_SOURCE_DIR}/../../build/install")
include(cmake/import_ascii_engine_from_install.cmake)

add_executable(label_demo)
target_sources(label_demo
   PRIVATE
      label_demo.cpp
)

target_link_libraries(label_demo PRIVATE ascii_engine::ascii_engine)

