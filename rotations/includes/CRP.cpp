//
// Created by Alex Post on 3/18/20.
//

#include "CRP.hpp"
#include <cmath>

CRP::CRP(Vector &v) {
   this->q = new Vector();
   *(this->q) = v;
}

CRP::CRP(Quaternion &q) {
    Vector v = q.getBVector();
    this->q = new Vector({
        -v[1] / -v[0],
        -v[2] / -v[0],
        -v[3] / -v[0]
    });
}

CRP::CRP(const std::initializer_list<double> &list) {
    this->q = new Vector(list);
}

CRP::CRP(const CRP &o) {
    *(this->q) = *(o.q);
}

CRP::~CRP() {
    delete this->q;
}

CRP& CRP::operator=(const CRP &o) {
    if(this == &o)
        return *this;
    *(this->q) = *(o.q);
    return *this;
}

Matrix CRP::toDCM() {
    Matrix c = Matrix(
            {
                    {
                        1 + pow((*q)[0], 2) - pow((*q)[1], 2) - pow((*q)[2], 2),
                        2 * ((*q)[0] * (*q)[1] + (*q)[2]),
                        2 * ((*q)[0] * (*q)[2] - (*q)[1])
                    },
                    {
                        2 * ((*q)[1] * (*q)[0] - (*q)[2]),
                        1 - pow((*q)[0], 2) + pow((*q)[1], 2) - pow((*q)[2], 2),
                        2 * ((*q)[1] * (*q)[2] + (*q)[0]),
                    },
                    {
                        2 * ((*q)[2] * (*q)[0] + (*q)[1]),
                        2 * ((*q)[2] * (*q)[1] - (*q)[0]),
                        1 - pow((*q)[0], 2) - pow((*q)[1], 2) + pow((*q)[2], 2),
                    }
            }
            );
    double den = 1 + (*q).dot(*q);
    return (1/den) * c;
}

CRP CRP::fromDCM(Matrix &dcm) {
    double s = sqrt(dcm.trace() + 1);
    double c = 1 / pow(s, 2);
    Vector q = Vector({
        c * (dcm(1, 2) - dcm(2, 1)),
        c * (dcm(2, 0) - dcm(0, 2)),
        c * (dcm(0, 1) - dcm(1, 0))
    });
    return CRP(q);
}

std::ostream &operator<<(std::ostream &os, CRP &crp) {
    os << *(crp.q);
    return os;
}

bool operator==(const CRP &lhs, const CRP &rhs) {
    return *(lhs.q) == *(rhs.q);
}

CRP operator+(CRP &lhs, CRP &rhs) {
    Vector cross = rhs.q->cross(*(lhs.q));
    Vector num = *(rhs.q) + *(lhs.q) - cross;
    double den = 1 - rhs.q->dot(*(lhs.q));
    Vector q = (1/den) * num;
    return CRP(q);
}

CRP operator+(CRP &lhs, RotationParameters &rhs) {
    Matrix dcm = lhs.addDCM(rhs);
    return CRP::fromDCM(dcm);
}

CRP operator-(CRP &lhs, CRP &rhs) {
    Vector cross = lhs.q->cross(*(rhs.q));
    Vector num = *(lhs.q) - *(rhs.q) + cross;
    double den = 1 + lhs.q->dot(*(rhs.q));
    Vector q = (1/den) * num;
    return CRP(q);
}

CRP operator-(CRP &lhs, RotationParameters &rhs) {
    Matrix dcm = lhs.subtractDCM(rhs);
    return CRP::fromDCM(dcm);
}

