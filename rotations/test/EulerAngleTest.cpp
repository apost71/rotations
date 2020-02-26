//
// Created by Alex Post on 2/23/20.
//

#include <PRV.hpp>
#include "catch2/catch.hpp"
#include "EulerAngle.hpp"

TEST_CASE( "Euler Angles can perform basic operations", "[Euler_Angles]" ) {

    EulerAngle e = EulerAngle(3, 2, 1, 10, 20, 30);

    SECTION( "Should convert to DCM and back" ) {
        Matrix dcm = e.toDCM();
        EulerAngle e2 = EulerAngle(3, 2, 1);
        EulerAngle e3 = *dynamic_cast<EulerAngle*>(e2.fromDCM(dcm).get());

        REQUIRE( e == e3 );
    }

    SECTION( "Should add and subtract properly" ) {
        EulerAngle e2 = EulerAngle(3, 2, 1, 20, 10, 5);
        EulerAngle e3 = *dynamic_cast<EulerAngle*>(e.add(e2).get());
        EulerAngle e4 = *dynamic_cast<EulerAngle*>(e3.subtract(e2).get());

        REQUIRE(e == e4);
    }
}

TEST_CASE( "PRV should perform basic operations", "[PRV]" ) {

    EulerAngle e = EulerAngle(3, 2, 1, 10, 20, 30);
    PRV p = PRV();
    Matrix m = e.toDCM();
    p = *dynamic_cast<PRV *>(p.fromDCM(m).get());

    SECTION("Should convert to DCM and back") {
        PRV r;
        Matrix m2 = p.toDCM();
        r = *dynamic_cast<PRV *>(r.fromDCM(m2).get());

        REQUIRE(p == r);
    }

    SECTION("Should add and subtract properly") {
        EulerAngle e2 = EulerAngle(3, 2, 1, 20, 5, 15);
        PRV p2 = PRV();
        Matrix m2 = e.toDCM();
        p2 = *dynamic_cast<PRV *>(p2.fromDCM(m2).get());

        PRV p3 = *dynamic_cast<PRV*>(p.add(p2).get());
        PRV p4 = *dynamic_cast<PRV*>(p3.subtract(p2).get());

        REQUIRE(p == p4);
    }
}