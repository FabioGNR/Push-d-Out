#include "Sound.h"

namespace engine {
namespace sound {
    Sound::Sound(std::string soundPath)
        : m_soundPath(std::move(soundPath))
    {
    }

    const std::string& Sound::soundPath() const
    {
        return m_soundPath;
    }

    void Sound::setSoundPath(std::string soundPath)
    {
        m_soundPath = std::move(soundPath);
    }
} // end namespace sound
} // end namespace engine
