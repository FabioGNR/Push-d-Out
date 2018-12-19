#include "PlayerNameSystem.h"
#include "game/states/GameState.h"
#include <game/components/DimensionComponent.h>
#include <game/components/PlayerInputComponent.h>
#include <game/components/PlayerNameComponent.h>
#include <game/components/PositionComponent.h>
#include <sstream>

namespace game {
namespace systems {
    void game::systems::PlayerNameSystem::update(std::chrono::nanoseconds /*timeStep*/)
    {
    }
    void game::systems::PlayerNameSystem::render(engine::IRenderer& renderer)
    {
        m_world->forEachEntityWith<components::PlayerNameComponent>([&](auto& entity) {
            common::Vector2D<double> position = m_world->getComponent<components::PositionComponent>(entity).position;
            common::Vector2D<double> dimension = m_world->getComponent<components::DimensionComponent>(entity).dimension;
            std::string name = m_world->getComponent<components::PlayerNameComponent>(entity).name;

            if (GameState::MVP == name) {
                // Don't draw the name above the player.
            } else {
                // Set the font
                engine::Font font{ "assets/fonts/Pixeled.ttf", name, 12, engine::Color(255, 255, 255, 255), { 0, 0 } };
                common::Vector2D<int> fontSize = renderer.calculateFontSize(font);

                // Position the name in the center of the player
                auto positionInPixels = m_camera->translatePosition(position);
                auto dimensionInPixels = m_camera->scaleSize(dimension);
                int center = positionInPixels.x + dimensionInPixels.x / 2 - fontSize.x / 2;
                common::Vector2D<int> fontPosition{ center, positionInPixels.y - dimensionInPixels.y - fontSize.y };

                font.setPosition(fontPosition);
                renderer.calculateFontSize(font);
                renderer.draw(font);
            }
        });
    }
}
}
