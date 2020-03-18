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
#include <memory>


EulerAngle::EulerAngle(int axis1, int axis2, int axis3):
    EulerAngle::EulerAngle(axis1, axis2, axis3, 0., 0., 0.){}

EulerAngle::EulerAngle(int axis1, int axis2, int axis3, std::string name):
    EulerAngle::EulerAngle(axis1, axis2, axis3, 0., 0., 0., name) {}

EulerAngle::EulerAngle(int axis1, int axis2, int axis3, double t1, double t2, double t3, std::string name){
    m_axis1 = axis1;
    m_axis2 = axis2;
    m_axis3 = axis3;
    m_t1 = degreeToRadians(t1);
    m_t2 = degreeToRadians(t2);
    m_t3 = degreeToRadians(t3);
    m_name = name;
}

EulerAngle::EulerAngle(int axis1, int axis2, int axis3, double t1, double t2, double t3):
    EulerAngle::EulerAngle(axis1, axis2, axis3, t1, t2, t3, "Euler Angle") {}

EulerAngle::EulerAngle(const EulerAngle &o) {
    this->m_axis1 = o.m_axis1;
    this->m_axis2 = o.m_axis2;
    this->m_axis3 = o.m_axis3;
    this->m_t1 = o.m_t1;
    this->m_t2 = o.m_t2;
    this->m_t3 = o.m_t3;
}

EulerAngle::~EulerAngle(){}

bool EulerAngle::isSymmetric() {
    return false;
}

Matrix EulerAngle::toDCM() {
    if (! m_dcm) {
        auto dcm = new Matrix(3, 3);
        if (m_axis1 == 3 && m_axis2 == 2 && m_axis3 == 1) {
            (*dcm)(0, 0) = cos(m_t2)*cos(m_t1);
            (*dcm)(0, 1) = cos(m_t2)*sin(m_t1);
            (*dcm)(0, 2) = -sin(m_t2);
            (*dcm)(1, 0) = sin(m_t3)*sin(m_t2)*cos(m_t1) - cos(m_t3)*sin(m_t1);
            (*dcm)(1, 1) = sin(m_t3)*sin(m_t2)*sin(m_t1) + cos(m_t3)*cos(m_t1);
            (*dcm)(1, 2) = sin(m_t3)*cos(m_t2);
            (*dcm)(2, 0) = cos(m_t3)*sin(m_t2)*cos(m_t1) + sin(m_t3)*sin(m_t1);
            (*dcm)(2, 1) = cos(m_t3)*sin(m_t2)*sin(m_t1) - sin(m_t3)*cos(m_t1);
            (*dcm)(2, 2) = cos(m_t3)*cos(m_t2);
            this->m_dcm = dcm;
        } else if (m_axis1 == 3 && m_axis2 == 1 && m_axis3 == 3) {
            (*dcm)(0, 0) = cos(m_t3)*cos(m_t1) - sin(m_t3)*cos(m_t2)*sin(m_t1);
            (*dcm)(0, 1) = cos(m_t3)*sin(m_t1) + sin(m_t3)*cos(m_t2)*cos(m_t1);
            (*dcm)(0, 2) = sin(m_t3)*sin(m_t2);
            (*dcm)(1, 0) = -sin(m_t3)*cos(m_t1) - cos(m_t3)*cos(m_t2)*sin(m_t1);
            (*dcm)(1, 1) = -sin(m_t3)*sin(m_t1) + cos(m_t3)*cos(m_t2)*cos(m_t1);
            (*dcm)(1, 2) = cos(m_t3)*sin(m_t2);
            (*dcm)(2, 0) = sin(m_t2)*sin(m_t1);
            (*dcm)(2, 1) = -sin(m_t2)*cos(m_t1);
            (*dcm)(2, 2) = cos(m_t2);
            this->m_dcm = dcm;
        }
        
        else {
            throw "Unimplemented Exception";
        }
    }
    return *m_dcm;
}

EulerAngle EulerAngle::fromDCM(int axis1, int axis2, int axis3, Matrix &dcm){
    if (axis1 == 3 && axis2 == 2 && axis3 == 1) {
        double t1 = atan2(dcm(0, 1), dcm(0, 0));
        double t2 = -asin(dcm(0, 2));
        double t3 = atan2(dcm(1, 2), dcm(2, 2));
        return EulerAngle(axis1, axis2, axis3, radianToDegrees(t1), radianToDegrees(t2), radianToDegrees(t3));
    } else if (axis1 == 3 && axis2 == 1 && axis3 == 3) {
        double t1 = atan2(dcm(2, 0), -dcm(2, 1));
        double t2 = acos(dcm(2, 2));
        double t3 = atan2(dcm(0, 2), dcm(1, 2));
        return EulerAngle(axis1, axis2, axis3, radianToDegrees(t1), radianToDegrees(t2), radianToDegrees(t3));
    } else {
        throw "Unimplemented Exception";
    }
}

Matrix EulerAngle::B(double t1, double t2, double t3) {
    auto B = Matrix(3, 3);
    if (m_axis1 == 3 && m_axis2 == 2 && m_axis3 == 1) {
        double c = 1/cos(t2);
        B(0, 0) = 0.;
        B(0, 1) = c*sin(t3);
        B(0, 2) = c*cos(t3);
        B(1, 0) = 0.;
        B(1, 1) = c*cos(t2)*cos(t3);
        B(1, 2) = -c*cos(t2)*sin(t3);
        B(2, 0) = c*cos(t2);
        B(2, 1) = c*sin(t2)*sin(t3);
        B(2, 2) = c*sin(t2)*cos(t3);
        return B;
    } else {
        throw "Unimplemented Exception";
    }
}

Matrix EulerAngle::integrate(std::function<Matrix&(double)> w, double duration, double step) {
    Matrix Xn = w(0);
    for (double i = 1; i <= duration; i += 5) {
        Matrix Xi = w(i);
        Matrix Wn = B(Xn(0, 0), Xn(1, 0), Xn(2, 0));
        Matrix n = Wn.multiply(Xi);
        Xn = n;
    }
    return Xn;
}

std::ostream& operator<<(std::ostream &os, EulerAngle &e) {
    os << "Axes: (" << e.m_axis1 << ", " << e.m_axis2 << ", " << e.m_axis3 << ")";
    os << " Thetas: (" << e.m_t1 << ", " << e.m_t2 << ", " << e.m_t3 << ")";
    return os;
}

bool operator==(const EulerAngle &lhs, const EulerAngle &rhs) {
    return
        lhs.m_axis1 == rhs.m_axis1 &&
        lhs.m_axis2 == rhs.m_axis2 &&
        lhs.m_axis3 == rhs.m_axis3 &&
        abs(lhs.m_t1 - rhs.m_t1) < std::numeric_limits<double>::epsilon() &&
        abs(lhs.m_t2 - rhs.m_t2) < std::numeric_limits<double>::epsilon() &&
        abs(lhs.m_t3 - rhs.m_t3) < std::numeric_limits<double>::epsilon();
}

EulerAngle &EulerAngle::operator=(const EulerAngle &o) {
    if (this == &o) {
        return *this;
    }
    this->m_axis1 = o.m_axis1;
    this->m_axis2 = o.m_axis2;
    this->m_axis3 = o.m_axis3;
    this->m_t1 = o.m_t1;
    this->m_t2 = o.m_t2;
    this->m_t3 = o.m_t3;
    return *this;
}

EulerAngle operator+(EulerAngle &lhs, EulerAngle &rhs){
    Matrix dcm = lhs.addDCM(rhs);
    return EulerAngle::fromDCM(lhs.m_axis1, lhs.m_axis2, lhs.m_axis3, dcm);
}

EulerAngle operator+(EulerAngle &lhs, RotationParameters &rhs) {
    Matrix dcm = lhs.addDCM(rhs);
    return EulerAngle::fromDCM(lhs.m_axis1, lhs.m_axis2, lhs.m_axis3, dcm);}

EulerAngle operator-(EulerAngle &lhs, EulerAngle &rhs) {
    Matrix dcm = lhs.subtractDCM(rhs);
    return EulerAngle::fromDCM(lhs.m_axis1, lhs.m_axis2, lhs.m_axis3, dcm);
}

EulerAngle operator-(EulerAngle &lhs, RotationParameters &rhs) {
    Matrix dcm = lhs.subtractDCM(rhs);
    return EulerAngle::fromDCM(lhs.m_axis1, lhs.m_axis2, lhs.m_axis3, dcm);
}

