#pragma once

#include <Rengine/Resources/Resources.h>
#include <Rengine/Resources/Types/Window.h>

struct GLFWwindow;

namespace RENGINE
{
    CREATE_RESOURCE(GLFW_Window, Window)
    {
    public:
        GLFW_Window();
        virtual ~GLFW_Window() override;

        virtual bool update() override;
        virtual WindowSurface createSurface(VulkanAPI::VulkanLogicalDevice& logicalDevice) override;
    private:
        GLFWwindow* window;
    };
}