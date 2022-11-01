#pragma once
#include <pch.h>
#include "VulkanDefinitions.h"



namespace RENGINE
{
    namespace VulkanAPI
    {

        class VulkanPhysicalDevice
        {
        public:
            VulkanPhysicalDevice(const VkPhysicalDevice device, VulkanManager& manager);
            ~VulkanPhysicalDevice();
            VulkanPhysicalDevice(VulkanPhysicalDevice&& device);
            VulkanPhysicalDevice(const VulkanPhysicalDevice& device) = delete;
            VulkanPhysicalDevice(VulkanPhysicalDevice& device) = delete;
            VulkanPhysicalDevice& operator=(const VulkanPhysicalDevice&) = delete;

            //create New data
            VulkanLogicalDevice createLogicalDevice(const std::vector<VulkanQueueSettings>& queueSettings, VkPhysicalDeviceFeatures& enabledFeatures);

            //device capabilites
            std::uint32_t getScore() const; //TODO implement
            bool supportsDeviceExtensions() const;
            
            //device parameters
            VkPhysicalDeviceProperties getProperties() const;
            VkPhysicalDeviceFeatures getFeatures() const;
            std::vector<VulkanQueueFamily> getQueueFamilies() const;
            std::vector<VkExtensionProperties> getSupportedExtensions() const;

            //device queue indecies
            std::uint32_t getGraphicsQueueIndex() const;
            std::uint32_t getPresentQueueIndex(VulkanSurface& windowSurface) const;
            
            const VulkanManager& getManager() const;

            operator VkPhysicalDevice () { return m_PhysicalDevice; }
            VulkanManager& manager_ptr;
        private:
            VkPhysicalDevice m_PhysicalDevice;
            std::vector<std::uint32_t> m_QueueFamilyUsage;
        };
    }
}