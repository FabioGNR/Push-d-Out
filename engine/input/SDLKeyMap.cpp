#include "SDLKeyMap.h"
#include <events/models/KeyEvent.h>

namespace engine {
namespace input {
    events::IEvent* SDLKeyMap::getKeyValue(SDL_Event event, bool pressed)
    {
        return new events::KeyEvent(keyCode[event.key.keysym.sym], pressed);
    }
}
}
