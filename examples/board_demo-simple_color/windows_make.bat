msbuild /m /p:Configuration=Release windows_msbuild/board_demo-simple_color.vcxproj
mkdir build
mkdir build\board_configs
copy windows_msbuild\Release\board_demo-simple_color.exe build\
copy ..\..\build\ascii_engine.dll build\
copy board_configs\* build\board_configs\
FOR /D %%p IN ("windows_msbuild\*.*") DO rmdir "%%p" /s /q