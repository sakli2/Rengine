#include "ConsoleLog.h"
#include <Rengine/ResourceManager.h>


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