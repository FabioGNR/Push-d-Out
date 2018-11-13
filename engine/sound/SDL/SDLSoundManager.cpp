#include "SDLSoundManager.h"

#include <SDL_mixer.h>
#include <exceptions/SDLMixerException.h>

// TODO: Use ResourceCache
static std::map<std::string, std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)>> m_soundEffectCache;

// Mix_Music is a typedef, cannot forward declare
static std::map<std::string, std::unique_ptr<Mix_Music, void (*)(Mix_Music*)>> m_musicCache;

namespace engine {
namespace sound {
    SDLSoundManager::SDLSoundManager()
    {
        static bool isInitialized = false;

        if (!isInitialized) {
            /*
             * From http://lazyfoo.net/SDL_tutorials/lesson11/index.php
             * Mix_OpenAudio()'s first argument is the sound frequency we use, and in this case it's 22050 which is what's recommended.
             * The second argument is the sound format used which we set to the default.
             * The third argument is how many channels we plan to use.
             * We set it to 2 so we have stereo sound, if it was set to one we'd have mono sound.
             * The last argument is the sample size, which is set to 4096.
             */

            if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
                throw SDLMixerException(Mix_GetError());
            }
            isInitialized = true;
        }
    }

    SDLSoundManager::~SDLSoundManager() = default;

    void SDLSoundManager::play(const SoundEffect& sound)
    {
        Mix_Chunk* chunk = nullptr;

        const auto find = m_soundEffectCache.find(sound.soundPath());
        // if not found
        if (find == m_soundEffectCache.end()) {
            std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)> newChunk = {
                Mix_LoadWAV(sound.soundPath().c_str()),
                Mix_FreeChunk
            };

            if (newChunk == nullptr) {
                throw std::runtime_error("Could not load chunk");
            }

            chunk = newChunk.get();
            m_soundEffectCache.insert({ sound.soundPath(), std::move(newChunk) });
        } else {
            chunk = find->second.get();
        }

        Mix_PlayChannel(-1, chunk, sound.loops());
    }

    void SDLSoundManager::play(const Music& sound)
    {
        Mix_Music* chunk = nullptr;

        const auto find = m_musicCache.find(sound.soundPath());
        // if not found
        if (find == m_musicCache.end()) {
            std::unique_ptr<Mix_Music, void (*)(Mix_Music*)> newChunk = {
                Mix_LoadMUS(sound.soundPath().c_str()),
                Mix_FreeMusic
            };

            if (newChunk == nullptr) {
                throw std::runtime_error("Could not load chunk");
            }

            chunk = newChunk.get();
            m_musicCache.insert({ sound.soundPath(), std::move(newChunk) });
        } else {
            chunk = find->second.get();
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
