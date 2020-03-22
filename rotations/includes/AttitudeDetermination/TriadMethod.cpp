//
// Created by Alex Post on 3/21/20.
//

#include "TriadMethod.hpp"
#include "PRV.hpp"

TriadMethod::TriadMethod(Vector &b1, Vector &b2, Vector &n1, Vector &n2) {
    b1.normalize();
    b2.normalize();
    n1.normalize();
    n2.normalize();
    this->b1 = new Vector(b1);
    this->b2 = new Vector(b2);
    this->n1 = new Vector(n1);
    this->n2 = new Vector(n2);
}

TriadMethod::TriadMethod(const TriadMethod &o) {
    this->b1 = new Vector(*(o.b1));
    this->b2 = new Vector(*(o.b2));
    this->n1 = new Vector(*(o.n1));
    this->n2 = new Vector(*(o.n2));
}

TriadMethod::~TriadMethod() {
    delete b1, b2, n1, n2;
}

Matrix TriadMethod::solve() {
    Matrix Bt = tRelativeTo(*b1, *b2);
    std::cout << Bt << std::endl;
    Matrix Nt = tRelativeTo(*n1, *n2);
    Matrix Tn = Nt.transpose();
    this->result = new Matrix(Bt * Tn);
    return *result;
}

Matrix TriadMethod::tRelativeTo(Vector &v1, Vector &v2) {
    Vector t1 = v1;
    Vector cross = v1.cross(v2);
    double crossNorm = cross.norm();
    Vector t2 = cross / crossNorm;
    Vector t3 = t1.cross(t2);
    Matrix m({t1, t2, t3});
    m.transpose();
    return m;
}

double TriadMethod::principalRotationError(Matrix &bEstimated, Matrix &bTrue) {
    bTrue.transpose();
    Matrix diff = bEstimated * bTrue;
    PRV p = PRV::fromDCM(diff);

    return radianToDegrees(p.getPhi());
}

double TriadMethod::principalRotationError(Matrix &bTrue) {
    if (! result) {
        solve();
    }
    return principalRotationError(*result, bTrue);
}
