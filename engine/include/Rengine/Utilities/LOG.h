#pragma once
#include <pch.h>

namespace RENGINE
{
    void throw_error(const std::string& text);

    class LOG
    {
    public:
        static void write(const std::string& text);
        
    };
}