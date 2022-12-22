#include <pch.h>

#include "VulkanApi/VulkanDefinitions.h"
#include "VulkanApi/VkManager.h"
#include "VulkanApi/VkPhysicalDevice.h"
#include "VulkanApi/VkLogicalDevice.h"
//#include "VulkanApi/VkQueueFamily.h"
//#include "VulkanApi/VkSurface.h"
//#include "VulkanApi/VkSwapChain.h"

namespace RENGINE
{                                
    struct VulkanRendererSettings
    {
        VulkanRendererSettings(const nlohmann::json settings)
        {
            {
                //VULKAN MANAGER
                managerSettings.debugLvl = VulkanAPI::VulkanManagerSettings::VulkanAPIDebugLvl::debug;//settings["debugLvl"];
                //managerSettings.validationLayers = settings["validationLayers"];
                managerSettings.extensions = {};
                managerSettings.errorFunc = [](const std::string& text) {LOG::error(text);};
                managerSettings.warningFunc = [](const std::string& text) {LOG::warning(text);};
                managerSettings.infoFunc = [](const std::string& text) {LOG::info(text);};
                

            }
            
            {
                //LOGICAL DEVICE
                logicalDeviceSettings.deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
                logicalDeviceSettings.enabledFeatures; //...

                logicalDeviceSettings.queueSettings.resize(1);
                logicalDeviceSettings.queueSettings[0].priority= 1.0f;
                logicalDeviceSettings.queueSettings[0].type = VulkanAPI::VulkanQueueSettings::VulkanQueueType::Graphics;
                //logicalDeviceSettings.queueSettings[0].queueFamilyIndex = 0;
            }
        }


        VulkanAPI::VulkanManagerSettings managerSettings;
        VulkanAPI::VulkanLogicalDeviceSettings logicalDeviceSettings;
    };
}