#include <pch.h>
#include <Rengine/EntryPoint/Entrypoint.h>
#include "Resources/Types.h"


namespace RENGINE
{
    Application::Application(const std::string& settingsFilePath)
    {
        loadBaseResources(settingsFilePath);
        //LOG::warning("asd");
        //ResourceManager::provideResources<ResourceDefinition::ConsoleLogger>();

    }

    Application::~Application()
    {

    }

    void Application::run() 
    {
        //ResourceManager::getResource<Renderer>()->setup();

        

        while(!ResourceManager::getResource<Window>()->update())
        {
            //ResourceManager::getResource<Logger>()->write("hi");
        }
        
    } 
}




int main()
{
    RENGINE::Application* app = nullptr;
    try {
        app = RENGINE::CreateApplication();
        app->run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    delete app;
}