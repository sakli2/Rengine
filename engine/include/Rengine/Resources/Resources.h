#pragma once
#include <pch.h>



#define CREATE_RESOURCE(ResourceName, BaseResource)\
class ResourceName; \
namespace BaseResource##_##ResourceName \
{\
     static bool init() \
     {\
        RENGINE::s_ResourceProviders->push_back([]\
        {\
            if(ResourceManager::getResource<ConfigManager>()->getContainer("Resources")[#BaseResource] == #ResourceName)\
            {\
                ResourceManager::provideResources<ResourceName>();\
            }\
        });\
        return 0;\
    }\
    inline bool b = init();\
}\
class ResourceName : public BaseResource     


#define RESOURCE_PARAMETER(PARAMETER) defineResourceParameter(PARAMETER, __FUNCTION__, #PARAMETER)

namespace RENGINE
{   
    template<typename T>
    void defineResourceParameter(T& parameter, const std::string& Resource, const std::string& parameterName);   
}


#include <Rengine/Resources/ResourceManager.h>