#include "ConsoleLog.h"


namespace RENGINE
{
    ConsoleLog::ConsoleLog()
        :Log()
    {

    }

    ConsoleLog::~ConsoleLog()
    {

    }

    void ConsoleLog::write(const std::string& text)
    {
        std::cout << text << std::endl;
    }
}