#pragma once

#include "InputHandeling/IObserver.h"

class InputObserver : public IObserver {
private:
public:
    void update(std::map<Keys, IControlEvent *> &keyMap) override;
};
