#pragma once
#include <pch.h>
#include <cxxabi.h>

#define quote(x) #x

namespace RENGINE
{
    class Utilities
    {
    public:
        template<typename T>
        std::string static getClassName()
        {
            int status;
            std::string className = std::string(abi::__cxa_demangle(typeid(T).name(),0,0,&status));

            std::string namespaceName = std::string(quote(RENGINE)) + "::";
            className = className.substr(className.find_first_of(namespaceName) + namespaceName.size(), className.size());
            return className;
        }

        static std::string quotate(const std::string& string); 
    };
}