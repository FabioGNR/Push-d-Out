#include <Catch/catch2.hpp>
#include "engine/input/maps/InputMap.h"

using namespace engine::input;

TEST_CASE("InputMap::setKeyState correctly sets PRESSED_AND_RELEASED state")
{
    maps::InputMap map;
    SECTION("Pressed -> released")
    map.setValue(Keys::A, KeyStates::PRESSED);
    REQUIRE(map.getKeyState(Keys::A) == KeyStates::PRESSED);
    map.setValue(Keys::A, KeyStates::RELEASED);
    REQUIRE(map.getKeyState(Keys::A) == KeyStates::PRESSED_AND_RELEASED);
}

TEST_CASE("InputMap::update correctly sets DOWN state")
{
    maps::InputMap map;
    SECTION("Pressed -> down")
    map.setValue(Keys::A, KeyStates::PRESSED);
    REQUIRE(map.getKeyState(Keys::A) == KeyStates::PRESSED);
    map.update();
    REQUIRE(map.getKeyState(Keys::A) == KeyStates::DOWN);
}

TEST_CASE("InputMap::update correctly sets UP state")
{
    maps::InputMap map;
    SECTION("Released -> up")
    map.setValue(Keys::A, KeyStates::RELEASED);
    REQUIRE(map.getKeyState(Keys::A) == KeyStates::RELEASED);
    map.update();
    REQUIRE(map.getKeyState(Keys::A) == KeyStates::UP);
}

TEST_CASE("InputMap::hasKeyState correctly returns state when key state is PRESSED")
{
    maps::InputMap map;
    map.setValue(Keys::A, KeyStates::PRESSED);
    SECTION("PRESSED")
    REQUIRE(map.hasKeyState(Keys::A, KeyStates::PRESSED));
    SECTION("RELEASED")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::RELEASED));
    SECTION("DOWN")
    REQUIRE(map.hasKeyState(Keys::A, KeyStates::DOWN));
    SECTION("UP")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::UP));
    SECTION("PRESSED_AND_RELEASED")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::PRESSED_AND_RELEASED));
}

TEST_CASE("InputMap::hasKeyState correctly returns state when key state is DOWN")
{
    maps::InputMap map;
    map.setValue(Keys::A, KeyStates::DOWN);
    SECTION("PRESSED")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::PRESSED));
    SECTION("RELEASED")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::RELEASED));
    SECTION("DOWN")
    REQUIRE(map.hasKeyState(Keys::A, KeyStates::DOWN));
    SECTION("UP")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::UP));
    SECTION("PRESSED_AND_RELEASED")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::PRESSED_AND_RELEASED));
}

TEST_CASE("InputMap::hasKeyState correctly returns state when key state is UP")
{
    maps::InputMap map;
    map.setValue(Keys::A, KeyStates::UP);
    SECTION("PRESSED")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::PRESSED));
    SECTION("RELEASED")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::RELEASED));
    SECTION("DOWN")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::DOWN));
    SECTION("UP")
    REQUIRE(map.hasKeyState(Keys::A, KeyStates::UP));
    SECTION("PRESSED_AND_RELEASED")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::PRESSED_AND_RELEASED));
}

TEST_CASE("InputMap::hasKeyState correctly returns state when key state is RELEASED")
{
    maps::InputMap map;
    map.setValue(Keys::A, KeyStates::RELEASED);
    SECTION("PRESSED")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::PRESSED));
    SECTION("RELEASED")
    REQUIRE(map.hasKeyState(Keys::A, KeyStates::RELEASED));
    SECTION("DOWN")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::DOWN));
    SECTION("UP")
    REQUIRE(map.hasKeyState(Keys::A, KeyStates::UP));
    SECTION("PRESSED_AND_RELEASED")
    REQUIRE(!map.hasKeyState(Keys::A, KeyStates::PRESSED_AND_RELEASED));
}

TEST_CASE("InputMap::hasKeyState correctly returns state when key state is PRESSED_AND_RELEASED")
{
    maps::InputMap map;
    map.setValue(Keys::A, KeyStates::PRESSED_AND_RELEASED);
    SECTION("PRESSED")
    REQUIRE(map.hasKeyState(Keys::A, KeyStates::PRESSED));
    SECTION("RELEASED")
    REQUIRE(map.hasKeyState(Keys::A, KeyStates::RELEASED));
    SECTION("DOWN")
    REQUIRE(map.hasKeyState(Keys::A, KeyStates::DOWN));
    SECTION("UP")
    REQUIRE(map.hasKeyState(Keys::A, KeyStates::UP));
    SECTION("PRESSED_AND_RELEASED")
    REQUIRE(map.hasKeyState(Keys::A, KeyStates::PRESSED_AND_RELEASED));
}