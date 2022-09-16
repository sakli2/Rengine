#pragma once
#include <pch.h>
#include <Rengine/SettingsManager/ConfigManager.h>
#include <Rengine/Resources/ResourceManager.h>

#ifndef CONFIG_PATH
#define CONFIG_PATH "/home/szabi/Desktop/Rengine/engine/configs/example.config"
#endif

#define CREATE_RESOURCE(ResourceName, BaseResource)                                                 \
class ResourceName;                                                                                 \
namespace BaseResource##_##ResourceName                                                             \
{                                                                                                   \
    static bool init()                                                                              \
    {                                                                                               \
        ConfigManager::loadConfig(CONFIG_PATH);                                                     \
        if(ConfigManager::getValue<std::string>("Resources", #BaseResource) == #ResourceName) {     \
            ResourceManager::provideResources<ResourceName>();                                      \
        }                                                                                           \
        return 0;                                                                                   \
    }                                                                                               \
    inline bool b = init();                                                                         \
}                                                                                                   \
                                                                                                    \
class ResourceName : public BaseResource                
