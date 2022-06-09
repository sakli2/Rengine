#pragma once
#include <string>

class Utilities
{
public:
    template<typename T>
    std::string static getClassName()
    {
        {
        std::string c_name = std::string(typeid(T).name());
        int i = 0;
        while (isdigit(c_name.at(i)))
        {
            i++;
        }
        std::string className = std::string(c_name.substr(i,c_name.size()));
        return className;
}
    }
};