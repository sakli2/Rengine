#pragma once
#include <pch.h>
#include "Rengine/Utilities/StringOperations.h"
#include "Rengine/Utilities/LOG.h"



namespace RENGINE
{
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
                LOG::write(std::string("Using ") +  Utilities::getClassName<ResourceIterator>() + " platform \'" +  Utilities::getClassName<Resource>() + "\'!");
            }
            else
            {
                setBaseResource<Resource, Resources...>();
            }
        }
        template<typename Resource > 
        inline static void setBaseResource()
        {
            LOG::write("Unsupported Resource \'" + Utilities::getClassName<Resource>() + "\'!");
        }

    private:
        inline static std::tuple<ResourceList*...> m_Resources;
    };
}

#include "Types.h"