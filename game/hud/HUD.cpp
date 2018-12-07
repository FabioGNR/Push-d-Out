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
    m_hudSize.at(0) = std::pair(common::Vector2D<int>{ 0, 0 }, size);
    m_hudSize.at(1) = std::pair(common::Vector2D<int>{ windowSize.x - size.x, 0 }, size);
    m_hudSize.at(2) = std::pair(common::Vector2D<int>{ 0, windowSize.y - size.y }, size);
    m_hudSize.at(3) = std::pair(common::Vector2D<int>{ windowSize.x - size.x, windowSize.y - size.y }, size);
}

HUD::~HUD()
{
    m_fpsKeySubscription->close();
}

void HUD::update(std::chrono::nanoseconds /* timestep */)
{
    updateHudTransparancy();
    updateLives();
    updateItems();
}

void HUD::render(engine::IRenderer& renderer)
{
    for (const auto& playerIdAndInfo : m_playerInfo) {
        renderer.draw(*playerIdAndInfo.second);
    }

    if (m_showFps) {
        renderer.draw(m_fpsCounter);
    }
}

void HUD::updateLives()
{
    m_foundPlayers = 0;
    m_world.forEachEntityWith<components::LifeComponent>([&](engine::ecs::Entity& entity) {
        // 4 is max players atm
        if (m_foundPlayers < 4) {
            // Assign new player to PlayerInfo UI
            if (m_playerInfo.count(entity.id()) == 0) {
                auto size = m_hudSize.at(m_foundPlayers);
                m_playerInfo[entity.id()] = std::make_unique<ui::PlayerInfo>(&entity, "P" + std::to_string(m_foundPlayers + 1), size.first, size.second, m_foundPlayers % 2);
                ++m_foundPlayers;
            }
        }

        const auto lives = m_world.getComponent<components::LifeComponent>(entity).count;

        auto* playerInfo = m_playerInfo.at(entity.id()).get();
        playerInfo->setRemainingLifes(lives);
        if (lives <= 0) {
            playerInfo->setAlpha(75);
        }
    });
}

void HUD::updateHudTransparancy()
{
    for (auto& surface : m_playerInfo) {
        surface.second->setAlpha(255);
    }

    m_world.forEachEntityWith<components::PlayerInputComponent, components::PositionComponent>([&](auto& entity) {
        auto pos = m_world.getComponent<components::PositionComponent>(entity).position;
        const auto screenPos = m_camera->translatePosition(pos);
        if (m_camera->isPointVisible(pos)) {
            for (auto& surface : m_playerInfo) {
                const auto& surfacePos = surface.second->position();
                const auto& surfaceSize = surface.second->size();

                if (screenPos.x >= surfacePos.x && screenPos.x <= surfacePos.x + surfaceSize.x
                    && screenPos.y >= surfacePos.y && screenPos.y <= surfacePos.y + surfaceSize.y) {
                    surface.second->setAlpha(100); // if player is behind HUD, change to alpha
                }
            }
        }
    });
}

void HUD::updateItems()
{
    std::for_each(m_playerInfo.begin(), m_playerInfo.end(), [&](auto& surface) {
        surface.second->update(m_world);
    });
}
}
