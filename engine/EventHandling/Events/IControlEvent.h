#pragma once

#include "IEvent.h"

class IControlEvent : public IEvent {
public:
    virtual char getValue() = 0;
};
