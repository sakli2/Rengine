#pragma once
#include <memory>
#include <tuple>
#include <string>
#include "Utilities/StringOperations.h"
#include "Resources/Log.h"
#include "Resources/Window.h"



template <typename... ResourceList>
class ResourceManager_
{
public:
    ResourceManager_() = default;
    
    template<typename Resource>
    inline static constexpr Resource*& getResource() { return std::get<Resource*>(m_Resources); }
    
    template<typename Resource1, typename Resource2, typename... rest>
    inline static void provideResources()
    {
        setBaseResource<Resource1,ResourceList...>();
        provideResources<Resource2,rest...>();
    }

    template<typename Resource>
    inline static void provideResources()
    {
        setBaseResource<Resource,ResourceList...>();
    }

private:
    template<typename Resource,typename ResourceIterator,typename... Resources> 
    inline static void setBaseResource()
    {
        if(std::is_base_of<ResourceIterator, Resource>())
        {
            ResourceIterator*& base_resource = getResource<ResourceIterator>();
            if(base_resource != nullptr)
                delete base_resource;
            base_resource = reinterpret_cast<ResourceIterator*>(new Resource());
            getResource<Log>()->write(std::string("Using ") +  Utilities::getClassName<ResourceIterator>() + " platform \'" +  Utilities::getClassName<Resource>() + "\'!");
        }
        else
        {
            setBaseResource<Resource, Resources...>();
        }
    }
    template<typename Resource > 
    inline static void setBaseResource()
    {
        getResource<Log>()->write(std::string("Unsupported Resource \'") + Utilities::getClassName<Resource>() + std::string("\'!"));
    }

private:
    inline static std::tuple<ResourceList*...> m_Resources;
};


using ResourceManager = ResourceManager_<Log,Window>;


namespace LOG
{
    inline void write(const std::string& text)
    {
        ResourceManager::getResource<Log>()->write(text);
    }
}