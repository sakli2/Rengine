#pragma once

class Application
{
public:
    Application();
    virtual ~Application();

    void run();
};

extern Application* CreateApplication();