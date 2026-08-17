add_executable(action_tile_pattern_maker)

target_sources(action_tile_pattern_maker
   PRIVATE
   main.cpp
   action_tile_pattern_maker.cpp
)

target_link_libraries(action_tile_pattern_maker
   PRIVATE
      libfile_manager
      libboard_config_field_parser
      libvalidate_board_config
)

if(WIN32)
   target_compile_definitions(action_tile_pattern_maker PRIVATE FILE_MANAGER_EXPORTS)
endif()
