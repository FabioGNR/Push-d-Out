#include "MainMenuState.h"
#include "GameState.h"
#include "LevelEditorState.h"
#include "LevelSelectorState.h"
#include "game/Game.h"

#include <engine/common/Vector2D.h>
#include <engine/game/IGame.h>
#include <engine/game/State.h>
#include <engine/sound/SDL/SDLSoundManager.h>
#include <engine/ui/components/Button.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/Label.h>
#include <engine/ui/components/LayoutPanel.h>
#include <engine/ui/components/StackPanel.h>
#include <game/config/ConfigurationRepository.h>

using namespace std::chrono_literals;

namespace game {
MainMenuState::MainMenuState(engine::IGame& context)
    : BaseMenuState(context)
{
}

void MainMenuState::prependButtons(engine::ui::StackPanel& panel)
{
    auto startButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Stretch,
            engine::ui::ComponentSizeType::Fit),
        "START");
    startButton->setAction(std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.next(std::make_unique<LevelSelectorState>(m_context));
    }));
    panel.addComponent(std::move(startButton));

    auto editorButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Stretch,
            engine::ui::ComponentSizeType::Fit),
        "EDITOR");
    editorButton->setAction(std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.next(std::make_unique<LevelEditorState>(m_context));
    }));
    panel.addComponent(std::move(editorButton));
}

void MainMenuState::appendButtons(engine::ui::StackPanel& panel)
{
    auto creditsButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Stretch,
            engine::ui::ComponentSizeType::Fit),
        "CREDITS");
    creditsButton->setAction(std::make_unique<engine::ui::CustomAction>([&]() {
        openCreditsFrame();
    }));
    panel.addComponent(std::move(creditsButton));
}

void MainMenuState::openCreditsFrame()
{
    auto fitSize = engine::ui::ComponentSize(
        engine::ui::ComponentSizeType::Fit,
        engine::ui::ComponentSizeType::Fit,
        common::Vector2D<double>(1, 1));
    auto stretchSize = engine::ui::ComponentSize(
        engine::ui::ComponentSizeType::Stretch,
        engine::ui::ComponentSizeType::Stretch,
        common::Vector2D<double>(1, 1));

    auto creditsRootLayout = std::make_unique<engine::ui::LayoutPanel>(stretchSize,
        engine::ui::FlowDirection::Vertical);
    auto centeredLayout = std::make_unique<engine::ui::LayoutPanel>(stretchSize,
        engine::ui::FlowDirection::Horizontal);
    auto centeredStack = std::make_unique<engine::ui::StackPanel>(fitSize, engine::ui::FlowDirection::Vertical);
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("PUSH'D OUT"), 14));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("CREATED BY"), 13));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("FABIO WALJAARD"), 12));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("MATTHIAS AARNOUTSE"), 12));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("RICHARD VAN DER MARK"), 12));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("ZAIN AHMAD"), 12));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("JEFFREY DUFOUR"), 12));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("JORIS WILLIG"), 12));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("LIBRARIES"), 13));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("SDL2 | BOX2D | SDL_IMAGE | SDL_TTF | SDL_MIXER"), 12));

    auto backButton = std::make_unique<engine::ui::Button>(
        fitSize, std::string(" BACK "), 12);
    backButton->setAction(std::make_unique<engine::ui::CustomAction>([&]() {
        m_uiSystem->pop();
    }));
    centeredStack->addComponent(std::move(backButton));
    centeredLayout->addComponent(std::move(centeredStack), engine::ui::LayoutAnchor::Center);
    creditsRootLayout->addComponent(std::move(centeredLayout), engine::ui::LayoutAnchor::Center);
    engine::ui::Frame creditsFrame{ std::move(creditsRootLayout) };
    m_uiSystem->push(std::move(creditsFrame));
}

void MainMenuState::init()
{
    auto& game = dynamic_cast<Game&>(m_context);
    m_soundManager = game.getSoundManager();
    engine::sound::Music music("assets/sounds/menu.wav");
    m_soundManager->play(music);
    BaseMenuState::init();
}

void MainMenuState::resume()
{
    m_soundManager->resume();
    BaseMenuState::resume();
}

void MainMenuState::pause()
{
    m_soundManager->pause();
    BaseMenuState::pause();
}

void MainMenuState::close()
{
    m_soundManager->pause();
    BaseMenuState::close();
}
}
