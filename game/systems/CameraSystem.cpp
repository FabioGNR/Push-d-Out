#include "CameraSystem.h"
#include <cmath>

namespace game {
namespace systems {
    void CameraSystem::update(std::chrono::nanoseconds timeStep)
    {
        static long timePassed = 0;
        static bool reverse = false;
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timeStep);
        timePassed += milliseconds.count();
        double progress = timePassed / 4000.0;

        double baseZoom = 0.75;
        double zoom = baseZoom + 0.5 * (reverse ? 1 - progress : progress);
        if (progress > 1) {
            timePassed = 0;
            reverse = !reverse;
        }
        m_camera->setZoom(zoom);
    }

    void CameraSystem::render(engine::IRenderer& /*renderer*/)
    {
    }
}
}