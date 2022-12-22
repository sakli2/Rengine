#pragma once
#include <pch.h>
#include "VulkanDefinitions.h"
#include "VkLogicalDevice.h"


namespace RENGINE
{
    namespace VulkanAPI
    {
        class VulkanPhysicalQueueFamily
        {
        public:
            VulkanPhysicalQueueFamily(VkQueueFamilyProperties properties, std::uint32_t queueFamilyIndex);
            
            bool isQueuetype(VulkanQueueSettings::VulkanQueueType type) const;

            std::uint32_t getQueueCount() const;
            std::int32_t getQueueScore() const;
            std::uint32_t getQueueFamilyIndex() const;
            
        private:
            VkQueueFamilyProperties m_Properties;
            std::uint32_t m_QueueFamilyIndex;
        };

        class VulkanPhysicalDevice
        {
        public:
            VulkanPhysicalDevice(VkPhysicalDevice& device);
            ~VulkanPhysicalDevice();

            
            std::unique_ptr<VulkanLogicalDevice> createLogicalDevice(const VulkanLogicalDeviceSettings& settings);

            //device capabilites
            std::uint32_t getScore() const; //TODO implement
            
            //device parameters
            VkPhysicalDeviceProperties getProperties() const;
            VkPhysicalDeviceFeatures getFeatures() const;
            std::vector<VkExtensionProperties> getSupportedExtensions() const;
            std::vector<VulkanPhysicalQueueFamily> getQueueFamilies() const;
        private:
            bool supportsDeviceExtensions(const VulkanLogicalDeviceSettings& settings) const;
            
            VkPhysicalDevice m_PhysicalDevice;
            std::vector<std::uint32_t> m_QueueFamilyUsage;
        };
    }
}