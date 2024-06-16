#include "console.h"
#include "ascii_io.h"

void console::display()
{
	std::string output = "";
	for (unsigned int i = 0; i < frames.size(); i++)
	{
		output = output + frames[i].output;
		if (i < (frames.size() - 1))
		{
			output = output + "\n";
		}
	}
	ascii_io::clear();
	ascii_io::print(output);
}

int console::generate_frame_id()
{
	int id = frames.size();
	return id;
}

int console::add_frame()
{
	int id = generate_frame_id();
	frame_info new_frame;
	new_frame.id = id;
	frames.push_back(new_frame);
	return id;
}

int console::set_output(int id, const std::string& output)
{
	int status = 1;
	for (unsigned int i = 0; i < frames.size(); i++)
	{
		if (frames[i].id == id)
		{
			frames[i].output = output;
			status = 0;
			break;
		}
	}
	return status;
}