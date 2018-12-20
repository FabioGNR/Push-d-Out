#pragma once

#include "engine/graphics/Camera.h"
#include <engine/ecs/Entity.h>
#include <engine/ecs/System.h>
#include <engine/ecs/World.h>
#include <engine/input/InputManager.h>
#include <engine/physics/World.h>
#include <game/components/DirectionComponent.h>
#include <game/components/WeaponComponent.h>
#include <game/definitions/Action.h>
#include <game/definitions/WeaponType.h>

#include <engine/sound/ISoundManager.h>

namespace game {
namespace systems {
    using WeaponFireFunc = std::function<engine::ecs::Entity&(const engine::ecs::Entity&, const common::Vector2D<double>&, engine::physics::World*, engine::ecs::World*, engine::sound::ISoundManager*, common::Vector2D<double>& direction)>;

    class WeaponSystem : public engine::ecs::BaseSystem<WeaponSystem> {
    private:
        engine::ecs::World* m_ecsWorld;
        engine::physics::World* m_physicsWorld;
        engine::graphics::Camera* m_camera;
        engine::input::maps::InputMaps* m_inputMaps;
        engine::sound::ISoundManager* m_soundManager;

        void updateLastFiredTimers(const std::chrono::nanoseconds& timeStep) const;
        void shoot(const engine::ecs::Entity& entity, components::WeaponComponent& weapon, common::Vector2D<double>& fireDirection);
        void shootAlternative(engine::ecs::Entity& entity, components::WeaponComponent& weapon, common::Vector2D<double>& fireDirection);

        std::map<definitions::WeaponType, WeaponFireFunc> fireFunctionMap;
        std::map<definitions::WeaponType, WeaponFireFunc> altFireFunctionMap;

        void calculateDirection(const engine::ecs::Entity& entity, common::Vector2D<double>& direction, const game::components::DirectionComponent& directionComponent, bool mouse);

    public:
        WeaponSystem(engine::ecs::World* ecsWorld, engine::physics::World* physicsWorld, engine::input::InputManager* inputManager, engine::sound::ISoundManager* soundManager, engine::graphics::Camera* camera);

        void update(std::chrono::nanoseconds timeStep) override;
        void render(engine::IRenderer& renderer) override;
    };
}
}
