//
//  main.cpp
//  rotations
//
//  Created by Alex Post on 1/25/20.
//  Copyright © 2020 Alex Post. All rights reserved.
//

#include <iostream>
#include "Matrix.hpp"
#include "EulerAngle.hpp"


/*
 This is just an example of one way to implement a way of computing rotation parameters that allows them to be treated almost interchangably.  The base class of RotationParameters is basically an interface that will be extended by new types of rotations.  This is where the DCM lives, so whenever we dont know how to do something strictly within the confines of a given type, we can always default back to the base behavior using the DCM.
 
 This is just a quick prototype that could be improved by adding more types, improving the Matrix functionality (There may be a good library out there)...I havent implemented inverse yet.  Also, only two types of Euler angles are implemented and I have not included the ability to add symmetrical Euler Angles - although that can be done using the DCM still.
 */
int main(int argc, const char * argv[]) {
    
    // Example of taking Euler angle, converting to DCM, and converting back...
    // We should get the same angle out if.
    
    EulerAngle e = EulerAngle(3, 2, 1, 10, 20, -20);
    Matrix result = e.toDCM();
    std::cout << result << std::endl;
//    EulerAngle e2 = EulerAngle(3, 2, 1, "e2");
//    EulerAngle e3 = *dynamic_cast<EulerAngle*>(e2.fromDCM(result).get());
//    std::cout << *dynamic_cast<EulerAngle*>(e2.fromDCM(result).get()) << std::endl;
//    std::cout << e3 << std::endl;
//    std::cout << e << std::endl;
//
//    EulerAngle t = EulerAngle(3, 2, 1, 20, 30, 10);
//    EulerAngle e4 = *dynamic_cast<EulerAngle*>(e.add(t).get());
//    EulerAngle e5 = *dynamic_cast<EulerAngle*>(e4.subtract(t).get());
//
//    std::cout << "E4: " << e4 << std::endl;
//    std::cout << "E5: " << e5 << std::endl;
//    std::cout << "E: " << e << std::endl;
//
//    std::cout << "-------------------" << std::endl;
//
//    auto m = Matrix(3, 3);
//    std::cout << m << std::endl;
//
//    for (int i = 0; i < m.getRows(); i++) {
//        for (int j = 0; j < m.getColumns(); j ++) {
//            m(i, j) = (i*m.getColumns() + j + 1);
//        }
//    }
//
//    std::cout << m << std::endl;
//    Matrix test = 2. * m;
//
//    std::cout << test << std::endl;
//
//    Matrix m2 = Matrix(3, 3);
//    m2(0, 0) = 2;
//    m2(0, 1) = 3;
//    m2(0, 2) = 4;
//    m2(1, 0) = 3;
//    m2(1, 1) = 4;
//    m2(1, 2) = 5;
//    m2(2, 0) = 4;
//    m2(2, 1) = 5;
//    m2(2, 2) = 6;
//
//    Matrix test2 = m * m2;
//
//    std::cout << test2 << std::endl;
//
//    Matrix m3 = Matrix(3, 1);
//    m3(0, 0) = 1;
//    m3(1, 0) = 2;
//    m3(2, 0) = 3;
//
//    Matrix m4 = m * m3;
//
//    std::cout << m4 << std::endl;
//
//    std::cout << m << std::endl;
//    std::cout << m.det() << std::endl;
//
////    m1 = np.array([
////    [1, 2, 10, 4],
////    [4, 5, 6, 7],
////    [7, 8, 9, 10],
////    [10, 9, 1, 11]
////    ])
//
//    Matrix m6 = Matrix(4, 4);
//    m6(0, 0) = 1;
//    m6(0, 1) = 2;
//    m6(0, 2) = 10;
//    m6(0, 3) = 4;
//    m6(1, 0) = 4;
//    m6(1, 1) = 5;
//    m6(1, 2) = 6;
//    m6(1, 3) = 7;
//    m6(2, 0) = 7;
//    m6(2, 1) = 8;
//    m6(2, 2) = 9;
//    m6(2, 3) = 10;
//    m6(3, 0) = 10;
//    m6(3, 1) = 9;
//    m6(3, 2) = 1;
//    m6(3, 3) = 11;
//
//    std::cout << "Starting...\n\n" << std::endl;
//    std::cout << m6 << std::endl;
//    std::cout << m6.det() << std::endl;

//    std::cout << m << std::endl;
//
//    std::cout << "Original Euler Angle: ";
//    std::cout << e << std::endl;
//    std::cout << std::endl << "DCM: " << std::endl;
//    Matrix em = e.toDCM();
//    std::cout << em << std::endl;
//    std::cout << std::endl << "New Euler Angle: ";
//    e2.printDegrees();
//    std::cout << std::endl;

//
//
//    // Here is an example of how you might integrate.  Takes a lambda function defining omega at time t
//    double c =(2*M_PI)*(20./360);
//    std::cout << c << std::endl;
//    e2->integrate(
//        [=](double t){
//            Matrix* m = new Matrix(3, 1);
//            m->insert(0, 0, c*sin(0.1*t));
//            m->insert(1, 0, c*0.01);
//            m->insert(2, 0, c*cos(0.1*t));
//            return m;
//    }, 42, 0.1);
//
//    // The RotationParameters interface exists so that we can add angles of different types.  Heres an example of adding Euler Angles and PRVs
//    Matrix* v = new Matrix(3, 1);
//    v->insert(0, 0, 0.1);
//    v->insert(1, 0, 0.5);
//    v->insert(2, 0, -1);
//    PRV p = PRV(20, v);
//
//    std::cout << "Original PRV: ";
//    p.printDegrees();
//    std::cout << std::endl;
//
//    // We have to cast to PRV because the parent class RotationParameters is the defined return type
//    PRV* p2 = dynamic_cast<PRV*>(p.add(e));
//
//    std::cout << "New PRV: ";
//    p2->printDegrees();
//    std::cout << std::endl;
}
