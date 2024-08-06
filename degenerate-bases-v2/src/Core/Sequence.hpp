#pragma once
#include "Core/Encoding/Encoding.hpp"
#include "Core/Base.hpp"

namespace dgn
{
	inline std::vector<encoded_sequence> segmentEncodedSequence(const encoded_sequence& sequence, std::size_t chunkAmount)
	{
		size_t actualChunkAmount = std::min(chunkAmount, sequence.size());

		std::vector<encoded_sequence> segments;
		segments.reserve(actualChunkAmount);

		for (size_t i = 0; i < sequence.size(); i += actualChunkAmount)
		{
			size_t end = std::min(i + actualChunkAmount, sequence.size());

			encoded_sequence chunk(sequence.begin() + i, sequence.begin() + end);
			segments.push_back(std::move(chunk));
		}

		return segments;
	}
}