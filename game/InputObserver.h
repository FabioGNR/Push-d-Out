#pragma once

#include "input/IObserver.h"

class InputObserver : public engine::input::IObserver {
private:
public:
    void update(std::map<engine::input::Keys, engine::events::IControlEvent *> &keyMap) override;
};
