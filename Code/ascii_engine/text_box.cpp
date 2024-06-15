#include "text_box.h"
#include "widget_types.h"

text_box::text_box(frame* parent) : widget(parent)
{
	set_widget_type(TEXTBOX);
}