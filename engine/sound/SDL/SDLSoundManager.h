#pragma once

#include <sound/ISoundManager.h>
#include <sound/Music.h>
#include <sound/Sound.h>
#include <sound/SoundEffect.h>

#include <map>
#include <memory>
#include <string>


namespace engine {
namespace sound {
    class SDLSoundManager : public ISoundManager {

    public:
        SDLSoundManager();
        virtual ~SDLSoundManager();

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
