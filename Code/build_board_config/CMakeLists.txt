add_executable(build_board_config)
target_sources(build_board_config
   PRIVATE
      main.cpp
      build_board_config.cpp
)

target_link_libraries(build_board_config 
   PRIVATE
   libfile_manager
)
