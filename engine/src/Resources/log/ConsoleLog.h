#pragma once 
#include <iostream>
#include <Rengine/Resources/Log.h>


class ConsoleLog : public Log
{
public:
    ConsoleLog();
    virtual ~ConsoleLog() override;

    virtual void write(const std::string& text) override;
private:

};
