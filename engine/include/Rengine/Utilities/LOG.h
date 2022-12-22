#pragma once
#include <pch.h>

namespace RENGINE
{   
    class Logger;

    class LOG
    {
    public:

        static void info(const std::string& text);
        static void warning(const std::string& text);
        static void error(const std::string& text);

    private:
        static void processMessages();
        static void baseInfoFunction(const std::string& message);
        static void baseWarningFunction(const std::string& message);
        static void baseErrorFunction(const std::string& message);

        static std::list<std::pair<std::function<void(const std::string&)> , std::string>> unprocessed_messages; 
    };
}