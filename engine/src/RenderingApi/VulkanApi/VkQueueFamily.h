#pragma once
#include <pch.h>
#include "VulkanDefinitions.h"

namespace RENGINE
{
    namespace VulkanAPI
    {
        class VulkanQueueFamily
        {
        public:
            VulkanQueueFamily(VkQueueFamilyProperties properties);
             ~VulkanQueueFamily();
            VulkanQueueFamily(VulkanQueueFamily&& queueFamily);
            VulkanQueueFamily(const VulkanQueueFamily& device) = delete;
            VulkanQueueFamily(VulkanQueueFamily& device) = delete;
            VulkanQueueFamily& operator=(const VulkanQueueFamily&) = delete;

            std::uint32_t getQueueCount() const;
            VkQueueFlags getQueueflags() const;
            bool hasGraphicsBit() const;
            bool hasComputeBit() const;
            bool hasPresentBit() const;
            
        private:
            VkQueueFamilyProperties m_Properties;
        };
    }
}