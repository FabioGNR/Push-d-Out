#pragma once
#include "IAction.h"
#include "ui/Frame.h"
#include "ui/UISystem.h"

namespace engine {
namespace ui {
    class OpenFrameAction : public IAction {
    public:
        OpenFrameAction(Frame& target, UISystem& system)
            : m_targetFrame{ target }
            , m_system{ system }
        {
        }
        void execute() override;

    private:
        Frame& m_targetFrame;
        UISystem& m_system;
    };
}
}