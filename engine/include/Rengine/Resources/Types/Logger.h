#pragma once 
#include <pch.h>

namespace RENGINE
{
    class Logger
    {
    public:
        Logger()
        {
        }
        virtual ~Logger() {}

        virtual void write(const std::string& text) = 0;
        virtual void info(const std::string& text) = 0;
        virtual void warning(const std::string& text) = 0;
        virtual void error(const std::string& text) = 0;
    };
}