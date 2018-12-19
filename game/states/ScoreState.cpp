#include "ScoreState.h"
#include "game/states/GameState.h"
#include "game/states/LevelSelectorState.h"
#include <engine/ui/components/Button.h>
#include <engine/ui/components/CustomAction.h>
#include <engine/ui/components/Label.h>
#include <engine/ui/components/LayoutPanel.h>
#include <engine/ui/components/StackPanel.h>
#include <sstream>

namespace game {
using ScorePair = std::pair<std::string, long double>;
using Comparator = std::function<bool(ScorePair, ScorePair)>;

void ScoreState::update(std::chrono::nanoseconds /*timeStep*/)
{
}
void ScoreState::render(engine::IRenderer& renderer)
{
    m_UISystem->draw(renderer, common::Vector2D<int>(m_screenSize));
}

void ScoreState::init()
{
    const auto fitSize = engine::ui::ComponentSize(engine::ui::ComponentSizeType::Fit,
        engine::ui::ComponentSizeType::Fit);

    auto rootLayout = std::make_unique<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(
            engine::ui::ComponentSizeType::Fit, engine::ui::ComponentSizeType::Stretch,
            common::Vector2D<double>(1, 1)),
        engine::ui::FlowDirection::Horizontal);
    auto centerLayout = std::make_unique<engine::ui::LayoutPanel>(
        engine::ui::ComponentSize(fitSize),
        engine::ui::FlowDirection::Vertical);
    auto stack = std::make_unique<engine::ui::StackPanel>(
        engine::ui::ComponentSize(fitSize),
        engine::ui::FlowDirection::Vertical);

    Comparator compFunctor = [](ScorePair element1, ScorePair element2) {
        return element1.second > element2.second;
    };

    std::set<ScorePair, Comparator> scoreList(m_score.begin(), m_score.end(), compFunctor);

    for (const ScorePair &element : scoreList) {
        std::string name = element.first;
        std::stringstream s;
        auto score = std::round(element.second);

        s << name << " has a score of ";

        if (element == *scoreList.begin()) {
            s << score + 1000 /* bonus points yay */ << " (winner)";
        } else {
            s << score;
        }

        auto playerLabel = std::make_unique<engine::ui::Label>(engine::ui::ComponentSize(fitSize), s.str());
        stack->addComponent(std::move(playerLabel));
    }

    GameState::MVP = scoreList.begin()->first;

    std::unique_ptr<engine::ui::IAction> restart = std::make_unique<engine::ui::CustomAction>([&]() {
        auto* context = &m_context;
        context->clearStates();
        context->next(std::make_unique<LevelSelectorState>(*context));
    });
    auto button = std::make_unique<engine::ui::Button>(
        engine::ui::ComponentSize(fitSize),
        "Restart");
    button->setAction(std::move(restart));

    stack->addComponent(std::move(button));
    centerLayout->addComponent(std::move(stack), engine::ui::LayoutAnchor::Center);
    rootLayout->addComponent(std::move(centerLayout), engine::ui::LayoutAnchor::Center);
    auto frame = engine::ui::Frame(std::move(rootLayout));
    m_UISystem->push(std::move(frame));
}
void ScoreState::resume()
{
    m_UISystem->setActive(true);
}

void ScoreState::pause()
{
    m_UISystem->setActive(false);
}

void ScoreState::close()
{
    m_UISystem->setActive(false);
}
}
