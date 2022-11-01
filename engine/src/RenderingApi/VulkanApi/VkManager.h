#pragma once
#include <pch.h>
#include "VulkanDefinitions.h"
#include "VkPhysicalDevice.h"

namespace RENGINE
{
    namespace VulkanAPI
    {
        class VulkanManager
        {
        public:
            VulkanManager(RenderAPIDebugLvl debug_lvl);
            ~VulkanManager();
            VulkanManager(VulkanManager&) = delete;
            VulkanManager & operator=(const VulkanManager&) = delete;

            //actual functions
            std::vector<VulkanPhysicalDevice> listPhysicalDevices();
            const std::vector<const char*>& getValidationLayers() const;
            const std::vector<const char*>& getExtensions() const;
            const std::vector<const char*>& getDeviceExtensions() const;
            
            operator VkInstance() const {  return m_VKinstance; }
            operator VkInstance() {  return m_VKinstance; }
        private:
            void setDebugLvl(RenderAPIDebugLvl debug_lvl, VkDebugUtilsMessengerCreateInfoEXT* debug_info);
            void checkValidationLayerSupport();

            VkInstance m_VKinstance;
            VkDebugUtilsMessengerEXT m_DebugManager;
            RenderAPIDebugLvl m_DebugLvl;

            std::vector<const char*> m_vkValidationLayers;
            std::vector<const char*> m_vkExtensions;
            std::vector<const char*> m_vkDeviceExtensions;
        };
    }
}