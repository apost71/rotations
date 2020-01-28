//
//  EulerAngle.hpp
//  rotations
//
//  Created by Alex Post on 1/26/20.
//  Copyright © 2020 Alex Post. All rights reserved.
//

#ifndef EulerAngle_hpp
#define EulerAngle_hpp

#include <stdio.h>
#include "RotationParameters.hpp"
#include "Matrix.hpp"
#include <iostream>

class EulerAngle: public RotationParameters {
private:
    int m_axis1 = 0;
    int m_axis2 = 0;
    int m_axis3 = 0;
    double m_t1 = 0.0;
    double m_t2 = 0.0;
    double m_t3 = 0.0;
    
public:
    EulerAngle(int axis1, int axis2, int axis3, double t1, double t2, double t3);
    
    EulerAngle(int axis1, int axis2, int axis3);
    
    EulerAngle(const EulerAngle &o);
    
    ~EulerAngle();
    
    RotationParameters* add(RotationParameters &o);
    
    RotationParameters* subtract(RotationParameters &o);
    
    Matrix* toDCM();
    
    RotationParameters* fromDCM(Matrix dcm);
        
    bool isSymmetric();
    
    void printDegrees();
    
    void printRadians();
    
    Matrix* B(double t1, double t2, double t3);
    
    Matrix* integrate(std::function<Matrix*(double)> w, double duration, double step);
};

#endif /* EulerAngle_hpp */
