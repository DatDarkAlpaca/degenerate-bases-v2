#pragma once
#include <filesystem>
#include <memory>

#include "SettingsData.hpp"
#include "SettingsParser.hpp"

namespace dgn
{
	class SettingsSystem
	{
	public:
		explicit SettingsSystem(const std::filesystem::path& configFilepath)
			: m_ConfigFilepath(configFilepath)
		{

		}

		SettingsSystem() = default;

	public:
		void initialize(std::unique_ptr<ISettingsParser> configParser)
		{
			setParser(std::move(configParser));

			if (!std::filesystem::exists(m_ConfigFilepath))
				save();

			load();
		}

	public:
		void load()
		{
			m_Settings = m_SettingsParser->load(m_ConfigFilepath);
		}

		void save()
		{
			m_SettingsParser->save(m_Settings, m_ConfigFilepath);
		}

	public:
		void setFilepath(const std::filesystem::path& filepath)
		{
			m_ConfigFilepath = filepath;
		}

		void setParser(std::unique_ptr<ISettingsParser> parser)
		{
			m_SettingsParser = std::move(parser);
		}

	public:
		const SettingsData& settings() const { return m_Settings; }

		SettingsData& settings() { return m_Settings; }

	private:
		std::filesystem::path m_ConfigFilepath;
		std::unique_ptr<ISettingsParser> m_SettingsParser;
		SettingsData m_Settings;
	};
}