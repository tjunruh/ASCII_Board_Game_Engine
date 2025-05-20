msbuild /m /p:Configuration=Release windows_msbuild/text_box_demo.vcxproj
mkdir build
copy windows_msbuild\Release\text_box_demo.exe build\
copy ..\..\build\ascii_engine.dll build\
FOR /D %%p IN ("windows_msbuild\*.*") DO rmdir "%%p" /s /q