#pragma once

#include <algorithm>

namespace engine {
namespace sound {

    // TODO: Make not ugly
    const static int MUTED_VOLUME = 0;
    const static int MAX_VOLUME = 100;
    struct Volume {
        int volume;

        explicit Volume(int volume)
        {
            this->volume = std::min(MAX_VOLUME, std::max(volume, MUTED_VOLUME));
        }
    };

    class SoundEffect;
    class Music;
    class ISoundManager {
    public:
        ISoundManager() = default;
        ISoundManager(const ISoundManager& other) = default;
        ISoundManager& operator=(const ISoundManager& other) = default;

        ISoundManager(ISoundManager&& other) = default;
        ISoundManager& operator=(ISoundManager&& other) = default;
        virtual ~ISoundManager() = default;
        virtual void play(const SoundEffect& sound) = 0;
        virtual void play(const Music& sound) = 0;
        virtual void resume() const = 0;
        virtual void pause() const = 0;
        virtual void setMusicVolume(Volume volume) = 0;
        virtual void setSfxVolume(Volume volume) = 0;
    };
}
}
