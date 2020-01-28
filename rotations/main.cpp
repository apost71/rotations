//
//  main.cpp
//  rotations
//
//  Created by Alex Post on 1/25/20.
//  Copyright © 2020 Alex Post. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "Matrix.hpp"
#include "RotationParameters.hpp"
#include "EulerAngle.hpp"
#include "PRV.hpp"

/*
 This is just an example of one way to implement a way of computing rotation parameters that allows them to be treated almost interchangably.  The base class of RotationParameters is basically an interface that will be extended by new types of rotations.  This is where the DCM lives, so whenever we dont know how to do something strictly within the confines of a given type, we can always default back to the base behavior using the DCM.
 
 This is just a quick prototype that could be improved by adding more types, improving the Matrix functionality (There may be a good library out there)...I havent implemented inverse yet.  Also, only two types of Euler angles are implemented and I have not included the ability to add symmetrical Euler Angles - although that can be done using the DCM still.
 */
int main(int argc, const char * argv[]) {
    
    // Example of taking Euler angle, converting to DCM, and converting back...
    // We should get the same angle out if.
    
    EulerAngle e = EulerAngle(3, 2, 1, 10, 20, -20);
    Matrix* result = e.toDCM();
    EulerAngle* e2 = new EulerAngle(3, 2, 1);
    e2->fromDCM(*result);
    
    std::cout << "Original Euler Angle: ";
    e.printDegrees();
    std::cout << std::endl << "DCM: " << std::endl;
    result->print();
    std::cout << std::endl << "New Euler Angle: ";
    e2->printDegrees();
    std::cout << std::endl;

    
    // Here is an example of how you might integrate.  Takes a lambda function defining omega at time t
    double c =(2*M_PI)*(20./360);
    std::cout << c << std::endl;
    e2->integrate(
        [=](double t){
            Matrix* m = new Matrix(3, 1);
            m->insert(0, 0, c*sin(0.1*t));
            m->insert(1, 0, c*0.01);
            m->insert(2, 0, c*cos(0.1*t));
            return m;
    }, 42, 0.1);
    
    // The RotationParameters interface exists so that we can add angles of different types.  Heres an example of adding Euler Angles and PRVs
    Matrix* v = new Matrix(3, 1);
    v->insert(0, 0, 0.1);
    v->insert(1, 0, 0.5);
    v->insert(2, 0, -1);
    PRV p = PRV(20, v);
    
    std::cout << "Original PRV: ";
    p.printDegrees();
    std::cout << std::endl;
    
    // We have to cast to PRV because the parent class RotationParameters is the defined return type
    PRV* p2 = dynamic_cast<PRV*>(p.add(e));
    
    std::cout << "New PRV: ";
    p2->printDegrees();
    std::cout << std::endl;
}
