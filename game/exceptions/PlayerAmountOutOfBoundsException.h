#pragma once

#include <exception>
#include <string>

namespace game {
namespace exceptions {
    struct PlayerAmountOutOfBoundsException : public std::exception {
        std::string message;

        explicit PlayerAmountOutOfBoundsException()
            : message(std::string("Maximum amount of players reached"))
        {
        }

        const char* what() const noexcept override
        {
            return message.c_str();
        }
    };
}
}
