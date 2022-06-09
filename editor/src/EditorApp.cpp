#include "UI/UI_CONTROL/LayerStack.h"
#include <Rengine.h>
#include <iostream>

class EditorApp : public Application
{
public:
    EditorApp()
        :Application()
    {
        
    }

    ~EditorApp()
    {

    }


};

Application* CreateApplication()
{
    return new EditorApp();
} 

