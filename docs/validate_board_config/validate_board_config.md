# validate_board_config

Usage:
```
Executing the binary on the command line will output instructions:

Windows:
.\validate_board_config.exe
You must include the following argument:
[1] Path to text file containing config

Linux:
./validate_board_config.out
You must include the following argument:
[1] Path to text file containing config
```

Look at build_board_config.md to create the board config file. An example of correct validation usage when metadata **is not** included in the config is:
```
Windows:
.\validate_board_config.exe demo_board_config.txt

Linux:
./validate_board_config.out demo_board_config.txt

Output:
Passed: Board begin tag found.
Passed: Board end tag found.
Passed: Array dimensions begin tag found.
Passed: Array dimensions end tag found.
Passed: Action tiles begin tag found.
Passed: Action tiles end tag found.
Failed: Metadata field begin tag is missing or malformed. - ignoring metadata
Missing: ** metadata begin **
Failed: Metadata field end tag is missing or malformed. - ignoring metadata
Missing: ** metadata end **
Passed: Lines of board are the same length.
Passed: Parenthesis validation in dimension field.
Passed: Parenthesis validation in action tiles field.
Passed: Curley brackets validation in action tiles field.
Passed: Correct number of parameters in dimension field parenthesis.
Passed: Correct number of parameters in action tiles field parenthesis.
Passed: Valid parameters in dimension field.
Passed: Valid parameters in action tiles field.
Passed: Valid range using hyphen in action tiles field.
Passed: Array dimensions valid.
Passed: Board dimensions valid.
All validations passed.
```

An example of correct validation usage when metadata **is** included in the config is:
```
Windows:
.\validate_board_config.exe demo_board_config.txt

Linux:
./validate_board_config.out demo_board_config.txt

Output:
Passed: Board begin tag found.
Passed: Board end tag found.
Passed: Array dimensions begin tag found.
Passed: Array dimensions end tag found.
Passed: Action tiles begin tag found.
Passed: Action tiles end tag found.
Passed: Metadata field begin tag found.
Passed: Metadata field end tag found.
Passed: Lines of board are the same length.
Passed: Parenthesis validation in dimension field.
Passed: Parenthesis validation in action tiles field.
Passed: Curley brackets validation in action tiles field.
Passed: Correct number of parameters in dimension field parenthesis.
Passed: Correct number of parameters in action tiles field parenthesis.
Passed: Valid parameters in dimension field.
Passed: Valid parameters in action tiles field.
Passed: Parenthesis validation in metadata field.
Passed: Curly brackets validation in metadata field.
Passed: Correct number of parameters in metadata field parenthesis.
Passed: Valid parameters in metadata field.
Passed: Valid range using hyphen in action tiles field.
Passed: Array dimensions valid.
Passed: Board dimensions valid.
All validations passed.
```

If there are any errors in validation, output will state what case failed, the line number of the field where the error occurred, and the content of the line where the error occurred.