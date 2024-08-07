#pragma once
#include "SettingsParser.hpp"
#include "SettingsData.hpp"
#include "Utils/FileJSON.hpp"

namespace dgn
{
	class SettingsParserJSON : public ISettingsParser
	{
	public:
		SettingsData load(const std::filesystem::path& filepath) override
		{
			SettingsData data;

			nlohmann::json jsonObject = ReadJson(filepath);

			data.chunkData = parseChunkData(jsonObject);
			data.fastaData = parseFastaData(jsonObject);;
			data.debugData = parseDebugData(jsonObject);;

			return data;
		}

		void save(const SettingsData& settings, const std::filesystem::path& filepath)
		{
			nlohmann::ordered_json jsonObject;

			jsonObject["Chunk"]["chunk-size"] = getChunkAmountString(settings.chunkData.chunkAmount);

			jsonObject["Fasta"]["header-character"]		= settings.fastaData.headerCharacter;
			jsonObject["Fasta"]["header-template"]		= settings.fastaData.headerTemplate;
			jsonObject["Fasta"]["results-prefix"]		= settings.fastaData.resultsPrefix;
			jsonObject["Fasta"]["results-format"]		= settings.fastaData.resultsFormat;
			jsonObject["Fasta"]["results-directory"]	= settings.fastaData.resultsDirectory;

			jsonObject["Debug"]["debug-enable"]			= settings.debugData.debugEnable;
			jsonObject["Debug"]["generate-report"]		= settings.debugData.generateReport;

			std::ofstream jsonFile(filepath);
			jsonFile << std::setw(4) << jsonObject << std::endl;
		}

	private:
		ChunkData parseChunkData(const nlohmann::json& jsonObject)
		{
			ChunkData data;
			data.chunkAmount = getChunkAmountNumber(jsonObject["Chunk"]["chunk-size"]);

			return data;
		}

		FastaData parseFastaData(const nlohmann::json& jsonObject)
		{
			FastaData data;

			data.headerCharacter = jsonObject["Fasta"]["header-character"];
			data.headerTemplate = jsonObject["Fasta"]["header-template"];
			data.resultsPrefix = jsonObject["Fasta"]["results-prefix"];
			data.resultsFormat = jsonObject["Fasta"]["results-format"];
			data.resultsDirectory = jsonObject["Fasta"]["results-directory"];

			return data;
		}

		DebugData parseDebugData(const nlohmann::json& jsonObject)
		{
			DebugData data;

			data.debugEnable = jsonObject["Debug"]["debug-enable"];
			data.generateReport = jsonObject["Debug"]["generate-report"];

			return data;
		}
	};
}