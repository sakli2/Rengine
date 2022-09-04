#include <Rengine/Utilities/LOG.h>
#include <Rengine/Resources/Resources.h>

namespace RENGINE
{
    void LOG::write(const std::string& text)
    {
        Log* Logger = ResourceManager::getResource<Log>();
        if(Logger)
            Logger->write(text);
    }
}

