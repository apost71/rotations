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

PRV::PRV(double phi, Matrix* Ev): m_phi(phi), m_Ev(Ev){
    m_phi = degreeToRadians(phi);
    m_name = "PRV";
}

PRV::PRV(const PRV &o) {
    this->m_phi = o.m_phi;
    this->m_Ev = o.m_Ev;
}

PRV::~PRV() {
    delete m_Ev;
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
    
    Matrix* dcm = new Matrix(3, 3);
    if (! m_dcm) {
        double sigma = 1-cos(m_phi);
        dcm->insert(0, 0, pow(m_Ev->get(0, 0), 2)*sigma + cos(m_phi));
        dcm->insert(0, 1, m_Ev->get(0, 0)*m_Ev->get(1, 0)*sigma + m_Ev->get(2, 0)*sin(m_phi));
        dcm->insert(0, 2, m_Ev->get(0, 0)*m_Ev->get(2, 0)*sigma - m_Ev->get(1, 0)*sin(m_phi));
        dcm->insert(1, 0, m_Ev->get(1, 0)*m_Ev->get(0, 0)*sigma - m_Ev->get(2, 0)*sin(m_phi));
        dcm->insert(1, 1, pow(m_Ev->get(1, 0), 2)*sigma + cos(m_phi));
        dcm->insert(1, 2, m_Ev->get(1, 0)*m_Ev->get(2, 0)*sigma + m_Ev->get(0, 0)*sin(m_phi));
        dcm->insert(2, 0, m_Ev->get(2, 0)*m_Ev->get(0, 0)*sigma + m_Ev->get(1, 0)*sin(m_phi));
        dcm->insert(2, 1, m_Ev->get(2, 0)*m_Ev->get(1, 0)*sigma - m_Ev->get(0, 0)*sin(m_phi));
        dcm->insert(2, 2, pow(m_Ev->get(2, 0), 2)*sigma + cos(m_phi));
        this->m_dcm = dcm;
    } else {
        throw "Unimplemented Exception";
    }
    return *m_dcm;
}

std::unique_ptr<RotationParameters> PRV::fromDCM(Matrix &dcm) {
    double c_phi = 0.5 * (dcm.get(0,0) + dcm.get(1, 1) + dcm.get(2, 2) - 1);
    double phi = acos(c_phi);
    double c = 1 / (2*sin(phi));
    
    Matrix* e_hat = new Matrix(3, 1);
    e_hat->insert(0, 0, c * (dcm.get(1, 2) - dcm.get(2, 1)));
    e_hat->insert(1, 0, c * (dcm.get(2, 0) - dcm.get(0, 2)));
    e_hat->insert(2, 0, c * (dcm.get(0, 1) - dcm.get(1, 0)));
    
    return std::make_unique<PRV>(PRV(phi, e_hat));
}

void PRV::printRadians() {
    std::cout << "Phi: " << m_phi << "  E_v: [" << m_Ev->get(0, 0) << ", " << m_Ev->get(1, 0) << ", " << m_Ev->get(2, 0) << "]";
}

void PRV::printDegrees() {
    std::cout << "Phi: " << radianToDegrees(m_phi) << "  E_v: [" << radianToDegrees(m_Ev->get(0, 0)) << ", " << radianToDegrees(m_Ev->get(1, 0)) << ", " << radianToDegrees(m_Ev->get(2, 0)) << "]";
}
