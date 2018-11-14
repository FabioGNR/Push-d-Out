#include "MainMenuState.h"
#include "GameState.h"
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

using namespace std::chrono_literals;

namespace game {
MainMenuState::MainMenuState(engine::IGame& context)
    : BaseMenuState(context)
    , m_soundManager(new engine::sound::SDLSoundManager)
{
    //m_uiSystem = std::make_unique<engine::ui::UISystem>();
/*
    // subscribe button press
    dynamic_cast<Game&>(m_context).getInputManager().subscribe(
        [&](engine::input::ControlMap controlMap, engine::events::Subscription<engine::input::ControlMap>& subscription) {
            if (controlMap.hasKeyState(engine::input::Keys::SPACE, engine::input::PRESSED)) {
                m_context.next(std::make_shared<GameState>(m_context));
                subscription.close(); // close stream
            }
        });*/
    //auto& game = dynamic_cast<Game&>(m_context);
    //m_uiSystem = std::make_unique<engine::ui::UISystem>(game.getInputManager());
}

void MainMenuState::prependButtons(engine::ui::StackPanel& panel)
{
    std::unique_ptr<engine::ui::IAction> startGameAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.next(std::make_shared<GameState>(m_context));
    });
    auto startButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "START");
    startButton->setAction(std::move(startGameAction));
    panel.addComponent(std::move(startButton));
}

void MainMenuState::appendButtons(engine::ui::StackPanel& panel)
{
    auto openCreditsAction = std::make_unique<engine::ui::CustomAction>([&]() {
        openCreditsFrame();
    });
    auto creditsButton = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(1, 1)),
        "CREDITS");
    creditsButton->setAction(std::move(openCreditsAction));
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
    auto goBackAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_uiSystem->pop();
    });
    auto backButton = std::make_unique<engine::ui::Button>(fitSize, std::string(" BACK "), 12);
    backButton->setAction(std::move(goBackAction));
    centeredStack->addComponent(std::move(backButton));
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
}
