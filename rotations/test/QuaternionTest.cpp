//
// Created by Alex Post on 2/23/20.
//

#include <EulerAngle.hpp>
#include "catch2/catch.hpp"
#include "Quaternion.hpp"

TEST_CASE( "Quaternions can be converted to and from DCM", "[Quaternion]") {

    EulerAngle e = EulerAngle(3, 2, 1, 10, 20, 30);
    PRV p = PRV();
    Matrix m = e.toDCM();
    p = *dynamic_cast<PRV*>(p.fromDCM(m).get());
    std::cout << p << std::endl;
//    Quaternion q = Quaternion::fromPRV(p);
//    std::cout << &q << std::endl;

}