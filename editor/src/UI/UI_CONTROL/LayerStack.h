#pragma once

#include <tuple>
namespace UI
{
    template<typename... Args>
    class Stack
    {
    public:
        
    private:
        std::tuple<Args...> m_Layers; 
    };
}