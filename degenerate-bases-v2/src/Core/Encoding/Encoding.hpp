#pragma once
#include <numeric>
#include <vector>
#include <string>

#include "Core/Base.hpp"

namespace dgn
{
	using encoded_sequence = std::vector<base_type>;

	encoded_sequence encodeInput(std::string_view input);
}