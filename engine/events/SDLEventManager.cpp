#include "SDLEventManager.h"
#include <SDL.h>
namespace engine {
bool SDLEventManager::processEvents()
{
    bool continueRunning = true;
    SDL_Event evt;
    while (SDL_PollEvent(&evt) != 0) {
        switch (evt.type) {
        case SDL_QUIT:
            continueRunning = false;
            break;
        }
    }
    return continueRunning;
}
}