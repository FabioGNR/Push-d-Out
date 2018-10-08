#pragma once

#include "IOtherEvent.h"

class UnknownEvent : public IOtherEvent {
private:
public:
    void printType() override;
};
