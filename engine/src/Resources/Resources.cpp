#include <pch.h>
#include <Rengine/Resources/Resources.h>

namespace RENGINE{
    template<typename T>
    void defineResourceParameter(T& parameter, const std::string& Resource, const std::string& parameterName)
    {
        ConfigManager*& config = ResourceManager::getResource<ConfigManager>();
        auto& data = config->getContainer("Resources");
        if(data[Resource].type() == nlohmann::json::value_t::object)
        {
            parameter = data["ResourceSettings"][Resource][parameterName];
        }
        else 
        {
            std::string SuperResource = data[Resource];
            parameter = data["ResourceSettings"][SuperResource][parameterName];
        }
    }    
    template void defineResourceParameter<float>(float& parameter, const std::string& Resource, const std::string& parameterName);
    template void defineResourceParameter<std::string>(std::string& parameter, const std::string& Resource, const std::string& parameterName);
}
