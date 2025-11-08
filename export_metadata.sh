#!/bin/bash

mkdir -p exported_metadata
cp Code/ascii_engine/board_metadata.cpp exported_metadata/
cp Code/ascii_engine/board_metadata.h exported_metadata/
cp Code/ascii_engine/error_codes.h exported_metadata/

sed -i 's/#ifdef _WIN32//g' exported_metadata/board_metadata.h
sed -i 's/#ifdef BOARD_METADATA_EXPORTS//g' exported_metadata/board_metadata.h
sed -i 's/#define BOARD_METADATA_API __declspec(dllexport)//g' exported_metadata/board_metadata.h
sed -i 's/#else//g' exported_metadata/board_metadata.h
sed -i 's/#define BOARD_METADATA_API __declspec(dllimport)//g' exported_metadata/board_metadata.h
sed -i 's/#endif//g' exported_metadata/board_metadata.h
sed -i 's/#elif __linux__//g' exported_metadata/board_metadata.h
sed -i 's/#define BOARD_METADATA_API//g' exported_metadata/board_metadata.h

sed -i 's/BOARD_METADATA_API //g' exported_metadata/board_metadata.h

sed -i 's/#include "..\/ascii_engine_dll_files\/pch.h"//g' exported_metadata/board_metadata.cpp
