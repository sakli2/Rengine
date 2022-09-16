#pragma once
#include <pch.h>

#define CONFIG_PARAMETER(VALUE) \
float f; \
ConfigManager::declareValue(f, "asd");

namespace RENGINE 
{
    class ConfigManager
    {
        public:
            ConfigManager() = default;
            ~ConfigManager() = default;
            static void loadConfig(const std::string& filePath);
            
            template<typename T> 
            inline static T getValue(const std::string& title, const std::string& variable)
            {
                return std::get<std::unordered_map<std::string, std::unordered_map<std::string, T>>>(s_Configs()).at(title).at(variable);
            }

            template<typename T> 
            inline static void declareValue(T& value, const std::string& variable)
            {
                //std::cout << location << std::endl;
                //value = std::get<std::unordered_map<std::string, std::unordered_map<std::string, T>>>(s_Configs()).at(title).at(variable);
            }
        private:
            inline static std::string getBracketInside(const std::string& inside);

            using floatHolder = std::unordered_map<std::string, std::unordered_map<std::string, float>>;
            using stringHolder = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;
            static std::tuple<floatHolder,stringHolder>& s_Configs() {static std::tuple<floatHolder,stringHolder> instance; return instance;}
            static std::string& s_filePath() {static std::string instance; return instance;}
    };
}