#include <pch.h>
#include <Rengine/EntryPoint/Entrypoint.h>
#include <Rengine/Resources/Resources.h>

#include "Resources/log/ConsoleLog.h"
#include "Resources/window/GLFW_window.h"



namespace RENGINE
{
    Application::Application()
    {
        ResourceManager::provideResources<ConsoleLog,GLFW_window>();
    }

    Application::~Application()
    {
        
    }

    void Application::run() 
    {
        VkInstance instance;
        
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;


        while(!ResourceManager::getResource<Window>()->update())
        {
            //ResourceManager::getResource<Log>()->write("hi");
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