//
// Created by Alex Post on 2/23/20.
//

#include "catch2/catch.hpp"
#include "Matrix.hpp"

TEST_CASE("Should perform basic matrix operations", "[matrix]") {
    Matrix m = Matrix(3, 3);
    m(0, 0) = 0;
    m(0, 1) = 1;
    m(0, 2) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;
    m(1, 2) = 5;
    m(2, 0) = 6;
    m(2, 1) = 7;
    m(2, 2) = 8;

    SECTION("Should transpose correctly") {
        Matrix e = Matrix(3, 3);
        e(0, 0) = 0;
        e(0, 1) = 3;
        e(0, 2) = 6;
        e(1, 0) = 1;
        e(1, 1) = 4;
        e(1, 2) = 7;
        e(2, 0) = 2;
        e(2, 1) = 5;
        e(2, 2) = 8;
        Matrix mT = m.transpose();
        REQUIRE(e == mT);
    }
}

TEST_CASE("Should initialize properly", "[matrix]") {

    SECTION("Should be created with zeros") {
        Matrix m = Matrix(3, 3);
        for (int i = 0; i < 3; i ++) {
            for (int j = 0; j < 3; j ++) {
                REQUIRE(m(i, j) == 0);
            }
        }
    }

    SECTION("Should be mutable") {
        Matrix m = Matrix(3, 3);
        m(1, 2) = 5;
        m(2, 0) = 3;

        REQUIRE(m(1, 2) == 5);
        REQUIRE(m(2, 0) == 3);
    }

    SECTION("Should be created with copy constructor") {
        Matrix m = Matrix(3, 3);
        Matrix m2 = m;
        m2(1, 0) = 5;

        REQUIRE(m(1, 0) == 0);
        REQUIRE(m2(1, 0) == 5);
    }

    SECTION("Should be created with copy assignment operator") {
        Matrix m = Matrix(3, 3);
        Matrix m2;
        m2 = m;
        m2(1, 0) = 5;

        REQUIRE(m(1, 0) == 0);
        REQUIRE(m2(1, 0) == 5);
    }
}