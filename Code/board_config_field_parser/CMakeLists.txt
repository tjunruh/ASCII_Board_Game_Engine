add_library(libboard_config_field_parser STATIC)
target_sources(libboard_config_field_parser
   PRIVATE
      board_config_field_parser.cpp
)

target_include_directories(libboard_config_field_parser
   PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIRECTORY}
)

set_target_properties(libboard_config_field_parser
   PROPERTIES
      POSITION_INDEPENDENT_CODE ON
)
