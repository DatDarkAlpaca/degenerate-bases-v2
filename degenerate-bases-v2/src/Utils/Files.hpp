#pragma once
#include <filesystem>

namespace dgn
{
	inline size_t countFilesInFilepath(const std::filesystem::path& folderPath)
	{
		using namespace std::filesystem;

		size_t results = 0;
		for (auto const& dir_entry : directory_iterator(folderPath))
			results += 1;

		return results;
	}
}