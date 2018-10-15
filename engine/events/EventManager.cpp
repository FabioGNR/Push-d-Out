#include "EventManager.h"
#include <events/models/QuitEvent.h>

namespace engine {
namespace events {
    bool EventManager::getEvents()
    {
        SDLEventAdapter ea;
        std::vector<IEvent*> test = ea.getEvents();

        im.startInput();
        for (IEvent* event : test) {
            if (dynamic_cast<IControlEvent*>(event)) {
                im.storeInput((IControlEvent*)event);
            } else if (dynamic_cast<QuitEvent*>(event)) { // TODO: eventually remove this
                return false;
            } else if (dynamic_cast<IOtherEvent*>(event)) {
                // do nothing
            }
        }
        return true;
    }

    input::InputManager* EventManager::getInput()
    {
        return &im;
    }
}
}