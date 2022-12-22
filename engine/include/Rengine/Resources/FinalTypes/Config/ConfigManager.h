#pragma once
#include <pch.h>


namespace RENGINE 
{
    class ConfigManager
    {
    public:
        ConfigManager()
        {

        }
        virtual ~ConfigManager() {}

        void loadConfig(const std::string& container, const std::string& filePath)
        {
            std::ifstream fileManager(filePath);
            nlohmann::json data = nlohmann::json::parse(fileManager);
            m_Configs.emplace(container, data);
        }
        const nlohmann::json& getContainer(const std::string& container) const
        {
            return m_Configs.at(container);
        }
    private:
        std::unordered_map<std::string, nlohmann::json> m_Configs;

    };
}


