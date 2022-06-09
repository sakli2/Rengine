#pragma once
//#include <glfw/glfw3.h>
#include <Rengine/Resources/Window.h>


class GLFW_window : public  Window
{
public:
    GLFW_window();
    virtual ~GLFW_window() override;

    virtual void OpenWindow() override;
    virtual bool Update() override;

private:
    
};