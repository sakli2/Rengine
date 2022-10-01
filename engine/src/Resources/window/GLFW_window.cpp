#include "GLFW_window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace RENGINE
{
    GLFW_Window::GLFW_Window()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, "Window", nullptr, nullptr);
    }
    GLFW_Window::~GLFW_Window() 
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }


    bool GLFW_Window::update()
    {

        glfwPollEvents();
        return glfwWindowShouldClose(window);
    }
}