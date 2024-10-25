msbuild /m /p:Configuration=Release Code/ascii_engine/ascii_engine.vcxproj
msbuild /m /p:Configuration=Release Code/build_board_config/build_board_config.vcxproj
msbuild /m /p:Configuration=Release Code/validate_board_config/validate_board_config.vcxproj
mkdir build
copy Code\ascii_engine\Release\ascii_engine.dll build
copy Code\ascii_engine\Release\ascii_engine.lib build
copy Code\build_board_config\Release\build_board_config.exe build
copy Code\validate_board_config\Release\validate_board_config.exe build
rd /s /q Code\ascii_engine\Release
rd /s /q Code\build_board_config\Release
rd /s /q Code\validate_board_config\Release