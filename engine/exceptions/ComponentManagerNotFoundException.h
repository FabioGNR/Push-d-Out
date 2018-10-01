#include <exception>

struct ComponentManagerNotFoundException : public std::exception {
    const char* what() const throw()
    {
        return "ComponentManager not found of the specified Component type";
    }
};
