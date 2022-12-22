#include <pch.h>
#include "VkPhysicalDevice.h"
#include "VkManager.h"
#include "VkLogicalDevice.h"
#include "VkSurface.h"

namespace RENGINE
{
    namespace VulkanAPI
    {
        VulkanPhysicalQueueFamily::VulkanPhysicalQueueFamily(VkQueueFamilyProperties properties, std::uint32_t queueFamilyIndex)
            :m_Properties(properties), m_QueueFamilyIndex(queueFamilyIndex)
        {

        }

        bool VulkanPhysicalQueueFamily::isQueuetype(VulkanQueueSettings::VulkanQueueType type) const
        {
            if(type == VulkanQueueSettings::VulkanQueueType::Graphics)
                return m_Properties.queueFlags & VK_QUEUE_GRAPHICS_BIT;
            VulkanError("[VulkanPhysicalQueueFamily] QueueType not yet Supported");
            return false;
        }

        std::uint32_t VulkanPhysicalQueueFamily::getQueueCount() const
        {
            return m_Properties.queueCount;
        }
        
        
        std::int32_t VulkanPhysicalQueueFamily::getQueueScore() const
        {
            std::uint32_t score = 0;
            score += 100* getQueueCount();

            return  score;
        }

        std::uint32_t VulkanPhysicalQueueFamily::getQueueFamilyIndex() const
        {
            return m_QueueFamilyIndex;
        }

        //VULKAN PHYSICAL DEVICE
        VulkanPhysicalDevice::VulkanPhysicalDevice(VkPhysicalDevice& device)
            :m_PhysicalDevice(device)
        {
            
        }

        
        VulkanPhysicalDevice::~VulkanPhysicalDevice()
        {
        }

        std::uint32_t VulkanPhysicalDevice::getScore() const
        {
            return 0;
        }

        bool VulkanPhysicalDevice::supportsDeviceExtensions(const VulkanLogicalDeviceSettings& settings) const
        {
           std::vector<VkExtensionProperties> availableExtensions = getSupportedExtensions();
           bool supports_all = true;
            for(const char* extension : settings.deviceExtensions)
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
                {
                    supports_all = false;
                    LOG::warning(std::string(getProperties().deviceName) + " does not support extension \"" + std::string(extension) + "\"!" );
                }
            }
            return  supports_all;
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

       std::vector<VulkanPhysicalQueueFamily> VulkanPhysicalDevice::getQueueFamilies() const
       {
            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &queueFamilyCount, nullptr);

            std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &queueFamilyCount, queueFamilies.data());

            std::vector<VulkanPhysicalQueueFamily> queues;

            std::uint32_t index = 0;
            for(VkQueueFamilyProperties properties : queueFamilies)
            {
                queues.emplace_back(properties, index);
                index++;
            }
            return queues;
        }

        std::unique_ptr<VulkanLogicalDevice> VulkanPhysicalDevice::createLogicalDevice(const VulkanLogicalDeviceSettings& settings)
        {
            supportsDeviceExtensions(settings);
            //sort queues

            //sort from highest priority
            std::vector<VulkanQueueSettings> queueRequests = settings.queueSettings;
            std::sort(queueRequests.begin(), queueRequests.end(),
            [](VulkanQueueSettings first, VulkanQueueSettings second){
                return first.priority > second.priority;
            });

            //sort from highest scores
            std::vector<VulkanPhysicalQueueFamily> queueFamilies = getQueueFamilies();
            std::vector<std::pair<VulkanPhysicalQueueFamily*, std::int32_t>> scoreBoard;
            for(VulkanPhysicalQueueFamily& queue : queueFamilies)
            {
                scoreBoard.emplace_back(&queue, queue.getQueueScore());
            }

            std::vector<std::pair<VulkanQueueSettings*, VulkanPhysicalQueueFamily*>> bestQueues;
            for(VulkanQueueSettings& request : queueRequests)
            {
                std::int32_t currentScore = -1;
                std::int32_t bestFamilyIndex = -1;
                std::int32_t i = 0; 
                for(auto& [queueFamily, score] :  scoreBoard)
                {
                    if(score > currentScore && queueFamily->isQueuetype(request.type)) 
                    {
                        currentScore = score;
                        bestFamilyIndex = i; 
                    }
                    i++;
                }
                if(bestFamilyIndex > -1)
                {
                    scoreBoard[bestFamilyIndex].second = scoreBoard[bestFamilyIndex].second * (1 - request.priority); 
                    bestQueues.emplace_back(&request , scoreBoard[bestFamilyIndex].first);
                }
                else
                {
                    VulkanError("No appropriate queue for queueType: \"" + std::to_string((int)request.type) + "\" and priority: \"" + std::to_string(request.priority) +"\"" );
                }
            }
            


            //create Logical Device
            VkDevice logicalDevice;

            std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
            int i =0;
            for (auto& [queueSetting, physicalQueue] : bestQueues)
            {
                VkDeviceQueueCreateInfo queueCreateInfo{};
                queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfo.queueFamilyIndex = physicalQueue->getQueueFamilyIndex();
                queueCreateInfo.queueCount = 1;
                queueCreateInfo.pQueuePriorities = &queueSetting->priority;
                queueCreateInfos.push_back(queueCreateInfo);
                i++;
            }

            VkPhysicalDeviceFeatures featues = getFeatures(); //for now just enable everything
            
            VkDeviceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            createInfo.pQueueCreateInfos = queueCreateInfos.data();
            createInfo.queueCreateInfoCount = queueCreateInfos.size();
            createInfo.pEnabledFeatures = &featues; //&settings.enabledFeatures;
            createInfo.ppEnabledExtensionNames = settings.deviceExtensions.data();
            createInfo.enabledExtensionCount = settings.deviceExtensions.size(); 
            //createInfo.enabledLayerCount = physicalDevice_ptr.getManager().getValidationLayers().size();
            //createInfo.ppEnabledLayerNames = physicalDevice_ptr.getManager().getValidationLayers().data();

            std::unordered_map<VulkanQueueSettings::VulkanQueueType, std::vector<VkQueue>> queues;
            if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &logicalDevice) != VK_SUCCESS)
                LOG::warning("Failed to create logical device for " + std::string(getProperties().deviceName) + "!");
            else 
            {
                
                for (auto& [queueSetting, physicalQueue] : bestQueues)
                {
                    VkQueue queue;
                    vkGetDeviceQueue(logicalDevice, physicalQueue->getQueueFamilyIndex(), 0, &queue);
                    queues[queueSetting->type].push_back(queue);
                }
            }
            return std::make_unique<VulkanLogicalDevice>(logicalDevice,std::move(queues));
        }
    }
}
