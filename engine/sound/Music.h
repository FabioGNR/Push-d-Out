#pragma once

#include "Sound.h"

namespace engine {
namespace sound {
    class Music : public Sound {
    public:
        explicit Music(std::string soundPath);
    };
}
}
