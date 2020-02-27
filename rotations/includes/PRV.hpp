//
//  PRV.hpp
//  rotations
//
//  Created by Alex Post on 1/26/20.
//  Copyright © 2020 Alex Post. All rights reserved.
//

#ifndef PRV_hpp
#define PRV_hpp

#include <stdio.h>
#include "Matrix.hpp"
#include "RotationParameters.hpp"

class PRV: public RotationParameters {
private:
    Vector* m_Ev = nullptr;
    double m_phi = 0.0;
public:
    PRV();
    PRV(double phi, Vector &Ev);
    PRV(double phi, const std::initializer_list<double> &list);
    PRV(const PRV &o);
    ~PRV();
    PRV& operator=(const PRV &o);
    
    std::unique_ptr<RotationParameters> add(RotationParameters &o);

    std::unique_ptr<RotationParameters> subtract(RotationParameters &o);
    
    Matrix toDCM();

    std::unique_ptr<RotationParameters> fromDCM(Matrix &dcm);
    
    void printRadians();
    
    void printDegrees();

    double getPhi();

    Vector getEv();

    friend std::ostream& operator<<(std::ostream &os, PRV &prv);

    friend bool operator==(const PRV &lhs, const PRV &rhs);
    
};

#endif /* PRV_hpp */
