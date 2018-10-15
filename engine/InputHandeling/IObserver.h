#pragma once

#include "EventHandling/Events/IControlEvent.h"
#include "Keys.h"

#include <map>
#include <memory>

class IObserver {

public:
    virtual void update(std::map<Keys, IControlEvent *> &keyMap) = 0;
};
