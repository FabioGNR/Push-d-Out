#pragma once

#include <exception>
#include <string>

namespace engine {
namespace exceptions {
    struct ComponentNotFoundException : public std::exception {
        std::string message;

        explicit ComponentNotFoundException()
            : message("Component not found!")
        {
        }

        const char* what() const noexcept override
        {
            return message.c_str();
        }
    };
}
}
