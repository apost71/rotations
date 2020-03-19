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
    return Matrix();
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

void MRP::update(Matrix Bi, double step) {

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

MRP operator+(MRP &lhs, MRP &rhs) {
    return MRP();
}

MRP operator+(MRP &lhs, RotationParameters &rhs) {
    return MRP();
}

MRP operator-(MRP &lhs, MRP &rhs) {
    return MRP();
}

MRP operator-(MRP &lhs, RotationParameters &rhs) {
    return MRP();
}


