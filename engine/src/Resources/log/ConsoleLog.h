#pragma once 
#include <pch.h>
#include <Rengine/Resources/Types/Log.h>

namespace RENGINE
{
    class ConsoleLog : public Log
    {
    public:
        ConsoleLog();
        virtual ~ConsoleLog() override;

        virtual void write(const std::string& text) override;
    private:

    };
}
