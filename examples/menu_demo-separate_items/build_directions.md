# Build Directions

## Windows

First, build ascii engine at root level of repository.
```
cd ASCII_Board_Game_Engine
.\windows_build
```

Then, build menu_demo-separate_items program.
```
cd ASCII_Board_Game_Engine\examples\menu_demo-separate_items
.\windows_build
```

Enter the new build directory and run the program
```
cd ASCII_Board_Game_Engine\examples\menu_demo-separate_items\build
.\menu_demo-separate_items
```

## Linux

First, build ascii engine at root level of repository.
```
cd ASCII_Board_Game_Engine
make engine
```

Then, build introduction program.
```
cd ASCII_Board_Game_Engine/examples/menu_demo-separate_items
make
```

Enter the new build directory and set LD_LIBRARY_PATH to the directory that the ascii engine shared object is in.
```
cd ASCII_Board_Game_Engine/examples/menu_demo-separae_items/build
export LD_LIBRARY_PATH=../../../build/
```

Run the program
```
./menu_demo-separate_items
```