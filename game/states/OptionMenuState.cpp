#include "OptionMenuState.h"
#include "BaseMenuState.h"
#include <engine/ui/components/Button.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/Label.h>
#include <engine/ui/components/LayoutPanel.h>
#include <engine/ui/components/NumericSlider.h>
#include <engine/ui/components/StackPanel.h>
#include <game/Game.h>
#include <game/config/ConfigurationRepository.h>
#include <game/ui/MenuButton.h>
#include <game/ui/MenuSlider.h>

namespace game {
OptionMenuState::OptionMenuState(engine::IGame& context)
    : engine::State(context)
    , m_background("assets/sprites/ui/bg.png", { 0, 0 }, { 0, 0 })
{
    auto& game = dynamic_cast<Game&>(m_context);
    m_uiSystem = std::make_unique<engine::ui::UISystem>(game.getInputManager());
    m_screenSize = game.getScreenSize();
    m_background.setSize(game.getScreenSize());
}

void OptionMenuState::init()
{
    m_currentConfig = config::ConfigurationRepository::get();
    m_updatedConfig = m_currentConfig;

    const engine::ui::ComponentSize fitSize{
        engine::ui::ComponentSizeType::Fit,
        engine::ui::ComponentSizeType::Fit
    };

    auto rootLayout = std::make_unique<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(engine::ui::ComponentSizeType::Fit, engine::ui::ComponentSizeType::Stretch),
        engine::ui::FlowDirection::Horizontal);
    auto centerLayout = std::make_unique<engine::ui::LayoutPanel>(fitSize, engine::ui::FlowDirection::Vertical);
    auto optionsStack = std::make_unique<engine::ui::StackPanel>(fitSize, engine::ui::FlowDirection::Vertical);
    auto optionsLabel = std::make_unique<engine::ui::Label>(fitSize, "OPTIONS");
    optionsStack->addComponent(std::move(optionsLabel));
    // Volume options
    const engine::ui::ComponentSize levelSliderSize{ engine::ui::ComponentSizeType::Minimum, engine::ui::ComponentSizeType::Fit, { 0.5, 1 } };

    auto masterLevelLabel = std::make_unique<engine::ui::Label>(fitSize, "Master volume");
    optionsStack->addComponent(std::move(masterLevelLabel));
    auto masterLevelSlider = std::make_unique<game::ui::MenuSlider>(levelSliderSize, 0, 100, m_updatedConfig.sound.masterVolume);
    m_masterLevelSlider = masterLevelSlider.get();
    optionsStack->addComponent(std::move(masterLevelSlider));

    auto musicLevelLabel = std::make_unique<engine::ui::Label>(fitSize, "Music volume");
    optionsStack->addComponent(std::move(musicLevelLabel));
    auto musicLevelSlider = std::make_unique<game::ui::MenuSlider>(levelSliderSize, 0, 100, m_updatedConfig.sound.musicVolume);
    m_musicSlider = musicLevelSlider.get();
    optionsStack->addComponent(std::move(musicLevelSlider));

    auto sfxLevelLabel = std::make_unique<engine::ui::Label>(fitSize, "SFX volume");
    optionsStack->addComponent(std::move(sfxLevelLabel));
    auto sfxLevelSlider = std::make_unique<game::ui::MenuSlider>(levelSliderSize, 0, 100, m_updatedConfig.sound.sfxVolume);
    m_sfxSlider = sfxLevelSlider.get();
    optionsStack->addComponent(std::move(sfxLevelSlider));

    // CANCEL / OK
    auto actionsPanelSize = engine::ui::ComponentSize(
        engine::ui::ComponentSizeType::Fit,
        engine::ui::ComponentSizeType::Fit);
    actionsPanelSize.setMarginStart({ 0, 10 });

    auto actionsPanel = std::make_unique<engine::ui::StackPanel>(actionsPanelSize,
        engine::ui::FlowDirection::Vertical);

    actionsPanelSize.setMarginStart({ 0, 10 });

    actionsPanel->addComponent(makeButton("CANCEL", [&] {
        auto& game = dynamic_cast<Game&>(m_context);
        game.applyConfig(m_currentConfig);
        m_context.previous();
    }));
    // dont @ me
    actionsPanel->addComponent(makeButton("    OK     ", [&] {
        saveConfig();
        m_context.previous();
    }));

    optionsStack->addComponent(std::move(actionsPanel));
    centerLayout->addComponent(std::move(optionsStack), engine::ui::LayoutAnchor::Center);
    rootLayout->addComponent(std::move(centerLayout), engine::ui::LayoutAnchor::Center);
    auto frame = engine::ui::Frame(std::move(rootLayout));
    m_uiSystem->push(std::move(frame));
}

void OptionMenuState::render(engine::IRenderer& renderer)
{
    renderer.draw(m_background);
    m_uiSystem->draw(renderer, m_screenSize);
}

void OptionMenuState::resume()
{
    m_uiSystem->setActive(true);
}

void OptionMenuState::pause()
{
    m_uiSystem->setActive(false);
}

void OptionMenuState::close()
{
    m_uiSystem->setActive(false);
}

void OptionMenuState::update(std::chrono::nanoseconds timeStep)
{
    static std::chrono::nanoseconds timeSinceUpdate = std::chrono::nanoseconds(0);
    timeSinceUpdate += timeStep;
    double msSinceUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceUpdate).count();
    if (msSinceUpdate > 500) {
        applyConfig(m_updatedConfig);
        auto& game = dynamic_cast<Game&>(m_context);
        game.applyConfig(m_updatedConfig);
    }
}

void OptionMenuState::saveConfig()
{
    config::ConfigurationRepository repository{};
    applyConfig(m_updatedConfig);
    repository.save(m_updatedConfig);
}

void OptionMenuState::applyConfig(config::Configuration& config)
{
    config.sound.musicVolume = static_cast<int>(m_musicSlider->getValue());
    config.sound.sfxVolume = static_cast<int>(m_sfxSlider->getValue());
    config.sound.masterVolume = static_cast<int>(m_masterLevelSlider->getValue());
}

std::unique_ptr<engine::ui::Button>
OptionMenuState::makeButton(const std::string& text, std::function<void()> function)
{
    auto button = std::make_unique<game::ui::MenuButton>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit,
            engine::ui::ComponentSizeType::Fit,
            common::Vector2D<double>(0.5, 1)),
        text);
    button->setAction(std::make_unique<engine::ui::CustomAction>(std::move(function)));
    return std::move(button);
}
}