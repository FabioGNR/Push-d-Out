#pragma once

#include "FpsCounter.h"
#include "ui/PlayerInfo.h"

#include <engine/ecs/World.h>
#include <engine/graphics/Camera.h>
#include <engine/graphics/drawable/Surface.h>
#include <engine/input/InputManager.h>
#include <engine/ui/UISystem.h>
#include <engine/window/Window.h>

#include <array>
#include <map>
#include <vector>

namespace game::hud {
class HUD {
private:
    engine::ecs::World& m_world;
    engine::Window& m_window;
    engine::graphics::Camera* m_camera;

    std::map<engine::ecs::EntityId, std::unique_ptr<ui::PlayerInfo>> m_playerInfo;
    std::array<std::pair<common::Vector2D<int>, common::Vector2D<int>>, 4> m_hudSize;

    bool m_showFps = false;
    game::hud::FpsCounter m_fpsCounter;
    int m_foundPlayers = 0;

    std::shared_ptr<engine::events::Subscription<engine::input::maps::AnalogMap>> m_fpsKeySubscription;

    engine::input::InputManager& m_inputManager;

public:
    HUD(engine::Window&, engine::ecs::World&, engine::graphics::Camera*, engine::input::InputManager&);
    ~HUD();

    void update(std::chrono::nanoseconds);
    void render(engine::IRenderer&);

private:
    void updateLives();
    void updateHudTransparancy();
    void updateItems();
};
}
