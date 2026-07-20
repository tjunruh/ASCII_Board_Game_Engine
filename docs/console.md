# Console API

console is responsible for monitoring user input and reporting events. It handles common operations such as scrolling, dragging, and widget interaction on its own. A console object will only accept widgets from one frame.

# Functions
- [int register_widget(label\* item)](#register_widget)
- [int register_widget(text_box\* item)](#register_widget-1)
- [int register_widget(menu\* item)](#register_widget-2)
- [int register_widget(ascii_board\* item)](#register_widget-3)
- [event run()](#run)

# Member structures

- [event](#struct-event)

---
# Function Descriptions
---
## register_widget
**int register_widget(label\* item)**

**Description:**

adds a label widget to the conole object so that the label will be interactive and report events when console's run function is called

**Parameters:**
1. label\* **item** - pointer to the label object used by console for handling of interaction and events

**Return value:**

int - status that will be:\
      SUCCESS if registered successfully\
      INVALID_VALUE if the widget's parent frame is not the same as the parent frame of other widgets already registerd\
      DUPLICATE_ELEMENT if the widget was already registered

---
## register_widget
**int register_widget(text_box\* item)**

**Description:**

adds a text box widget to the conole object so that the text box will be interactive and report events when console's run function is called

**Parameters:**
1. text_box\* **item** - pointer to the text_box object used by console for handling of interaction and events

**Return value:**

int - status that will be:\
      SUCCESS if registered successfully\
      INVALID_VALUE if the widget's parent frame is not the same as the parent frame of other widgets already registerd\
      DUPLICATE_ELEMENT if the widget was already registered

---
## register_widget
**int register_widget(menu\* item)**

**Description:**

adds a menu widget to the conole object so that the menu will be interactive and report events when console's run function is called

**Parameters:**
1. menu\* **item** - pointer to the menu object used by console for handling of interaction and events

**Return value:**

int - status that will be:\
      SUCCESS if registered successfully\
      INVALID_VALUE if the widget's parent frame is not the same as the parent frame of other widgets already registerd\
      DUPLICATE_ELEMENT if the widget was already registered

---
## register_widget
**int register_widget(ascii_board\* item)**

**Description:**

adds a ascii board widget to the conole object so that the ascii board will be interactive and report events when console's run function is called

**Parameters:**
1. ascii_board\* **item** - pointer to the ascii_board object used by console for handling of interaction and events

**Return value:**

int - status that will be:\
      SUCCESS if registered successfully\
      INVALID_VALUE if the widget's parent frame is not the same as the parent frame of other widgets already registerd\
      DUPLICATE_ELEMENT if the widget was already registered

---
## run
**event run()**

**Description:**

handles scrolling, dragging, and widget interaction with the user for all registered widgets until an event occurs at which point the function returns

**Return value:**

event - event that occured resulting in the function returning so the appropriate action can be taken in response to the event

---
# Member Structure Descriptions
---
## struct event

**Values:**

1. int **widget_id** = -1;
2. int **input** = ascii_io::undefined;
3. int **mouse_x_position** = -1;
4. int **mouse_y_position** = -1;

**Value descriptions:**

1. int **widget_id** - id of the widget that the event applies to
2. int **input** - keystroke that caused the event
3. int **mouse_x_position** - x position of the mouse when the event occured
4. int **mouse_y_position** - y position of the mouse when the event occured
