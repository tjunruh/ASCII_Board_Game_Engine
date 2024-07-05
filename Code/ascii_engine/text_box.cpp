#include "text_box.h"
#include "widget_types.h"

text_box::text_box(frame* parent, std::string special_operation) : widget(parent, special_operation)
{
	set_widget_type(TEXTBOX);
}