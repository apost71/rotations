//
// Created by Alex Post on 2/23/20.
//

#include <PRV.hpp>
#include <Quaternion.hpp>
#include <CRP.hpp>
#include "catch2/catch.hpp"
#include "EulerAngle.hpp"

TEST_CASE( "Euler Angles can perform basic operations", "[Euler_Angles]" ) {

    EulerAngle e = EulerAngle(3, 2, 1, 10, 20, 30);

    SECTION( "Should convert to DCM and back" ) {
        Matrix dcm = e.toDCM();
        EulerAngle e2 = EulerAngle::fromDCM(3, 2, 1, dcm);

        REQUIRE( e == e2 );
    }

    SECTION( "Should add and subtract properly" ) {
        EulerAngle e2 = EulerAngle(3, 2, 1, 20, 10, 5);
        EulerAngle e3 = e + e2;
        EulerAngle e4 = e3 - e2;

        REQUIRE(e == e4);
    }
}

TEST_CASE( "PRV should perform basic operations", "[PRV]" ) {

    EulerAngle e = EulerAngle(3, 2, 1, 10, 20, 30);
    PRV p = PRV();
    Matrix m = e.toDCM();
    p = PRV::fromDCM(m);

    SECTION("Should convert to DCM and back") {
        PRV r;
        Matrix m2 = p.toDCM();
        r = PRV::fromDCM(m2);

        REQUIRE(p == r);
    }

    SECTION("Should add and subtract properly") {
        EulerAngle e2 = EulerAngle(3, 2, 1, 20, 5, 15);
        PRV p2 = PRV();
        Matrix m2 = e.toDCM();
        p2 = PRV::fromDCM(m2);

        PRV p3 = p + p2;
        PRV p4 = p3 - p2;

        REQUIRE(p == p4);
    }
}

TEST_CASE( "Quaternion should perform basic operations", "[quaternion]") {
    EulerAngle e = EulerAngle(3, 2, 1, 10, 20, 30);
    Matrix m = e.toDCM();
    PRV p = PRV::fromDCM(m);
    Quaternion q = Quaternion::fromPRV(p);

    SECTION("Should convert to DCM and back") {
        Matrix dcm = q.toDCM();
        Quaternion r = Quaternion::fromDCM(dcm);

        REQUIRE(r == q);
    }

    SECTION("Should add and subtract properly") {
        EulerAngle e2 = EulerAngle(3, 2, 1, 5, 20, 10);
        PRV p2 = PRV();
        Matrix m2 = e.toDCM();
        p2 = PRV::fromDCM(m2);
        Quaternion q2 = Quaternion::fromPRV(p2);
        Quaternion q3 = q + q2;
        Quaternion q4 = q3 - q2;

        REQUIRE(q == q4);
    }

    SECTION("Should integrate properly") {
        Quaternion q1(0.408248, 0., 0.408248, 0.816497);

        Quaternion q2 = q1.integrate(
                [](double t) {
                    double c = degreeToRadians(20);
                    Matrix m({
                       {0.},
                       {c*sin(0.1*t)},
                       {c*0.01},
                       {c*cos(0.1*t)}
                    });
                    return m;
                }, 42, 0.001);

        Vector result({q2.getBVector()[1], q2.getBVector()[2], q2.getBVector()[3]});
        double norm = result.norm();

        REQUIRE(q2.getBVector().norm() == 1.0);
        REQUIRE(norm == 0.82009620132554206);
    }
}

TEST_CASE( "CRP should perform basic operations", "[quaternion]") {
    EulerAngle e = EulerAngle(3, 2, 1, 10, 20, 30);
    Matrix m = e.toDCM();
    PRV p = PRV::fromDCM(m);
    Quaternion q = Quaternion::fromPRV(p);
    CRP c = CRP(q);

    SECTION("Should convert to and from dcm") {
        Matrix dcm = c.toDCM();
        CRP c2 = CRP::fromDCM(dcm);

        REQUIRE(c == c2);
    }

    SECTION("Should add and subtract properly") {
        EulerAngle e2 = EulerAngle(3, 2, 1, 5, 20, 10);
        Matrix m2 = e.toDCM();
        CRP c2 = CRP::fromDCM(m2);
        CRP c3 = c + c2;
        CRP c4 = c3 - c2;

        REQUIRE(c == c4);
    }

    SECTION("Should integrate properly") {
        CRP initial({0.4, 0.2, -0.1});
        CRP result = initial.integrate(
                [](double t) {
                    double c = degreeToRadians(3);
                    Matrix m({
                                     {c*sin(0.1*t)},
                                     {c*0.01},
                                     {c*cos(0.1*t)}
                             });
                    return m;
                }, 42, 0.001);
        REQUIRE(result.getQVector().norm() == 1.1996198204022048);
    }

}