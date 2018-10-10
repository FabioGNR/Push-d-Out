#include "InputObserver.h"

void InputObserver::update(std::map<char, IControlEvent *> &keyMap) {
    std::cout << std::endl;
    for (auto it = keyMap.cbegin(); it != keyMap.cend(); it++) {
        std::cout << it->first << " " << it->second << std::endl;
    }
}
