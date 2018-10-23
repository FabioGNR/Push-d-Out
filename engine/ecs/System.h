#pragma once

#include "graphics/IRenderer.h"
#include <chrono>
#include <cstdint>

namespace engine {
namespace ecs {
    using SystemId = uint64_t;
    namespace internal {
        inline SystemId getNextSystemId()
        {
            static SystemId id = 0;
            return id++;
        }

        template <typename System>
        inline SystemId getNextSystemFamilyId()
        {
            static SystemId familyId = getNextSystemId();
            return familyId;
        }
    } // end namespace internal

    class ISystem {
    public:
        virtual ~ISystem() = default;
        virtual void update(std::chrono::nanoseconds timeStep) = 0;
        virtual void render(engine::IRenderer& renderer) = 0;
    };

    template <typename System>
    class BaseSystem : public ISystem {
    public:
        void update(std::chrono::nanoseconds timeStep) override = 0;
        void render(engine::IRenderer& renderer) override = 0;

        static SystemId getSystemId()
        {
            return internal::getNextSystemFamilyId<System>();
        }
    };
}
} // end namespace engine