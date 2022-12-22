#pragma once
#include <pch.h>
#include <Rengine/Resources/ResourceManager.h>

//ADD RESOURCES HERE
#include "Logger/ConsoleLogger.h"
#include "Logger/ColoredConsoleLogger.h"
#include "Window/GLFW_window.h"
#include "Renderer/VulkanRenderer/VulkanRenderer.h"


namespace RENGINE
{
    void loadBaseResources(const std::string& filePath)
    {
        //Add config for initializers
        ResourceManager::provideResources<ConfigManager>();
        ResourceManager::getResource<ConfigManager>()->loadConfig("Resources" ,filePath);

        for(auto initializer : *RENGINE::s_ResourceProviders)
            initializer();
        ResourceManager::checkResourceState();
        delete RENGINE::s_ResourceProviders;
    }
}