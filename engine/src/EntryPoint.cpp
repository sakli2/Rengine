#include <Rengine/EntryPoint/Entrypoint.h>
#include <Rengine/ResourceManager.h>

#include "Resources/log/ConsoleLog.h"
#include "Resources/window/GLFW_Window.h"

Application::Application()
{
    ResourceManager::provideResources<ConsoleLog,GLFW_window, Application>();

}

Application::~Application()
{
    
}

void Application::run() 
{
    while(true);

}


int main()
{
    auto app = CreateApplication();
    app->run();
    delete app;
}