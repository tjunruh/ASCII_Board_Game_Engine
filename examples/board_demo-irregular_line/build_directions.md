# Build Directions

## Windows

First, build ascii engine at root level of repository.
```
cd ASCII_Board_Game_Engine
.\windows_build
```

Then, build board_demo-irregular_line program.
```
cd ASCII_Board_Game_Engine\examples\board_demo-irregular_line
.\windows_build
```

Enter the new build directory and run the program
```
cd ASCII_Board_Game_Engine\examples\board_demo-irregular_line\build
.\board_demo-irregular_line
```

## Linux

First, build ascii engine at root level of repository.
```
cd ASCII_Board_Game_Engine
make engine
```

Then, build board_demo-irregular_line program.
```
cd ASCII_Board_Game_Engine/examples/board_demo-irregular_line
make
```

Enter the new build directory and set LD_LIBRARY_PATH to the directory that the ascii engine shared object is in.
```
cd ASCII_Board_Game_Engine/examples/board_demo-irregular_line/build
export LD_LIBRARY_PATH=../../../build/
```

Run the program
```
./board_demo-irregular_line
```