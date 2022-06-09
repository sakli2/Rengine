#pragma once

class Window
{
public:
    Window() {}
    virtual ~Window() {}

    virtual void OpenWindow() = 0;
    virtual bool Update() = 0;
};