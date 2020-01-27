//
//  RotationParameters.cpp
//  rotations
//
//  Created by Alex Post on 1/26/20.
//  Copyright © 2020 Alex Post. All rights reserved.
//

#include <iostream>
#include "DCM.hpp"
#include "Matrix.hpp"


DCM::DCM(const DCM &o){
    if (o.m_dcm) {
        this->m_dcm = o.m_dcm;
    }
}

DCM::~DCM(){
    if (this->m_dcm) {
        delete this->m_dcm;
    }
}

Matrix DCM::addDCM(DCM &o) {
    if (! m_dcm) {
        this->m_dcm = toDCM();
    }
    return m_dcm->multiply(*o.m_dcm);
}

Matrix DCM::subtractDCM(DCM &o) {
    if (! m_dcm) {
        this->m_dcm = toDCM();
    }
    return m_dcm->multiply(*o.m_dcm->transpose());
}

Matrix* DCM::toDCM() {
    return m_dcm;
}

std::ostream& operator<<(std::ostream& os, Matrix& m)
{
    os << "[" << std::endl;
    for (int i = 0; i < m.getRows(); i ++) {
        os << "  [";
        for (int j = 0; j < m.getColumns(); j ++) {
            os << m[i][j];
            if (j < m.getColumns() - 1) {
                os << ", ";
            }
        }
        os << "]" << std::endl;;
    }
    os << "]";
    return os;
}

