#pragma once
#include <Rengine/Resources/Resources.h>

namespace RENGINE
{
    class Application
    {
    public:
        Application(const std::string& settingsFilePath = "/home/szabi/Desktop/Rengine/engine/configs/example.config");
        virtual ~Application();

        void run();

    private:
        ResourceManager m_ResourceManager;
    };

    extern Application* CreateApplication();
}