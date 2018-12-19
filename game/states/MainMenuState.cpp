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
    , m_background("assets/sprites/ui/bg.png", { 0, 0 }, { 0, 0 })
{
    auto& game = dynamic_cast<Game&>(m_context);
    m_soundManager = game.getSoundManager();
    m_background.setSize(game.getScreenSize());
}

void MainMenuState::prependButtons(engine::ui::StackPanel& panel)
{
    panel.addComponent(makeStretchedButton("START", [&]() {
        m_context.next(std::make_unique<LevelSelectorState>(m_context));
    }));

    panel.addComponent(makeStretchedButton("EDITOR", [&]() {
        m_context.next(std::make_unique<LevelEditorState>(m_context));
    }));
}

void MainMenuState::appendButtons(engine::ui::StackPanel& panel)
{
    panel.addComponent(makeStretchedButton("CREDITS", [&] {
        openCreditsFrame();
    }));
}

void MainMenuState::openCreditsFrame()
{
    m_background.setSpritePath("assets/sprites/ui/bg.png");
    auto fitSize = engine::ui::ComponentSize(
        engine::ui::ComponentSizeType::Fit,
        engine::ui::ComponentSizeType::Fit,
        common::Vector2D<double>(1, 1));

    auto creditsRootLayout = std::make_unique<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Stretch,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Horizontal);

    auto centeredLayout = std::make_unique<engine::ui::LayoutPanel>(
        fitSize,
        engine::ui::FlowDirection::Vertical);

    auto centeredStack = std::make_unique<engine::ui::StackPanel>(fitSize, engine::ui::FlowDirection::Vertical);
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("CREATED BY"), 13));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("MATTHIAS AARNOUTSE"), 12));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("ZAIN AHMAD"), 12));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("JEFFREY DUFOUR"), 12));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("RICHARD VAN DER MARK"), 12));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("FABIO WALJAARD"), 12));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("JORIS WILLIG"), 12));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("LIBRARIES"), 13));
    centeredStack->addComponent(std::make_unique<engine::ui::Label>(fitSize, std::string("SDL2 | BOX2D | SDL_IMAGE | SDL_TTF | SDL_MIXER"), 12));

    centeredStack->addComponent(makeFittedButton("BACK", [&] {
        m_background.setSpritePath("assets/sprites/ui/bg.png");
        m_uiSystem->pop();
    }));

    centeredLayout->addComponent(std::move(centeredStack), engine::ui::LayoutAnchor::Center);
    creditsRootLayout->addComponent(std::move(centeredLayout), engine::ui::LayoutAnchor::Center);
    engine::ui::Frame creditsFrame{ std::move(creditsRootLayout) };
    m_uiSystem->push(std::move(creditsFrame));
}

void MainMenuState::init()
{
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

void MainMenuState::render(engine::IRenderer& renderer)
{
    renderer.draw(m_background);
    BaseMenuState::render(renderer);
}
}
