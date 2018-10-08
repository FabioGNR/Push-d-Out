#pragma once

#include "IOtherEvent.h"

class QuitEvent : public IOtherEvent {
private:
public:
    void printType() override;
};
