#include "pch.h"
#include <Rengine/Utilities/StringOperations.h>
namespace RENGINE
{
    std::string Utilities::quotate(const std::string& string)
    {
        return std::string("[\'") + string + "\']";
    }

    std::string Utilities::quotate(const char* string)
    {
        return std::string("[\'") + std::string(string) + "\']";
    }
}