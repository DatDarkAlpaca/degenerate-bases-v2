#include "pch.h"
#include "Core/Permutator/Permutator.hpp"

#include "Core/Information/Information.hpp"
#include "Core/Input/Input.hpp"

int main()
{
	std::size_t chunkAmount = std::thread::hardware_concurrency();

	while (true)
	{
		// Input processing:
		std::string userInput = dgn::getUserInput();
		std::string sanitizedInput = dgn::sanitizeInput(userInput);

		if (sanitizedInput.empty())
			std::cerr << "Invalid sequence input.\n";
		
		auto encodedInput = dgn::encodeInput(sanitizedInput);

		// Information gathering:
		dgn::Information sequenceInfo = dgn::generateInputInformation(encodedInput);

		// Sequence processing:
		auto start = std::chrono::high_resolution_clock::now();

		auto splitResults = dgn::processSequence(encodedInput, chunkAmount);
		auto results = dgn::combineResults(splitResults);

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		std::cout << "Elapsed time: " << duration.count() * 1000 << " ms" << '\n';
		std::cout << "Results: " << results.size() << "x\n";

	/*	for (auto r : results)
		{
			for(auto x : r)
				std::cout << dgn::g_NibbleToBase[x];
			std::cout << '\n';
		}	*/	
	}
}