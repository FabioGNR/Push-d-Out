#pragma once

#include <exception>
#include <string>

namespace game {
namespace exceptions {
    struct MissingCharacterSpawnException : public std::exception {
        std::string message;

        explicit MissingCharacterSpawnException()
            : message("There's not enough CharacterSpawnPoints in the level")
        {
        }

        const char* what() const noexcept override
        {
            return message.c_str();
        }
    };
}
}
