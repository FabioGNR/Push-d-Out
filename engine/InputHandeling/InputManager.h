#pragma once

#include "EventHandling/Events/IControlEvent.h"
#include "EventHandling/Events/IEvent.h"
#include "IObserver.h"
#include <map>
#include <memory>
#include <queue>
#include <vector>

class InputManager {
private:
    std::vector<IObserver*> observers;
    //std::unique_ptr<std::map<char, IControlEvent*>> mouseMap {new std::map<char, IControlEvent*>};
    std::unique_ptr<std::map<char, IControlEvent*>> keyMap { new std::map<char, IControlEvent*> };

public:
    void storeInput(IControlEvent* event);
    void subscribe(IObserver* observer);
    void notify();
};
