# ASCII_Board_Game_Engine

This respository contains software to generate ascii graphics in a terminal specifically for board game creation. Look at the repository's wiki on the top bar for the detailed API description.

## Windows
Build ASCII_Board_Game_Engine as a dll and link to your project. Also build the build_board_config and validate_board_config binaries. If you would prefer to not build everything, binaries are available in releases.

## Linux
Build ASCII_Board_Game_Engine as a shared object and link to your project. A make file is provided in the repository. To make the shared object, the build_board_config binary, and validate_board_config binary, simply run:
```
make engine
```

To make the test for ASCII_Board_Game_Engine, run:
```
make test
```

To build both, run:
```
make all
```

Note that you must have ncurses installed. If not installed, run:
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```

If you would prefer to not build everything, binaries are available in releases.