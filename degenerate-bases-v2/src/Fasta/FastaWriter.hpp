#pragma once
#include <filesystem>
#include <fstream>

#include "Core/Encoding/Encoding.hpp"
#include "Settings/FastaData.hpp"

#include "Utils/Files.hpp"

namespace dgn
{
	class FastaWriter
	{
	public:
		explicit FastaWriter(const FastaData& fastaData)
			: m_FastaData(fastaData)
		{

		}

	public:
		void saveAsBinary(const std::vector<encoded_sequence>& results)
		{
			std::ofstream file(generateFilepathBinary(), std::ios::binary);

			auto resultsSize = results.size();
			file.write(reinterpret_cast<const char*>(&resultsSize), sizeof(uint64_t));

			auto sequenceSize = results[0].size();
			file.write(reinterpret_cast<const char*>(&sequenceSize), sizeof(uint64_t));

			packSequences(results);

			for (const auto& packedByte : packSequences(results))
				file << packedByte;
		}

		void save(const std::vector<encoded_sequence>& results)
		{
			std::ofstream file(generateFilepath());

			size_t index = 0;
			for (const auto& result : results)
			{
				file << m_FastaData.headerCharacter << m_FastaData.headerTemplate << index << '\n';

				for (const auto& base : result)
					file << dgn::g_NibbleToBase[base];

				file << "\n";
				++index;
			}			
		}

	private:
		std::string generateFilepath() const
		{
			return m_FastaData.resultsDirectory
				+ m_FastaData.resultsPrefix + std::to_string(countFilesInFilepath(m_FastaData.resultsDirectory))
				+ "." + m_FastaData.resultsFormat;
		}

		std::string generateFilepathBinary() const
		{
			return m_FastaData.resultsDirectory
				+ m_FastaData.resultsPrefix + std::to_string(countFilesInFilepath(m_FastaData.resultsDirectory))
				+ ".bin";
		}

	private:
		FastaData m_FastaData;
	};
}