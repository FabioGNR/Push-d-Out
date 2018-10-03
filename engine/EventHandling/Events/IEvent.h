//
// Created by Richard on 26-9-2018.
//

#pragma once

#include <iostream>
#include <vector>

class IEvent {
private:
public:
    virtual void printType() = 0;
    virtual void store(std::vector<IEvent*>* controlEvents, std::vector<IEvent*>* otherEvents) = 0;
};
