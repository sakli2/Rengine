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
            float priority;
        };

        struct VulkanLogicalDeviceSettings
        {
            std::vector<const char*> deviceExtensions;
            VkPhysicalDeviceFeatures enabledFeatures;
            std::vector<VulkanQueueSettings> queueSettings;
        };

        class VulkanLogicalDevice
        {
        public:
            VulkanLogicalDevice(VkDevice logicalDevice, std::unordered_map<VulkanQueueSettings::VulkanQueueType, std::vector<VkQueue>>&& queues);
            ~VulkanLogicalDevice();
        
        private:
            VkDevice m_LogicalDevice;
            std::unordered_map<VulkanQueueSettings::VulkanQueueType, std::vector<VkQueue>> m_Queues;
        };
    }
}
