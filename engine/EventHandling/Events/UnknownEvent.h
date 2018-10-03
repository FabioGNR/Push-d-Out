#pragma once

#include "IEvent.h"

class UnknownEvent : public IEvent {
private:
public:
    void printType() override;
    void store(std::vector<IEvent *> *controlEvents, std::vector<IEvent *> *otherEvents) override;
};
