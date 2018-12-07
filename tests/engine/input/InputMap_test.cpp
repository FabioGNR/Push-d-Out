#include <Catch/catch2.hpp>
#include "engine/input/maps/InputMap.h"

using namespace engine::input;

TEST_CASE("InputMap::setKeyState correctly sets PRESSED_AND_RELEASED state")
{
    maps::InputMap map;
    SECTION("Pressed -> released")
    map.setValue(Keys::A, States::PRESSED);
    REQUIRE(map.getState(Keys::A) == States::PRESSED);
    map.setValue(Keys::A, States::RELEASED);
    REQUIRE(map.getState(Keys::A) == States::PRESSED_AND_RELEASED);
}

TEST_CASE("InputMap::update correctly sets DOWN state")
{
    maps::InputMap map;
    SECTION("Pressed -> down")
    map.setValue(Keys::A, States::PRESSED);
    REQUIRE(map.getState(Keys::A) == States::PRESSED);
    map.update();
    REQUIRE(map.getState(Keys::A) == States::DOWN);
}

TEST_CASE("InputMap::update correctly sets UP state")
{
    maps::InputMap map;
    SECTION("Released -> up")
    map.setValue(Keys::A, States::RELEASED);
    REQUIRE(map.getState(Keys::A) == States::RELEASED);
    map.update();
    REQUIRE(map.getState(Keys::A) == States::UP);
}

TEST_CASE("InputMap::hasState correctly returns state when key state is PRESSED")
{
    maps::InputMap map;
    map.setValue(Keys::A, States::PRESSED);
    SECTION("PRESSED")
    REQUIRE(map.hasState(Keys::A, States::PRESSED));
    SECTION("RELEASED")
    REQUIRE(!map.hasState(Keys::A, States::RELEASED));
    SECTION("DOWN")
    REQUIRE(map.hasState(Keys::A, States::DOWN));
    SECTION("UP")
    REQUIRE(!map.hasState(Keys::A, States::UP));
    SECTION("PRESSED_AND_RELEASED")
    REQUIRE(!map.hasState(Keys::A, States::PRESSED_AND_RELEASED));
}

TEST_CASE("InputMap::hasState correctly returns state when key state is DOWN")
{
    maps::InputMap map;
    map.setValue(Keys::A, States::DOWN);
    SECTION("PRESSED")
    REQUIRE(!map.hasState(Keys::A, States::PRESSED));
    SECTION("RELEASED")
    REQUIRE(!map.hasState(Keys::A, States::RELEASED));
    SECTION("DOWN")
    REQUIRE(map.hasState(Keys::A, States::DOWN));
    SECTION("UP")
    REQUIRE(!map.hasState(Keys::A, States::UP));
    SECTION("PRESSED_AND_RELEASED")
    REQUIRE(!map.hasState(Keys::A, States::PRESSED_AND_RELEASED));
}

TEST_CASE("InputMap::hasState correctly returns state when key state is UP")
{
    maps::InputMap map;
    map.setValue(Keys::A, States::UP);
    SECTION("PRESSED")
    REQUIRE(!map.hasState(Keys::A, States::PRESSED));
    SECTION("RELEASED")
    REQUIRE(!map.hasState(Keys::A, States::RELEASED));
    SECTION("DOWN")
    REQUIRE(!map.hasState(Keys::A, States::DOWN));
    SECTION("UP")
    REQUIRE(map.hasState(Keys::A, States::UP));
    SECTION("PRESSED_AND_RELEASED")
    REQUIRE(!map.hasState(Keys::A, States::PRESSED_AND_RELEASED));
}

TEST_CASE("InputMap::hasState correctly returns state when key state is RELEASED")
{
    maps::InputMap map;
    map.setValue(Keys::A, States::RELEASED);
    SECTION("PRESSED")
    REQUIRE(!map.hasState(Keys::A, States::PRESSED));
    SECTION("RELEASED")
    REQUIRE(map.hasState(Keys::A, States::RELEASED));
    SECTION("DOWN")
    REQUIRE(!map.hasState(Keys::A, States::DOWN));
    SECTION("UP")
    REQUIRE(map.hasState(Keys::A, States::UP));
    SECTION("PRESSED_AND_RELEASED")
    REQUIRE(!map.hasState(Keys::A, States::PRESSED_AND_RELEASED));
}

TEST_CASE("InputMap::hasState correctly returns state when key state is PRESSED_AND_RELEASED")
{
    maps::InputMap map;
    map.setValue(Keys::A, States::PRESSED_AND_RELEASED);
    SECTION("PRESSED")
    REQUIRE(map.hasState(Keys::A, States::PRESSED));
    SECTION("RELEASED")
    REQUIRE(map.hasState(Keys::A, States::RELEASED));
    SECTION("DOWN")
    REQUIRE(map.hasState(Keys::A, States::DOWN));
    SECTION("UP")
    REQUIRE(map.hasState(Keys::A, States::UP));
    SECTION("PRESSED_AND_RELEASED")
    REQUIRE(map.hasState(Keys::A, States::PRESSED_AND_RELEASED));
}