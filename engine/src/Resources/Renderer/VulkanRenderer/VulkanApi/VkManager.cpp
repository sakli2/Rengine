#include <pch.h>
#include <Rengine/Utilities/Utilities.h>
#include "VkManager.h"
#include "VkPhysicalDevice.h"


namespace RENGINE
{
    namespace VulkanAPI
    {
        static VulkanManager* instance;  
        void VulkanError(const std::string& text)
        {
            instance->getCurrentSettings().errorFunc(text);
        }
        void VulkanWarning(const std::string& text)
        {
            instance->getCurrentSettings().warningFunc(text);
        }
        void VulkanInfo(const std::string& text)
        {
            instance->getCurrentSettings().infoFunc(text);
        }



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

        //debugger
        VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,VkDebugUtilsMessageTypeFlagsEXT messageType,const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,void* pUserData)
         {
            if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
                VulkanWarning( "[VULKAN] : " + std::string(pCallbackData->pMessage));
            }
            else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
                VulkanError( "[VULKAN] : " + std::string(pCallbackData->pMessage));
            }
            else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
                VulkanError( "[VULKAN] : " + std::string(pCallbackData->pMessage));
            }
            else 
            {
                VulkanInfo( "[VULKAN] : " + std::string(pCallbackData->pMessage));
            }
            return VK_FALSE;
        }

        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) 
        {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
            if (func != nullptr) {
                func(instance, debugMessenger, pAllocator);
            }
        }


        VulkanManager::VulkanManager(VulkanManagerSettings& settings)
            :m_VKinstance(nullptr),m_DebugManager(nullptr),m_Settings(settings)
        {
            if(instance)
            {
                VulkanError("Only one \"VulkanManager\" allowed");
                throw std::runtime_error("VULKANERROR");
            }
            
            instance = this;
            VkDebugUtilsMessengerCreateInfoEXT debugInfo;
            this->setDebugLvl(&debugInfo);

            //appInfo
            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "VKinstace";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "Rengine";
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;
            
            //VkInstance CreateInfo
            VkInstanceCreateInfo InstanceCreateInfo{};
            InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            InstanceCreateInfo.pApplicationInfo = &appInfo;   
            InstanceCreateInfo.enabledExtensionCount = m_Settings.extensions.size();
            InstanceCreateInfo.ppEnabledExtensionNames = m_Settings.extensions.data();       
            InstanceCreateInfo.enabledLayerCount = m_Settings.validationLayers.size();
            InstanceCreateInfo.ppEnabledLayerNames = m_Settings.validationLayers.data();
            if(m_Settings.debugLvl >= VulkanAPI::VulkanManagerSettings::VulkanAPIDebugLvl::debug_all)
                InstanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugInfo;

            
            if(vkCreateInstance(&InstanceCreateInfo, nullptr, &m_VKinstance))
                VulkanError("Failed to create \"VKInstance\"");

            if(m_Settings.debugLvl == VulkanAPI::VulkanManagerSettings::VulkanAPIDebugLvl::debug)
                if (CreateDebugUtilsMessengerEXT(m_VKinstance, &debugInfo, nullptr, &m_DebugManager) != VK_SUCCESS)
                    VulkanError("Failed to set up debug messenger for vulkan!");
        }

        VulkanManager::~VulkanManager()
        {
            if (m_DebugManager) {
                 DestroyDebugUtilsMessengerEXT(m_VKinstance, m_DebugManager, nullptr);
            }
            if(m_VKinstance)
                vkDestroyInstance(m_VKinstance, nullptr);
        }


        void VulkanManager::setDebugLvl(VkDebugUtilsMessengerCreateInfoEXT* debug_info)
        {
            
            //ALL
            {
                
            }
            //DEBUG ALL
            if(m_Settings.debugLvl == VulkanManagerSettings::VulkanAPIDebugLvl::debug_all)
            {
                 //validation layers
                m_Settings.validationLayers.push_back("VK_LAYER_KHRONOS_validation");

                //extensions
                m_Settings.extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

                *debug_info= {};
                debug_info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
                debug_info->pfnUserCallback = debugCallback;
                debug_info->messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | 
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT; 
                //VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;

                debug_info->messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            }

            //DEBUG LVL
            if(m_Settings.debugLvl == VulkanManagerSettings::VulkanAPIDebugLvl::debug)
            {
                //validation layers
                m_Settings.validationLayers.push_back("VK_LAYER_KHRONOS_validation");

                //extensions
                m_Settings.extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

                *debug_info= {};
                debug_info->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
                debug_info->pfnUserCallback = debugCallback;
                debug_info->messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | 
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT; 
                debug_info->messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
                
            }
            //PERFORMANCE LVL
            if (m_Settings.debugLvl == VulkanManagerSettings::VulkanAPIDebugLvl::performance)
            {

            }
            checkValidationLayerSupport();
        }


        void VulkanManager::checkValidationLayerSupport() 
        {
            m_Settings.validationLayers.shrink_to_fit();
            
            std::uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

            std::vector<VkLayerProperties> availableLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
            

            for (const char* layerName : m_Settings.validationLayers)
            {
                bool layerFound = false;
                for (const auto& layerProperties : availableLayers) {
                    if (strcmp(layerName, layerProperties.layerName) == 0) {
                        layerFound = true;
                        break;
                    }
                }
                if (!layerFound)
                    VulkanError("Validation layer " + Utilities::quotate(layerName) + " not supported");
            }
        }


        std::vector<VulkanPhysicalDevice> VulkanManager::getPhysicalDevices()
        {
            uint32_t deviceCount = 0;
            vkEnumeratePhysicalDevices(m_VKinstance, &deviceCount, nullptr);
            if (deviceCount == 0) {
                 VulkanError("Failed to find any GPUs that support vulkan");
            }

            std::vector<VkPhysicalDevice> devices_(deviceCount);
            vkEnumeratePhysicalDevices(m_VKinstance, &deviceCount, devices_.data());

            std::vector<VulkanPhysicalDevice> devices;
            for(VkPhysicalDevice device : devices_)
                devices.emplace_back(device);
            return devices;
        }


        const VulkanManagerSettings& VulkanManager::getCurrentSettings() const
        {
            return m_Settings;
        }


        std::unique_ptr<VulkanManager> createVulkanManager(VulkanManagerSettings& settings)
        {
            return std::make_unique<VulkanManager>(settings);
        }
    }
}

        