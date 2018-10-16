#pragma once

#include "Sound.h"

namespace engine {
namespace sound {
    class Music : public Sound {
    public:
        Music(std::string soundPath);
    };
}
}
