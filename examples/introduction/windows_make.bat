msbuild /m /p:Configuration=Release windows_msbuild/introduction.vcxproj
mkdir build
copy windows_msbuild\Release\introduction.exe build\
copy ..\..\build\ascii_engine.dll build\
FOR /D %%p IN ("windows_msbuild\*.*") DO rmdir "%%p" /s /q