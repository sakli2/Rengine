#include <pch.h>
#include "VkQueueFamily.h"

namespace RENGINE
{
    namespace VulkanAPI
    {
        VulkanQueueFamily::VulkanQueueFamily(VkQueueFamilyProperties properties)
            :m_Properties(properties)
        {
        }
        VulkanQueueFamily::~VulkanQueueFamily()
        {

        }

        VulkanQueueFamily::VulkanQueueFamily(VulkanQueueFamily&& queueFamily)
            :m_Properties(queueFamily.m_Properties)
        {
        }

        std::uint32_t VulkanQueueFamily::getQueueCount() const
        {
            return m_Properties.queueCount;
        }
        VkQueueFlags VulkanQueueFamily::getQueueflags() const
        {
            return m_Properties.queueFlags;
        }

        bool VulkanQueueFamily::hasGraphicsBit() const
        {
            return m_Properties.queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT;
        }

        bool VulkanQueueFamily::hasComputeBit() const
        {
            return m_Properties.queueFlags & VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT;
        }
        bool VulkanQueueFamily::hasPresentBit() const
        {
            //VkBool32 presentSupport = false;
            //vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
            //m_Properties.queueCount
            ////vkGetPhysicalDeviceSurfaceSupportKHR()
            return false;
        }


    }
}
