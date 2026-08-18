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

install(
   TARGETS action_tile_pattern_maker
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
