//
//  RotationParameters.hpp
//  rotations
//
//  Created by Alex Post on 1/26/20.
//  Copyright © 2020 Alex Post. All rights reserved.
//

#ifndef RotationParameters_hpp
#define RotationParameters_hpp

#include <stdio.h>
#include "Matrix.hpp"
#include <math.h>
#include <string>

#define _USE_MATH_DEFINES

class RotationParameters {
protected:
    std::string m_name;
    Matrix* m_dcm = nullptr;
    const int rows = 3;
    const int cols = 3;
    
public:
    RotationParameters(){};
    RotationParameters(const RotationParameters &o);
    virtual ~RotationParameters();
    
    Matrix addDCM(RotationParameters &o);
    
    Matrix subtractDCM(RotationParameters &o);
    
    virtual std::unique_ptr<RotationParameters> add(RotationParameters &o) = 0;
    
    virtual std::unique_ptr<RotationParameters> subtract(RotationParameters &o) = 0;
    
    virtual Matrix toDCM() = 0;
    
    virtual std::unique_ptr<RotationParameters> fromDCM(Matrix &dcm) = 0;
    
    virtual void printRadians() = 0;
    
    virtual void printDegrees() = 0;
    
};

double degreeToRadians(double d);
double radianToDegrees(double d);

#endif /* RotationParameters_hpp */
