add_library(libfile_manager OBJECT)
target_sources(libfile_manager
   PRIVATE
      file_manager.cpp
)

target_include_directories(libfile_manager
   PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}
)

set_property(TARGET libfile_manager PROPERTY POSITION_INEPENDENT_CODE ON)
