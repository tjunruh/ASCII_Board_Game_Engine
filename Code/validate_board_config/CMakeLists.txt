add_library(libvalidate_board_config STATIC)
target_sources(libvalidate_board_config
   PRIVATE
      validate_board_config.cpp

   PUBLIC
      FILE_SET libvalidate_board_config_headers
      TYPE HEADERS
      FILES
         validate_board_config.h
)

add_executable(validate_board_config)
target_sources(validate_board_config
   PRIVATE
      main.cpp
)

target_link_libraries(validate_board_config PRIVATE
   libvalidate_board_config
   libfile_manager
   libboard_config_field_parser
)

set_target_properties(libvalidate_board_config
   PROPERTIES
      POSITION_INDEPENDENT_CODE ON
)
