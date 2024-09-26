#pragma once
#include <string>
#include <vector>

struct expected_display_data
{
	std::string output = "";
	const std::vector<int> x_origins;
	const std::vector<int> y_origins;
	const std::vector<unsigned int> widths;
	const std::vector<unsigned int> heights;
	const std::vector<unsigned int> widths_with_spacing;
	const std::vector<unsigned int> heights_with_spacing;
};
