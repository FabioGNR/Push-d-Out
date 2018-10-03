#include "UnknownEvent.h"

void UnknownEvent::printType()
{
    //std::cout << "Unknown Event: " << std::endl;
}

void UnknownEvent::store(std::vector<IEvent*>* controlEvents, std::vector<IEvent*>* otherEvents)
{
    otherEvents->push_back(this);
}