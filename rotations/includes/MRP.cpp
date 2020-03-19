//
// Created by Alex Post on 3/18/20.
//

#include "MRP.hpp"
#include <cmath>

MRP::MRP(Vector &v) {
    this->q = new Vector(v);
}

MRP::MRP(Quaternion &q) {
    Vector v = q.getBVector();
    this->q = new Vector({
                                 v[1] / 1 + v[0],
                                 v[2] / 1 + v[0],
                                 v[3] / 1 + v[0]
                         });
}

MRP::MRP(PRV &p) {
    Vector v = p.getEv();
    this->q = new Vector((tan(p.getPhi() / 2)) * v);
}

MRP::MRP(const std::initializer_list<double> &list) {
    this->q = new Vector(list);
}

MRP::MRP(const MRP &o) {
    this->q = new Vector(*(o.q));
}

MRP::~MRP() {
    delete this->q;
}

MRP &MRP::operator=(const MRP &o) {
    if(this == &o)
        return *this;
    this->q = new Vector(*(o.q));
    return *this;
}

Matrix MRP::B() {
    return Matrix({
                          {
                              1 - pow(q->norm(), 2) + 2 * pow((*q)[0], 2),
                              2 * ((*q)[0] * (*q)[1] - (*q)[2]),
                              2 * ((*q)[0] * (*q)[2] + (*q)[1])
                          },
                          {
                              2 * ((*q)[1] * (*q)[0] + (*q)[2]),
                              1 - pow(q->norm(), 2) + 2 * pow((*q)[1], 2),
                              2 * ((*q)[1] * (*q)[2] - (*q)[0])
                          },
                          {
                              2 * ((*q)[2] * (*q)[0] - (*q)[1]),
                              2 * ((*q)[2] * (*q)[1] + (*q)[0]),
                              1 - pow(q->norm(), 2) + 2 * pow((*q)[2], 2)
                          }
    });
}

Matrix MRP::toDCM() {
    Matrix tilde = Matrix::tilde(*q);
    Matrix tilde2 = tilde * tilde;
    Matrix first = 8 * tilde2;
    Matrix toSubtract = (4*(1 - pow(q->norm(), 2))) * tilde;
    Matrix num = first - toSubtract;
    double den = pow(1 + pow(q->norm(), 2), 2);
    Matrix result = num / den;
    Matrix identity = Matrix::identity(3, 3);
    return identity + result;
}

Vector &MRP::getQVector() {
    return *q;
}

Quaternion MRP::toQuaternion() {
    double b_0 = (1 - q->dot(*q)) / (1 + q->dot(*q));
    Vector b_i = (2 * *q) / (1 + q->dot(*q));
    return Quaternion({b_0, b_i[0], b_i[1], b_i[2]});
}

CRP MRP::toCRP() {
    return CRP((2 * *q) / (1 + q->dot(*q)));
}

void MRP::update(Matrix Xi, double step) {
    Matrix Wn = B();
    Matrix tmp = Wn * Xi;
    Matrix Bi = 0.25 * tmp;
    (*q)[0] = (*q)[0] + step * Bi(0, 0);
    (*q)[1] = (*q)[1] + step * Bi(1, 0);
    (*q)[2] = (*q)[2] + step * Bi(2, 0);
    if (q->norm() >= 1) {
        Vector v = -*q / pow(q->norm(), 2);
        this->q = new Vector(v);
    }
}

MRP MRP::fromDCM(Matrix &dcm) {
    Matrix c = Matrix(dcm);
    Matrix c_t = dcm.transpose();
    Matrix num = c_t - c;
    double s = sqrt(c.trace() + 1);
    if (s == 0) {
        PRV p = PRV::fromDCM(c);
        return MRP(p);
    } else {
        double den = s * (s + 2);
        Matrix tilde = num / den;
        Vector result = tilde.fromTilde();
        return MRP(result);
    }
}

std::ostream &operator<<(std::ostream &os, MRP &e) {
    os << *(e.q);
    return os;
}

bool operator==(const MRP &lhs, const MRP &rhs) {
    return *(lhs.q) == *(rhs.q);
}

MRP operator+(MRP &rhs, MRP &lhs) {
    double lhs2 = pow(lhs.q->norm(), 2);
    double rhs2 = pow(rhs.q->norm(), 2);
    Vector cross = (*rhs.q).cross(*(lhs.q));
    Vector num = (1 - lhs2) * *(rhs.q) + (1 - rhs2) * *(lhs.q) - 2 * cross;
    double den = 1 + lhs2 * rhs2 - (2 * *(lhs.q)).dot(*(rhs.q));
    return num / den;
}

MRP operator+(MRP &lhs, RotationParameters &rhs) {
    Matrix dcm = lhs.addDCM(rhs);
    return MRP::fromDCM(dcm);
}

MRP operator-(MRP &rhs, MRP &lhs) {
    double lhs2 = pow(lhs.q->norm(), 2);
    double rhs2 = pow(rhs.q->norm(), 2);
    Vector cross = (*rhs.q).cross(*(lhs.q));
    Vector num = (1 - lhs2) * *(rhs.q) - (1 - rhs2) * *(lhs.q) + 2 * cross;
    double den = 1 + lhs2 * rhs2 + (2 * *(lhs.q)).dot(*(rhs.q));
    return num / den;
}

MRP operator-(MRP &lhs, RotationParameters &rhs) {
    Matrix dcm = lhs.subtractDCM(rhs);
    return MRP::fromDCM(dcm);
}


