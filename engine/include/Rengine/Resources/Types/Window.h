#pragma once
#include <pch.h>



namespace RENGINE
{
    BASE_RESOURCE(Window)
    {
    public:
        Window()
        {
            CONFIG_PARAMETER(width);
            CONFIG_PARAMETER(height);
        }
        virtual ~Window() {}

        virtual bool update() = 0;

    protected:
         float width;
         float height;
    };
}