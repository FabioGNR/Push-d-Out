#include <Catch/catch2.hpp>
#include "engine/common/Vector2D.h"

using Vector2D = common::Vector2D;

TEST_CASE("Vector2D's can handle basic arithmetics") {
    common::Vector2D testVector(3, 4);
    SECTION("Magnitude")
    REQUIRE(testVector.magnitude() == 5);
}

TEST_CASE("Vector2D's have basic mathematical properties") {
    common::Vector2D testVector(0.5,5);
    SECTION("Equals") {
        REQUIRE(testVector == Vector2D(0.5, 5));
        REQUIRE(testVector != Vector2D(5, 0.5));
        REQUIRE(testVector != Vector2D(0.5, 4));
    }
    SECTION("Min") {
        REQUIRE(testVector.min(Vector2D(1, 1)) == Vector2D(0.5, 1));
        REQUIRE(testVector.min(Vector2D(1, 1)) != Vector2D(1, 1));
        REQUIRE(testVector.min(Vector2D(1, 1)) == Vector2D(0.5, 5));
    }
    SECTION("Max") {
        REQUIRE(testVector.max(Vector2D(1, 1)) == Vector2D(1, 5));
        REQUIRE(testVector.max(Vector2D(1, 1)) != Vector2D(0.5, 5));
        REQUIRE(testVector.max(Vector2D(1, 1)) == Vector2D(1, 1));
    }
}
