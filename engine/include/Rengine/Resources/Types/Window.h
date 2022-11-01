#pragma once
#include <pch.h>
#include "Rengine/RenderingApi/RenderApi.h"


namespace RENGINE
{
    class Window
    {
    public:
        Window()
        {
            CONFIG_PARAMETER(width);
            CONFIG_PARAMETER(height);
        }
        virtual ~Window() {}

        virtual bool update() = 0;
        virtual WindowSurface createSurface(VulkanAPI::VulkanLogicalDevice& logicalDevice) = 0;
    protected:
         float width;
         float height;
    };
}