#pragma once
#include <pch.h>

namespace RENGINE
{
    class Window
    {
    public:
        Window() {}
        virtual ~Window() {}

        virtual bool update() = 0;
    };
}