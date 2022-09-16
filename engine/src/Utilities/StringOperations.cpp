#include <Rengine/Utilities/StringOperations.h>

namespace RENGINE
{
    std::string Utilities::quotate(const std::string& string)
    {
        return std::string("[\'") + string + "\']";
    }
}