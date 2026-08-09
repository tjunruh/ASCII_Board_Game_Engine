add_library(libfile_manager STATIC)
target_sources(libfile_manager
   PRIVATE
      file_manager.cpp

   PUBLIC
      FILE_SET libfile_manager_headers
      TYPE HEADERS
      BASE_DIRS .
      FILES
         file_manager.h
)

set_property(TARGET libfile_manager PROPERTY POSITION_INEPENDENT_CODE ON)
