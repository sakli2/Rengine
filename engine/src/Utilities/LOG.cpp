#include <Rengine/Utilities/LOG.h>
#include <Rengine/Resources/ResourceManager.h>

namespace RENGINE
{

    void throw_error(const std::string& text)
    {
        Logger* logger = ResourceManager::getResource<Logger>();
        if(logger)
            logger->write("[ERROR] " + text);
        else
        {
            std::cout << "[Warning] Logger not Initalized!" << std::endl;
            std::cout << text << std::endl;
        }
        std::cin.get();
    }


    void LOG::write(const std::string& text)
    {
        Logger* logger = ResourceManager::getResource<Logger>();
        if(logger)
            logger->write(text);
        else
        {
            std::cout << "[Warning] Logger not Initalized!" << std::endl;
            std::cout << text << std::endl;
        }
    }
}

