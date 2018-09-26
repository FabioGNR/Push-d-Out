#include "QuitEvent.h"

void QuitEvent::printType()
{
    std::cout << "Quit Event: " << std::endl;
}

char QuitEvent::store()
{
    return storeType;
}