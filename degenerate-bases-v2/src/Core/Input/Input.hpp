#pragma once
#include <string>

namespace dgn
{
	std::string getUserInput();

	std::string sanitizeInput(std::string_view input);
}