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

    std::map<engine::ecs::EntityId, ui::PlayerInfo*> m_playerInfoById;
    std::array<std::unique_ptr<ui::PlayerInfo>, 4> m_playerInfo;

    bool m_showFps = false;
    game::hud::FpsCounter m_fpsCounter;
    int m_foundPlayers = 0;

    std::shared_ptr<engine::events::Subscription<engine::input::maps::InputMap>> m_fpsKeySubscription;

    engine::input::InputManager& m_inputManager;

public:
    HUD(engine::Window&, engine::ecs::World&, engine::graphics::Camera*, engine::input::InputManager&);
    ~HUD();

    void update(std::chrono::nanoseconds);
    void render(engine::IRenderer&);

private:
    void updatePlayerLifes();
    void updateHudTransparancy();
};
}
