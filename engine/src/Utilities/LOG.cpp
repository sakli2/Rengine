#include "pch.h"
#include <Rengine/Utilities/LOG.h>
#include <Rengine/Resources/ResourceManager.h>
namespace RENGINE
{
    std::list<std::pair<std::function<void(const std::string&)>, std::string>> LOG::unprocessed_messages; 


    void LOG::processMessages()
    {
        for (auto& [func, param] : unprocessed_messages)
        {
            func(param);
        }
        unprocessed_messages.clear();
    }

    void LOG::info(const std::string& text)
    {
        Logger* activeLogger = ResourceManager::getResource<Logger>();
        if(activeLogger)
        {
            processMessages();
            activeLogger->info(text);
        }
        else
            baseInfoFunction(text);

    }
    void LOG::warning(const std::string& text)
    {
        Logger* activeLogger = ResourceManager::getResource<Logger>();
        if(activeLogger)
        {
            processMessages();
            activeLogger->warning(text);
        }
        else
            baseWarningFunction(text);
    }

    void LOG::error(const std::string& text)
    {
        Logger* activeLogger = ResourceManager::getResource<Logger>();
        if(activeLogger)
        {
            processMessages();
            activeLogger->error(text);
        }
        else
            baseErrorFunction(text);
    }



    void LOG::baseInfoFunction(const std::string& message)
    {
        unprocessed_messages.emplace_back([&](const std::string& text ) { ResourceManager::getResource<Logger>()->info(text);}, message);
    }
    void LOG::baseWarningFunction(const std::string& message)
    {
        unprocessed_messages.emplace_back([&](const std::string& text ) { ResourceManager::getResource<Logger>()->warning(text);}, message);
    }
    void LOG::baseErrorFunction(const std::string& message)
    {
        unprocessed_messages.emplace_back([&](const std::string& text ) { ResourceManager::getResource<Logger>()->error(text);}, message);
    }
}

