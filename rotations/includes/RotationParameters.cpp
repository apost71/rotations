//
//  RotationParameters.cpp
//  rotations
//
//  Created by Alex Post on 1/26/20.
//  Copyright © 2020 Alex Post. All rights reserved.
//

#include <iostream>
#include "RotationParameters.hpp"
#include "Matrix.hpp"


RotationParameters::RotationParameters(const RotationParameters &o){
    if (o.m_dcm) {
        this->m_dcm = new Matrix(*(o.m_dcm));
    }
}

RotationParameters::~RotationParameters() {
        delete m_dcm;
}


Matrix RotationParameters::addDCM(RotationParameters &o) {
    if (! m_dcm) {
        this->m_dcm = new Matrix(toDCM());
    }
    return m_dcm->multiply(o.toDCM());
}

Matrix RotationParameters::subtractDCM(RotationParameters &o) {
    if (! m_dcm) {
        this->m_dcm = new Matrix(toDCM());
    }
    auto o_dcm = o.toDCM().transpose();
    return m_dcm->multiply(o.toDCM().transpose());
}


double degreeToRadians(double d) {
    return (2*M_PI) * (d / 360);
}

double radianToDegrees(double r) {
    return r * (180./M_PI);
}

std::string RotationParameters::getName() {
    return m_name;
}
