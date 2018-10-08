#include "KeyEvent.h"

void KeyEvent::printType()
{
    std::cout << "KeyEvent: " << value << " pressed: " << pressed << std::endl;
}

KeyEvent::KeyEvent(char value, bool pressed)
{
    this->value = value;
    this->pressed = pressed;
}