#pragma once

#include <SDL2/SDL_blendmode.h>
#include <graphics/BlendModes.h>
#include <map>

namespace engine {
namespace graphics {
    class SDLBlendModes {
    public:
        static SDL_BlendMode getMode(BlendModes);
    };
}
}
