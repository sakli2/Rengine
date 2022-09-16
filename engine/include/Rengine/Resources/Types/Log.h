#pragma once 
#include <pch.h>

namespace RENGINE
{
    class Logger
    {
    public:
        Logger() {}
        virtual ~Logger() {}

        virtual void write(const std::string& text) = 0;
    };
}