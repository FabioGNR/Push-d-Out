#pragma once

#include "IControlEvent.h"

class KeyEvent : public IControlEvent {
private:
    Keys value;
    bool pressed;
public:
    KeyEvent(Keys value, bool pressed);
    void printType() override;
    Keys getValue() override;
};
