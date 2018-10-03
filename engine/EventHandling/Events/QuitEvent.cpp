#include "QuitEvent.h"

void QuitEvent::printType()
{
    std::cout << "Quit Event: " << std::endl;
}

void QuitEvent::store(std::vector<IEvent*>* controlEvents, std::vector<IEvent*>* otherEvents)
{
    otherEvents->push_back(this);
}