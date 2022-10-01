#pragma once
#include <pch.h>
#include "Rengine/Utilities/StringOperations.h"
#include "Rengine/Utilities/LOG.h"

namespace RENGINE
{
    namespace Systems {

    template <typename... ResourceList>
    class ResourceManager_
    {
    public:
        ResourceManager_() { s_instance = this; }
        ~ResourceManager_() { m_deleteResources<ResourceList...>(); }

        ResourceManager_(const ResourceManager_&) = delete;
        ResourceManager_ & operator=(const ResourceManager_&) = delete;
        ResourceManager_(ResourceManager_&) = delete;
        

        template<typename Resource>
        inline static constexpr Resource*& getResource() { return s_instance->m_getResource<Resource>(); } 

        template<typename... rest>
        inline static void provideResources()
        {
            s_instance->m_provideResources<rest...>();
        }

        inline static void checkResourceState()
        {
            s_instance->m_checkResourceState<ResourceList...>();
        }

    private:
        template<typename Resource>
        inline constexpr Resource*& m_getResource() { return std::get<Resource*>(m_Resources); }

        template<typename Resource, typename... rest>
        inline void m_provideResources()
        {
            m_setBaseResource<Resource,ResourceList...>();

            if constexpr (sizeof...(rest) > 0)
                m_provideResources<rest...>();
        }

        template<typename Resource,typename ResourceIterator,typename... Resources> 
        inline void m_setBaseResource()
        {
            
            if constexpr(std::is_base_of<ResourceIterator, Resource>())
            {
                ResourceIterator*& base_resource = m_getResource<ResourceIterator>();
                bool is_null = base_resource != nullptr;
                if(is_null)  
                    delete base_resource;
                base_resource = reinterpret_cast<ResourceIterator*>(new Resource());
                
                if(is_null)
                    LOG::info(std::string("Switching ") +  Utilities::getClassName<ResourceIterator>() + " platform to \'" +  Utilities::getClassName<Resource>() + "\'!");
                else
                    LOG::info(std::string("Using ") +  Utilities::getClassName<ResourceIterator>() + " platform \'" +  Utilities::getClassName<Resource>() + "\'!");
            }
            else
            {
                if constexpr (sizeof...(Resources) > 0)
                    m_setBaseResource<Resource, Resources...>();
                else
                    LOG::warning("Unsupported Resource \'" + Utilities::getClassName<Resource>() + "\'!");
            }
        }


        template<typename ResourceIterator,typename... Resources>
        inline void m_deleteResources()
        {
            delete m_getResource<ResourceIterator>();
            
            if constexpr (sizeof...(Resources) > 0)
                m_deleteResources<Resources...>();
        }


        template<typename ResourceIterator,typename... Resources>
        inline void m_checkResourceState()
        {
            if(m_getResource<ResourceIterator>() == nullptr)
                LOG::warning("Resource " + Utilities::quotate(Utilities::getClassName<ResourceIterator>()) + " not initialized!");
            
            if constexpr (sizeof...(Resources) > 0)
                m_checkResourceState<Resources...>();
        }

    private:
        std::tuple<ResourceList*...> m_Resources;
        inline static ResourceManager_<ResourceList...>* s_instance;
    };

    }
}

#include "Types.h"