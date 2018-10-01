#pragma once

#include "System.h"
#include "definitions/SystemPriority.h"

#include <map>
#include <memory>
#include <unordered_map>

namespace engine {
class SystemManager {
    std::map<definitions::SystemPriority,
        std::unordered_map<SystemId, std::unique_ptr<ISystem>>>
        m_systems;

public:
    SystemManager();
    virtual ~SystemManager();

    template <typename System, typename... SystemArgs>
    void add(definitions::SystemPriority priority, SystemArgs&&... args)
    {
        static_assert(std::is_base_of<ISystem, System>::value,
            "System must be inherited from BaseSystem");

        m_systems[priority].insert({ System::getSystemId(),
            std::make_unique<System>(std::forward<SystemArgs>(args)...) });
    }

    void update(double frameTime);
};
}
