# Build Directions

## Windows

First, build ascii engine at root level of repository.
```
cd ASCII_Board_Game_Engine
.\windows_build
```

Then, build board_demo-multi_color program.
```
cd ASCII_Board_Game_Engine\examples\board_demo-mlti_color
.\windows_build
```

Enter the new build directory and run the program
```
cd ASCII_Board_Game_Engine\examples\board_demo-multi_color\build
.\board_demo-multi_color
```

## Linux

First, build ascii engine at root level of repository.
```
cd ASCII_Board_Game_Engine
make engine
```

Then, build board_demo-multi_color program.
```
cd ASCII_Board_Game_Engine/examples/board_demo-multi_color
make
```

Enter the new build directory and set LD_LIBRARY_PATH to the directory that the ascii engine shared object is in.
```
cd ASCII_Board_Game_Engine/examples/board_demo-multi_color/build
export LD_LIBRARY_PATH=../../../build/
```

Run the program
```
./board_demo-multi_color
```