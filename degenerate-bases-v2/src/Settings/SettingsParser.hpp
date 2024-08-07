#pragma once
#include <filesystem>
#include "SettingsData.hpp"

namespace dgn
{
    class ISettingsParser
    {
    public:
        virtual ~ISettingsParser() = default;

    public:
        virtual SettingsData load(const std::filesystem::path& filepath) = 0;

        virtual void save(const SettingsData& config, const std::filesystem::path& filepath) = 0;
    };
}