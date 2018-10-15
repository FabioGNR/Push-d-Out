#pragma once

#include <InputHandeling/Keys.h>
#include "IEvent.h"

class IControlEvent : public IEvent {
public:
    virtual Keys getValue() = 0;
};
