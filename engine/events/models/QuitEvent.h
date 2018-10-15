#pragma once

#include "IOtherEvent.h"

namespace engine {
namespace events {
    class QuitEvent : public IOtherEvent {
    private:
    public:
        void printType() override;
    };
}
}
