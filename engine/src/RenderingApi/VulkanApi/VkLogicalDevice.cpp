#include <pch.h>
#include "VkLogicalDevice.h"
#include "VkPhysicalDevice.h"
#include "VkManager.h"
#include "Rengine/Resources/ResourceManager.h"

namespace RENGINE
{
    namespace VulkanAPI
    {
        VulkanLogicalDevice::VulkanLogicalDevice(const std::vector<VulkanQueueSettings>& queueSettings, VkPhysicalDeviceFeatures enabledFeatures, VulkanPhysicalDevice& physicalDevice)
            :physicalDevice_ptr(physicalDevice)
        {

            //TODO
            //GET ALL QUEUES AND MAKE METHODS TO GET REFERENCES OF RENDER/TRANSFER/COMPUTE QUEUE
            std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
            for (VulkanQueueSettings setting: queueSettings)
            {
                VkDeviceQueueCreateInfo queueCreateInfo{};
                queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfo.queueFamilyIndex = setting.queueFamilyIndex;
                queueCreateInfo.queueCount = 1;
                queueCreateInfo.pQueuePriorities = &setting.priority;
                queueCreateInfos.push_back(queueCreateInfo);
            }


            
            VkDeviceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            createInfo.pQueueCreateInfos = queueCreateInfos.data();
            createInfo.queueCreateInfoCount = queueCreateInfos.size();

            createInfo.pEnabledFeatures = &enabledFeatures;

            createInfo.ppEnabledExtensionNames = physicalDevice_ptr.getManager().getDeviceExtensions().data();
            createInfo.enabledExtensionCount = physicalDevice_ptr.getManager().getDeviceExtensions().size(); 

            createInfo.enabledLayerCount = physicalDevice_ptr.getManager().getValidationLayers().size();
            createInfo.ppEnabledLayerNames = physicalDevice_ptr.getManager().getValidationLayers().data();

            if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &m_LogicalDevice) != VK_SUCCESS)
                LOG::warning("Failed to create logical device for " + std::string(physicalDevice.getProperties().deviceName) + "!");

            for (VulkanQueueSettings setting: queueSettings)
            {
                VkQueue queue;
                switch (setting.type)
                {
                case VulkanQueueSettings::VulkanQueueType::Graphics :
                    vkGetDeviceQueue(m_LogicalDevice, setting.queueFamilyIndex, 0, &queue);
                    m_GraphicsQueue.push_back(queue);
                    break;
                case VulkanQueueSettings::VulkanQueueType::Present :
                    vkGetDeviceQueue(m_LogicalDevice, setting.queueFamilyIndex, 0, &queue);
                    m_PresentQueue.push_back(queue);
                    break;
                default:
                    LOG::warning("QueueFamily support not yet implemented!");
                    return;
                }
            }
            m_GraphicsQueue.shrink_to_fit();
            m_PresentQueue.shrink_to_fit();
        }

    
        VulkanLogicalDevice::~VulkanLogicalDevice()
        {
            vkDestroyDevice(m_LogicalDevice, nullptr);
        }
    }
}