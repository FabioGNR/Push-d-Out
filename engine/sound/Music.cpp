#include "Music.h"

namespace engine {
namespace sound {

    Music::Music(std::string soundPath)
        : Sound(std::move(soundPath))
    {
    }
}
}
