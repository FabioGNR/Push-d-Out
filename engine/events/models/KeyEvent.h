#pragma once

#include "IControlEvent.h"

namespace engine {
namespace events {
    class KeyEvent : public IControlEvent {
    private:
        input::Keys value;
        bool pressed;

    public:
        KeyEvent(input::Keys value, bool pressed);

        void printType() override;
        input::Keys getValue() override;
    };
}
}
