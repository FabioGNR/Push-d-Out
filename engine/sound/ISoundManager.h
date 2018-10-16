#pragma once

#include <algorithm>

namespace engine {
namespace sound {

    // TODO: Make not ugly
    const static int MUTED_VOLUME = 0;
    const static int MAX_VOLUME = 100;
    struct Volume {
        int volume;

        Volume(int volume)
        {
            this->volume = std::min(MAX_VOLUME, std::max(volume, MUTED_VOLUME));
        }
    };

    class SoundEffect;
    class Music;
    class ISoundManager {
    public:
        virtual void play(const SoundEffect& sound) = 0;
        virtual void play(const Music& sound) = 0;
        virtual void resume() const = 0;
        virtual void pause() const = 0;
        virtual void setMusicVolume(Volume volume) = 0;
        virtual void setSfxVolume(Volume volume) = 0;
    };
}
}
