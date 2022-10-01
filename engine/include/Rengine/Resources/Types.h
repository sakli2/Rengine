#pragma once

#define CREATE_RESOURCE(ResourceName, BaseResource) \
class ResourceName; \
namespace BaseResource##_##ResourceName \
{\
     static bool init() \
     {\
        RENGINE::s_ResourceProviders->push_back([]\
        {\
            if(ConfigManager::getValue<std::string>("Resources", #BaseResource) == #ResourceName)\
            {\
                ResourceManager::provideResources<ResourceName>();\
            }\
        });\
        return 0;\
    }\
    inline bool b = init();\
}\
class ResourceName : public BaseResource     



//ADD RESOURCES HERE

#include "Types/Log.h"
#include "Types/Window.h"




namespace RENGINE 
{

    inline std::vector<std::function<void()>>* s_ResourceProviders = new std::vector<std::function<void()>>();
    
    
    //TODO MAKE SOME STUPID MACRO
    using ResourceManager = Systems::ResourceManager_<Logger,Window>;
}
//------------------------------------
