# controls API

controls is an object that maps a control name to an ascii code and can save a controls configuration to file or load controls configuration from file. ascii_io contains ascii codes. Public member functions of controls include:

```
int bind(const std::string& control_name, const int key)
void force_bind(const std::string& control_name, const int key)
int unbind(const std::string& control_name)
int get_key(const std::string& control_name)
int load_controls(const std::string& file_path)
int save_controls(const std::string& file_path)
void set_select_keys(const std::vector<int>& select_keys)
std::vector<int> get_select_keys()
bool key_in_select_keys(const int key)
```

---
# Function Descriptions
---
## bind
**int bind(const std::string& control_name, const int key)**
```
Description:
maps an ascii code representing a keyboard stroke to be identified by a name

Parameters:
const std::string& control_name - name to be used to identify the ascii code
const int key - ascii code to be bound to control_name identifier

Return value:
int - status code that will be SUCCESS if binding is successful or DUPLICATE_ELEMENT if control_name already exists
```

## force_bind
**void force_bind(const std::string& control_name, const int key)**
```
Description:
maps an ascii code representing a keyboard stroke to be idnetified by a name (will overwrite binding if one control_name already exists)

Parameters:
const std::string& control_name - name to be used to identify the ascii code
const int key - ascii code to be bound to control_name identifier
```

---
## unbind
**int unbind(const std::string& control_name)**
```
Description:
unmaps the ascii code from the control name and then deletes the control name from internal data

Parameters:
const std::string& control_name - name to have the ascii code unmapped from and then deleted

Return value:
int - status code that will be SUCCESS if unbinding is successful or ELEMENT_NOT_FOUND if control_name cannot be found in internal data
```

---
## get_key
**int get_key(const std::string& control_name)**
```
Description:
returns the ascii code mapped to a control name

Parameters:
const std::string& control_name - name of the control to retrive the mapped ascii code

Return value:
int - ascii code mapped to the control name (will be ascii_io::undefined if control_name is not found)
```

---
## load_controls
**int load_controls(const std::string& file_path)**
```
Description:
loads control names and the ascii codes mapped to them from file

Parameters:
const std::string& file_path - absolute or relative path to file holding control data

Return value:
int - status code that will be SUCCESS if loading is successful and INVALID_PATH if the file cannot be loaded
```

---
## save_controls
**int save_controls(const std::string& file_path)**
```
Description:
saves control names and the ascii codes mapped to them to a file

Parameters:
const std::string& file_path - absolute or relative path to file that should contain the saved control data

Return value:
int - status code that will be SUCCESS if saving to file is successful and INVALID_PATH if the file cannot be saved
```

---
## set_select_keys
**void set_select_keys(const std::vector<int>& select_keys)**
```
Description:
used to define multiple keys for selection in frame and widgets

Parameters:
consts std::vector<int>& select_keys - vector containing selection keys
```

---
## get_select_keys
**std::vector<int> get_select_keys()**
```
Description:
returns vector containing selection keys

Return value:
std::vector<int> - vector containg selection keys
```

---
##
**bool key_in_select_keys(const int key)**
```
Description:
used to determine if a key is a selection key

Return value:
bool - true if key is in selection keys and false if it is not
```

---
# Control Names Used by Frame and Widgets
---
## namespace control_names
```
const std::string up = "up"
const std::string down = "down"
const std::string right = "right"
const std::string left = "left"
const std::string select = "select"
const std::string quit = "quit
```