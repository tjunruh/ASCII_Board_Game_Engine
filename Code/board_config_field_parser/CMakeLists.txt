add_library(libboard_config_field_parser STATIC)
target_sources(libboard_config_field_parser
   PRIVATE
      board_config_field_parser.cpp

   PUBLIC
      FILE_SET lib_board_config_field_parser_headers
      TYPE HEADERS
      FILES
         board_config_field_parser.h
)

set_target_properties(libboard_config_field_parser
   PROPERTIES
      POSITION_INDEPENDENT_CODE ON
)
