#include "pch.h"
#include "Core/Permutator/Permutator.hpp"

#include "Core/Information/Information.hpp"
#include "Core/Input/Input.hpp"

#include "Settings/SettingsSystem.hpp"
#include "Settings/SettingsParserJSON.hpp"

#include "Fasta/FastaWriter.hpp"

int main()
{
	using namespace dgn;

	// Settings:
	SettingsSystem settings("settings.json");
	settings.initialize(std::make_unique<SettingsParserJSON>());

	const auto& chunkData = settings.settings().chunkData;
	const auto& fastaSettings = settings.settings().fastaData;
	const auto& debugData = settings.settings().debugData;

	// Directory preparation:
	if (!std::filesystem::is_directory(fastaSettings.resultsDirectory))
		std::filesystem::create_directory(fastaSettings.resultsDirectory);

	bool running = true;
	while (running)
	{
		std::cout << "> ";

		std::string userInput = getUserInput();

		if (userInput == "quit")
			return 0;

		// Base Input:
		std::string sanitizedInput = sanitizeInput(userInput);
		if (sanitizedInput.empty())
		{
			std::cerr << "Invalid sequence input.\n\n";
			continue;
		}

		encoded_sequence encodedInput = encodeInput(sanitizedInput);

		// Information gathering:
		Information sequenceInfo = generateInputInformation(encodedInput);

		// Chunk size:
		size_t usedChunkAmount = chunkData.chunkAmount;
		if (chunkData.chunkAmount == static_cast<size_t>(ChunkData::ChunkAmount::AUTO))
			usedChunkAmount = std::thread::hardware_concurrency();

		// Sequence processing:
		auto start = std::chrono::high_resolution_clock::now();

		auto splitResults = processSequence(encodedInput, usedChunkAmount);
		auto results = combineResults(splitResults);

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;

		std::cout << "Elapsed time: " << duration.count() * 1000 << " ms" << '\n';
		std::cout << "Results: " << results.size() << "x\n";

		std::cout << "\n";

		// Sequence writing:
		FastaWriter writer(fastaSettings);
		writer.save(results);
		writer.saveAsBinary(results);
	}
}