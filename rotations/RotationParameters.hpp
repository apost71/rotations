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

class RotationParameters {
private:
    Matrix* m_dcm = nullptr;
    const int rows = 3;
    const int cols = 3;
    
public:
    RotationParameters(){};
    
    RotationParameters(const RotationParameters &o);
    ~RotationParameters();
    
    Matrix addDCM(RotationParameters &o);
    
    Matrix subtractDCM(RotationParameters &o);
    
    virtual Matrix add(RotationParameters &o) = 0;
    
    virtual Matrix subtract(RotationParameters &o) = 0;
    
    virtual Matrix* toDCM() = 0;
    
    virtual *RotationParameters fromDCM(Matrix &dcm) = 0;
    
};

#endif /* RotationParameters_hpp */
