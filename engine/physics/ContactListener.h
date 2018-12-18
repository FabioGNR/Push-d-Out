#pragma once

#include "Contact.h"
#include <chrono>

namespace engine {
namespace physics {
    class ContactListener {
    public:
        virtual ~ContactListener() = default;

        virtual void beginContact(Contact& /* contact */) = 0;
        virtual void endContact(Contact& /* contact */) = 0;
        virtual void preSolve(Contact& /* contact */) = 0;
        virtual void postSolve(Contact& /* contact */) = 0;

        virtual void update(std::chrono::nanoseconds /* timeStep */) {}
    };
}
}
