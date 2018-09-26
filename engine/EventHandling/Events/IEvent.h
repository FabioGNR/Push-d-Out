//
// Created by Richard on 26-9-2018.
//

#pragma once

#include <iostream>

class IEvent {
private:
public:
    virtual void printType() = 0;
    virtual char store() = 0;
};
