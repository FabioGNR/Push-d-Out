#pragma once

#include <map>
#include <utility>
#include <functional>

namespace engine {
namespace events {
    template <typename T>
    struct Subscription {
        Subscription(std::function<void(T)> update_)
            : update{ std::move(update_) }
            , isActive{ true } {};

        ~Subscription() = default;

        std::function<void(T)> update;
        bool isActive;

        void close()
        {
            isActive = false;
        }
    };
}
}
