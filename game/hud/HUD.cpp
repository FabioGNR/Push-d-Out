#include "HUD.h"
#include <engine/graphics/Camera.h>
#include <engine/graphics/drawable/Circle.h>
#include <engine/graphics/drawable/RectangleShape.h>
#include <engine/graphics/drawable/Sprite.h>
#include <engine/graphics/drawable/Surface.h>
#include <engine/ui/UISystem.h>
#include <engine/ui/components/StackPanel.h>
#include <game/components/LifeComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PositionComponent.h>
#include <game/exceptions/PlayerAmountOutOfBoundsException.h>
#include <iostream>

namespace game {
namespace hud {
    HUD::HUD(engine::Window& window,
        engine::ecs::World& world,
        engine::graphics::Camera* camera,
        engine::input::InputManager& inputManager)
        : m_world{ world }
        , m_window{ window }
        , m_camera{ camera }
        , m_inputManager{ inputManager }
    {
        m_fpsKeySubscription = m_inputManager.subscribeAll([&](engine::input::maps::InputMap inputMap, auto&) {
            if (inputMap.getState(engine::input::Keys::F1) == engine::input::States::PRESSED) {
                m_showFps = !m_showFps;
            }
        });
    }

    HUD::~HUD()
    {
        m_fpsKeySubscription->close();
    }

    void HUD::update(std::chrono::nanoseconds /* timestep */)
    {
        size_t amount = m_players.size();

        m_players.clear();
        m_lives.clear();
        m_world.forEachEntityWith<components::PlayerInputComponent,
            components::LifeComponent>([&](engine::ecs::Entity& entity) {
            m_players.push_back(entity.id());
            m_lives[entity.id()] = &m_world.getComponent<components::LifeComponent>(entity);
            if (m_players.size() > AMOUNT) {
                throw exceptions::PlayerAmountOutOfBoundsException();
            }
        });
        std::sort(m_players.begin(), m_players.end());

        if (amount != m_players.size()) { // update
            setPlayerHUDs();
        }

        // reset all alpha's
        for (auto& surface : m_playerHUDs) {
            surface.second->alpha(255);
        }

        m_world.forEachEntityWith<components::PlayerInputComponent, components::PositionComponent>([&](auto& entity) {
            auto pos = m_world.getComponent<components::PositionComponent>(entity).position;
            if (m_camera->isPointVisible(pos)) {
                auto screenPos = m_camera->translatePosition(pos);
                for (auto& surface : m_playerHUDs) {
                    auto surfacePos = surface.second->position();
                    auto surfaceSize = surface.second->size();
                    if (screenPos.x >= surfacePos.x && screenPos.x <= surfacePos.x + surfaceSize.x
                        && screenPos.y >= surfacePos.y && screenPos.y <= surfacePos.y + surfaceSize.y) {
                        surface.second->alpha(100); // if player is behind HUD, change to alpha
                    }
                }
            }
        });

        for (auto& lifeEntity : m_lives) {
            if (lifeEntity.second->count == 0) {
                auto& surface = m_playerHUDs[lifeEntity.first];
                surface->alpha(75);
            }

            auto hearts = m_hearts[lifeEntity.first];
            size_t count = 0;
            int lives = lifeEntity.second->count;
            for (auto& heart : hearts) {
                if (lives > 0) {
                    heart->spritePath("assets/sprites/heart-0.png");
                } else {
                    heart->spritePath("assets/sprites/heart-1.png");
                }
                ++count;
                --lives;
            }
        }
    }

    void HUD::setPlayerHUDs()
    {
        m_playerHUDs.clear();
        m_shapes.clear();

        int i = 1;
        auto size = common::Vector2D<int>{ m_window.getDimensions().x / SCALE, m_window.getDimensions().y / SCALE };
        engine::Color white{ 255, 255, 255, 255 };

        for (auto it = m_players.begin(); it != m_players.end(); ++it, ++i) {
            if (i == 1) {
                auto pos = common::Vector2D<int>{ 0, 0 };
                m_playerHUDs[*it] = std::make_unique<engine::Surface>(pos, size, 255);
                m_shapes[*it].push_back(std::make_unique<engine::Circle>(common::Vector2D<double>(80, 100),
                    50.0,
                    white,
                    true));
                m_shapes[*it].push_back(std::make_unique<engine::Circle>(common::Vector2D<double>(50.0, 50.0),
                    30.0,
                    white,
                    true));
                m_shapes[*it].push_back(std::make_unique<engine::Circle>(common::Vector2D<double>(150, 80),
                    30.0,
                    white,
                    true));
                m_shapes[*it].push_back(std::make_unique<engine::Font>("assets/fonts/8bit.ttf",
                    "P1",
                    24,
                    white,
                    common::Vector2D<int>(pos.x + 150, pos.y + 120)));

                auto heart1 = std::make_unique<engine::Sprite>("assets/sprites/heart-0.png",
                    common::Vector2D<int>(pos.x + 100, pos.y + 15),
                    common::Vector2D<int>(16, 16));
                auto heart2 = std::make_unique<engine::Sprite>("assets/sprites/heart-0.png",
                    common::Vector2D<int>(pos.x + 130, pos.y + 15),
                    common::Vector2D<int>(16, 16));
                auto heart3 = std::make_unique<engine::Sprite>("assets/sprites/heart-0.png",
                    common::Vector2D<int>(pos.x + 160, pos.y + 15),
                    common::Vector2D<int>(16, 16));

                m_hearts[*it].push_back(heart1.get());
                m_hearts[*it].push_back(heart2.get());
                m_hearts[*it].push_back(heart3.get());
                m_shapes[*it].push_back(std::move(heart1));
                m_shapes[*it].push_back(std::move(heart2));
                m_shapes[*it].push_back(std::move(heart3));
            } else if (i == 2) {
                auto pos = common::Vector2D<int>{ m_window.getDimensions().x - size.x, 0 };
                m_playerHUDs[*it] = std::make_unique<engine::Surface>(pos, size, 255);
                m_shapes[*it].push_back(std::make_unique<engine::Circle>(common::Vector2D<double>(size.x - 80, 100),
                    50.0,
                    white,
                    true)); // primary
                m_shapes[*it].push_back(std::make_unique<engine::Circle>(common::Vector2D<double>(size.x - 50, 50),
                    30.0,
                    white,
                    true)); // secondary
                m_shapes[*it].push_back(std::make_unique<engine::Circle>(common::Vector2D<double>(size.x - 150, 80),
                    30.0,
                    white,
                    true)); // item
                m_shapes[*it].push_back(std::make_unique<engine::Font>("assets/fonts/8bit.ttf",
                    "P2",
                    24,
                    white,
                    common::Vector2D<int>(size.x - 200, 120)));

                auto heart1 = std::make_unique<engine::Sprite>("assets/sprites/heart-0.png",
                    common::Vector2D<int>(pos.x + 100, pos.y + 15),
                    common::Vector2D<int>(16, 16));
                auto heart2 = std::make_unique<engine::Sprite>("assets/sprites/heart-0.png",
                    common::Vector2D<int>(pos.x + 130, pos.y + 15),
                    common::Vector2D<int>(16, 16));
                auto heart3 = std::make_unique<engine::Sprite>("assets/sprites/heart-0.png",
                    common::Vector2D<int>(pos.x + 160, pos.y + 15),
                    common::Vector2D<int>(16, 16));

                m_hearts[*it].push_back(heart1.get());
                m_hearts[*it].push_back(heart2.get());
                m_hearts[*it].push_back(heart3.get());
                m_shapes[*it].push_back(std::move(heart1));
                m_shapes[*it].push_back(std::move(heart2));
                m_shapes[*it].push_back(std::move(heart3));
            } else if (i == 3) {
                auto pos = common::Vector2D<int>{ 0, m_window.getDimensions().y - size.y };
                m_playerHUDs[*it] = std::make_unique<engine::Surface>(pos, size, 255);
                m_shapes[*it].push_back(std::make_unique<engine::Circle>(common::Vector2D<double>(80, 120),
                    50.0,
                    white,
                    true)); // primary
                m_shapes[*it].push_back(std::make_unique<engine::Circle>(common::Vector2D<double>(50, 70),
                    30.0,
                    white,
                    true)); // secondary
                m_shapes[*it].push_back(std::make_unique<engine::Circle>(common::Vector2D<double>(150, 100),
                    30.0,
                    white,
                    true)); // item
                m_shapes[*it].push_back(std::make_unique<engine::Font>("assets/fonts/8bit.ttf",
                    "P3",
                    24,
                    white,
                    common::Vector2D<int>(150, 140))); // p1

                auto heart1 = std::make_unique<engine::Sprite>("assets/sprites/heart-0.png",
                    common::Vector2D<int>(pos.x + 100, pos.y + 15),
                    common::Vector2D<int>(16, 16));
                auto heart2 = std::make_unique<engine::Sprite>("assets/sprites/heart-0.png",
                    common::Vector2D<int>(pos.x + 130, pos.y + 15),
                    common::Vector2D<int>(16, 16));
                auto heart3 = std::make_unique<engine::Sprite>("assets/sprites/heart-0.png",
                    common::Vector2D<int>(pos.x + 160, pos.y + 15),
                    common::Vector2D<int>(16, 16));

                m_hearts[*it].push_back(heart1.get());
                m_hearts[*it].push_back(heart2.get());
                m_hearts[*it].push_back(heart3.get());
                m_shapes[*it].push_back(std::move(heart1));
                m_shapes[*it].push_back(std::move(heart2));
                m_shapes[*it].push_back(std::move(heart3));
            } else if (i == 4) {
                auto pos = common::Vector2D<int>{ m_window.getDimensions().x - size.x, m_window.getDimensions().y - size.y };
                m_playerHUDs[*it] = std::make_unique<engine::Surface>(pos, size, 255);
                m_shapes[*it].push_back(std::make_unique<engine::Circle>(common::Vector2D<double>(size.x - 80, 120),
                    50.0,
                    white,
                    true)); // primary
                m_shapes[*it].push_back(std::make_unique<engine::Circle>(common::Vector2D<double>(size.x - 50, 70),
                    30.0,
                    white,
                    true)); // secondary
                m_shapes[*it].push_back(std::make_unique<engine::Circle>(common::Vector2D<double>(size.x - 150, 100),
                    30.0,
                    white,
                    true)); // item
                m_shapes[*it].push_back(std::make_unique<engine::Font>("assets/fonts/8bit.ttf",
                    "P4",
                    24,
                    white,
                    common::Vector2D<int>(size.x - 200, 140))); // p1

                auto heart1 = std::make_unique<engine::Sprite>("assets/sprites/heart-0.png",
                    common::Vector2D<int>(pos.x + 100, pos.y + 15),
                    common::Vector2D<int>(16, 16));
                auto heart2 = std::make_unique<engine::Sprite>("assets/sprites/heart-0.png",
                    common::Vector2D<int>(pos.x + 130, pos.y + 15),
                    common::Vector2D<int>(16, 16));
                auto heart3 = std::make_unique<engine::Sprite>("assets/sprites/heart-0.png",
                    common::Vector2D<int>(pos.x + 160, pos.y + 15),
                    common::Vector2D<int>(16, 16));

                m_hearts[*it].push_back(heart1.get());
                m_hearts[*it].push_back(heart2.get());
                m_hearts[*it].push_back(heart3.get());
                m_shapes[*it].push_back(std::move(heart1));
                m_shapes[*it].push_back(std::move(heart2));
                m_shapes[*it].push_back(std::move(heart3));
            }
        }

        for (const auto id : m_players) {
            for (const auto& shape : m_shapes[id]) {
                m_playerHUDs[id]->draw(shape.get());
            }
        }
    }

    void HUD::render(engine::IRenderer& renderer)
    {
        if (m_showFps) {
            m_fpsCounter.render(renderer);
        }

        for (const auto id : m_players) {
            renderer.draw(*m_playerHUDs[id]);
        }
    }
}
}
