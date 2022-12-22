#pragma once
#include <pch.h>
#include <Rengine/Resources/Resources.h>

namespace RENGINE
{
    class WindowSurface;

    class Window
    {
    public:
        Window()
        {
            RESOURCE_PARAMETER(width);
            RESOURCE_PARAMETER(height);
        }
        virtual ~Window() {}

        virtual bool update() = 0;
        //virtual WindowSurface createSurface(VulkanAPI::VulkanLogicalDevice& logicalDevice) = 0;
    protected:
         float width;
         float height;
    };
}