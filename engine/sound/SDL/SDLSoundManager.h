#pragma once

#include "engine/sound/ISoundManager.h"
#include "engine/sound/Music.h"
#include "engine/sound/Sound.h"
#include "engine/sound/SoundEffect.h"

#include <map>
#include <memory>
#include <string>

namespace engine {
namespace sound {
    class SDLSoundManager : public ISoundManager {

    public:
        SDLSoundManager();

        SDLSoundManager(const SDLSoundManager& other) = default;
        SDLSoundManager& operator=(const SDLSoundManager& other) = default;

        SDLSoundManager(SDLSoundManager&& other) = default;
        SDLSoundManager& operator=(SDLSoundManager&& other) = default;

        ~SDLSoundManager() override;

        void play(const SoundEffect& sound) override;
        void play(const Music& sound) override;
        void resume() const override;
        void pause() const override;
        void setMusicVolume(Volume volume) override;
        void setSfxVolume(Volume volume) override;

    private:
        int scaleToSDLVolume(Volume volume) const;
    };
} // end namespace sound
} // end namespace engine
