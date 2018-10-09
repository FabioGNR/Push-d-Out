#include "SystemManager.h"

namespace engine {
namespace ecs {
    void SystemManager::update(const double frameTime)
    {
        for (auto& mapsByPriority : m_systems) {
            for (auto& map : mapsByPriority.second) {
                map.second->update(frameTime);
            }
        }
    }
}
} // end namespace engine
