#pragma once
#include <pch.h>
#include <Rengine/Resources/Resources.h>

namespace RENGINE
{                                

    CREATE_RESOURCE(ColoredConsoleLogger, Logger)
    {
    public:
        ColoredConsoleLogger();
        virtual ~ColoredConsoleLogger() override;

        virtual void write(const std::string& text) override;
        virtual void info(const std::string& text) override;
        virtual void warning(const std::string& text) override;
        virtual void error(const std::string& text) override;

    private:
    
    };
}

