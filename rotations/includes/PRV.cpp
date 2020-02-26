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
PRV::PRV(double phi, Vector &Ev){
    this->m_Ev = &Ev;
    m_phi = degreeToRadians(phi);
    m_name = "PRV";
}

PRV::PRV(double phi, const std::initializer_list<double> &list) {
    this->m_phi = degreeToRadians(phi);
    this->m_Ev = new Vector(list);
    (*this->m_Ev)[0] = degreeToRadians((*this->m_Ev)[0]);
    (*this->m_Ev)[1] = degreeToRadians((*this->m_Ev)[1]);
    (*this->m_Ev)[2] = degreeToRadians((*this->m_Ev)[2]);
    this->m_Ev->normalize();
}

PRV::PRV(const PRV &o) {
    this->m_phi = o.m_phi;
    this->m_Ev = new Vector(o.m_Ev->getLength());
    for (int i = 0; i < o.m_Ev->getLength(); i ++) {
        (*this->m_Ev)[i] = (*o.m_Ev)[i];
    }
    this->m_Ev->normalize();
}

PRV::~PRV() {}

PRV& PRV::operator=(const PRV &o) {
    if (this == &o)
        return *this;
    this->m_phi = o.m_phi;
    this->m_Ev = new Vector(o.m_Ev->getLength());
    for (int i = 0; i < o.m_Ev->getLength(); i ++) {
        (*this->m_Ev)[i] = (*o.m_Ev)[i];
    }
    this->m_Ev->normalize();
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
    Matrix dcm = *m_dcm * o.toDCM().transpose();
    return fromDCM(dcm);
}

Matrix PRV::toDCM() {
    if (! m_Ev) {
        throw "Must initialize Ev and Phi to convert to DCM";
    }
    
    if (! m_dcm) {
        double sigma = 1-cos(m_phi);
        auto dcm = new Matrix({
          {pow((*m_Ev)[0], 2)*sigma + cos(m_phi), (*m_Ev)[0]*(*m_Ev)[1]*sigma + (*m_Ev)[2]*sin(m_phi), (*m_Ev)[0]*(*m_Ev)[2]*sigma - (*m_Ev)[1]*sin(m_phi)},
          {(*m_Ev)[1]*(*m_Ev)[0]*sigma - (*m_Ev)[2]*sin(m_phi), pow((*m_Ev)[1], 2)*sigma + cos(m_phi), (*m_Ev)[1]*(*m_Ev)[2]*sigma + (*m_Ev)[0]*sin(m_phi)},
          {(*m_Ev)[2]*(*m_Ev)[0]*sigma + (*m_Ev)[1]*sin(m_phi), (*m_Ev)[2]*(*m_Ev)[1]*sigma - (*m_Ev)[0]*sin(m_phi), pow((*m_Ev)[2], 2)*sigma + cos(m_phi)}
        });
        this->m_dcm = dcm;
    }

    return *m_dcm;
}

std::unique_ptr<RotationParameters> PRV::fromDCM(Matrix &dcm) {
    double c_phi = 0.5 * (dcm(0,0) + dcm(1, 1) + dcm(2, 2) - 1);
    double phi = acos(c_phi);
    double c = 1 / (2*sin(phi));

    auto Ev = new Vector({
        c * (dcm(1, 2) - dcm(2, 1)),
        c * (dcm(2, 0) - dcm(0, 2)),
        c * (dcm(0, 1) - dcm(1, 0))
    });
    
    return std::make_unique<PRV>(radianToDegrees(phi), *Ev);
}

void PRV::printRadians() {
    std::cout << "Phi: " << m_phi << "  E_v: [" << (*m_Ev)[0] << ", " << (*m_Ev)[0] << ", " << (*m_Ev)[0] << "]";
}

void PRV::printDegrees() {
    std::cout << "Phi: " << radianToDegrees(m_phi) << "  E_v: [" << radianToDegrees((*m_Ev)[0]) << ", " << radianToDegrees((*m_Ev)[1]) << ", " << radianToDegrees((*m_Ev)[2]) << "]";
}

double PRV::getPhi() {
    return m_phi;
}

Matrix PRV::getEv() {
    return *m_Ev;
}

std::ostream &operator<<(std::ostream &os, PRV &prv){
    os << "Phi: " << radianToDegrees(prv.m_phi) << " E_v: [" <<
    radianToDegrees((*prv.m_Ev)[0]) << ", " <<
    radianToDegrees((*prv.m_Ev)[1]) << ", " <<
    radianToDegrees((*prv.m_Ev)[2]) << "]";

    return os;
}

bool operator==(const PRV &lhs, const PRV &rhs) {
    return abs(lhs.m_phi - rhs.m_phi) < std::numeric_limits<double>::epsilon() &&
           *lhs.m_Ev == *rhs.m_Ev;
}
