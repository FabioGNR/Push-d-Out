#pragma once

#include "FpsCounter.h"
#include "game/components/LifeComponent.h"
#include <engine/ecs/World.h>
#include <engine/graphics/Camera.h>
#include <engine/graphics/drawable/Surface.h>
#include <engine/input/InputManager.h>
#include <engine/ui/UISystem.h>
#include <engine/window/Window.h>
#include <vector>

namespace game {
namespace hud {
    class HUD {
    private:
        const int SCALE = 4;
        const size_t AMOUNT = 4;

        engine::ecs::World& m_world;
        engine::Window& m_window;
        engine::graphics::Camera* m_camera;

        std::vector<engine::ecs::EntityId> m_players;
        std::map<engine::ecs::EntityId, std::vector<std::unique_ptr<engine::IGraphicsElement>>> m_shapes;
        std::map<engine::ecs::EntityId, std::unique_ptr<engine::Surface>> m_playerHUDs;
        std::map<engine::ecs::EntityId, components::LifeComponent*> m_lives;
        std::map<engine::ecs::EntityId, std::vector<engine::Sprite*>> m_hearts;

        bool m_showFps = false;
        game::hud::FpsCounter m_fpsCounter;
        std::shared_ptr<engine::events::Subscription<engine::input::maps::InputMap>> m_fpsKeySubscription;

        engine::input::InputManager& m_inputManager;

        void setPlayerHUDs();

    public:
        HUD(engine::Window&, engine::ecs::World&, engine::graphics::Camera*, engine::input::InputManager&);
        ~HUD();

        void update(std::chrono::nanoseconds);
        void render(engine::IRenderer&);
    };
}
}
