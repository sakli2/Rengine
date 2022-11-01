#pragma once
#include <pch.h>
#include "VulkanDefinitions.h"

namespace RENGINE
{
    namespace VulkanAPI
    {
        struct VulkanQueueSettings
        {
            enum class VulkanQueueType
            {
                None = 0,
                Graphics = 1,
                Present = 2
            };
            VulkanQueueType type; 
            std::uint32_t queueFamilyIndex;
            float priority;
        };

        class VulkanLogicalDevice
        {
        public:
            VulkanLogicalDevice(const std::vector<VulkanQueueSettings>& queueSettings,VkPhysicalDeviceFeatures enabledFeatures, VulkanPhysicalDevice& device);
            ~VulkanLogicalDevice();
            VulkanLogicalDevice(const VulkanLogicalDevice& device) = delete;
            VulkanLogicalDevice(VulkanLogicalDevice& device) = delete;
            VulkanLogicalDevice& operator=(const VulkanLogicalDevice&) = delete;
            operator VkDevice () {   return m_LogicalDevice; }

            
            VulkanPhysicalDevice& physicalDevice_ptr;
        
        private:
            VkDevice m_LogicalDevice;
            std::vector<VkQueue> m_GraphicsQueue;
            std::vector<VkQueue> m_PresentQueue;
            
        };
    }
}
