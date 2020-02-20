//
// Created by Alex Post on 2/19/20.
//

#include <cmath>
#include "Quaternion.hpp"


Quaternion::Quaternion(double b0, double b1, double b2, double b3) {
    m_b(0, 0) = b0;
    m_b(1, 0) = b1;
    m_b(2, 0) = b2;
    m_b(3, 0) = b3;
}

Quaternion::Quaternion(const Quaternion &o) {
    m_b = o.m_b;
}

std::unique_ptr<RotationParameters> Quaternion::add(RotationParameters &o) {
    return RotationParameters::add(o);
}

std::unique_ptr<RotationParameters> Quaternion::subtract(RotationParameters &o) {
    return RotationParameters::subtract(o);
}

Matrix Quaternion::toDCM() {
    if (! m_dcm ) {
        m_dcm = new Matrix(3, 3);
        (*m_dcm)(0, 0) = pow(m_b(0, 0), 2) + pow(m_b(1, 0), 2) - pow(m_b(2, 0), 2) - pow(m_b(3, 0), 2);
        (*m_dcm)(0, 1) = 2 * (m_b(1, 0) * m_b(2, 0) + m_b(0, 0) * m_b(2, 0));
        (*m_dcm)(0, 2) = 2 * (m_b(1, 0) * m_b(3, 0) - m_b(0, 0) * m_b(2, 0));
        (*m_dcm)(1, 0) = 2 * (m_b(1, 0) * m_b(2, 0) - m_b(0, 0) * m_b(3, 0));
        (*m_dcm)(1, 1) = pow(m_b(0, 0), 2) - pow(m_b(1, 0), 2) + pow(m_b(2, 0), 2) - pow(m_b(3, 0), 2);
        (*m_dcm)(1, 2) = 2 * (m_b(2, 0) * m_b(3, 0) + m_b(0, 0) * m_b(1, 0));
        (*m_dcm)(2, 0) = 2 * (m_b(1, 0) * m_b(3, 0) + m_b(0, 0) * m_b(2, 0));
        (*m_dcm)(2, 1) = 2 * (m_b(2, 0) * m_b(3, 0) - m_b(0, 0) * m_b(1, 0));
        (*m_dcm)(1, 1) = pow(m_b(0, 0), 2) - pow(m_b(1, 0), 2) - pow(m_b(2, 0), 2) + pow(m_b(3, 0), 2);
    }
    return *m_dcm;
}

std::unique_ptr<RotationParameters> Quaternion::fromDCM(Matrix &dcm) {
    throw "unimplemented error";
}

void Quaternion::printRadians() {
    return;
}

void Quaternion::printDegrees() {
    return;
}

void Quaternion::normalize(){
    m_b = m_b / length();
}

double Quaternion::length() {
    return m_b(0, 0) + m_b(1, 0) + m_b(2, 0) + m_b(3, 0);
}

Quaternion Quaternion::fromPRV(PRV &p) {
    double b0 = cos(p.getPhi()/2);
    Matrix tmp = p.getEv();
    Matrix e = sin(p.getPhi()/2) * tmp;
    return Quaternion(b0, e(0, 0), e(1, 0), e(2, 0));
}

std::ostream& operator>>(std::ostream& os, Quaternion &q) {
    os << "B_0: " << q.m_b(0, 0) << " B_1: " << q.m_b(1, 0) << " B_2: " << q.m_b(2, 0) << " B_3: " << q.m_b(3, 0);
    return os;
}
