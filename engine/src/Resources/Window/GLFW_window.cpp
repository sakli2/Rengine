#include "GLFW_window.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace RENGINE
{

    //inline  WindowSurface createGLFWwindowSurface(VulkanAPI::VulkanLogicalDevice& logicalDevice, GLFWwindow* window)
    //{
    //    //VkSurfaceKHR surface;
    //    //if (glfwCreateWindowSurface(logicalDevice.physicalDevice_ptr.manager_ptr, window, nullptr, &surface))
    //    //    LOG::warning("failed to create window surface!");
    //    //return WindowSurface(surface ,logicalDevice);
    //}

    GLFW_Window::GLFW_Window()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

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

    //WindowSurface GLFW_Window::createSurface(VulkanAPI::VulkanLogicalDevice& logicalDevice)
    //{
    //    return createGLFWwindowSurface(logicalDevice, window);
    //}

}