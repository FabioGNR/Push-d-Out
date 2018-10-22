#pragma once

#include <exception>
#include <string>

struct ResourceNotFoundException : public std::exception {
    std::string file;

    ResourceNotFoundException(std::string file)
        : file(std::move(file))
    {
    }

    const char* what() const noexcept override
    {
        const std::string message = "Could not find resource '" + file + "'.";
        return message.c_str();
    }
};
