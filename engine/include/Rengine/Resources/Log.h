#pragma once 
#include <string>

class Log
{
public:
    Log() {}
    virtual ~Log() {}

    virtual void write(const std::string& text) = 0;
};
