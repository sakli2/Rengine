#include "pch.h"
#include "ColoredConsoleLogger.h"

namespace RENGINE
{
    ColoredConsoleLogger::ColoredConsoleLogger()
    {
        std::cout << "\n";
    }

    ColoredConsoleLogger::~ColoredConsoleLogger()
    {
        std::cout << "\033[1;32m\n\n";
    }

    void ColoredConsoleLogger::write(const std::string& text)
    {
        std::cout << "\033[0m" << text << "\033[1;31m" <<  std::endl;
    }

     void ColoredConsoleLogger::info(const std::string& text)
     {
         std::cout << "\033[1;34m" << "[INFO]     " << "\033[0m" << text << "\033[1;31m" << std::endl;
     }
     void ColoredConsoleLogger::warning(const std::string& text)
     {
         std::cout << "\033[1;33m" << "[WARNING]  " << "\033[0;33m" << text << "\033[1;31m" << std::endl;
     }
     void ColoredConsoleLogger::error(const std::string& text)
     {
        std::cout << "\033[1;31m" << "[ERROR]    " << "\033[0;31m" << text << "\033[1;31m" << std::endl;
     }
}