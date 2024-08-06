#include "pch.h"
#include "Input.hpp"

#include "Core/Base.hpp"

namespace dgn
{
	std::string getUserInput()
	{
		std::string input;
		std::getline(std::cin, input);

		return input;
	}

	std::string dgn::sanitizeInput(std::string_view input)
	{
		std::string result(input);

		// Capitalize:
		std::transform(result.begin(), result.end(), result.begin(), ::toupper);

		// Remove invalid bases:
		result.erase(std::remove_if(result.begin(), result.end(), [](char& c) {
			return !(std::find(g_ValidBases.begin(), g_ValidBases.end(), c) != g_ValidBases.end());
		}), result.end());

		// Convert other empty bases to the default one:
		std::replace(result.begin(), result.end(), '.', g_DefaultEmptyBase);
		std::replace(result.begin(), result.end(), '-', g_DefaultEmptyBase);

		return result;
	}
}