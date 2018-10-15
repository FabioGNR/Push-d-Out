#include "KeyEvent.h"

namespace engine {
namespace events {
    void KeyEvent::printType()
    {
        std::cout << "KeyEvent: " << value << ", KeyDown: " << pressed << std::endl;
    }

    KeyEvent::KeyEvent(input::Keys value, bool pressed)
    {
        this->value = value;
        this->pressed = pressed;
    }

    input::Keys KeyEvent::getValue()
    {
        return value;
    }
}
}
