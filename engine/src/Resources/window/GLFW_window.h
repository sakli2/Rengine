#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Rengine/Resources/Types/Window.h>

namespace RENGINE
{
    class GLFW_window : public  Window
    {
    public:
        GLFW_window();
        virtual ~GLFW_window() override;

        virtual bool update() override;
    private:
        GLFWwindow* m_Window;
    };
}