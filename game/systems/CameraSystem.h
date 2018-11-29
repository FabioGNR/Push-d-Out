#pragma once

#include <chrono>
#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/graphics/Camera.h>
#include <engine/graphics/IRenderer.h>
#include <memory>

namespace game {
namespace systems {
    class CameraSystem : public engine::ecs::BaseSystem<CameraSystem> {
    public:
        explicit CameraSystem(engine::ecs::World* ecsWorld, engine::graphics::Camera* camera)
            : m_camera{ camera }
            , m_ecsWorld{ ecsWorld }
        {
        }

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;

    private:
        engine::graphics::Camera* m_camera;
        engine::ecs::World* m_ecsWorld;
        bool findPlayerCenterOfMass(common::Vector2D<double>& center,
            common::Vector2D<double>& lower,
            common::Vector2D<double>& upper);
        common::Vector2D<double> getLevelDimensions() const;
        void centerOnLevel();
        bool isEntityWithinRegion(const engine::ecs::Entity& entity, const common::Vector2D<double>& region) const;
        common::Vector2D<double> clampCameraPosition(common::Vector2D<double> pos) const;
    };
}
}