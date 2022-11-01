#pragma once
#include <pch.h>


//ADD RESOURCES HERE
#include "log/ConsoleLogger.h"
#include "log/ColoredConsoleLogger.h"
#include "window/GLFW_window.h"



namespace RENGINE
{
    void loadBaseResources(const std::string& filePath)
    {
        ConfigManager::loadConfig(filePath);

        for(auto initializer : *RENGINE::s_ResourceProviders)
            initializer();
        ResourceManager::checkResourceState();
        delete RENGINE::s_ResourceProviders;
    }
}