#pragma once

#include "InputManager.h"

class IObserver {

public:
    virtual void update() = 0;
};
