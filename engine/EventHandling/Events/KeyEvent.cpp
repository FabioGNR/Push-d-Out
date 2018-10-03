#include "KeyEvent.h"

void KeyEvent::printType()
{
    std::cout << "KeyEvent: " << value << " pressed: " << pressed << std::endl;
}

void KeyEvent::store(std::vector<IEvent*>* controlEvents, std::vector<IEvent*>* otherEvents)
{
    controlEvents->push_back(this);
}

KeyEvent::KeyEvent(char value, bool pressed)
{
    this->value = value;
    this->pressed = pressed;
}