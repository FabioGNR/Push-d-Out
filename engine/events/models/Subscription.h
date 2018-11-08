#pragma once

#include <functional>
#include <map>
#include <utility>

namespace engine {
namespace events {
    template <typename T>
    struct Subscription {
        std::function<void(T, events::Subscription<T>&)> update;
        bool isActive;
        int subbedTo;

        Subscription(std::function<void(T, events::Subscription<T>&)> update, int id)
            : update { std::move(update) }
            , isActive { true }
            , subbedTo { id } {};
        Subscription(const Subscription& other) = default;
        Subscription& operator=(const Subscription& other) = default;

        Subscription(Subscription&& other) = default;
        Subscription& operator=(Subscription&& other) = default;
        virtual ~Subscription() = default;

        void close()
        {
            isActive = false;
        }
    };
}
}
