add_library(ascii_engine SHARED)
target_sources(ascii_engine
   # Files to compile
   PRIVATE
      ascii_board.cpp
      ascii_io.cpp
      board_metadata.cpp
      console.cpp
      controls.cpp
      dec_formatter.cpp
      format_tools.cpp
      frame.cpp
      label.cpp
      logger.cpp
      menu.cpp
      text_box.cpp
      widget.cpp

   # Files to include in the creation of library
   PUBLIC
      FILE_SET ascii_engine_headers
      TYPE HEADERS
      BASE_DIRS ..
      FILES
         ascii_board.h
         ascii_io.h
         board_metadata.h
         console.h
         controls.h
         dec_formatter.h
         error_codes.h
         format_tools.h
         frame.h
         label.h
         logger.h
         menu.h
         text_box.h
         widget.h
         widget_types.h
         file_manager.h

)

target_include_directories(ascii_engine
   PRIVATE
      ${PROJECT_ROOT}/external_libraries
)

target_link_libraries(ascii_engine
   PUBLIC
   libfile_manager
   libboard_config_field_parser
   libvalidate_board_config
)

target_precompile_headers(ascii_engine
   PRIVATE ../ascii_engine_dll_files/pch.h
)

install(
   TARGETS ascii_engine

   FILE_SET HEADERS
   FILE_SET ascii_engine_headers
)
