#include <pch.h>
#include <GLFW/glfw3.h>
#include "VkManager.h"
#include "VkPhysicalDevice.h"

namespace RENGINE
{
    namespace VulkanAPI
    {
        //query for functions
        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
        {
            auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
            if (func != nullptr) {
                return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
            } else {
                return VK_ERROR_EXTENSION_NOT_PRESENT;
            }
        }

        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) 
        {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
            if (func != nullptr) {
                func(instance, debugMessenger, pAllocator);
            }
        }


        VulkanManager::VulkanManager(RenderAPIDebugLvl debug_lvl)
            :m_DebugLvl(RenderAPIDebugLvl::none),m_VKinstance(nullptr),m_DebugManager(nullptr)
        {

            //TODO CHANGE THIS SO IT DOESNT RELY ON GLFW
            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions;
            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
            m_vkExtensions.swap(extensions);
            
            VkDebugUtilsMessengerCreateInfoEXT debugInfo;
            this->setDebugLvl(debug_lvl, &debugInfo);
    

            //appInfo
            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "VKinstace";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "No Engine";
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;
            
            //Instance CreateInfo
            VkInstanceCreateInfo InstanceCreateInfo{};
            InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            InstanceCreateInfo.pApplicationInfo = &appInfo;
            InstanceCreateInfo.enabledExtensionCount = m_vkExtensions.size();
            InstanceCreateInfo.ppEnabledExtensionNames = m_vkExtensions.data();
            
            InstanceCreateInfo.ppEnabledLayerNames = m_vkValidationLayers.data();
            InstanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(m_vkValidationLayers.size());
            InstanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugInfo;

            
            if(vkCreateInstance(&InstanceCreateInfo, nullptr, &m_VKinstance))
                LOG::warning("Failed to create Vulkan Instance");

            if(m_DebugLvl == RenderAPIDebugLvl::debug)
                if (CreateDebugUtilsMessengerEXT(m_VKinstance, &debugInfo, nullptr, &m_DebugManager) != VK_SUCCESS)
                    LOG::warning("Failed to set up debug messenger!");
        }

        VulkanManager::~VulkanManager()
        {
            m_DebugLvl = RenderAPIDebugLvl::none;
            if (m_DebugManager) {
                 DestroyDebugUtilsMessengerEXT(m_VKinstance, m_DebugManager, nullptr);
            }
            if(m_VKinstance)
                vkDestroyInstance(m_VKinstance, nullptr);


            m_vkValidationLayers.clear();
            m_vkExtensions.clear();
        }

        VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,VkDebugUtilsMessageTypeFlagsEXT messageType,const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,void* pUserData)
         {
            if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                RENGINE::LOG::warning( "[VULKAN] : " + std::string(pCallbackData->pMessage));
            }
            else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
                RENGINE::LOG::error( "[VULKAN] : " + std::string(pCallbackData->pMessage));
            }
            else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
                RENGINE::LOG::info( "[VULKAN] : " + std::string(pCallbackData->pMessage));
            }
            else 
            {
                RENGINE::LOG::write( "[VULKAN] : " + std::string(pCallbackData->pMessage));
            }
            return VK_FALSE;
        }

        void VulkanManager::setDebugLvl(RenderAPIDebugLvl debug_lvl, VkDebugUtilsMessengerCreateInfoEXT* debug_info)
        {
            if(m_DebugLvl == debug_lvl)
                return;
            m_DebugLvl = debug_lvl;
            
            //ALL
            {
                m_vkDeviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
            }
            //DEBUG LVL
            if(m_DebugLvl == RenderAPIDebugLvl::debug)
            {
                //validation layers
                m_vkValidationLayers.push_back("VK_LAYER_KHRONOS_validation");

                //extensions
                m_vkExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

                *debug_info= {};
                debug_info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
                debug_info->pfnUserCallback = debugCallback;
                debug_info->messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | 
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT; 
                // | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
                debug_info->messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
                
            }
            //PERFORMANCE LVL
            else if (m_DebugLvl == RenderAPIDebugLvl::performance)
            {

            }
            checkValidationLayerSupport();
        }


        void VulkanManager::checkValidationLayerSupport() 
        {
            m_vkValidationLayers.shrink_to_fit();
            
            std::uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

            std::vector<VkLayerProperties> availableLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
            

            for (const char* layerName : m_vkValidationLayers)
            {
                bool layerFound = false;
                for (const auto& layerProperties : availableLayers) {
                    if (strcmp(layerName, layerProperties.layerName) == 0) {
                        layerFound = true;
                        break;
                    }
                }
                if (!layerFound)
                    LOG::warning("Validation layer " + Utilities::quotate(layerName) + " not supported");
            }
        }


        std::vector<VulkanPhysicalDevice> VulkanManager::listPhysicalDevices()
        {
            uint32_t deviceCount = 0;
            vkEnumeratePhysicalDevices(m_VKinstance, &deviceCount, nullptr);
            if (deviceCount == 0) {
                 LOG::warning("Failed to find any GPUs that support vulkan");
            }

            std::vector<VkPhysicalDevice> devices_(deviceCount);
            vkEnumeratePhysicalDevices(m_VKinstance, &deviceCount, devices_.data());

            std::vector<VulkanPhysicalDevice> devices;
            devices.reserve(deviceCount);
            for(const VkPhysicalDevice device : devices_)
                devices.emplace_back(device,*this);
            return devices;
        }


        const std::vector<const char*>& VulkanManager::getValidationLayers() const
        {
            return m_vkValidationLayers;
        }
        const std::vector<const char*>& VulkanManager::getExtensions() const
        {
            return m_vkExtensions;
        }

        const std::vector<const char*>& VulkanManager::getDeviceExtensions() const
        {
            return m_vkDeviceExtensions;
        }
    }
}

        