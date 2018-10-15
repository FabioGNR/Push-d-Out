#include <Catch/catch2.hpp>
#include "engine/common/Vector2D.h"
#include <iostream>

using Vector2D = common::Vector2D;

TEST_CASE("Vector2D's can handle basic arithmetics") {
    Vector2D testVector(3, 4);
    SECTION("Magnitude")
        REQUIRE(testVector.magnitude() == 5);
}

TEST_CASE("Vector2D's have basic mathematical properties") {
    Vector2D testVector(0.5,5);
    SECTION("Equals") {
        REQUIRE(testVector == Vector2D(0.5, 5));
        REQUIRE(testVector !=Vector2D(5, 0.5));
        REQUIRE(testVector !=Vector2D(0.5, 4));
    }
    SECTION("Min") {
        REQUIRE(testVector.min(Vector2D(1, 1)) == Vector2D(0.5, 1));
        REQUIRE(testVector.min(Vector2D(1, 1)) != Vector2D(1, 1));
        REQUIRE(testVector.min(Vector2D(1, 1)) != Vector2D(0.5, 5));
    }
    SECTION("Max") {
        REQUIRE(testVector.max(Vector2D(1, 1)) == Vector2D(1, 5));
        REQUIRE(testVector.max(Vector2D(1, 1)) != Vector2D(0.5, 5));
        REQUIRE(testVector.max(Vector2D(1, 1)) != Vector2D(1, 1));
    }
}

TEST_CASE("Vector2D rotation") {
    Vector2D testVector(3, 5);
    SECTION("Positive angle") {
        REQUIRE(testVector.rotateCounterClockwise(270) == Vector2D(5, -3));
        REQUIRE(testVector.rotateCounterClockwise(90) == Vector2D(-5, 3));
        REQUIRE(testVector.rotateCounterClockwise(38) == Vector2D(-0.714275, 5.787038));
    }

    SECTION("negative angle") {
        REQUIRE(testVector.rotateCounterClockwise(-90) == Vector2D(5, -3));
    }

    SECTION("More than 360 degrees") {
        REQUIRE(testVector.rotateCounterClockwise(450) == Vector2D(-5, 3));
    }
}
