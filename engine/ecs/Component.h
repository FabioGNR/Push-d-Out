#pragma once

#include <cassert>
#include <cstdint>
#include <type_traits>

namespace engine {
namespace ecs {
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
        IComponent(const IComponent& other) = default;
        IComponent& operator=(const IComponent& other) = default;

        IComponent(IComponent&& other) = default;
        IComponent& operator=(IComponent&& other) = default;
        virtual ~IComponent();
    };

    template <typename Component>
    struct BaseComponent : public IComponent {
        static ComponentId familyId()
        {
            return internal::getComponentFamilyId<Component>();
        }
    };
}
} // end namespace engine
