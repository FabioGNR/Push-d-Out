#include "SystemManager.h"

namespace engine {
namespace ecs {
    void SystemManager::update(std::chrono::nanoseconds timeStep)
    {
        for (auto& mapsByPriority : m_systems) {
            for (auto& map : mapsByPriority.second) {
                map.second->update(timeStep);
            }
        }
    }

    void SystemManager::render(engine::IRenderer& renderer)
    {
        for (auto& mapsByPriority : m_systems) {
            for (auto& map : mapsByPriority.second) {
                map.second->render(renderer);
            }
        }
    }
}
} // end namespace engine
