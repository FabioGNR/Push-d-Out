//
// Created by Richard on 26-9-2018.
//

#pragma once

#include "IEvent.h"

class WindowEvent : public IEvent {
private:
public:
    void printType() override;
};
