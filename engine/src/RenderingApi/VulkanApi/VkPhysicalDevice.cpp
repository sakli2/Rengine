#include <pch.h>
#include "VkPhysicalDevice.h"
#include "VkManager.h"
#include "VkQueueFamily.h"
#include "VkLogicalDevice.h"
#include "VkSurface.h"

namespace RENGINE
{
    namespace VulkanAPI
    {

        VulkanPhysicalDevice::VulkanPhysicalDevice(const VkPhysicalDevice device, VulkanManager& manager)
            :m_PhysicalDevice(device), manager_ptr(manager)
        {
            
        }

        VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanPhysicalDevice&& device)
            :m_PhysicalDevice(device.m_PhysicalDevice), manager_ptr(device.manager_ptr)
        {
            device.m_PhysicalDevice = VK_NULL_HANDLE;
        }
        
        VulkanPhysicalDevice::~VulkanPhysicalDevice()
        {
        }

        std::uint32_t VulkanPhysicalDevice::getScore() const
        {
            return 0;
        }

        bool VulkanPhysicalDevice::supportsDeviceExtensions() const
        {
           std::vector<VkExtensionProperties> availableExtensions = getSupportedExtensions();
            for(const char* extension: manager_ptr.getDeviceExtensions())
            {
                bool found = false;
                for(const VkExtensionProperties& avaiableExtension : availableExtensions)
                {
                    if( std::strcmp(extension, avaiableExtension.extensionName) == 0) 
                    {
                        found = true;
                        break;
                    }
                }
                if(!found)
                    return false;
            }
            return  true;
        }

        std::vector<VkExtensionProperties> VulkanPhysicalDevice::getSupportedExtensions() const
        {
             std::uint32_t extensionCount;
            vkEnumerateDeviceExtensionProperties(m_PhysicalDevice, nullptr, &extensionCount, nullptr);

            std::vector<VkExtensionProperties> availableExtensions(extensionCount);
            vkEnumerateDeviceExtensionProperties(m_PhysicalDevice, nullptr, &extensionCount, availableExtensions.data());
            return availableExtensions;
        }

        VkPhysicalDeviceProperties VulkanPhysicalDevice::getProperties() const
        {
            VkPhysicalDeviceProperties deviceProperties;
            vkGetPhysicalDeviceProperties(m_PhysicalDevice, &deviceProperties);
            return deviceProperties;
        }
        VkPhysicalDeviceFeatures VulkanPhysicalDevice::getFeatures() const
        {
            VkPhysicalDeviceFeatures deviceFeatures;
            vkGetPhysicalDeviceFeatures(m_PhysicalDevice, &deviceFeatures);
            return deviceFeatures;
        }

        std::vector<VulkanQueueFamily> VulkanPhysicalDevice::getQueueFamilies() const
        {
           uint32_t queueFamilyCount = 0;
           vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &queueFamilyCount, nullptr);

           std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
           vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &queueFamilyCount, queueFamilies.data());

           std::vector<VulkanQueueFamily> vulkanAPI_queueFamilies;
           vulkanAPI_queueFamilies.reserve(queueFamilyCount);

           for (VkQueueFamilyProperties family : queueFamilies)
               vulkanAPI_queueFamilies.emplace_back(family);
           return vulkanAPI_queueFamilies;
        }

        const VulkanManager& VulkanPhysicalDevice::getManager() const
        {
            return manager_ptr;
        }


        std::uint32_t VulkanPhysicalDevice::getGraphicsQueueIndex() const
        {
            std::vector<VulkanQueueFamily> queues = getQueueFamilies();
            for(std::uint32_t i = 0; i < queues.size(); i++)
            {
                if(queues[i].hasGraphicsBit())
                    return i;
            }
            LOG::warning("Failed to find graphics queue for device:  " + std::string(getProperties().deviceName));
            return 0;
        }

        std::uint32_t VulkanPhysicalDevice::getPresentQueueIndex(VulkanSurface& windowSurface) const
        {
            std::vector<VulkanQueueFamily> queues = getQueueFamilies();

            for(std::uint32_t i = 0; i < queues.size(); i++)
            {
                VkBool32 presentSupport = false;
                vkGetPhysicalDeviceSurfaceSupportKHR(m_PhysicalDevice, i, windowSurface, &presentSupport);
                if(presentSupport)
                    return i;
            }
            LOG::warning("Failed to find present queue for device:  " + std::string(getProperties().deviceName));
            return 0;
        }

        VulkanLogicalDevice VulkanPhysicalDevice::createLogicalDevice(const std::vector<VulkanQueueSettings>& queueSettings, VkPhysicalDeviceFeatures& enabledFeatures)
        {
            VkPhysicalDeviceFeatures enabledFeaturess = getFeatures(); //Todo make config
            return VulkanLogicalDevice(queueSettings, enabledFeaturess, *this);
        }


    }
}
