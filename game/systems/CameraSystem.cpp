#include "CameraSystem.h"
namespace game {
namespace systems {

    void CameraSystem::update(std::chrono::nanoseconds timeStep)
    {
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timeStep);
        auto pos = m_camera->getPosition();
        pos.x += milliseconds.count() * 0.0001;
        m_camera->setPosition(pos);
    }

    void CameraSystem::render(engine::IRenderer& /*renderer*/)
    {

    }
}
}