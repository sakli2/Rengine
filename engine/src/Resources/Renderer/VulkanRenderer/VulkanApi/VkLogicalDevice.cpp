#include <pch.h>
#include "VkLogicalDevice.h"
#include "VkPhysicalDevice.h"
#include "VkManager.h"
#include "Rengine/Resources/ResourceManager.h"

namespace RENGINE
{
    namespace VulkanAPI
    {
        VulkanLogicalDevice::VulkanLogicalDevice(VkDevice logicalDevice, std::unordered_map<VulkanQueueSettings::VulkanQueueType, std::vector<VkQueue>>&& queues)
            :m_LogicalDevice(logicalDevice), m_Queues(queues)
        {
            
        }

    
        VulkanLogicalDevice::~VulkanLogicalDevice()
        {
            vkDestroyDevice(m_LogicalDevice, nullptr);
        }
    }
}