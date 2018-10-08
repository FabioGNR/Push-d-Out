#include "InputManager.h"

void InputManager::storeInput(IControlEvent* event)
{
    char value = 'A';

    keyMap->insert(std::pair<char, IControlEvent*>(value, event));
}