#pragma once

#include <engine/graphics/drawable/Font.h>
#include <engine/graphics/drawable/RectangleShape.h>

#include <array>
#include <functional>
#include <memory>

namespace engine {
class IRenderer;
}

namespace game::level::editor::ui {
struct KeyboardButton {
    engine::RectangleShape buttonShape;
    engine::Font buttonText;
    std::function<void()> onClick;
};

template <size_t T>
struct KeyboardRow {
    const size_t NUM_BUTTONS = T;
    std::array<std::unique_ptr<KeyboardButton>, T> buttons;
};

struct TextInput {
    engine::RectangleShape boundingBox;
    engine::Font text;
};

class KeyboardScreen {
    TextInput m_textInput;

    KeyboardRow<10> m_numRow{};
    KeyboardRow<10> m_qRow{};
    KeyboardRow<9> m_aRow{};
    KeyboardRow<7> m_zRow{};

    KeyboardRow<2> m_OkCancelRow{};

    int m_currentX{};
    int m_currentY{};

public:
    explicit KeyboardScreen(const common::Vector2D<int>& screenSize);
    void move(int x, int y);
    void makeSelection();
    void draw(engine::IRenderer& renderer);

    const std::string& getInputText() const;
    void onOk(std::function<void()> onClick);
    void onCancel(std::function<void()> onClick);

private:
    KeyboardButton* getButton(int x, int y);

    void initNumRow(const common::Vector2D<int>& buttonPositionBegin, const common::Vector2D<int>& buttonSize);
    void initQRow(const common::Vector2D<int>& buttonPositionBegin, const common::Vector2D<int>& buttonSize);
    void initARow(const common::Vector2D<int>& buttonPositionBegin, const common::Vector2D<int>& buttonSize);
    void initZRow(const common::Vector2D<int>& buttonPositionBegin, const common::Vector2D<int>& buttonSize);
    void initOkCancelRow(const common::Vector2D<int>& buttonPositionBegin, const common::Vector2D<int>& buttonSize);

    template <size_t N>
    void makeKeyboardRow(
        KeyboardRow<N>& row,
        const std::array<const char*, N>& keyboardText,
        const common::Vector2D<int>& buttonPositionBegin,
        const common::Vector2D<int>& buttonSize,
        const std::function<void(size_t)>& func)
    {
        for (size_t i = 0; i < row.NUM_BUTTONS; ++i) {
            row.buttons.at(i) = std::make_unique<KeyboardButton>(KeyboardButton{
                engine::RectangleShape{
                    common::Vector2D<int>{ static_cast<int>(buttonPositionBegin.x + i * buttonSize.x), buttonPositionBegin.y },
                    buttonSize,
                    engine::Color(0, 0, 0, 255) },
                engine::Font{
                    "assets/fonts/Pixeled.ttf",
                    keyboardText.at(i),
                    32,
                    engine::Color{ 255, 255, 255, 255 },
                    common::Vector2D<int>{ static_cast<int>(buttonPositionBegin.x + i * buttonSize.x + buttonSize.x / 2), buttonPositionBegin.y } },
                [i, func]() {
                    func(i);
                } });
        }
    }
};
}
