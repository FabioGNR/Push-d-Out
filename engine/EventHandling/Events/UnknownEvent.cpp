#include "UnknownEvent.h"

void UnknownEvent::printType()
{
    std::cout << "Unknown Event: " << std::endl;
}

char UnknownEvent::store() {
    return 'E';
}