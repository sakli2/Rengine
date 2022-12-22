#pragma once
#include <pch.h>
#include "VulkanDefinitions.h"
#include "VkPhysicalDevice.h"



namespace RENGINE
{
    namespace VulkanAPI
    {

        //VulkanManager
        struct VulkanManagerSettings
        {
            enum class VulkanAPIDebugLvl
            {
                none = -1,
                performance = 0,
                debug = 1,
                debug_all = 2
            };
            VulkanAPIDebugLvl debugLvl;
            std::vector<const char*> validationLayers;
            std::vector<const char*> extensions;

            std::function<void(const std::string&)> infoFunc;
            std::function<void(const std::string&)> warningFunc;
            std::function<void(const std::string&)> errorFunc;
        };
        

        class VulkanManager
        {
        public:
            VulkanManager(VulkanManagerSettings& settings);
            ~VulkanManager();


            //member functions
            std::vector<VulkanPhysicalDevice> getPhysicalDevices();
            const VulkanManagerSettings& getCurrentSettings() const;
            
        private:
            void setDebugLvl(VkDebugUtilsMessengerCreateInfoEXT* debug_info);
            void checkValidationLayerSupport();

            VkInstance m_VKinstance;
            VkDebugUtilsMessengerEXT m_DebugManager;
            VulkanManagerSettings& m_Settings;
        };

        std::unique_ptr<VulkanManager> createVulkanManager(VulkanManagerSettings& settings);
    }
}