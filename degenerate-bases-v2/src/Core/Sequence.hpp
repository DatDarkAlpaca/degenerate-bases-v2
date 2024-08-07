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

	inline std::vector<uint8_t> packSequence(const encoded_sequence& sequence)
	{
		std::vector<uint8_t> packedData;

		for (size_t i = 0; i < sequence.size(); i += 2)
		{
			uint8_t packedByte = sequence[i] << 4;

			if (i + 1 < sequence.size())
				packedByte |= sequence[i + 1];

			packedData.push_back(packedByte);
		}

		return packedData;
	}

	inline std::vector<uint8_t> packSequences(const std::vector<encoded_sequence>& sequences)
	{
		std::vector<uint8_t> packedData;

		encoded_sequence masterSequence;
		masterSequence.reserve(sequences.size() * sequences[0].size());
		for (size_t i = 0; i < sequences.size(); ++i)
		{
			for (size_t j = 0; j < sequences[i].size(); ++j)
				masterSequence.push_back(sequences[i][j]);
		}

		return packSequence(masterSequence);
	}

	inline std::vector<uint8_t> unpackBase(uint8_t& base)
	{
		std::vector<uint8_t> unpackedBases;

		unpackedBases.push_back(base >> 4);
		unpackedBases.push_back(base & 0x0F);

		return unpackedBases;
	}

	inline encoded_sequence unpackSequence(const std::vector<uint8_t>& packedData)
	{
		encoded_sequence unpackedSequence;

		for (uint8_t packedByte : packedData) 
		{
			unpackedSequence.push_back(packedByte >> 4);
			unpackedSequence.push_back(packedByte & 0x0F);
		}

		return unpackedSequence;
	}

	inline std::vector<encoded_sequence> unpackSequences(const std::vector<uint8_t>& packedData, uint64_t sequenceSize, uint64_t sequenceAmount)
	{
		encoded_sequence unpackedSequence;

		size_t iterator = 0;
		for (uint8_t packedByte : packedData)
		{
			if (iterator >= sequenceAmount * sequenceSize / 2)
				break;

			unpackedSequence.push_back(packedByte >> 4);
			unpackedSequence.push_back(packedByte & 0x0F);

			++iterator;
		}

		iterator = 0;

		encoded_sequence sequence;
		std::vector<encoded_sequence> results;
		for (uint8_t unpackedByte : unpackedSequence)
		{
			if (iterator == sequenceSize)
			{
				results.push_back(sequence);

				iterator = 0;
				sequence.clear();
			}

			sequence.push_back(unpackedByte);
			++iterator;
		}

		if(!sequence.empty())
			results.push_back(sequence);

		return results;
	}
}