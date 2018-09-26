#pragma once

#include "IEvent.h"

class UnknownEvent : public IEvent {
private:
public:
    void printType() override;
    char store() override;
};
