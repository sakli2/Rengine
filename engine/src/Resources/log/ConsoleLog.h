#pragma once 
#include <pch.h>
#include <Rengine/Resources/Types/Log.h>
#include <Rengine/Resources/ResourceLoader.h>

namespace RENGINE
{                                

    CREATE_RESOURCE(ConsoleLog, Logger)
    {
    public:
        ConsoleLog();
        virtual ~ConsoleLog() override;

        virtual void write(const std::string& text) override;
    private:

    };
}

