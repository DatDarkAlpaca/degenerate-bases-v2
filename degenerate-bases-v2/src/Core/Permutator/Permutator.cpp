#include "pch.h"
#include "Permutator.hpp"
#include "Core/Information/Information.hpp"

namespace dgn
{
	static std::vector<encoded_sequence> expandSegment(const dgn::encoded_sequence& segment)
	{
		auto possibleOutputs = dgn::getPossibleAmountOutputs(segment);

		std::vector<encoded_sequence> results;
		std::fill_n(std::back_inserter(results), possibleOutputs, segment);

		for (size_t i = 0; i < possibleOutputs; ++i)
		{
			size_t combinationIndex = i;
			for (size_t j = 0; j < segment.size(); ++j)
			{
				const auto& currentBase = segment[j];
				if (!isDegenerateBase(currentBase))
					continue;

				const auto& possibleBases = g_BaseMap[currentBase];
				results[i][j] = possibleBases[combinationIndex % possibleBases.size()];

				combinationIndex /= possibleBases.size();
			}
		}

		return results;
	}

	std::vector<std::vector<encoded_sequence>> dgn::processSequence(const encoded_sequence& sequence, std::size_t chunkAmount)
	{
		std::vector<std::future<std::vector<encoded_sequence>>> futures;

		std::vector<encoded_sequence> segments = dgn::segmentEncodedSequence(sequence, chunkAmount);
		for (const auto& segment : segments)
			futures.push_back(std::async(std::launch::async, expandSegment, segment));

		std::vector<std::vector<encoded_sequence>> results;
		for (auto& future : futures)
			results.push_back(future.get());

		return results;
	}

	std::vector<encoded_sequence> combineResults(const std::vector<std::vector<encoded_sequence>>& results)
	{
		if (results.empty())
			return {};

		std::vector<encoded_sequence> combined = results[0];

		for (std::size_t i = 1; i < results.size(); ++i)
		{
			std::vector<encoded_sequence> newCombined;

			for (const encoded_sequence& result1 : combined)
			{
				for (const encoded_sequence& result2 : results[i])
				{
					encoded_sequence finalResult = result1;
					finalResult.insert(finalResult.end(), result2.begin(), result2.end());
					newCombined.push_back(finalResult);
				}
			}

			combined = newCombined;
		}

		return combined;
	}
}