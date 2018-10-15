#include <events/models/KeyEvent.h>
#include "InputObserver.h"

void InputObserver::update(std::map<engine::input::Keys, engine::events::IControlEvent *> &keyMap) {
    for (auto& it : keyMap) {
        dynamic_cast<engine::events::KeyEvent*>(it.second)->printType();
    }
}
