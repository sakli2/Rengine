#include <pch.h>
#include <Rengine/EntryPoint/Entrypoint.h>
#include "Resources/Types.h"


 #include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include "Rengine/RenderingApi/RenderApi.h"





namespace RENGINE
{
    Application::Application(const std::string& settingsFilePath)
    {
        loadBaseResources(settingsFilePath);
        
    }

    Application::~Application()
    {

    }

    void Application::run() 
    {
        {
            RenderApiManager instance(RenderAPIDebugLvl::debug);
            for (auto& queue :instance.listPhysicalDevices()[0].getQueueFamilies())
                std::cout << queue.getQueueCount() << " - " << std::to_string(queue.getQueueflags()) << std::endl;


            std::vector<RENGINE::VulkanAPI::VulkanPhysicalDevice> physicalDevices = instance.listPhysicalDevices();
            RENGINE::VulkanAPI::VulkanPhysicalDevice& activeDevice = physicalDevices[0];

            std::cout << activeDevice.getProperties().deviceName << std::endl;
            auto features = activeDevice.getFeatures();
            RENGINE::VulkanAPI::VulkanLogicalDevice logical_device = activeDevice.createLogicalDevice({
                {VulkanAPI::VulkanQueueSettings::VulkanQueueType::Graphics, 0 , 1.0f},
                {VulkanAPI::VulkanQueueSettings::VulkanQueueType::Present, 1 , 1.0f}
            },features);

            

            RENGINE::VulkanAPI::VulkanSurface surface = ResourceManager::getResource<Window>()->createSurface(logical_device);
            std::cout << surface.getSurfaceCapabilities().maxImageExtent.width << " - " << surface.getSurfaceCapabilities().maxImageExtent.height <<  std::endl;
            RENGINE::VulkanAPI::VulkanSwapChainConfig config;
            {
                auto& createInfo = config.swapChainInfo; 
                createInfo.imageArrayLayers = 1;
                createInfo.imageExtent.height = 600;
                createInfo.imageExtent.width = 800;
                createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
                //createInfo.queueFamilyIndexCount = 2;
                //createInfo.pQueueFamilyIndices = queueFamilyIndices;
                createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

                //config.swapChainInfo.imageExtent
            }
            RENGINE::VulkanAPI::VulkanSwapChain swapChain = surface.createSwapChain(config);
        }

        

        while(!ResourceManager::getResource<Window>()->update())
        {
            //ResourceManager::getResource<Logger>()->write("hi");
        }

    } 
}




int main()
{

    RENGINE::Application* app;
    try {
        app = RENGINE::CreateApplication();
        app->run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    delete app;
}