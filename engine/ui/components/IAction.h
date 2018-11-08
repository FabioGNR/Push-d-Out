#pragma once

namespace engine {
namespace ui {
    class IAction {
    public:
        IAction() = default;

        IAction(const IAction& other) = default;
        IAction& operator=(const IAction& other) = default;

        IAction(IAction&& other) = default;
        IAction& operator=(IAction&& other) = default;

        virtual ~IAction() = default;
        virtual void execute() = 0;
    };
}
}