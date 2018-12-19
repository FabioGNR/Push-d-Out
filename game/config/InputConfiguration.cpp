#include "InputConfiguration.h"
namespace game::config {
std::map<game::definitions::Action, engine::input::Keys> InputConfiguration::getKeyboardControls() const
{
    std::map<game::definitions::Action, engine::input::Keys> KBM_Controls;
    KBM_Controls[definitions::Action::Punch] = engine::input::Keys::R;
    KBM_Controls[definitions::Action::UseWeapon] = engine::input::Keys::MOUSE_BUTTON_LEFT;
    KBM_Controls[definitions::Action::UseWeaponAlternative] = engine::input::Keys::Q;
    KBM_Controls[definitions::Action::SwitchWeapon] = engine::input::Keys::X;
    KBM_Controls[definitions::Action::PickupEquippable] = engine::input::Keys::E;
    KBM_Controls[definitions::Action::MoveLeft] = engine::input::Keys::A;
    KBM_Controls[definitions::Action::MoveRight] = engine::input::Keys::D;
    KBM_Controls[definitions::Action::Jump] = engine::input::Keys::SPACE;
    KBM_Controls[definitions::Action::UseItem] = engine::input::Keys::G;
    KBM_Controls[definitions::Action::InfiniteJumpCheat] = engine::input::Keys::F10;
    KBM_Controls[definitions::Action::NoCooldownCheat] = engine::input::Keys::F11;
    KBM_Controls[definitions::Action::ResetLivesCheat] = engine::input::Keys::F12;
    return KBM_Controls;
}

std::map<game::definitions::Action, engine::input::Keys> InputConfiguration::getControllerControls() const
{
    std::map<game::definitions::Action, engine::input::Keys> controls;
    controls[definitions::Action::Jump] = engine::input::Keys::CON_A;
    controls[definitions::Action::UseItem] = engine::input::Keys::CON_LEFTSTICK;
    controls[definitions::Action::PickupEquippable] = engine::input::Keys::CON_LEFTSHOULDER;
    controls[definitions::Action::SwitchWeapon] = engine::input::Keys::CON_RIGHTSHOULDER;
    controls[definitions::Action::Punch] = engine::input::Keys::CON_Y;
    return controls;
}

std::map<game::definitions::Action, engine::input::AnalogKeys> InputConfiguration::getAnalogControls() const
{
    std::map<game::definitions::Action, engine::input::AnalogKeys> analogControls;
    analogControls[definitions::Action::UseWeapon] = engine::input::AnalogKeys::CON_TRIGGER_RIGHT;
    analogControls[definitions::Action::UseWeaponAlternative] = engine::input::AnalogKeys::CON_TRIGGER_LEFT;
    analogControls[definitions::Action::MoveLeft] = engine::input::AnalogKeys::CON_LEFTSTICK_X;
    analogControls[definitions::Action::MoveRight] = engine::input::AnalogKeys::CON_LEFTSTICK_X;
    return analogControls;
}
}