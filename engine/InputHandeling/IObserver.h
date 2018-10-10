#pragma once

#include "EventHandling/Events/IControlEvent.h"
#include <map>
#include <memory>

class IObserver {

public:
    virtual void update(std::map<char, IControlEvent*>& keyMap) = 0;
};
