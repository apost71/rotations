//
// Created by Alex Post on 2/19/20.
//

#include <cmath>
#include "Quaternion.hpp"


Quaternion::Quaternion(double b0, double b1, double b2, double b3) {
    this->m_b = new Vector({b0, b1, b2, b3});
}

Quaternion::Quaternion(const Quaternion &o) {
    this->m_b = new Vector(o.m_b->getLength());
    for (int i = 0 ; i < o.m_b->getLength(); i ++) {
        (*this->m_b)[i] = (*o.m_b)[i];
    }
}

Quaternion::Quaternion(Vector &v) {
    this->m_b = new Vector(v.getLength());
    for (int i = 0; i < v.getLength(); i ++) {
        (*this->m_b)[i] = v[i];
    }
}

Quaternion::Quaternion(std::initializer_list<double> &list) {
    this->m_b = new Vector(list);
    this->m_b->normalize();
}

Quaternion::~Quaternion() {
    delete this->m_b;
}

Quaternion& Quaternion::operator=(const Quaternion &o) {
    if(this == &o)
        return *this;

    this->m_b = new Vector(o.m_b->getLength());
    for (int i = 0; i < o.m_b->getLength(); i++) {
        (*this->m_b)[i] = (*o.m_b)[i];
    }
    return *this;
}

Matrix Quaternion::toDCM() {
    if (! m_dcm ) {
        this->m_dcm = new Matrix({
             {
                     pow((*m_b)[0], 2) + pow((*m_b)[1], 2) - pow((*m_b)[2], 2) - pow((*m_b)[3], 2),
                     2 * ((*m_b)[1] * (*m_b)[2] + (*m_b)[0] * (*m_b)[3]),
                     2 * ((*m_b)[1] * (*m_b)[3] - (*m_b)[0] * (*m_b)[2])
             },
             {
                     2 * ((*m_b)[1] * (*m_b)[2] - (*m_b)[0] * (*m_b)[3]),
                     pow((*m_b)[0], 2) - pow((*m_b)[1], 2) + pow((*m_b)[2], 2) - pow((*m_b)[3], 2),
                     2 * ((*m_b)[2] * (*m_b)[3] + (*m_b)[0] * (*m_b)[1])
             },
             {
                     2 * ((*m_b)[1] * (*m_b)[3] + (*m_b)[0] * (*m_b)[2]),
                     2 * ((*m_b)[2] * (*m_b)[3] - (*m_b)[0] * (*m_b)[1]),
                     pow((*m_b)[0], 2) - pow((*m_b)[1], 2) - pow((*m_b)[2], 2) + pow((*m_b)[3], 2)
             }
        });
    }
    return *m_dcm;
}

Quaternion Quaternion::fromDCM(Matrix &dcm) {
    auto solver = ShepperdMethod(dcm);
    Vector& b = solver.solve();
    return Quaternion(b);
}

Quaternion Quaternion::fromPRV(PRV &p) {
    double b0 = cos(p.getPhi()/2);
    Vector tmp = p.getEv();
    Vector e = sin(p.getPhi()/2) * tmp;
    return Quaternion(b0, e[0], e[1], e[2]);
}

std::ostream& operator<<(std::ostream& os, Quaternion &q) {
    os << "B_0: " << (*q.m_b)[0] << " B_1: " << (*q.m_b)[1] << " B_2: " << (*q.m_b)[2] << " B_3: " << (*q.m_b)[3];
    return os;
}

bool operator==(const Quaternion &q1, const Quaternion &q2) {
    return *q1.m_b == *q2.m_b;
}

Matrix Quaternion::B() {
    return Matrix({
            {
               (*m_b)[0], -(*m_b)[1], -(*m_b)[2], -(*m_b)[3]
            },
            {
                (*m_b)[1], (*m_b)[0], -(*m_b)[3], (*m_b)[2]
            },
            {
                (*m_b)[2], (*m_b)[3], (*m_b)[0], -(*m_b)[1]
            },
            {
                (*m_b)[3], -(*m_b)[2], (*m_b)[1], (*m_b)[0]
            }
    });
}

Vector& Quaternion::getBVector() {
    return *m_b;
}

Quaternion operator+(Quaternion &lhs, Quaternion &rhs) {
    Matrix dcm = lhs.addDCM(rhs);
    return Quaternion::fromDCM(dcm);}

Quaternion operator-(Quaternion &lhs, Quaternion &rhs) {
    Matrix dcm = lhs.subtractDCM(rhs);
    return Quaternion::fromDCM(dcm);
}

Quaternion operator+(Quaternion &lhs, RotationParameters &rhs) {
    Matrix dcm = lhs.addDCM(rhs);
    return Quaternion::fromDCM(dcm);
}

Quaternion operator-(Quaternion &lhs, RotationParameters &rhs) {
    Matrix dcm = lhs.subtractDCM(rhs);
    return Quaternion::fromDCM(dcm);
}

void Quaternion::update(Matrix Xi, double step) {
    Matrix Wn = B();
    Matrix tmp = Wn * Xi;
    Matrix Bi = 0.5 * tmp;
    (*m_b)[0] = (*m_b)[0] + step * Bi(0, 0);
    (*m_b)[1] = (*m_b)[1] + step * Bi(1, 0);
    (*m_b)[2] = (*m_b)[2] + step * Bi(2, 0);
    (*m_b)[3] = (*m_b)[3] + step * Bi(3, 0);
    (*m_b).normalize();
}


Vector& ShepperdMethod::solve() {
    Vector b_squares = bSquares();
    auto result = new Vector(4);
    auto max = b_squares.maxIndex();
    for (int i = 0; i < result->getLength(); i ++) {
        (*result)[i] = m_bFunctions[max][i](m_C, sqrt(b_squares[max]));
    }
    return *result;
}

ShepperdMethod::ShepperdMethod(const ShepperdMethod &o) {
    this->m_C = o.m_C;
}

ShepperdMethod::~ShepperdMethod() {}

Vector ShepperdMethod::bSquares() {
    auto b_squares = Vector(4);
    b_squares[0] = 0.25 * (1 + m_C->trace());
    b_squares[1] = 0.25 * (1 + 2*(*m_C)(0, 0) - m_C->trace());
    b_squares[2] = 0.25 * (1 + 2*(*m_C)(1, 1) - m_C->trace());
    b_squares[3] = 0.25 * (1 + 2*(*m_C)(2, 2) - m_C->trace());
    return b_squares;
}
