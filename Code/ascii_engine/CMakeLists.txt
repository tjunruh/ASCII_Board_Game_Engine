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
)

target_include_directories(ascii_engine
   PRIVATE
      ${PROJECT_ROOT}/external_libraries
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/..
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
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
install(FILES
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
   DESTINATION include/ascii_engine
)

if(WIN32)
   target_compile_definitions(ascii_engine PRIVATE ASCII_BOARD_EXPORTS)
   target_compile_definitions(ascii_engine PRIVATE ASCII_IO_EXPORTS)
   target_compile_definitions(ascii_engine PRIVATE BOARD_METADATA_EXPORTS)
   target_compile_definitions(ascii_engine PRIVATE CONSOLE_EXPORTS)
   target_compile_definitions(ascii_engine PRIVATE CONTROLS_EXPORTS)
   target_compile_definitions(ascii_engine PRIVATE FILE_MANAGER_EXPORTS)
   target_compile_definitions(ascii_engine PRIVATE FORMAT_TOOLS_EXPORTS)
   target_compile_definitions(ascii_engine PRIVATE FRAME_EXPORTS)
   target_compile_definitions(ascii_engine PRIVATE LABEL_EXPORTS)
   target_compile_definitions(ascii_engine PRIVATE LOGGER_EXPORTS)
   target_compile_definitions(ascii_engine PRIVATE MENU_EXPORTS)
   target_compile_definitions(ascii_engine PRIVATE TEXT_BOX_EXPORTS)
   target_compile_definitions(ascii_engine PRIVATE WIDGET_EXPORTS)
endif()
