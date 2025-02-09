msbuild /m /p:Configuration=Release windows_msbuild/menu_demo-adding_labels.vcxproj
mkdir build
copy windows_msbuild\Release\menu_demo-adding_labels.exe build\
copy ..\..\build\ascii_engine.dll build\
FOR /D %%p IN ("windows_msbuild\*.*") DO rmdir "%%p" /s /q