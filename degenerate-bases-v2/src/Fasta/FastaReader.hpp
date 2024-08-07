#pragma once
#include <filesystem>
#include <fstream>

namespace dgn
{
	class FastaReader
	{
	public:
		std::vector<encoded_sequence> readBinary(const std::filesystem::path& filepath)
		{
			std::ifstream file(filepath, std::ios::binary);
			
			uint64_t sequenceAmount = 0;
			file.read(reinterpret_cast<char*>(&sequenceAmount), sizeof(uint64_t));

			uint64_t sequenceSize = 0;
			file.read(reinterpret_cast<char*>(&sequenceSize), sizeof(uint64_t));

			std::vector<uint8_t> packedData(sequenceAmount * 2);
			file.read(reinterpret_cast<char*>(packedData.data()), sizeof(uint8_t) * std::pow(2, sequenceAmount / 2));
			
			auto results = unpackSequences(packedData, sequenceSize, sequenceAmount);

			return results;
		}
	};
}