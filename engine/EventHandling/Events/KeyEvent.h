#pragma once

#include "IEvent.h"

class KeyEvent : public IEvent {
private:
    char value;
    bool pressed;
public:
    KeyEvent(char value, bool pressed);
    void printType() override;
    void store(std::vector<IEvent*>* controlEvents, std::vector<IEvent*>* otherEvents) override;
};
