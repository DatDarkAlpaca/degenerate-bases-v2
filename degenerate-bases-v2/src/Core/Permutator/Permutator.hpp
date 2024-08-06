#pragma once
#include <future>

#include "Core/Encoding/Encoding.hpp"
#include "Core/Sequence.hpp"
#include "Core/Base.hpp"

namespace dgn
{
	std::vector<std::vector<encoded_sequence>> processSequence(const encoded_sequence& sequence, std::size_t chunkAmount);

	std::vector<encoded_sequence> combineResults(const std::vector<std::vector<encoded_sequence>>& results);
}