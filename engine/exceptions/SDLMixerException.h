#pragma once

#include <exception>
#include <string>

struct SDLMixerException : public std::exception {
    std::string message;

    explicit SDLMixerException(std::string message)
        : message(std::move(message))
    {
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};
