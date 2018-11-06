#pragma once

#include "Sound.h"

namespace engine {
namespace sound {
    class SoundEffect : public Sound {
        int m_loops;

    public:
        SoundEffect(const std::string& soundPath, int loops);

        int loops() const;
        void setLoops(int loops);
    };

} // end namespace sound
} // end namespace engine
