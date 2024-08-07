#pragma once
#include "FastaData.hpp"
#include "ChunkData.hpp"
#include "DebugData.hpp"

namespace dgn
{
	struct SettingsData
	{
		FastaData fastaData;
		ChunkData chunkData;
		DebugData debugData;
	};
}