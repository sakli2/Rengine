#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Rengine/Resources/ResourceLoader.h>

namespace RENGINE
{
    CREATE_RESOURCE(GLFW_Window, Window)
    {
    public:
        GLFW_Window();
        virtual ~GLFW_Window() override;

        virtual bool update() override;
    private:
        GLFWwindow* m_Window;
    };
}