#pragma once

#include <exception>
#include <string>

namespace game {
namespace exceptions {
    struct CanNotSaveConfigException : public std::exception {
        std::string message;

        explicit CanNotSaveConfigException()
            : message("Could not open file to write config")
        {
        }

        const char* what() const noexcept override
        {
            return message.c_str();
        }
    };
}
}
