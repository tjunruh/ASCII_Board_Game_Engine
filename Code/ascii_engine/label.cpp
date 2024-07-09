#include "label.h"
#include "widget_types.h"

label::label(frame* parent, std::string special_operation) : widget(parent, special_operation)
{
	set_widget_type(LABEL);
}

void label::set_output(const std::string& output)
{
	set_output_to_frame(output);
}