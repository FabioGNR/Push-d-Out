#include "SoundEffect.h"

namespace engine {
namespace sound {
    SoundEffect::SoundEffect(const std::string& soundPath, int loops)
        : Sound(soundPath)
        , m_loops(loops)
    {
    }

    int SoundEffect::loops() const
    {
        return m_loops;
    }

    void SoundEffect::setLoops(int loops)
    {
        m_loops = loops;
    }
} // end namespace sound
} // end namespace engine
