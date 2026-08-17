add_library(libvalidate_board_config OBJECT)
target_sources(libvalidate_board_config
   PRIVATE
      validate_board_config.cpp
)

add_executable(validate_board_config)
target_sources(validate_board_config
   PRIVATE
      main.cpp
)

target_include_directories(libvalidate_board_config
   PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIRECTORY}
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

install(
   TARGETS validate_board_config
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)

if(WIN32)
   target_compile_definitions(validate_board_config PRIVATE FILE_MANAGER_EXPORTS)
endif()
