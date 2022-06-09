#include "GLFW_Window.h"
#include <Rengine/ResourceManager.h>

GLFW_window::GLFW_window()
    :Window()
{
    
}
GLFW_window::~GLFW_window() 
{

}

void GLFW_window::OpenWindow() 
{
    LOG::write("opening window...");
}

bool GLFW_window::Update()
{
    return false;
}