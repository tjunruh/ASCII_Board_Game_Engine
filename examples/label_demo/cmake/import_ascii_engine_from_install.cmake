
if(NOT DEFINED ASCII_ENGINE_INSTALL_ROOT)
   message(FATAL_ERROR "Set ASCII_ENGINE_INSTALL_ROOT to your install tree (e.g. ../../build/install)")
endif()

set(_inc_dir "${ASCII_ENGINE_INSTALL_ROOT}/include")
set(_lib_file "${ASCII_ENGINE_INSTALL_ROOT}/lib/libascii_engine.so")

if(NOT EXISTS "${_inc_dir}")
   message(FATAL_ERROR "Missing include dir: ${_inc_dir}. Is ascii_engine built/installed?")
endif()

if(NOT EXISTS "${_lib_file}")
   message(FATAL_ERROR "Missing shared_library: ${_lib_file}. Is ascii_engine built/installed?")
endif()

add_library(ascii_engine::ascii_engine SHARED IMPORTED GLOBAL)
set_target_properties(ascii_engine::ascii_engine PROPERTIES
   IMPORTED_LOCATION "${_lib_file}"
   INTERFACE_INCLUDE_DIRECTORIES "${_inc_dir}"
)
