#pragma once

#include <iostream>
#include <vector>

namespace engine {
namespace events {
    class IEvent {
    private:
    public:
        virtual void printType() = 0;
    };
}
}
