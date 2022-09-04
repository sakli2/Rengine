#include "GLFW_window.h"
#include <vulkan/vulkan.h>

namespace RENGINE
{
    GLFW_window::GLFW_window()
        :Window()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Window = glfwCreateWindow(800, 600, "Window", nullptr, nullptr);
    }
    GLFW_window::~GLFW_window() 
    {
         glfwDestroyWindow(m_Window);
        glfwTerminate();
    }


    bool GLFW_window::update()
    {


        glfwPollEvents();
        return glfwWindowShouldClose(m_Window);
    }
}