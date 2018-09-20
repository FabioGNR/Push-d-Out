#ifndef SDL_GAME_COMPONENT_H
#define SDL_GAME_COMPONENT_H

#include <cassert>
#include <cstdint>
#include <type_traits>

namespace engine {

using ComponentId = uint64_t;

namespace internal {
    inline ComponentId getNextComponentId()
    {
        static ComponentId id = 0;
        return id++;
    }

    template <typename Component>
    inline ComponentId getComponentFamilyId()
    {
        static ComponentId familyId = getNextComponentId();
        return familyId;
    }
} // end namespace internal

struct IComponent {
    IComponent();
    virtual ~IComponent();
};

template <typename Component>
struct BaseComponent : public IComponent {
    static ComponentId familyId()
    {
        return internal::getComponentFamilyId<Component>();
    }
};

} // end namespace engine

#endif //SDL_GAME_COMPONENT_H
