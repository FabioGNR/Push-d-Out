#include "HUD.h"

#include <engine/common/RNG.h>
#include <engine/graphics/Camera.h>
#include <game/components/LifeComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>
#include <game/exceptions/PlayerAmountOutOfBoundsException.h>

namespace game::hud {
HUD::HUD(engine::Window& window,
    engine::ecs::World& world,
    engine::graphics::Camera* camera,
    engine::input::InputManager& inputManager)
    : m_world{ world }
    , m_window{ window }
    , m_camera{ camera }
    , m_playerInfo{ nullptr }
    , m_fpsCounter({ 0, 0 })
    , m_inputManager{ inputManager }
{
    m_fpsKeySubscription = m_inputManager.subscribeAll([&](engine::input::maps::InputMap inputMap, auto&) {
        if (inputMap.getState(engine::input::Keys::F1) == engine::input::States::PRESSED) {
            m_showFps = !m_showFps;
        }
    });

    const auto& windowSize = m_window.getDimensions();
    const auto size = common::Vector2D<int>{ 300, 170 };
    m_playerInfo.at(0) = std::make_unique<ui::PlayerInfo>("P1", common::Vector2D<int>{ 0, 0 }, size);
    m_playerInfo.at(1) = std::make_unique<ui::PlayerInfo>("P2", common::Vector2D<int>{ windowSize.x - size.x, 0 }, size, true);
    m_playerInfo.at(2) = std::make_unique<ui::PlayerInfo>("P3", common::Vector2D<int>{ 0, windowSize.y - size.y }, size);
    m_playerInfo.at(3) = std::make_unique<ui::PlayerInfo>("P4", common::Vector2D<int>{ windowSize.x - size.x, windowSize.y - size.y }, size, true);
}

HUD::~HUD()
{
    m_fpsKeySubscription->close();
}

void HUD::update(std::chrono::nanoseconds /* timestep */)
{
    updateHudTransparancy();
    updatePlayerLifes();
}

void HUD::render(engine::IRenderer& renderer)
{
    for (const auto& playerIdAndInfo : m_playerInfoById) {
        renderer.draw(*playerIdAndInfo.second);
    }

    if (m_showFps) {
        renderer.draw(m_fpsCounter);
    }
}

void HUD::updatePlayerLifes()
{
    m_foundPlayers = 0;
    m_world.forEachEntityWith<components::LifeComponent>([&](engine::ecs::Entity& entity) {
        // 4 is max players atm
        if (m_foundPlayers < 4) {
            // Assign new player to PlayerInfo UI
            if (m_playerInfoById.count(entity.id()) == 0) {
                m_playerInfoById[entity.id()] = m_playerInfo.at(m_foundPlayers++).get();
            }
        }

        const auto playerLifes = m_world.getComponent<components::LifeComponent>(entity).count;

        auto* playerInfo = m_playerInfoById.at(entity.id());
        playerInfo->setRemainingLifes(playerLifes);
        if (playerLifes <= 0) {
            playerInfo->setAlpha(75);
        }
    });
}

void HUD::updateHudTransparancy()
{
    for (auto& surface : m_playerInfo) {
        surface->setAlpha(255);
    }

    m_world.forEachEntityWith<components::PlayerInputComponent, components::PositionComponent>([&](auto& entity) {
        auto pos = m_world.getComponent<components::PositionComponent>(entity).position;
        const auto screenPos = m_camera->translatePosition(pos);
        if (m_camera->isPointVisible(pos)) {
            for (auto& surface : m_playerInfo) {
                const auto& surfacePos = surface->position();
                const auto& surfaceSize = surface->size();

                if (screenPos.x >= surfacePos.x && screenPos.x <= surfacePos.x + surfaceSize.x
                    && screenPos.y >= surfacePos.y && screenPos.y <= surfacePos.y + surfaceSize.y) {
                    surface->setAlpha(100); // if player is behind HUD, change to alpha
                }
            }
        }
    });
}
}
