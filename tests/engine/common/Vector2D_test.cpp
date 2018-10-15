#include <Catch/catch2.hpp>
#include "engine/common/Vector2D.h"
#include <iostream>

TEST_CASE("common::Vector2D's can handle basic arithmetics") {
    common::Vector2D<int> testVector(3, 4);
    SECTION("Magnitude")
        REQUIRE(testVector.magnitude() == 5);
}

TEST_CASE("common::Vector2D's have basic mathematical properties") {
    common::Vector2D<double> testVector(0.5,5);
    SECTION("Equals") {
        REQUIRE(testVector == common::Vector2D<double>(0.5, 5));
        REQUIRE(testVector !=common::Vector2D<double>(5, 0.5));
        REQUIRE(testVector !=common::Vector2D<double>(0.5, 4));
    }
    SECTION("Min") {
        common::Vector2D<double> minVector = common::Vector2D<double>::min({1,1}, testVector);
        REQUIRE(minVector == common::Vector2D<double>(0.5, 1));
    }
    SECTION("Max") {
        common::Vector2D<double> maxVector = common::Vector2D<double>::max({1,1}, testVector);
        REQUIRE(maxVector == common::Vector2D<double>(1, 5));

    }
}

TEST_CASE("common::Vector2D rotation") {
    common::Vector2D<double> testVector(3, 5);
    SECTION("Positive angle") {
        REQUIRE(testVector.rotateCounterClockwise(270) == common::Vector2D<double>(5, -3));
        REQUIRE(testVector.rotateCounterClockwise(90) == common::Vector2D<double>(-5, 3));
        REQUIRE(testVector.rotateCounterClockwise(38) == common::Vector2D<double>(-0.714275, 5.787038));
    }

    SECTION("negative angle") {
        REQUIRE(testVector.rotateCounterClockwise(-90) == common::Vector2D<double>(5, -3));
    }

    SECTION("More than 360 degrees") {
        REQUIRE(testVector.rotateCounterClockwise(450) == common::Vector2D<double>(-5, 3));
    }
}
