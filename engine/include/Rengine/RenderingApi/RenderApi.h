#pragma once

#define USE_VULKAN


#ifdef USE_VULKAN
    #include "../src/RenderingApi/VulkanApi/VkManager.h"
    #include "../src/RenderingApi/VulkanApi/VkPhysicalDevice.h"
    #include "../src/RenderingApi/VulkanApi/VkLogicalDevice.h"
    #include "../src/RenderingApi/VulkanApi/VkQueueFamily.h"

    #include "../src/RenderingApi/VulkanApi/VkSurface.h"
    #include "../src/RenderingApi/VulkanApi/VkSwapChain.h"

    #define GLFW_INCLUDE_VULKAN
    #include <GLFW/glfw3.h>

    namespace RENGINE
    {
        //this is temporary

        using RenderApiManager = VulkanAPI::VulkanManager;
        using WindowSurface = VulkanAPI::VulkanSurface;

        inline static WindowSurface createGLFWwindowSurface(VulkanAPI::VulkanLogicalDevice& logicalDevice, GLFWwindow* window)
        {
            VkSurfaceKHR surface;
            if (glfwCreateWindowSurface(logicalDevice.physicalDevice_ptr.manager_ptr, window, nullptr, &surface))
                LOG::warning("failed to create window surface!");
            return WindowSurface(surface ,logicalDevice);
        }
    }
#endif
