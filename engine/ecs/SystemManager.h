#pragma once

#include <chrono>
#include <map>
#include <memory>
#include <unordered_map>

#include "System.h"
#include "engine/definitions/SystemPriority.h"

namespace engine {
namespace ecs {
    class SystemManager {
        std::map<definitions::SystemPriority, std::map<SystemId, std::unique_ptr<ISystem>>> m_systems;

    public:
        SystemManager() = default;
        virtual ~SystemManager() = default;

        SystemManager(const SystemManager& other) = delete;
        SystemManager& operator=(const SystemManager& other) = delete;

        SystemManager(SystemManager&& other) = default;
        SystemManager& operator=(SystemManager&& other) = default;

        template <typename System, typename... SystemArgs>
        void add(definitions::SystemPriority priority, SystemArgs&&... args)
        {
            static_assert(std::is_base_of<ISystem, System>::value,
                "System must be inherited from BaseSystem");

            m_systems[priority].insert({ System::getSystemId(),
                std::make_unique<System>(std::forward<SystemArgs>(args)...) });
        }

        void update(std::chrono::nanoseconds timeStep);
        void render(engine::IRenderer& renderer);
    };
}
}
