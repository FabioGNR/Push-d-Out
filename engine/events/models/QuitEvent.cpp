#include "QuitEvent.h"

namespace engine {
namespace events {
    void QuitEvent::printType()
    {
        std::cout << "Quit Event: " << std::endl;
    }
}
}
