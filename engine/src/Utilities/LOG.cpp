#include <Rengine/Utilities/LOG.h>
#include <Rengine/Resources/ResourceManager.h>

namespace RENGINE
{

    void throw_error(const std::string& text)
    {
        Logger* logger = ResourceManager::getResource<Logger>();
        if(logger)
            logger->error(text);
        else
        {
            std::cout << "[Warning] Logger not Initalized!" << std::endl;
            std::cout << text << std::endl;
        }
        std::cin.get();
    }


    void LOG::warning(const std::string& text)
    {
        Logger* logger = ResourceManager::getResource<Logger>();
        if(logger)
            logger->warning(text);
        else
        {
            std::cout << "[Warning] Logger not Initalized!" << std::endl;
            std::cout << text << std::endl;
        }
    }

    void LOG::info(const std::string& text)
    {
        Logger* logger = ResourceManager::getResource<Logger>();
        if(logger)
            logger->info(text);
        else
        {
            std::cout << "[Warning] Logger not Initalized!" << std::endl;
            std::cout << "[INFO] " << text << std::endl;
        }
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


    void LOG::error(const std::string& text)
    {
        Logger* logger = ResourceManager::getResource<Logger>();
        if(logger)
            logger->error(text);
        else
        {
            std::cout << "[Warning] Logger not Initalized!" << std::endl;
            std::cout << text << std::endl;
        }
    }
}

