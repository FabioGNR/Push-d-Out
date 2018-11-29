#include <utility>

#include "KeyboardScreen.h"

#include <engine/common/RNG.h>
#include <engine/graphics/IRenderer.h>

namespace game::level::editor::ui {

KeyboardScreen::KeyboardScreen(const common::Vector2D<int>& screenSize)
    : m_textInput{
        engine::RectangleShape{
            common::Vector2D<int>{ 0, 0 },
            common::Vector2D<int>{ screenSize.x, screenSize.y / 8 },
            engine::Color(128, 128, 128, 255) },
        engine::Font{
            "assets/fonts/Pixeled.ttf",
            "",
            24,
            engine::Color(255, 255, 255, 255),
            common::Vector2D<int>{ 0, 0 },
        }
    }
{
    const auto buttonPositionBegin = common::Vector2D<int>{ 0, screenSize.y / 8 };
    const auto buttonSize = common::Vector2D<int>{ screenSize.x / 10, screenSize.x / 10 };

    initNumRow(buttonPositionBegin, buttonSize);
    initQRow(buttonPositionBegin + common::Vector2D<int>{ 0, buttonSize.y }, buttonSize);
    initARow(buttonPositionBegin + common::Vector2D<int>{ 50, buttonSize.y * 2 }, buttonSize);
    initZRow(buttonPositionBegin + common::Vector2D<int>{ 100, buttonSize.y * 3 }, buttonSize);
    initOkCancelRow(buttonPositionBegin + common::Vector2D<int>{ 300, buttonSize.y * 4 }, common::Vector2D<int>{ buttonSize.x * 3, buttonSize.y });

    move(0, 0);
}

void KeyboardScreen::draw(engine::IRenderer& renderer)
{
    renderer.draw(m_textInput.boundingBox);
    renderer.draw(m_textInput.text);
    for (const auto& row : m_numRow.buttons) {
        renderer.draw(row->buttonShape);
        renderer.draw(row->buttonText);
    }
    for (const auto& row : m_qRow.buttons) {
        renderer.draw(row->buttonShape);
        renderer.draw(row->buttonText);
    }
    for (const auto& row : m_aRow.buttons) {
        renderer.draw(row->buttonShape);
        renderer.draw(row->buttonText);
    }
    for (const auto& row : m_zRow.buttons) {
        renderer.draw(row->buttonShape);
        renderer.draw(row->buttonText);
    }
    for (const auto& row : m_OkCancelRow.buttons) {
        renderer.draw(row->buttonShape);
        renderer.draw(row->buttonText);
    }
}

void KeyboardScreen::move(int x, int y)
{
    getButton(m_currentX, m_currentY)->buttonShape.setColor(engine::Color{ 0, 0, 0, 255 });
    m_currentY = std::clamp(m_currentY - y, 0, 4);
    switch (m_currentY) {
    case 0: {
        m_currentX = std::clamp(m_currentX + x, 0, (const int&)m_numRow.NUM_BUTTONS - 1);
    } break;
    case 1: {
        m_currentX = std::clamp(m_currentX + x, 0, (const int&)m_qRow.NUM_BUTTONS - 1);
    } break;
    case 2: {
        m_currentX = std::clamp(m_currentX + x, 0, (const int&)m_aRow.NUM_BUTTONS - 1);
    } break;
    case 3: {
        m_currentX = std::clamp(m_currentX + x, 0, (const int&)m_zRow.NUM_BUTTONS - 1);
    } break;
    case 4: {
        m_currentX = std::clamp(m_currentX + x, 0, (const int&)m_OkCancelRow.NUM_BUTTONS - 1);
    } break;
    default:
        break;
    }
    getButton(m_currentX, m_currentY)->buttonShape.setColor(engine::Color{ 128, 128, 128, 255 });
}

void KeyboardScreen::initNumRow(const common::Vector2D<int>& buttonPositionBegin, const common::Vector2D<int>& buttonSize)
{
    const std::array<const char*, 10> text = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };
    makeKeyboardRow(m_numRow, text, buttonPositionBegin, buttonSize, [&](size_t index) {
        m_textInput.text.setText(
            m_textInput.text.text() + m_numRow.buttons.at(index)->buttonText.text());
    });
}

void KeyboardScreen::initQRow(const common::Vector2D<int>& buttonPositionBegin, const common::Vector2D<int>& buttonSize)
{
    const std::array<const char*, 10> text = { "q", "w", "e", "r", "t", "y", "u", "i", "o", "p" };
    makeKeyboardRow(m_qRow, text, buttonPositionBegin, buttonSize, [&](size_t index) {
        m_textInput.text.setText(
            m_textInput.text.text() + m_qRow.buttons.at(index)->buttonText.text());
    });
}

void KeyboardScreen::initARow(const common::Vector2D<int>& buttonPositionBegin, const common::Vector2D<int>& buttonSize)
{
    const std::array<const char*, 9> text = { "a", "s", "d", "f", "g", "h", "j", "k", "l" };
    makeKeyboardRow(m_aRow, text, buttonPositionBegin, buttonSize, [&](size_t index) {
        m_textInput.text.setText(
            m_textInput.text.text() + m_aRow.buttons.at(index)->buttonText.text());
    });
}

void KeyboardScreen::initZRow(const common::Vector2D<int>& buttonPositionBegin, const common::Vector2D<int>& buttonSize)
{
    const std::array<const char*, 7> text = { "z", "x", "c", "v", "b", "n", "m" };
    makeKeyboardRow(m_zRow, text, buttonPositionBegin, buttonSize, [&](size_t index) {
        m_textInput.text.setText(
            m_textInput.text.text() + m_zRow.buttons.at(index)->buttonText.text());
    });
}

void KeyboardScreen::initOkCancelRow(
    const common::Vector2D<int>& buttonPositionBegin,
    const common::Vector2D<int>& buttonSize)
{
    const std::array<const char*, 2> text = { "Ok", "Cancel" };
    makeKeyboardRow(m_OkCancelRow, text, buttonPositionBegin, buttonSize, [&](size_t) {
        // default to empty action
    });
}

KeyboardButton* KeyboardScreen::getButton(int x, int y)
{
    switch (y) {
    case 0: {
        return m_numRow.buttons.at(x).get();
    }
    case 1: {
        return m_qRow.buttons.at(x).get();
    }
    case 2: {
        return m_aRow.buttons.at(x).get();
    }
    case 3: {
        return m_zRow.buttons.at(x).get();
    }
    case 4: {
        return m_OkCancelRow.buttons.at(x).get();
    }
    default:
        return nullptr;
    }
}

void KeyboardScreen::makeSelection()
{
    getButton(m_currentX, m_currentY)->onClick();
}

const std::string& KeyboardScreen::getInputText() const
{
    return m_textInput.text.text();
}

void KeyboardScreen::onOk(std::function<void()> onClick)
{
    m_OkCancelRow.buttons.at(0)->onClick = std::move(onClick);
}

void KeyboardScreen::onCancel(std::function<void()> onClick)
{
    m_OkCancelRow.buttons.at(1)->onClick = std::move(onClick);
}
}
