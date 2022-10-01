#include "UI/UI_CONTROL/LayerStack.h"
#include <Rengine.h>
#include <iostream>

class EditorApp : public RENGINE::Application
{
public:
    EditorApp()
        :RENGINE::Application()
    {
        
    }

    virtual ~EditorApp() override
    {

    }


};

RENGINE::Application* RENGINE::CreateApplication()
{
    return new EditorApp();
} 

