#pragma once
#include "IAction.h"
#include <functional>
#include <utility>

namespace engine {
namespace ui {
    class CustomAction : public IAction {
    public:
        CustomAction(std::function<void()> executeFunc)
            : m_execute{ std::move(executeFunc) }
        {
        }
        void execute() override { m_execute(); };

    private:
        std::function<void()> m_execute;
    };
}
}