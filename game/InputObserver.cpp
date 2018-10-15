#include "InputObserver.h"

void InputObserver::update(std::map<Keys, IControlEvent *> &keyMap) {
    for (auto it : keyMap) {
        std::cout << it.first << " " << it.second << std::endl;
    }
}
