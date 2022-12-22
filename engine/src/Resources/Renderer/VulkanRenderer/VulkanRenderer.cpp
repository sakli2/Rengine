#include <pch.h>
#include "VulkanRenderer.h"
#include "GLFW/glfw3.h"

namespace RENGINE
{                                
    VulkanRenderer::VulkanRenderer()
        :m_RendererSettings(ResourceManager::getResource<ConfigManager>()->getContainer("Resources")["ResourceSettings"]["VulkanRenderer"])
    {
        //TODO "Request" from Window
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
        m_RendererSettings.managerSettings.extensions.swap(extensions);

       this->setup();
    }

    VulkanRenderer::~VulkanRenderer()
    {

    }

    void VulkanRenderer::setup()
    {
        m_Manager = VulkanAPI::createVulkanManager(m_RendererSettings.managerSettings);
        VulkanAPI::VulkanPhysicalDevice activePhysicalDevice = m_Manager->getPhysicalDevices().at(0);
        m_ActiveDevice = activePhysicalDevice.createLogicalDevice(m_RendererSettings.logicalDeviceSettings);
        
        //m_vkExtensions.swap(extensions);
          
          //  for (auto& queue :instance.listPhysicalDevices()[0].getQueueFamilies())
          //      std::cout << queue.getQueueCount() << " - " << std::to_string(queue.getQueueflags()) << std::endl;
//
//
          //  std::vector<RENGINE::VulkanAPI::VulkanPhysicalDevice> physicalDevices = instance.listPhysicalDevices();
          //  RENGINE::VulkanAPI::VulkanPhysicalDevice& activeDevice = physicalDevices[0];
//
          //  std::cout << activeDevice.getProperties().deviceName << std::endl;
          //  auto features = activeDevice.getFeatures();
          //  RENGINE::VulkanAPI::VulkanLogicalDevice logical_device = activeDevice.createLogicalDevice({
          //      {VulkanAPI::VulkanQueueSettings::VulkanQueueType::Graphics, 0 , 1.0f},
          //      {VulkanAPI::VulkanQueueSettings::VulkanQueueType::Present, 1 , 1.0f}
          //  },features);
//
          //  
//
          //  RENGINE::VulkanAPI::VulkanSurface surface = ResourceManager::getResource<Window>()->createSurface(logical_device);
          //  std::cout << surface.getSurfaceCapabilities().maxImageExtent.width << " - " << surface.getSurfaceCapabilities().maxImageExtent.height <<  std::endl;
          //  RENGINE::VulkanAPI::VulkanSwapChainConfig config;
          //  {
          //      auto& createInfo = config.swapChainInfo; 
          //      createInfo.imageArrayLayers = 1;
          //      createInfo.imageExtent.height = 600;
          //      createInfo.imageExtent.width = 800;
          //      createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
          //      //createInfo.queueFamilyIndexCount = 2;
          //      //createInfo.pQueueFamilyIndices = queueFamilyIndices;
          //      createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
//
          //      //config.swapChainInfo.imageExtent
          //  }
          //  //RENGINE::VulkanAPI::VulkanSwapChain swapChain = surface.createSwapChain(config);
    }
}