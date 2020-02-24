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