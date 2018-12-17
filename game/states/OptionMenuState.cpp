#include "OptionMenuState.h"
#include <engine/ui/components/Button.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/Label.h>
#include <engine/ui/components/LayoutPanel.h>
#include <engine/ui/components/NumericSlider.h>
#include <engine/ui/components/StackPanel.h>
#include <game/Game.h>
#include <game/config/ConfigurationRepository.h>

namespace game {
OptionMenuState::OptionMenuState(engine::IGame& context)
    : engine::State(context)
{
    auto& game = dynamic_cast<Game&>(m_context);
    m_uiSystem = std::make_unique<engine::ui::UISystem>(game.getInputManager());
    m_screenSize = game.getScreenSize();
}

void OptionMenuState::init()
{
    m_currentConfig = config::ConfigurationRepository::get();

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
    auto masterLevelSlider = std::make_unique<engine::ui::NumericSlider>(levelSliderSize, 0, 100, m_currentConfig.sound.masterVolume);
    m_masterLevelSlider = masterLevelSlider.get();
    optionsStack->addComponent(std::move(masterLevelSlider));

    auto musicLevelLabel = std::make_unique<engine::ui::Label>(fitSize, "Music volume");
    optionsStack->addComponent(std::move(musicLevelLabel));
    auto musicLevelSlider = std::make_unique<engine::ui::NumericSlider>(levelSliderSize, 0, 100, m_currentConfig.sound.musicVolume);
    m_musicSlider = musicLevelSlider.get();
    optionsStack->addComponent(std::move(musicLevelSlider));

    auto sfxLevelLabel = std::make_unique<engine::ui::Label>(fitSize, "SFX volume");
    optionsStack->addComponent(std::move(sfxLevelLabel));
    auto sfxLevelSlider = std::make_unique<engine::ui::NumericSlider>(levelSliderSize, 0, 100, m_currentConfig.sound.sfxVolume);
    m_sfxSlider = sfxLevelSlider.get();
    optionsStack->addComponent(std::move(sfxLevelSlider));

    // CANCEL / OK
    auto actionsPanelSize = engine::ui::ComponentSize(
        engine::ui::ComponentSizeType::Fit,
        engine::ui::ComponentSizeType::Fit);
    actionsPanelSize.setMarginStart({ 0, 10 });

    auto actionsPanel = std::make_unique<engine::ui::StackPanel>(actionsPanelSize,
        engine::ui::FlowDirection::Vertical);

    auto cancelAction = std::make_unique<engine::ui::CustomAction>([&]() {
        m_context.previous();
    });

    actionsPanelSize.setMarginStart({ 0, 10 });
    const auto actionButtonSize = engine::ui::ComponentSize(
        engine::ui::ComponentSizeType::Minimum,
        engine::ui::ComponentSizeType::Fit,
        { 0.5, 1 });
    auto cancelSize = actionButtonSize;
    cancelSize.setMarginEnd({ 0, 5 });
    auto cancelButton = std::make_unique<engine::ui::Button>(cancelSize, "CANCEL");
    cancelButton->setAction(std::move(cancelAction));
    actionsPanel->addComponent(std::move(cancelButton));

    auto okAction = std::make_unique<engine::ui::CustomAction>([&]() {
        saveConfig();
        m_context.previous();
    });
    auto okButton = std::make_unique<engine::ui::Button>(actionButtonSize, "OK");
    okButton->setAction(std::move(okAction));
    actionsPanel->addComponent(std::move(okButton));

    optionsStack->addComponent(std::move(actionsPanel));
    centerLayout->addComponent(std::move(optionsStack), engine::ui::LayoutAnchor::Center);
    rootLayout->addComponent(std::move(centerLayout), engine::ui::LayoutAnchor::Center);
    auto frame = engine::ui::Frame(std::move(rootLayout));
    m_uiSystem->push(std::move(frame));
}

void OptionMenuState::render(engine::IRenderer& renderer)
{
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
        updateCurrentConfig();
        auto& game = dynamic_cast<Game&>(m_context);
        game.applyConfig(m_currentConfig);
    }
}

void OptionMenuState::saveConfig()
{
    config::ConfigurationRepository repository{};
    updateCurrentConfig();
    repository.save(m_currentConfig);
}

void OptionMenuState::updateCurrentConfig()
{

    m_currentConfig.sound.musicVolume = static_cast<int>(m_musicSlider->getValue());
    m_currentConfig.sound.sfxVolume = static_cast<int>(m_sfxSlider->getValue());
    m_currentConfig.sound.masterVolume = static_cast<int>(m_masterLevelSlider->getValue());
}
}