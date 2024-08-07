#pragma once
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

namespace dgn
{
	inline nlohmann::json ReadJson(const std::filesystem::path& filepath)
	{
		using namespace nlohmann;

		std::ifstream file(filepath);
		return json::parse(file);
	}
}