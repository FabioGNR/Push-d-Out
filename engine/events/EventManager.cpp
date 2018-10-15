#include "EventManager.h"
#include <events/models/QuitEvent.h>
#include <input/InputManager.h>

namespace engine {
namespace events {
    bool EventManager::getEvents()
    {
        SDLEventAdapter ea;
        std::vector<IEvent*> test = ea.getEvents();

        m_inputManager.startInput();
        for (IEvent* event : test) {
            if (dynamic_cast<IControlEvent*>(event)) {
                m_inputManager.storeInput((IControlEvent*)event);
            } else if (dynamic_cast<QuitEvent*>(event)) { // TODO: eventually remove this
                return false;
            } else if (dynamic_cast<IOtherEvent*>(event)) {
                // do nothing
            }
        }
        return true;
    }

    input::InputManager& EventManager::getInput()
    {
        return m_inputManager;
    }
}
}