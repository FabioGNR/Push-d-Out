#include "SDLBlendModes.h"

namespace engine {
namespace graphics {
    static const std::map<BlendModes, SDL_BlendMode> m_modes = {
        { BlendModes::ADDITIVE, SDL_BlendMode::SDL_BLENDMODE_ADD },
        { BlendModes::NONE, SDL_BlendMode::SDL_BLENDMODE_NONE },
        { BlendModes::COLOR_MODULATE, SDL_BlendMode::SDL_BLENDMODE_MOD },
        { BlendModes::ALPHA, SDL_BlendMode::SDL_BLENDMODE_BLEND },
    };

    SDL_BlendMode SDLBlendModes::getMode(BlendModes mode)
    {
        return m_modes.at(mode);
    }
}
}
