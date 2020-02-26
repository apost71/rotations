//
// Created by Alex Post on 2/25/20.
//

#include <Vector.hpp>
#include "catch2/catch.hpp"

TEST_CASE("Should initialize correctly", "[vector]") {

    SECTION("Should initialize with zeros") {
        Vector v = Vector(5);
        for (int i = 0; i < v.getLength(); i ++ ) {
            REQUIRE(v[i] == 0);
        }
        REQUIRE(v.getLength() == 5);
    }

    SECTION("Should be able to alter just one value") {
        Vector v = Vector(5);
        v[0] = 1;
        REQUIRE(v[0] == 1);
        for (int i = 1; i < v.getLength(); i ++) {
            REQUIRE(v[i] == 0);
        }
    }

    SECTION("Should initialize with initializer list") {
        Vector v = Vector({0, 1, 2});
        REQUIRE(v.getLength() == 3);
        for (int i = 0; i < v.getLength(); i ++) {
            REQUIRE(v[i] == i);
        }
    }
}

TEST_CASE("Should copy properly", "[vector]") {
    Vector v = Vector({0, 1, 2});

    SECTION("Should use copy constructor") {
        Vector v2 = v;
        v2[0] = 3;

        REQUIRE(v2[0] == 3);
        REQUIRE(v[0] == 0);
    }

    SECTION("Should use copy assignment operator") {
        Vector v2;
        v2 = v;
        v2[0] = 3;

        REQUIRE(v2[0] == 3);
        REQUIRE(v[0] == 0);
    }
}

TEST_CASE("Should perform vector operations") {

    SECTION("Should compute norm") {
        Vector v = Vector({1, 2, 3});
        REQUIRE(v.norm() == 3.7416573867739413);
    }
}