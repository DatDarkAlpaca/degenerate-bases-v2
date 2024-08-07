#pragma once
#include <numeric>
#include <limits>

namespace dgn
{
	struct ChunkData
	{
		enum class ChunkAmount : size_t { AUTO = std::numeric_limits<size_t>::max() };

	public:
		size_t chunkAmount = static_cast<size_t>(ChunkAmount::AUTO);
	};

	inline std::string getChunkAmountString(size_t chunkAmount)
	{
		if (chunkAmount == static_cast<size_t>(ChunkData::ChunkAmount::AUTO))
			return "AUTO";

		return std::to_string(chunkAmount);
	}

	inline size_t getChunkAmountNumber(std::string chunkAmountString)
	{
		if (chunkAmountString == "AUTO")
			return static_cast<size_t>(ChunkData::ChunkAmount::AUTO);

		return std::stoul(chunkAmountString);
	}
}