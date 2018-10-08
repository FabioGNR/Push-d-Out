#include <exception>

struct ComponentManagerNotFoundException : public std::exception {
    const char* what() const noexcept override {
        return "ComponentManager not found of the specified Component type";
    }
};
