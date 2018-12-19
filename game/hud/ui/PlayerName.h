#pragma once

#include <engine/graphics/IGraphicsElement.h>
#include <engine/graphics/drawable/Sprite.h>
#include <game/builders/SpriteBuilder.h>

#include <cctype>
#include <memory>
#include <string>
#include <vector>

namespace game::hud::ui {
class PlayerName : public engine::IGraphicsElement {
public:
    enum class Color {
        GREEN,
        BLUE,
        RED,
        YELLOW
    };

private:
    std::string m_name;
    Color m_color;
    common::Vector2D<int> m_beginPosition;
    common::Vector2D<int> m_letterSize;
    std::vector<engine::Sprite> m_sprites;

public:
    PlayerName(const std::string& name, Color color, const common::Vector2D<int>& beginPosition, const common::Vector2D<int>& letterSize)
        : m_name(name)
        , m_color(color)
        , m_beginPosition(beginPosition)
        , m_letterSize(letterSize)
    {
        generate();
    }

    ~PlayerName() override = default;

    void draw(const engine::IRenderer& renderer) const override;

    const common::Vector2D<int>& position() const override;

    void setPosition(const common::Vector2D<int>& position) override;

private:
    void generate()
    {
        const auto colorAsString = [&]() -> std::string {
            switch (m_color) {
            case Color::RED:
                return "red";
            case Color::GREEN:
                return "green";
            case Color::BLUE:
                return "blue";
            case Color::YELLOW:
                return "yellow";
            default:
                return "";
            }
        }();

        game::builders::SpriteBuilder builder("assets/sprites/font/font.png", "assets/sprites/font/font.json");
        const auto map = builder.build();
        m_sprites.clear();

        for (size_t i = 0; i < m_name.size(); ++i) {
            const auto& sprites = map.at(colorAsString).sprites;
            const auto& selectedSprite = std::isdigit(m_name[i]) ? sprites[m_name[i] - '0'] : sprites[std::tolower(m_name[i]) - 'a' + 10];

            auto sprite = engine::Sprite(selectedSprite.spriteSheet, selectedSprite.offset, selectedSprite.size, selectedSprite.position);
            sprite.setSize(m_letterSize);
            sprite.setPosition(m_beginPosition + common::Vector2D<int>((m_letterSize.x * i) / 2, 0));

            m_sprites.push_back(std::move(sprite));
        }
    }
};
}
