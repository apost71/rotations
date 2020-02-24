//
//  PRV.cpp
//  rotations
//
//  Created by Alex Post on 1/26/20.
//  Copyright © 2020 Alex Post. All rights reserved.
//

#include "PRV.hpp"
#include "Matrix.hpp"
#include "RotationParameters.hpp"
#include <math.h>
#include <iostream>

#define _USE_MATH_DEFINES


PRV::PRV(){}

// phi and E_v should be in radians
PRV::PRV(double phi, Matrix &Ev){
    m_Ev = new Matrix(3, 1);
    (*m_Ev)(0, 0) = Ev(0, 0);
    (*m_Ev)(1, 0) = Ev(1, 0);
    (*m_Ev)(2, 0) = Ev(2, 0);
    m_phi = degreeToRadians(phi);
    m_name = "PRV";
}

PRV::PRV(const PRV &o) {
    this->m_phi = o.m_phi;
    this->m_Ev = new Matrix(3, 1);
    (*m_Ev)(0, 0) = (*o.m_Ev)(0, 0);
    (*m_Ev)(1, 0) = (*o.m_Ev)(1, 0);
    (*m_Ev)(2, 0) = (*o.m_Ev)(2, 0);
}

PRV::~PRV() {
    delete m_Ev;
}

PRV& PRV::operator=(const PRV &o) {
    if (this == &o)
        return *this;
    this->m_phi = o.m_phi;
    this->m_Ev = new Matrix(3, 1);
    (*m_Ev)(0, 0) = (*o.m_Ev)(0, 0);
    (*m_Ev)(1, 0) = (*o.m_Ev)(1, 0);
    (*m_Ev)(2, 0) = (*o.m_Ev)(2, 0);

    return *this;
}

std::unique_ptr<RotationParameters> PRV::add(RotationParameters &o){
    if (! m_dcm) {
        *m_dcm = toDCM();
    }
    Matrix dcm = m_dcm->multiply(o.toDCM());
    return fromDCM(dcm);
}

std::unique_ptr<RotationParameters> PRV::subtract(RotationParameters &o) {
    if (! m_dcm) {
        *m_dcm = toDCM();
    }
    Matrix dcm = m_dcm->multiply(o.toDCM().transpose());
    return fromDCM(dcm);
}

Matrix PRV::toDCM() {
    if (! m_Ev) {
        throw "Must initialize Ev and Phi to convert to DCM";
    }
    
    auto dcm = new Matrix(3, 3);
    if (! m_dcm) {
        double sigma = 1-cos(m_phi);
        (*dcm)(0, 0) = pow(m_Ev->get(0, 0), 2)*sigma + cos(m_phi);
        (*dcm)(0, 1) = m_Ev->get(0, 0)*m_Ev->get(1, 0)*sigma + m_Ev->get(2, 0)*sin(m_phi);
        (*dcm)(0, 2) = m_Ev->get(0, 0)*m_Ev->get(2, 0)*sigma - m_Ev->get(1, 0)*sin(m_phi);
        (*dcm)(1, 0) = m_Ev->get(1, 0)*m_Ev->get(0, 0)*sigma - m_Ev->get(2, 0)*sin(m_phi);
        (*dcm)(1, 1) = pow(m_Ev->get(1, 0), 2)*sigma + cos(m_phi);
        (*dcm)(1, 2) = m_Ev->get(1, 0)*m_Ev->get(2, 0)*sigma + m_Ev->get(0, 0)*sin(m_phi);
        (*dcm)(2, 0) = m_Ev->get(2, 0)*m_Ev->get(0, 0)*sigma + m_Ev->get(1, 0)*sin(m_phi);
        (*dcm)(2, 1) = m_Ev->get(2, 0)*m_Ev->get(1, 0)*sigma - m_Ev->get(0, 0)*sin(m_phi);
        (*dcm)(2, 2) = pow(m_Ev->get(2, 0), 2)*sigma + cos(m_phi);
        this->m_dcm = dcm;
    } else {
        throw "Unimplemented Exception";
    }
    return *m_dcm;
}

std::unique_ptr<RotationParameters> PRV::fromDCM(Matrix &dcm) {
    double c_phi = 0.5 * (dcm(0,0) + dcm(1, 1) + dcm(2, 2) - 1);
    this->m_phi = acos(c_phi);
    double c = 1 / (2*sin(this->m_phi));
    
    this->m_Ev = new Matrix(3, 1);
    (*m_Ev)(0, 0) = c * (dcm.get(1, 2) - dcm.get(2, 1));
    (*m_Ev)(1, 0) = c * (dcm.get(2, 0) - dcm.get(0, 2));
    (*m_Ev)(2, 0) = c * (dcm.get(0, 1) - dcm.get(1, 0));
    
    return std::make_unique<PRV>(*this);
}

void PRV::printRadians() {
    std::cout << "Phi: " << m_phi << "  E_v: [" << (*m_Ev)(0, 0) << ", " << (*m_Ev)(1, 0) << ", " << (*m_Ev)(2, 0) << "]";
}

void PRV::printDegrees() {
    std::cout << "Phi: " << radianToDegrees(m_phi) << "  E_v: [" << radianToDegrees((*m_Ev)(0, 0)) << ", " << radianToDegrees((*m_Ev)(1, 0)) << ", " << radianToDegrees((*m_Ev)(2, 0)) << "]";
}

double PRV::getPhi() {
    return m_phi;
}

Matrix PRV::getEv() {
    return *m_Ev;
}

std::ostream &operator<<(std::ostream &os, PRV &prv){
    os << "Phi: " << radianToDegrees(prv.m_phi) << " E_v: [" <<
    radianToDegrees((*prv.m_Ev)(0, 0)) << ", " <<
    radianToDegrees((*prv.m_Ev)(1, 0)) << ", " <<
    radianToDegrees((*prv.m_Ev)(2, 0)) << "]";

    return os;
}
