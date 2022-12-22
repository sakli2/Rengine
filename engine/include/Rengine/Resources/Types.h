#pragma once



//ADD RESOURCES HERE
#include "Types/Logger.h"
#include "Types/Window.h"
#include "Types/Renderer.h"
#include "FinalTypes/Config/ConfigManager.h"



namespace RENGINE 
{

    inline std::vector<std::function<void()>>* s_ResourceProviders = new std::vector<std::function<void()>>(); //todo change to map
    
    
    //TODO MAKE SOME STUPID MACRO
    using ResourceManager = Systems::ResourceManager_<
        Logger,
        Window,
        Renderer,
        ConfigManager
    >;
}
//------------------------------------