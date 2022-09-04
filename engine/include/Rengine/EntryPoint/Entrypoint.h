#pragma once

namespace RENGINE
{
    class Application
    {
    public:
        Application(const std::string& settingsFilePath);
        virtual ~Application();

        void run();
    };

    extern Application* CreateApplication();
}