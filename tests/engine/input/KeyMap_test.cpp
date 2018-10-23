#include <Catch/catch2.hpp>
#include "engine/input/KeyMap.h"
using namespace engine::input;

TEST_CASE("KeyMap::setKeyState correctly sets PRESSED_AND_RELEASED state") {
    KeyMap map;
    SECTION("Pressed -> released")
        map.setKeyState(Keys::A, KeyStates::PRESSED);
        REQUIRE(map.getKeyState(Keys::A) == KeyStates::PRESSED);
        map.setKeyState(Keys::A, KeyStates::RELEASED);
        REQUIRE(map.getKeyState(Keys::A) == KeyStates::PRESSED_AND_RELEASED);
}

TEST_CASE("KeyMap::update correctly sets DOWN state") {
    KeyMap map;
    SECTION("Pressed -> down")
        map.setKeyState(Keys::A, KeyStates::PRESSED);
        REQUIRE(map.getKeyState(Keys::A) == KeyStates::PRESSED);
        map.update();
        REQUIRE(map.getKeyState(Keys::A) == KeyStates::DOWN);
}

TEST_CASE("KeyMap::update correctly sets UP state") {
    KeyMap map;
    SECTION("Released -> up")
        map.setKeyState(Keys::A, KeyStates::RELEASED);
        REQUIRE(map.getKeyState(Keys::A) == KeyStates::RELEASED);
        map.update();
        REQUIRE(map.getKeyState(Keys::A) == KeyStates::UP);
}

TEST_CASE("KeyMap::hasKeyState correctly returns state when key state is PRESSED") {
    KeyMap map;
    map.setKeyState(Keys::A, KeyStates::PRESSED);
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

TEST_CASE("KeyMap::hasKeyState correctly returns state when key state is DOWN") {
    KeyMap map;
    map.setKeyState(Keys::A, KeyStates::DOWN);
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

TEST_CASE("KeyMap::hasKeyState correctly returns state when key state is UP") {
    KeyMap map;
    map.setKeyState(Keys::A, KeyStates::UP);
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

TEST_CASE("KeyMap::hasKeyState correctly returns state when key state is RELEASED") {
    KeyMap map;
    map.setKeyState(Keys::A, KeyStates::RELEASED);
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


TEST_CASE("KeyMap::hasKeyState correctly returns state when key state is PRESSED_AND_RELEASED") {
    KeyMap map;
    map.setKeyState(Keys::A, KeyStates::PRESSED_AND_RELEASED);
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