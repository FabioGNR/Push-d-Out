#pragma once

#include "IEvent.h"

class KeyEvent : public IEvent {
private:
public:
    void printType() override;
};
