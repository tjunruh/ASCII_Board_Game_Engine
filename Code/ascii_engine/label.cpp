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

int label::start_logging(const std::string& file_path)
{
	int status = log.start_widget_logging(file_path, get_widget_type());
	return status;
}

void label::stop_logging()
{
	log.stop_widget_logging();
}