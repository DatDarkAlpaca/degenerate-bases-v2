#pragma once
#include <string>

namespace dgn
{
	struct FastaData
	{
		std::string headerCharacter		= ">";
		std::string headerTemplate		= "seq";
		std::string resultsPrefix		= "Result_";
		std::string resultsFormat		= "fas";
		std::string resultsDirectory	= "./results/";
	};
}