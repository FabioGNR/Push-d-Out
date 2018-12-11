#pragma once
#include <engine/game/State.h>
#include <engine/ui/UISystem.h>
#include <engine/ui/components/NumericSlider.h>
#include <game/config/Configuration.h>
#include <memory>

namespace game {
class OptionMenuState : public engine::State {
    std::unique_ptr<engine::ui::UISystem> m_uiSystem;
    config::Configuration m_currentConfig{};
    common::Vector2D<int> m_screenSize{ 0, 0 };
    engine::ui::NumericSlider* m_sfxSlider{};
    engine::ui::NumericSlider* m_musicSlider{};
    engine::ui::NumericSlider* m_masterLevelSlider{};

    void saveConfig();

    void updateCurrentConfig();

public:
    explicit OptionMenuState(engine::IGame& context);

    void update(std::chrono::nanoseconds timeStep) override;

    void render(engine::IRenderer& renderer) override;

    void init() override;

    void resume() override;

    void pause() override;

    void close() override;
};
}