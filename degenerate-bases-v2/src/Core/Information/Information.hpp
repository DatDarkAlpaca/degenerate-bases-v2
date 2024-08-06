#pragma once
#include <numeric>
#include <string>

#include "Core/Encoding/Encoding.hpp"

namespace dgn
{
	struct Information
	{
		uint8_t normalBaseCount      = 0;
		uint8_t degenerateBaseCount  = 0;
		uint8_t possibleCombinations = 1;
	};

	Information generateInputInformation(const encoded_sequence& sequence);

	std::uint64_t getPossibleAmountOutputs(const encoded_sequence& sequence);
}