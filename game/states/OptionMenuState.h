#pragma once
#include <engine/game/State.h>
#include <engine/ui/UISystem.h>
#include <engine/ui/components/Button.h>
#include <engine/ui/components/NumericSlider.h>
#include <game/config/Configuration.h>
#include <memory>

namespace game {
class OptionMenuState : public engine::State {
    std::unique_ptr<engine::ui::UISystem> m_uiSystem;
    common::Vector2D<int> m_screenSize{ 0, 0 };
    engine::ui::NumericSlider* m_sfxSlider{};
    engine::ui::NumericSlider* m_musicSlider{};
    engine::ui::NumericSlider* m_masterLevelSlider{};

    config::Configuration m_currentConfig{};
    config::Configuration m_updatedConfig{};

    void saveConfig();
    void applyConfig(config::Configuration& config);

    engine::Sprite m_background;

public:
    explicit OptionMenuState(engine::IGame& context);

    void update(std::chrono::nanoseconds timeStep) override;

    void render(engine::IRenderer& renderer) override;

    void init() override;

    void resume() override;

    void pause() override;

    void close() override;

    std::unique_ptr<engine::ui::Button> makeButton(const std::string& text,
        std::function<void()> function);
};
}