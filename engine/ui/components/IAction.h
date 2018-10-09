#pragma once

namespace engine {
namespace ui {
    class IAction {
    public:
        virtual void execute() = 0;
    };
}
}