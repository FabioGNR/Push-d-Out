#pragma once

#include <exception>
#include <string>

namespace engine {
namespace exceptions {
    struct EntityNotFoundException : public std::exception {
        std::string message;

        explicit EntityNotFoundException()
            : message("Entity not found!")
        {
        }

        const char* what() const noexcept override
        {
            return message.c_str();
        }
    };
}
}
