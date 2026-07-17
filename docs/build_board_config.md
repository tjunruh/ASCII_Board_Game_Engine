# build_board_config binary

Usage:
```
Executing the binary on the command line will output instructions:

Windows:
.\build_board_config.exe
You must include the following argument:
[1] Path to text file containing map

Linux:
./build_board_config.out
You must include the following argument:
[1] Path to text file containing map
```

Example input file contents:
```
demo_board.txt:
.---.---.---.---.---.---.---.---.---.---.
|   |   |   |   |   |   |   |   |   |   |
.---+---+---+---+---+---+---+---+---+---.
|   |   |   |   |   |   |   |   |   |   |
.---+---+---+---+---+---+---+---+---+---.
|   |   |   |   |   |   |   |   |   |   |
.---+---+---+---+---+---+---+---+---+---.
|   |   |   |   |   |   |   |   |   |   |
.---+---+---+---+---+---+---+---+---+---.
|   |   |_-`|`-_|   |   |_-`|`-_|   |   |
.---+---+---+---+---+---+---+---+---+---.
|   |   |_-`|`-_|   |   |_-`|`-_|   |   |
.---+---+---+---+---+---+---+---+---+---.
|   |   |   |   |   |   |   |   |   |   |
.---+---+---+---+---+---+---+---+---+---.
|   |   |   |   |   |   |   |   |   |   |
.---+---+---+---+---+---+---+---+---+---.
|   |   |   |   |   |   |   |   |   |   |
.---+---+---+---+---+---+---+---+---+---.
|   |   |   |   |   |   |   |   |   |   |
.---.---.---.---.---.---.---.---.---.---.
```

Run the demo board through the build_board_config binary:
```
Windows:
.\build_board_config.exe demo_board.txt

Linux:
./build_board_config.out demo_board.txt
```

The output will be a file created in the same directory as the binary. Its name will be the name of the input file plus "_config" at the end. In this case, it is demo_board_config.txt
```
demo_board_config.txt:
** board begin **
             1111111111222222222233333333334
   01234567890123456789012345678901234567890
 0 .---.---.---.---.---.---.---.---.---.---.
 1 |   |   |   |   |   |   |   |   |   |   |
 2 .---+---+---+---+---+---+---+---+---+---.
 3 |   |   |   |   |   |   |   |   |   |   |
 4 .---+---+---+---+---+---+---+---+---+---.
 5 |   |   |   |   |   |   |   |   |   |   |
 6 .---+---+---+---+---+---+---+---+---+---.
 7 |   |   |   |   |   |   |   |   |   |   |
 8 .---+---+---+---+---+---+---+---+---+---.
 9 |   |   |_-`|`-_|   |   |_-`|`-_|   |   |
10 .---+---+---+---+---+---+---+---+---+---.
11 |   |   |_-`|`-_|   |   |_-`|`-_|   |   |
12 .---+---+---+---+---+---+---+---+---+---.
13 |   |   |   |   |   |   |   |   |   |   |
14 .---+---+---+---+---+---+---+---+---+---.
15 |   |   |   |   |   |   |   |   |   |   |
16 .---+---+---+---+---+---+---+---+---+---.
17 |   |   |   |   |   |   |   |   |   |   |
18 .---+---+---+---+---+---+---+---+---+---.
19 |   |   |   |   |   |   |   |   |   |   |
20 .---.---.---.---.---.---.---.---.---.---.
** board end **


** Define Dimensions of 2D Array Containing Action Tiles (Rows, Columns) **
** array dimensions begin **
(,)
** array dimensions end **


** Define Actions Tiles (Map Row Range, Map Column Range, Array Row, Array Column) **
** action tiles begin **
(,,,)
  .
  .
  .
** action tiles end **


** Define Metadata - Global: (Key, Value) Action Tile Specific: {(Key, Value), (Key, Value), (Key, Value)...} - value can be integer, float, or string (string must be enclosed in quotation marks).
Note that two key value pairs in each curly bracket block must be used to define the row and column of action tile the metadata is related to **
** metadata begin **
Global:
(Key, Value)
(Key, Value)

Action Tile Specific:
{
   (row, 0)
   (column, 0)
   (Key, Value)
   (Key, Value)
}

{
   (row, 0)
   (column, 0)
   (Key, Value)
   (Key, Value)
}
  .
  .
  .
** metadata end **
```

Fill out the dimensions of the two dimensional array to hold board action tiles and the size of each action tile. The metadata section can be removed if not used. An example of how it could be done for this board is shown below:
```
** board begin **
             1111111111222222222233333333334
   01234567890123456789012345678901234567890
 0 .---.---.---.---.---.---.---.---.---.---.
 1 |   |   |   |   |   |   |   |   |   |   |
 2 .---+---+---+---+---+---+---+---+---+---.
 3 |   |   |   |   |   |   |   |   |   |   |
 4 .---+---+---+---+---+---+---+---+---+---.
 5 |   |   |   |   |   |   |   |   |   |   |
 6 .---+---+---+---+---+---+---+---+---+---.
 7 |   |   |   |   |   |   |   |   |   |   |
 8 .---+---+---+---+---+---+---+---+---+---.
 9 |   |   |_-`|`-_|   |   |_-`|`-_|   |   |
10 .---+---+---+---+---+---+---+---+---+---.
11 |   |   |_-`|`-_|   |   |_-`|`-_|   |   |
12 .---+---+---+---+---+---+---+---+---+---.
13 |   |   |   |   |   |   |   |   |   |   |
14 .---+---+---+---+---+---+---+---+---+---.
15 |   |   |   |   |   |   |   |   |   |   |
16 .---+---+---+---+---+---+---+---+---+---.
17 |   |   |   |   |   |   |   |   |   |   |
18 .---+---+---+---+---+---+---+---+---+---.
19 |   |   |   |   |   |   |   |   |   |   |
20 .---.---.---.---.---.---.---.---.---.---.
** board end **


** Define Dimensions of 2D Array Containing Action Tiles (Rows, Columns) **
** array dimensions begin **
(10,10)
** array dimensions end **


** Define Actions Tiles (Map Row Range, Map Column Range, Array Row, Array Column) **
** action tiles begin **
(1,1-3,0,0)
(1,5-7,0,1)
(1,9-11,0,2)
(1,13-15,0,3)
(1,17-19,0,4)
(1,21-23,0,5)
(1,25-27,0,6)
(1,29-31,0,7)
(1,33-35,0,8)
(1,37-39,0,9)

(3,1-3,1,0)
(3,5-7,1,1)
(3,9-11,1,2)
(3,13-15,1,3)
(3,17-19,1,4)
(3,21-23,1,5)
(3,25-27,1,6)
(3,29-31,1,7)
(3,33-35,1,8)
(3,37-39,1,9)

(5,1-3,2,0)
(5,5-7,2,1)
(5,9-11,2,2)
(5,13-15,2,3)
(5,17-19,2,4)
(5,21-23,2,5)
(5,25-27,2,6)
(5,29-31,2,7)
(5,33-35,2,8)
(5,37-39,2,9)

(7,1-3,3,0)
(7,5-7,3,1)
(7,9-11,3,2)
(7,13-15,3,3)
(7,17-19,3,4)
(7,21-23,3,5)
(7,25-27,3,6)
(7,29-31,3,7)
(7,33-35,3,8)
(7,37-39,3,9)

(9,1-3,4,0)
(9,5-7,4,1)
(9,17-19,4,4)
(9,21-23,4,5)
(9,33-35,4,8)
(9,37-39,4,9)

(11,1-3,5,0)
(11,5-7,5,1)
(11,17-19,5,4)
(11,21-23,5,5)
(11,33-35,5,8)
(11,37-39,5,9)

(13,1-3,6,0)
(13,5-7,6,1)
(13,9-11,6,2)
(13,13-15,6,3)
(13,17-19,6,4)
(13,21-23,6,5)
(13,25-27,6,6)
(13,29-31,6,7)
(13,33-35,6,8)
(13,37-39,6,9)

(15,1-3,7,0)
(15,5-7,7,1)
(15,9-11,7,2)
(15,13-15,7,3)
(15,17-19,7,4)
(15,21-23,7,5)
(15,25-27,7,6)
(15,29-31,7,7)
(15,33-35,7,8)
(15,37-39,7,9)

(17,1-3,8,0)
(17,5-7,8,1)
(17,9-11,8,2)
(17,13-15,8,3)
(17,17-19,8,4)
(17,21-23,8,5)
(17,25-27,8,6)
(17,29-31,8,7)
(17,33-35,8,8)
(17,37-39,8,9)

(19,1-3,9,0)
(19,5-7,9,1)
(19,9-11,9,2)
(19,13-15,9,3)
(19,17-19,9,4)
(19,21-23,9,5)
(19,25-27,9,6)
(19,29-31,9,7)
(19,33-35,9,8)
(19,37-39,9,9)


** action tiles end **
```

Another example utilizing the metadata section is shown below:
```
** board begin **
             1111111111222222222233333333334
   01234567890123456789012345678901234567890
 0 .---.---.---.---.---.---.---.---.---.---.
 1 |   |   |   |   |   |   |   |   |   |   |
 2 .---+---+---+---+---+---+---+---+---+---.
 3 |   |   |   |   |   |   |   |   |   |   |
 4 .---+---+---+---+---+---+---+---+---+---.
 5 |   |   |   |   |   |   |   |   |   |   |
 6 .---+---+---+---+---+---+---+---+---+---.
 7 |   |   |   |   |   |   |   |   |   |   |
 8 .---+---+---+---+---+---+---+---+---+---.
 9 |   |   |_-`|`-_|   |   |_-`|`-_|   |   |
10 .---+---+---+---+---+---+---+---+---+---.
11 |   |   |_-`|`-_|   |   |_-`|`-_|   |   |
12 .---+---+---+---+---+---+---+---+---+---.
13 |   |   |   |   |   |   |   |   |   |   |
14 .---+---+---+---+---+---+---+---+---+---.
15 |   |   |   |   |   |   |   |   |   |   |
16 .---+---+---+---+---+---+---+---+---+---.
17 |   |   |   |   |   |   |   |   |   |   |
18 .---+---+---+---+---+---+---+---+---+---.
19 |   |   |   |   |   |   |   |   |   |   |
20 .---.---.---.---.---.---.---.---.---.---.
** board end **


** Define Dimensions of 2D Array Containing Action Tiles (Rows, Columns) **
** array dimensions begin **
(10,10)
** array dimensions end **


** Define Actions Tiles (Map Row Range, Map Column Range, Array Row, Array Column) **
** action tiles begin **
(1,1-3,0,0)
(1,5-7,0,1)
(1,9-11,0,2)
(1,13-15,0,3)
(1,17-19,0,4)
(1,21-23,0,5)
(1,25-27,0,6)
(1,29-31,0,7)
(1,33-35,0,8)
(1,37-39,0,9)

(3,1-3,1,0)
(3,5-7,1,1)
(3,9-11,1,2)
(3,13-15,1,3)
(3,17-19,1,4)
(3,21-23,1,5)
(3,25-27,1,6)
(3,29-31,1,7)
(3,33-35,1,8)
(3,37-39,1,9)

(5,1-3,2,0)
(5,5-7,2,1)
(5,9-11,2,2)
(5,13-15,2,3)
(5,17-19,2,4)
(5,21-23,2,5)
(5,25-27,2,6)
(5,29-31,2,7)
(5,33-35,2,8)
(5,37-39,2,9)

(7,1-3,3,0)
(7,5-7,3,1)
(7,9-11,3,2)
(7,13-15,3,3)
(7,17-19,3,4)
(7,21-23,3,5)
(7,25-27,3,6)
(7,29-31,3,7)
(7,33-35,3,8)
(7,37-39,3,9)

(9,1-3,4,0)
(9,5-7,4,1)
(9,17-19,4,4)
(9,21-23,4,5)
(9,33-35,4,8)
(9,37-39,4,9)

(11,1-3,5,0)
(11,5-7,5,1)
(11,17-19,5,4)
(11,21-23,5,5)
(11,33-35,5,8)
(11,37-39,5,9)

(13,1-3,6,0)
(13,5-7,6,1)
(13,9-11,6,2)
(13,13-15,6,3)
(13,17-19,6,4)
(13,21-23,6,5)
(13,25-27,6,6)
(13,29-31,6,7)
(13,33-35,6,8)
(13,37-39,6,9)

(15,1-3,7,0)
(15,5-7,7,1)
(15,9-11,7,2)
(15,13-15,7,3)
(15,17-19,7,4)
(15,21-23,7,5)
(15,25-27,7,6)
(15,29-31,7,7)
(15,33-35,7,8)
(15,37-39,7,9)

(17,1-3,8,0)
(17,5-7,8,1)
(17,9-11,8,2)
(17,13-15,8,3)
(17,17-19,8,4)
(17,21-23,8,5)
(17,25-27,8,6)
(17,29-31,8,7)
(17,33-35,8,8)
(17,37-39,8,9)

(19,1-3,9,0)
(19,5-7,9,1)
(19,9-11,9,2)
(19,13-15,9,3)
(19,17-19,9,4)
(19,21-23,9,5)
(19,25-27,9,6)
(19,29-31,9,7)
(19,33-35,9,8)
(19,37-39,9,9)

** action tiles end **


** Define Metadata {(Key, Value), (Key, Value), (Key, Value)...} - value can be integer, float, or string (string must be enclosed in quotation marks).
Note that two key value pairs in each curly bracket block must be used to define the row and column of action tile the metadata is related to **
** metadata begin **
(map_level, 1)
(map_name, "test")
(map_id, 123.456)
{(row,0) (column,0) (test_string, "0") (test_float, 0.0) (test_integer, 0)}
{(row,0) (column,1) (test_string, "0") (test_float, -0.1) (test_integer, -0)}
{(row,0) (column,2) (test_string, "0") (test_float, 0.2) (test_integer, 0)}
{(row,0) (column,3) (test_string, "0") (test_float, -0.3) (test_integer, -0)}
{(row,0) (column,4) (test_string, "0") (test_float, 0.4) (test_integer, 0)}
{(row,0) (column,5) (test_string, "0") (test_float, -0.5) (test_integer, -0)}
{(row,0) (column,6) (test_string, "0") (test_float, 0.6) (test_integer, 0)}
{(row,0) (column,7) (test_string, "0") (test_float, -0.7) (test_integer, -0)}
{(row,0) (column,8) (test_string, "0") (test_float, 0.8) (test_integer, 0)}
{(row,0) (column,9) (test_string, "0") (test_float, -0.9) (test_integer, -0)}

{(row,1) (column,0) (test_string, "1") (test_float, 1.0) (test_integer, 1)}
{(row,1) (column,1) (test_string, "1") (test_float, -1.1) (test_integer, -1)}
{(row,1) (column,2) (test_string, "1") (test_float, 1.2) (test_integer, 1)}
{(row,1) (column,3) (test_string, "1") (test_float, -1.3) (test_integer, -1)}
{(row,1) (column,4) (test_string, "1") (test_float, 1.4) (test_integer, 1)}
{(row,1) (column,5) (test_string, "1") (test_float, -1.5) (test_integer, -1)}
{(row,1) (column,6) (test_string, "1") (test_float, 1.6) (test_integer, 1)}
{(row,1) (column,7) (test_string, "1") (test_float, -1.7) (test_integer, -1)}
{(row,1) (column,8) (test_string, "1") (test_float, 1.8) (test_integer, 1)}
{(row,1) (column,9) (test_string, "1") (test_float, -1.9) (test_integer, -1)}

(map_sublevel, -10)
(map_heading, "test_map")
(map_stats, -89.98)

{(row,2) (column,0) (test_string, "2") (test_float, 2.0) (test_integer, 2)}
{(row,2) (column,1) (test_string, "2") (test_float, -2.1) (test_integer, -2)}
{(row,2) (column,2) (test_string, "2") (test_float, 2.2) (test_integer, 2)}
{(row,2) (column,3) (test_string, "2") (test_float, -2.3) (test_integer, -2)}
{(row,2) (column,4) (test_string, "2") (test_float, 2.4) (test_integer, 2)}
{(row,2) (column,5) (test_string, "2") (test_float, -2.5) (test_integer, -2)}
{(row,2) (column,6) (test_string, "2") (test_float, 2.6) (test_integer, 2)}
{(row,2) (column,7) (test_string, "2") (test_float, -2.7) (test_integer, -2)}
{(row,2) (column,8) (test_string, "2") (test_float, 2.8) (test_integer, 2)}
{(row,2) (column,9) (test_string, "2") (test_float, -2.9) (test_integer, -2)}

{(row,3) (column,0) (test_string, "3") (test_float, 3.0) (test_integer, 3)}
{(row,3) (column,1) (test_string, "3") (test_float, -3.1) (test_integer, -3)}
{(row,3) (column,2) (test_string, "3") (test_float, 3.2) (test_integer, 3)}
{(row,3) (column,3) (test_string, "3") (test_float, -3.3) (test_integer, -3)}
{(row,3) (column,4) (test_string, "3") (test_float, 3.4) (test_integer, 3)}
{(row,3) (column,5) (test_string, "3") (test_float, -3.5) (test_integer, -3)}
{(row,3) (column,6) (test_string, "3") (test_float, 3.6) (test_integer, 3)}
{(row,3) (column,7) (test_string, "3") (test_float, -3.7) (test_integer, -3)}
{(row,3) (column,8) (test_string, "3") (test_float, 3.8) (test_integer, 3)}
{(row,3) (column,9) (test_string, "3") (test_float, -3.9) (test_integer, -3)}

{(row,4) (column,0) (test_string, "4") (test_float, 4.0) (test_integer, 4)}
{(row,4) (column,1) (test_string, "4") (test_float, -4.1) (test_integer, -4)}
{(row,4) (column,4) (test_string, "4") (test_float, 4.4) (test_integer, 4)}
{(row,4) (column,5) (test_string, "4") (test_float, -4.5) (test_integer, -4)}
{(row,4) (column,8) (test_string, "4") (test_float, 4.8) (test_integer, 4)}
{(row,4) (column,9) (test_string, "4") (test_float, -4.9) (test_integer, -4)}

{(row,5) (column,0) (test_string, "5") (test_float, 5.0) (test_integer, 5)}
{(row,5) (column,1) (test_string, "5") (test_float, -5.1) (test_integer, -5)}
{(row,5) (column,4) (test_string, "5") (test_float, 5.4) (test_integer, 5)}
{(row,5) (column,5) (test_string, "5") (test_float, -5.5) (test_integer, -5)}
{(row,5) (column,8) (test_string, "5") (test_float, 5.8) (test_integer, 5)}
{(row,5) (column,9) (test_string, "5") (test_float, -5.9) (test_integer, -5)}

{(row,6) (column,0) (test_string, "6") (test_float, 6.0) (test_integer, 6)}
{(row,6) (column,1) (test_string, "6") (test_float, -6.1) (test_integer, -6)}
{(row,6) (column,2) (test_string, "6") (test_float, 6.2) (test_integer, 6)}
{(row,6) (column,3) (test_string, "6") (test_float, -6.3) (test_integer, -6)}
{(row,6) (column,4) (test_string, "6") (test_float, 6.4) (test_integer, 6)}
{(row,6) (column,5) (test_string, "6") (test_float, -6.5) (test_integer, -6)}
{(row,6) (column,6) (test_string, "6") (test_float, 6.6) (test_integer, 6)}
{(row,6) (column,7) (test_string, "6") (test_float, -6.7) (test_integer, -6)}
{(row,6) (column,8) (test_string, "6") (test_float, 6.8) (test_integer, 6)}
{(row,6) (column,9) (test_string, "6") (test_float, -6.9) (test_integer, -6)}

{(row,7) (column,0) (test_string, "7") (test_float, 7.0) (test_integer, 7)}
{(row,7) (column,1) (test_string, "7") (test_float, -7.1) (test_integer, -7)}
{(row,7) (column,2) (test_string, "7") (test_float, 7.2) (test_integer, 7)}
{(row,7) (column,3) (test_string, "7") (test_float, -7.3) (test_integer, -7)}
{(row,7) (column,4) (test_string, "7") (test_float, 7.4) (test_integer, 7)}
{(row,7) (column,5) (test_string, "7") (test_float, -7.5) (test_integer, -7)}
{(row,7) (column,6) (test_string, "7") (test_float, 7.6) (test_integer, 7)}
{(row,7) (column,7) (test_string, "7") (test_float, -7.7) (test_integer, -7)}
{(row,7) (column,8) (test_string, "7") (test_float, 7.8) (test_integer, 7)}
{(row,7) (column,9) (test_string, "7") (test_float, -7.9) (test_integer, -7)}

{(row,8) (column,0) (test_string, "8") (test_float, 8.0) (test_integer, 8)}
{(row,8) (column,1) (test_string, "8") (test_float, -8.1) (test_integer, -8)}
{(row,8) (column,2) (test_string, "8") (test_float, 8.2) (test_integer, 8)}
{(row,8) (column,3) (test_string, "8") (test_float, -8.3) (test_integer, -8)}
{(row,8) (column,4) (test_string, "8") (test_float, 8.4) (test_integer, 8)}
{(row,8) (column,5) (test_string, "8") (test_float, -8.5) (test_integer, -8)}
{(row,8) (column,6) (test_string, "8") (test_float, 8.6) (test_integer, 8)}
{(row,8) (column,7) (test_string, "8") (test_float, -8.7) (test_integer, -8)}
{(row,8) (column,8) (test_string, "8") (test_float, 8.8) (test_integer, 8)}
{(row,8) (column,9) (test_string, "8") (test_float, -8.9) (test_integer, -8)}

{(row,9) (column,0) (test_string, "9") (test_float, 9.0) (test_integer, 9)}
{(row,9) (column,1) (test_string, "9") (test_float, -9.1) (test_integer, -9)}
{(row,9) (column,2) (test_string, "9") (test_float, 9.2) (test_integer, 9)}
{(row,9) (column,3) (test_string, "9") (test_float, -9.3) (test_integer, -9)}
{(row,9) (column,4) (test_string, "9") (test_float, 9.4) (test_integer, 9)}
{(row,9) (column,5) (test_string, "9") (test_float, -9.5) (test_integer, -9)}
{(row,9) (column,6) (test_string, "9") (test_float, 9.6) (test_integer, 9)}
{(row,9) (column,7) (test_string, "9") (test_float, -9.7) (test_integer, -9)}
{(row,9) (column,8) (test_string, "9") (test_float, 9.8) (test_integer, 9)}
{(row,9) (column,9) (test_string, "9") (test_float, -9.9) (test_integer, -9)}

** metadata end **
```

Take a look at validate_board_config.md to learn how to make sure the board config has been created correctly.

Some more examples are below:

Multi line board configuration:
```
** board begin **
             1111111111222222222233333333334444444444555555555566666666667
   01234567890123456789012345678901234567890123456789012345678901234567890
 0 .=========.=========.=========.=========.=========.=========.=========.
 1 |         |         |         |         |         |         |         |
 2 |    *    |    *    |    *    |    *    |    *    |    *    |    *    |
 3 |         |         |         |         |         |         |         |
 4 .=========+=========+=========+=========+=========+=========+=========.
 5 |         |         |         |         |         |         |         |
 6 |    *    |    *    |    *    |    *    |    *    |    *    |    *    |
 7 |         |         |         |         |         |         |         |
 8 .=========+=========+=========+=========+=========+=========+=========.
 9 |         |         |         |         |         |         |         |
10 |    *    |    *    |    *    |    *    |    *    |    *    |    *    |
11 |         |         |         |         |         |         |         |
12 .=========+=========+=========+=========+=========+=========+=========.
13 |         |         |         |         |         |         |         |
14 |    *    |    *    |    *    |    *    |    *    |    *    |    *    |
15 |         |         |         |         |         |         |         |
16 .=========+=========+=========+=========+=========+=========+=========.
17 |         |         |         |         |         |         |         |
18 |    *    |    *    |    *    |    *    |    *    |    *    |    *    |
19 |         |         |         |         |         |         |         |
20 .=========+=========+=========+=========+=========+=========+=========.
21 |         |         |         |         |         |         |         |
22 |    *    |    *    |    *    |    *    |    *    |    *    |    *    |
23 |         |         |         |         |         |         |         |
24 .=========.=========.=========.=========.=========.=========.=========.
** board end **


** Define Dimensions of 2D Array Containing Action Tiles (Rows, Columns) **
** array dimensions begin **
(6,7)
** array dimensions end **


** Define Actions Tiles (Map Row Range, Map Column Range, Array Row, Array Column) **
** action tiles begin **
(1-3, 1-9, 0, 0)
(1-3, 11-19, 0, 1)
(1-3, 21-29, 0, 2)
(1-3, 31-39, 0, 3)
(1-3, 41-49, 0, 4)
(1-3, 51-59, 0, 5)
(1-3, 61-69, 0, 6)

(5-7, 1-9, 1, 0)
(5-7, 11-19, 1, 1)
(5-7, 21-29, 1, 2)
(5-7, 31-39, 1, 3)
(5-7, 41-49, 1, 4)
(5-7, 51-59, 1, 5)
(5-7, 61-69, 1, 6)

(9-11, 1-9, 2, 0)
(9-11, 11-19, 2, 1)
(9-11, 21-29, 2, 2)
(9-11, 31-39, 2, 3)
(9-11, 41-49, 2, 4)
(9-11, 51-59, 2, 5)
(9-11, 61-69, 2, 6)

(13-15, 1-9, 3, 0)
(13-15, 11-19, 3, 1)
(13-15, 21-29, 3, 2)
(13-15, 31-39, 3, 3)
(13-15, 41-49, 3, 4)
(13-15, 51-59, 3, 5)
(13-15, 61-69, 3, 6)

(17-19, 1-9, 4, 0)
(17-19, 11-19, 4, 1)
(17-19, 21-29, 4, 2)
(17-19, 31-39, 4, 3)
(17-19, 41-49, 4, 4)
(17-19, 51-59, 4, 5)
(17-19, 61-69, 4, 6)

(21-23, 1-9, 5, 0)
(21-23, 11-19, 5, 1)
(21-23, 21-29, 5, 2)
(21-23, 31-39, 5, 3)
(21-23, 41-49, 5, 4)
(21-23, 51-59, 5, 5)
(21-23, 61-69, 5, 6)

** action tiles end **
```

Irregular line board configuration:
```
** board begin **
             11111111112222222222333333333344
   012345678901234567890123456789012345678901
 0    /========\                /========\   
 1   /          \              /          \  
 2  /            \            /            \ 
 3 /              \          /              \
 4 \              //========\\              /
 5  \            //          \\            / 
 6   \          //            \\          /  
 7    \========//              \\========/   
 8    /========\\              //========\   
 9   /          \\            //          \  
10  /            \\          //            \ 
11 /              \\========//              \
12 \              //========\\              /
13  \            //          \\            / 
14   \          //            \\          /  
15    \========//              \\========/   
16    /========\\              //========\   
17   /          \\            //          \  
18  /            \\          //            \ 
19 /              \\========//              \
20 \              //========\\              /
21  \            //          \\            / 
22   \          //            \\          /  
23    \========//              \\========/   
24    /========\\              //========\   
25   /          \\            //          \  
26  /            \\          //            \ 
27 /              \\========//              \
28 \              //========\\              /
29  \            //          \\            / 
30   \          //            \\          /  
31    \========//              \\========/   
32              \              /             
33               \            /              
34                \          /               
35                 \========/                
** board end **


** Define Dimensions of 2D Array Containing Action Tiles (Rows, Columns) **
** array dimensions begin **
(4,3)
** array dimensions end **


** Define Actions Tiles (Map Row Range, Map Column Range, Array Row, Array Column) **
** action tiles begin **
{
(1, 3-12, 0, 0) (2, 2-13, 0, 0) (3, 1-14, 0, 0) (4, 1-14, 0, 0) (5, 2-13, 0, 0) (6, 3-12, 0, 0) 
}

{
(5, 16-25, 0, 1) (6, 15-26, 0, 1) (7, 14-27, 0, 1) (8, 14-27, 0, 1) (9, 15-26, 0, 1) (10, 16-25, 0, 1)
}

{
(1, 29-38, 0, 2) (2, 28-39, 0, 2) (3, 27-40, 0, 2) (4, 27-40, 0, 2) (5, 28-39, 0, 2) (6, 29-38, 0, 2)
}


{
(9, 3-12, 1, 0) (10, 2-13, 1, 0) (11, 1-14, 1, 0) (12, 1-14, 1, 0) (13, 2-13, 1, 0) (14, 3-12, 1, 0) 
}

{
(13, 16-25, 1, 1) (14, 15-26, 1, 1) (15, 14-27, 1, 1) (16, 14-27, 1, 1) (17, 15-26, 1, 1) (18, 16-25, 1, 1)
}

{
(9, 29-38, 1, 2) (10, 28-39, 1, 2) (11, 27-40, 1, 2) (12, 27-40, 1, 2) (13, 28-39, 1, 2) (14, 29-38, 1, 2)
}


{
(17, 3-12, 2, 0) (18, 2-13, 2, 0) (19, 1-14, 2, 0) (20, 1-14, 2, 0) (21, 2-13, 2, 0) (22, 3-12, 2, 0) 
}

{
(21, 16-25, 2, 1) (22, 15-26, 2, 1) (23, 14-27, 2, 1) (24, 14-27, 2, 1) (25, 15-26, 2, 1) (26, 16-25, 2, 1)
}

{
(17, 29-38, 2, 2) (18, 28-39, 2, 2) (19, 27-40, 2, 2) (20, 27-40, 2, 2) (21, 28-39, 2, 2) (22, 29-38, 2, 2)
}


{
(25, 3-12, 3, 0) (26, 2-13, 3, 0) (27, 1-14, 3, 0) (28, 1-14, 3, 0) (29, 2-13, 3, 0) (30, 3-12, 3, 0) 
}

{
(29, 16-25, 3, 1) (30, 15-26, 3, 1) (31, 14-27, 3, 1) (32, 14-27, 3, 1) (33, 15-26, 3, 1) (34, 16-25, 3, 1)
}

{
(25, 29-38, 3, 2) (26, 28-39, 3, 2) (27, 27-40, 3, 2) (28, 27-40, 3, 2) (29, 28-39, 3, 2) (30, 29-38, 3, 2)
}


** action tiles end **
```