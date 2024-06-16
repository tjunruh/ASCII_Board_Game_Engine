#include "text_box.h"
#include "widget_types.h"

text_box::text_box(frame* parent, int row, int column) : widget(parent, row, column)
{
	set_widget_type(TEXTBOX);
}