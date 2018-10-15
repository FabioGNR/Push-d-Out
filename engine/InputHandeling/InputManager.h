#pragma once

#include "IObserver.h"
#include <queue>
#include <vector>

class InputManager {
private:
    std::vector<IObserver*> observers;
    std::unique_ptr<std::map<Keys, IControlEvent*>> keyMap{ new std::map<Keys, IControlEvent*> };

public:
    void startInput();
    void storeInput(IControlEvent* event);
    void subscribe(IObserver* observer);
    void notify();
};
