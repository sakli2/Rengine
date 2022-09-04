#pragma once

namespace RENGINE
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void run();
    };

    extern Application* CreateApplication();
}