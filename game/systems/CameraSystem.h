#pragma once

#include <chrono>
#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/graphics/Camera.h>
#include <engine/graphics/IRenderer.h>
#include <memory>

namespace game::systems {
class CameraSystem : public engine::ecs::BaseSystem<CameraSystem> {
public:
    explicit CameraSystem(engine::ecs::World* ecsWorld, engine::graphics::Camera* camera)
        : m_camera{ camera }
        , m_ecsWorld{ ecsWorld }
    {
        m_currentPosition = m_camera->getPosition();
    };

    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;

private:
    static const common::Vector2D<double> PADDING;
    static const common::Vector2D<double> CAMERA_SAFE_ZONE_MARGIN;
    static constexpr double CAMERA_MOVEMENT_SPEED = 3;
    static constexpr double CAMERA_MOVEMENT_SPEED_FAST = 20;

    common::Vector2D<double> m_currentPosition;
    common::Vector2D<double> m_lastCenter;
    double m_moveSpeed;

    engine::graphics::Camera* m_camera;
    engine::ecs::World* m_ecsWorld;

    struct Boundaries {
        common::Vector2D<double> center;
        common::Vector2D<double> size;
    };

    void setCameraMoveSpeed();
    Boundaries findTargetBoundaries();
    common::Vector2D<double> getLevelDimensions() const;
    double findSmoothZoom(Boundaries boundaries, double seconds);
    common::Vector2D<double> findNextPosition(Boundaries boundaries, double seconds);
    bool isWithinLevel(common::Vector2D<double> point, common::Vector2D<double> dimensions) const;
    bool isOutOfSafeCameraBounds(common::Vector2D<double> point, common::Vector2D<double> dimensions) const;
};
}
