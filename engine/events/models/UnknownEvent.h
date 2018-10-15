#pragma once

#include "IOtherEvent.h"

namespace engine {
namespace events {
    class UnknownEvent : public IOtherEvent {
    private:
    public:
        void printType() override;
    };
}
}
