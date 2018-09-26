#pragma once

#include "IEvent.h"

class QuitEvent : public IEvent {
private:
    char storeType = 'W';

public:
    void printType() override;
    char store() override;
};
