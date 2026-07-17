# action_tile_pattern_maker binary

Filling out action tiles by hand in large board configs can be tedious. The action_tile_pattern_maker binary can make things easier by taking in an action tile configuration and outputing a pattern from that configuration. For example, a single action tile could be defined for a board config and the pattern maker could generate the action tile configuration for the entire row assuming all action tiles in that row are the same shape and size.

Usage:

```
Executing the binary on the command line will output instructions:
Windows:
.\action_tile_pattern_maker.exe
You must include the following arguments:
[1] Path to text_file constaining action tile pattern
[2] row increment
[3] column incrmeent
[4] array row increment
[5] array column incrment
[6] number of times for the pattern to repeat

Linux:
./action_tile_pattern_maker.out
You must include the following arguments:
[1] Path to text_file constaining action tile pattern
[2] row increment
[3] column incrmeent
[4] array row increment
[5] array column incrment
[6] number of times for the pattern to repeat
```

Say we want to create action tiles for this example board config:
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
(,)
** array dimensions end **


** Define Actions Tiles (Map Row Range, Map Column Range, Array Row, Array Column) **
** action tiles begin **
(,,,)
  .
  .
  .
** action tiles end **
```

First, create this example input file contents containg the action tile for the top left board tile:
```
action_tiles.txt:
(1,1-3,0,0)
```

Run the input file through the pattern maker to generate the action tiles for the whole row.
```
Windows:
.\action_tile_pattern_maker action_tiles.txt 0 4 0 1 9

Linux:
./action_tile_pattern_maker action_tiles.txt 0 4 0 1 9
```

The file containing the pattern will have the same name as the input file plus "_pattern" added to the end. Its contents in this case will be:
```
action_tiles_pattern.txt:
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
```

Now, use the pattern maker to generate all the rows for the board config. Put the configuration for the first row in the input file:
```
action_tiles.txt:
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
```

Run it through the pattern maker:
```
Windows:
.\action_tile_pattern_maker action_tiles.txt 2 0 1 0 9

Linux:
./action_tile_pattern_maker action_tiles.txt 2 0 1 0 9
```

The output file will contain:
```
action_tiles_pattern.txt:
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


(3,1-3,1,0) (3,5-7,1,1) (3,9-11,1,2) (3,13-15,1,3) (3,17-19,1,4) (3,21-23,1,5) (3,25-27,1,6) (3,29-31,1,7) (3,33-35,1,8) (3,37-39,1,9) 
(5,1-3,2,0) (5,5-7,2,1) (5,9-11,2,2) (5,13-15,2,3) (5,17-19,2,4) (5,21-23,2,5) (5,25-27,2,6) (5,29-31,2,7) (5,33-35,2,8) (5,37-39,2,9) 
(7,1-3,3,0) (7,5-7,3,1) (7,9-11,3,2) (7,13-15,3,3) (7,17-19,3,4) (7,21-23,3,5) (7,25-27,3,6) (7,29-31,3,7) (7,33-35,3,8) (7,37-39,3,9) 
(9,1-3,4,0) (9,5-7,4,1) (9,9-11,4,2) (9,13-15,4,3) (9,17-19,4,4) (9,21-23,4,5) (9,25-27,4,6) (9,29-31,4,7) (9,33-35,4,8) (9,37-39,4,9) 
(11,1-3,5,0) (11,5-7,5,1) (11,9-11,5,2) (11,13-15,5,3) (11,17-19,5,4) (11,21-23,5,5) (11,25-27,5,6) (11,29-31,5,7) (11,33-35,5,8) (11,37-39,5,9) 
(13,1-3,6,0) (13,5-7,6,1) (13,9-11,6,2) (13,13-15,6,3) (13,17-19,6,4) (13,21-23,6,5) (13,25-27,6,6) (13,29-31,6,7) (13,33-35,6,8) (13,37-39,6,9) 
(15,1-3,7,0) (15,5-7,7,1) (15,9-11,7,2) (15,13-15,7,3) (15,17-19,7,4) (15,21-23,7,5) (15,25-27,7,6) (15,29-31,7,7) (15,33-35,7,8) (15,37-39,7,9) 
(17,1-3,8,0) (17,5-7,8,1) (17,9-11,8,2) (17,13-15,8,3) (17,17-19,8,4) (17,21-23,8,5) (17,25-27,8,6) (17,29-31,8,7) (17,33-35,8,8) (17,37-39,8,9) 
(19,1-3,9,0) (19,5-7,9,1) (19,9-11,9,2) (19,13-15,9,3) (19,17-19,9,4) (19,21-23,9,5) (19,25-27,9,6) (19,29-31,9,7) (19,33-35,9,8) (19,37-39,9,9) 
```

Now all the action tiles for the board have been defined. Copy and paste them into the board config and format as desired:
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
