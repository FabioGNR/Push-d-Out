#include "SDLEventHandler.h"
#include <events/models/ControllerEvent.h>
#include <events/models/KeyDownEvent.h>
#include <events/models/KeyUpEvent.h>
#include <events/models/QuitEvent.h>
#include <events/models/UnknownEvent.h>

//#include "input/Keys.h" // TODO remove

namespace engine {
namespace events {
    std::vector<std::shared_ptr<IEvent>> SDLEventHandler::getEvents()
    {
        std::vector<std::shared_ptr<IEvent>> events;
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            events.push_back(mapEvent(event));
        }
        return events;
    }

    std::shared_ptr<IEvent> SDLEventHandler::mapEvent(SDL_Event event)
    {
        switch (event.type) {
        case SDL_QUIT:
            return std::make_shared<QuitEvent>();
        case SDL_KEYUP:
            return std::make_shared<KeyUpEvent>(input::SDLKeys::get(event.key.keysym.sym));
        case SDL_KEYDOWN:
            return std::make_shared<KeyDownEvent>(input::SDLKeys::get(event.key.keysym.sym));
        case SDL_CONTROLLERDEVICEADDED:
            SDL_GameControllerOpen(0);
            return std::make_shared<ControllerEvent>(input::Keys::CON_GUIDE);
        case SDL_CONTROLLERBUTTONDOWN:
            return std::make_shared<ControllerEvent>(input::SDLKeys::get(event.cbutton.button));
        default:
            return nullptr;
        }
    }
}
}
