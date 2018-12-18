#pragma once

#include <engine/game/State.h>
#include <engine/ui/UISystem.h>
#include <game/Game.h>
#include <utility>

namespace game {
class ScoreState : public engine::State {
private:
    common::Vector2D<int> m_screenSize{};
    std::unique_ptr<engine::ui::UISystem> m_UISystem;
    std::map<std::string, long int> m_score{};

public:
    ScoreState(engine::IGame& context, std::map<std::string, long int> score)
        : engine::State{ context }
        , m_score{ std::move(score) }
    {
        auto& game = dynamic_cast<Game&>(m_context);
        m_screenSize = game.getScreenSize();
        m_UISystem = std::make_unique<engine::ui::UISystem>(game.getInputManager());
    }
    void update(std::chrono::nanoseconds timeStep) override;
    void render(engine::IRenderer& renderer) override;
    void init() override;
    void resume() override;
    void pause() override;
    void close() override;
};
}
