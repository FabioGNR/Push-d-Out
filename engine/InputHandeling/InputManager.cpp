#include "InputManager.h"

void InputManager::storeInput(IControlEvent* event)
{
    char value = 'A';

    keyMap->insert(std::pair<char, IControlEvent*>(value, event));
}

void InputManager::subscribe(IObserver* observer)
{
    observers.push_back(observer);
}

void InputManager::notify()
{
    for (int i = 0; i < observers.size(); i++) {
        observers[i]->update();
    }
}