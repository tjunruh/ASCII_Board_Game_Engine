#pragma once
#include <string>
#include <vector>

class console
{
public:
	friend class frame;
	void display();
private:
	int generate_frame_id();
	int add_frame();
	int set_output(int id, const std::string& output);
	struct frame_info
	{
		int id;
		std::string output = "";
	};
	std::vector<frame_info> frames;
};