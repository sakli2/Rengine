#include "pch.h"
#include "ConsoleLogger.h"

namespace RENGINE
{
    ConsoleLogger::ConsoleLogger()
    {
        
    }

    ConsoleLogger::~ConsoleLogger()
    {

    }

    void ConsoleLogger::write(const std::string& text)
    {
        std::cout << text << std::endl;
    }

     void ConsoleLogger::info(const std::string& text)
     {
         std::cout << "[INFO] " << text << std::endl;
     }
     void ConsoleLogger::warning(const std::string& text)
     {
        std::cout << "[WARNING] " << text << std::endl; 
     }
     void ConsoleLogger::error(const std::string& text)
     {
         std::cout << "[ERROR] " << text << std::endl;
     }
}