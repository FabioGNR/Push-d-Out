#include "KeyEvent.h"

void KeyEvent::printType()
{
    std::cout << "KeyEvent: " << value << ", KeyDown: " << pressed << std::endl;
}

KeyEvent::KeyEvent(Keys value, bool pressed)
{
    this->value = value;
    this->pressed = pressed;
}

Keys KeyEvent::getValue()
{
    return value;
}
