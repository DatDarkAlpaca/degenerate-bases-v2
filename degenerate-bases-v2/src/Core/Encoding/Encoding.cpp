#include "pch.h"
#include "Encoding.hpp"
#include "Core/Base.hpp"

namespace dgn
{
	encoded_sequence encodeInput(std::string_view input)
	{
		encoded_sequence encoded;

		for (char base : input)
			encoded.push_back(g_BaseToNibble[base]);

		encoded.shrink_to_fit();
		return encoded;
	}
}