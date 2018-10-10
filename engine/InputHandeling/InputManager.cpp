#include "InputManager.h"

void InputManager::storeInput(IControlEvent* event)
{
    //char value = 'A';

    keyMap->insert(std::pair<char, IControlEvent*>(event->getValue(), event));
}

void InputManager::startInput()
{
    keyMap->clear();
}

void InputManager::subscribe(IObserver* observer)
{
    observers.push_back(observer);
}

void InputManager::notify()
{
    if (keyMap->empty()) {
        return;
    }
    for (int i = 0; i < observers.size(); i++) {
        observers[i]->update(*keyMap);
    }
}