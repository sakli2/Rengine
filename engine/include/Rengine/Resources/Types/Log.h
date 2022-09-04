#pragma once 
#include <pch.h>

namespace RENGINE
{
    class Log
    {
    public:
        Log() {}
        virtual ~Log() {}

        virtual void write(const std::string& text) = 0;
    };
}