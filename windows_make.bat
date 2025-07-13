status=0
msbuild /m /p:Configuration=Release Code/ascii_engine/windows_msbuild/ascii_engine.vcxproj
IF %ERRORLEVEL% NEQ 0 (
  set status=1
)
msbuild /m /p:Configuration=Release Code/build_board_config/windows_msbuild/build_board_config.vcxproj
IF %ERRORLEVEL% NEQ 0 (
  set status=1
)
msbuild /m /p:Configuration=Release Code/validate_board_config/windows_msbuild/validate_board_config.vcxproj
IF %ERRORLEVEL% NEQ 0 (
  set status=1
)

msbuild /m /p:Configuration=Release Code/action_tile_pattern_maker/windows_msbuild/action_tile_pattern_maker.vcxproj
IF %ERRORLEVEL% NEQ 0 (
  set status=1
)

mkdir build
mkdir build\headers
mkdir build\headers\ascii_engine
copy Code\ascii_engine\windows_msbuild\Release\ascii_engine.dll build
copy Code\ascii_engine\windows_msbuild\Release\ascii_engine.lib build
copy Code\build_board_config\windows_msbuild\Release\build_board_config.exe build
copy Code\validate_board_config\windows_msbuild\Release\validate_board_config.exe build
copy Code\action_tile_pattern_maker\windows_msbuild\Release\action_tile_pattern_maker.exe build
copy Code\ascii_engine\*.h build\headers\ascii_engine
copy Code\file_manager\*.h build\headers\ascii_engine
copy LICENSE build
FOR /D %%p IN ("Code\ascii_engine\windows_msbuild\*.*") DO rmdir "%%p" /s /q
FOR /D %%p IN ("Code\build_board_config\windows_msbuild\*.*") DO rmdir "%%p" /s /q
FOR /D %%p IN ("Code\validate_board_config\windows_msbuild\*.*") DO rmdir "%%p" /s /q
FOR /D %%p IN ("Code\action_tile_pattern_maker\windows_msbuild\*.*") DO rmdir "%%p" /s /q

EXIT /b %status%