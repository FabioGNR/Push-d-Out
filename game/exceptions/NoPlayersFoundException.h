#pragma once

#include <exception>
#include <string>

namespace game {
namespace exceptions {
    struct NoPlayersFoundException : public std::exception {
        std::string message;

        explicit NoPlayersFoundException()
            : message("There are no players specified")
        {
        }

        const char* what() const noexcept override
        {
            return message.c_str();
        }
    };
}
}
