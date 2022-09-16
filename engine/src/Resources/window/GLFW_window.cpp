#include "GLFW_window.h"
#include <vulkan/vulkan.h>

namespace RENGINE
{
    GLFW_Window::GLFW_Window()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Window = glfwCreateWindow(800, 600, "Window", nullptr, nullptr);
    }
    GLFW_Window::~GLFW_Window() 
    {
         glfwDestroyWindow(m_Window);
        glfwTerminate();
    }


    bool GLFW_Window::update()
    {


        glfwPollEvents();
        return glfwWindowShouldClose(m_Window);
    }
}