#pragma once

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
        virtual void update(double deltaTime) = 0;
    };

    template <typename System>
    class BaseSystem : public ISystem {
    public:
        void update(double deltaTime) override = 0;
        static SystemId getSystemId()
        {
            return internal::getNextSystemFamilyId<System>();
        }
    };
}
} // end namespace engine