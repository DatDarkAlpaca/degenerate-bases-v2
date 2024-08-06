#include "pch.h"
#include "Information.hpp"

#include "Core/Base.hpp"

namespace dgn
{
	Information generateInputInformation(const encoded_sequence& sequence)
	{
		Information information;
		
		for(uint8_t encodedBase : sequence)
		{
			// Quad Base (N):
			if (encodedBase > g_LastTripleBase) 
			{
				information.possibleCombinations *= 4;
				information.degenerateBaseCount += 1;
			}

			// Triple Bases:
			else if (encodedBase > g_LastDualBase) 
			{
				information.possibleCombinations *= 3;
				information.degenerateBaseCount += 1;
			}

			// Dual Bases:
			else if (encodedBase > g_LastNormalBase) 
			{
				information.possibleCombinations *= 2;
				information.degenerateBaseCount += 1;
			}
				
			else
				information.normalBaseCount += 1;
		}

		return information;
	}

	std::uint64_t getPossibleAmountOutputs(const encoded_sequence& sequence)
	{
		std::uint64_t outputs = 1;

		for (uint8_t encodedBase : sequence)
		{
			if (encodedBase > g_LastTripleBase)
				outputs *= 4;

			else if (encodedBase > g_LastDualBase)
				outputs *= 3;
	
			else if (encodedBase > g_LastNormalBase)
				outputs *= 2;
		}

		return outputs;
	}
}