#pragma once

#include "IControlEvent.h"

class KeyEvent : public IControlEvent {
private:
    char value;
    bool pressed;
public:
    KeyEvent(char value, bool pressed);
    void printType() override;
};
