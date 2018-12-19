#include "SDLSoundManager.h"

#include <SDL_mixer.h>
#include <common/LimitedResourceCache.h>
#include <exceptions/SDLMixerException.h>

static common::LimitedResourceCache<std::string, std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)>, 50> m_soundEffectCache;

// Mix_Music is a typedef, cannot forward declare
static common::LimitedResourceCache<std::string, std::unique_ptr<Mix_Music, void (*)(Mix_Music*)>, 50> m_musicCache;

namespace engine {
namespace sound {
    SDLSoundManager::SDLSoundManager()
    {
        static bool isInitialized = false;

        if (!isInitialized) {
            /*
             * From http://lazyfoo.net/SDL_tutorials/lesson11/index.php
             * Mix_OpenAudio()'s first argument is the sound frequency we use, and the default is 22050 which is what's recommended.
             * A higher frequency will reduce latency but leads to more CPU usage.
             * The second argument is the sound format used which we set to the default.
             * The third argument is how many channels we plan to use.
             * We set it to 2 so we have stereo sound, if it was set to one we'd have mono sound.
             * The last argument is the sample size, which is set to 1024.
             * Lower sample sizes lead to less latency but can lead to crackling on slower computers.
             */

            if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
                throw SDLMixerException(Mix_GetError());
            }
            isInitialized = true;
        }
    }

    SDLSoundManager::~SDLSoundManager() = default;

    void SDLSoundManager::play(const SoundEffect& sound)
    {
        Mix_Chunk* chunk = nullptr;

        if (!m_soundEffectCache.hasResource(sound.soundPath())) {
            std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)> newChunk = {
                Mix_LoadWAV(sound.soundPath().c_str()),
                Mix_FreeChunk
            };

            if (newChunk == nullptr) {
                throw std::runtime_error("Could not load chunk");
            }

            chunk = newChunk.get();
            m_soundEffectCache.addResource(sound.soundPath(), std::move(newChunk));
        } else {
            chunk = m_soundEffectCache.getResource(sound.soundPath()).get();
        }

        Mix_PlayChannel(-1, chunk, sound.loops());
    }

    void SDLSoundManager::play(const Music& sound)
    {
        Mix_Music* chunk = nullptr;
        if (!m_musicCache.hasResource(sound.soundPath())) {
            std::unique_ptr<Mix_Music, void (*)(Mix_Music*)> newChunk = {
                Mix_LoadMUS(sound.soundPath().c_str()),
                Mix_FreeMusic
            };

            if (newChunk == nullptr) {
                throw std::runtime_error("Could not load chunk");
            }

            chunk = newChunk.get();
            m_musicCache.addResource(sound.soundPath(), std::move(newChunk));
        } else {
            chunk = m_musicCache.getResource(sound.soundPath()).get();
        }
        Mix_PlayMusic(chunk, -1);
    }

    void SDLSoundManager::resume() const
    {
        Mix_ResumeMusic();
    }

    void SDLSoundManager::pause() const
    {
        Mix_PausedMusic();
    }

    void SDLSoundManager::setMusicVolume(const Volume volume)
    {
        const int sdl_volume = scaleToSDLVolume(volume);
        Mix_VolumeMusic(sdl_volume);
    }

    void SDLSoundManager::setSfxVolume(const Volume volume)
    {
        const int sdl_volume = scaleToSDLVolume(volume);
        Mix_Volume(-1, sdl_volume);
    }

    int SDLSoundManager::scaleToSDLVolume(Volume volume) const
    {
        return static_cast<int>(volume.volume * (MIX_MAX_VOLUME / 100.f));
    }
} // end namespace sound
} // end namespace engine
