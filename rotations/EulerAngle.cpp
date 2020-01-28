//
//  EulerAngle.cpp
//  rotations
//
//  Created by Alex Post on 1/26/20.
//  Copyright © 2020 Alex Post. All rights reserved.
//

#include "EulerAngle.hpp"
#include "RotationParameters.hpp"
#include "math.h"
#include <exception>
#include <iostream>


EulerAngle::EulerAngle(int axis1, int axis2, int axis3):EulerAngle::EulerAngle(axis1, axis2, axis3, 0., 0., 0.){}


EulerAngle::EulerAngle(int axis1, int axis2, int axis3, double t1, double t2, double t3){
    m_axis1 = axis1;
    m_axis2 = axis2;
    m_axis3 = axis3;
    m_t1 = degreeToRadians(t1);
    m_t2 = degreeToRadians(t2);
    m_t3 = degreeToRadians(t3);
    name = "Euler Angle";
}

EulerAngle::EulerAngle(const EulerAngle &o) {
    this->m_t1 = o.m_t1;
    this->m_t2 = o.m_t2;
    this->m_t3 = o.m_t3;
}

EulerAngle::~EulerAngle(){}

RotationParameters* EulerAngle::add(RotationParameters &o) {
    if (isSymmetric()) {
        // here we could put the math for adding symmetric Euler Angles
        return this;
    } else {
        if (! m_dcm) {
            m_dcm = toDCM();
        }
        Matrix* dcm = m_dcm->multiply(*o.toDCM());
        return fromDCM(*dcm);
    }
}

RotationParameters* EulerAngle::subtract(RotationParameters &o){
    return new EulerAngle(m_axis1, m_axis2, m_axis3);
}

bool EulerAngle::isSymmetric() {
    return m_axis1 == m_axis3;
}

Matrix* EulerAngle::toDCM() {
    if (! m_dcm) {
        Matrix* dcm = new Matrix(3, 3);
        if (m_axis1 == 3 && m_axis2 == 2 && m_axis3 == 1) {
            dcm->insert(0, 0, cos(m_t2)*cos(m_t1));
            dcm->insert(0, 1, cos(m_t2)*sin(m_t1));
            dcm->insert(0, 2, -sin(m_t2));
            dcm->insert(1, 0, sin(m_t3)*sin(m_t2)*cos(m_t1) - cos(m_t3)*sin(m_t1));
            dcm->insert(1, 1, sin(m_t3)*sin(m_t2)*sin(m_t1) + cos(m_t3)*cos(m_t1));
            dcm->insert(1, 2, sin(m_t3)*cos(m_t2));
            dcm->insert(2, 0, cos(m_t3)*sin(m_t2)*sin(m_t1) + sin(m_t3)*sin(m_t1));
            dcm->insert(2, 1, cos(m_t3)*sin(m_t2)*sin(m_t1) - sin(m_t3)*cos(m_t1));
            dcm->insert(2, 2, cos(m_t3)*cos(m_t2));
            this->m_dcm = dcm;
        } else if (m_axis1 == 3 && m_axis2 == 1 && m_axis3 == 3) {
            dcm->insert(0, 0, cos(m_t3)*cos(m_t1) - sin(m_t3)*cos(m_t2)*sin(m_t1));
            dcm->insert(0, 1, cos(m_t3)*sin(m_t1) + sin(m_t3)*cos(m_t2)*cos(m_t1));
            dcm->insert(0, 2, sin(m_t3)*sin(m_t2));
            dcm->insert(1, 0, -sin(m_t3)*cos(m_t1) - cos(m_t3)*cos(m_t2)*sin(m_t1));
            dcm->insert(1, 1, -sin(m_t3)*sin(m_t1) + cos(m_t3)*cos(m_t2)*cos(m_t1));
            dcm->insert(1, 2, cos(m_t3)*sin(m_t2));
            dcm->insert(2, 0, sin(m_t2)*sin(m_t1));
            dcm->insert(2, 1, -sin(m_t2)*cos(m_t1));
            dcm->insert(2, 2, cos(m_t2));
            this->m_dcm = dcm;
        }
        
        else {
            throw "Unimplemented Exception";
        }
    }
    return m_dcm;
}

RotationParameters* EulerAngle::fromDCM(Matrix dcm){
    if (m_axis1 == 3 && m_axis2 == 2 && m_axis3 == 1) {
        m_t1 = atan2(dcm.get(0, 1), dcm.get(0,0));
        m_t2 = -asin(dcm.get(0, 2));
        m_t3 = atan2(dcm.get(1, 2), dcm.get(2, 2));
        return this;
    } else if (m_axis1 == 3 && m_axis2 == 1 && m_axis3 == 3) {
        m_t1 = atan2(dcm.get(2, 0), -dcm.get(2, 1));
        m_t2 = acos(dcm.get(2, 2));
        m_t3 = atan2(dcm.get(0, 2), dcm.get(1, 2));
        return this;
    } else {
        throw "Unimplemented Exception";
    }
}

Matrix* EulerAngle::B(double t1, double t2, double t3) {
    Matrix* B = new Matrix(3, 3);
    if (m_axis1 == 3 && m_axis2 == 2 && m_axis3 == 1) {
        double c = 1/cos(t2);
        B->insert(0, 0, 0.);
        B->insert(0, 1, c*sin(t3));
        B->insert(0, 2, c*cos(t3));
        B->insert(1, 0, 0.);
        B->insert(1, 1, c*cos(t2)*cos(t3));
        B->insert(1, 2, -c*cos(t2)*sin(t3));
        B->insert(2, 0, c*cos(t2));
        B->insert(2, 1, c*sin(t2)*sin(t3));
        B->insert(2, 2, c*sin(t2)*cos(t3));
        return B;
    } else {
        throw "Unimplemented Exception";
    }
}

void EulerAngle::printRadians() {
    std::cout << "(" << m_axis1 << ", " << m_axis2 << ", " << m_axis3 << ") ";
    std::cout << "(" << m_t1 << ", " << m_t2 << ", " << m_t3 << ")" << std::endl;
}

void EulerAngle::printDegrees() {
    std::cout << "(" << m_axis1 << ", " << m_axis2 << ", " << m_axis3 << ") ";
    std::cout << "(" << radianToDegrees(m_t1) << ", " << radianToDegrees(m_t2) << ", " << radianToDegrees(m_t3) << ")" << std::endl;
}

Matrix* EulerAngle::integrate(std::function<Matrix*(double)> w, double duration, double step) {
    Matrix* Xn = w(0);
    for (double i = 1; i <= duration; i += 5) {
        Matrix* Xi = w(i);
        Matrix* Wn = B(Xn->get(0, 0), Xn->get(1, 0), Xn->get(2, 0));
        Matrix* n = Wn->multiply(*Xi);
        Xn = n;
    }
    return Xn;
}
