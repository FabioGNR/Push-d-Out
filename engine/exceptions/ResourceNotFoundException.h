#pragma once

#include <exception>
#include <string>

struct ResourceNotFoundException : public std::exception {
    std::string message;

    explicit ResourceNotFoundException(const std::string& file)
        : message("Could not find resource '" + file + "'.")
    {
    }

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};
