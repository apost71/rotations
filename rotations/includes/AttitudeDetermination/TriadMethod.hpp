//
// Created by Alex Post on 3/21/20.
//

#ifndef ROTATIONS_TRIADMETHOD_HPP
#define ROTATIONS_TRIADMETHOD_HPP


#include <math/Vector.hpp>
#include <math/Matrix.hpp>

class TriadMethod {
private:
    Vector* b1 = nullptr;
    Vector* b2 = nullptr;
    Vector* n1 = nullptr;
    Vector* n2 = nullptr;
    Matrix* result = nullptr;
public:
    TriadMethod(Vector &b1, Vector &b2, Vector &n1, Vector &n2);
    TriadMethod(const TriadMethod &o);
    ~TriadMethod();

    Matrix solve();
    static Matrix tRelativeTo(Vector &v1, Vector &v2);
    static double principalRotationError(Matrix &bEstimated, Matrix &bTrue);
    double principalRotationError(Matrix &bTrue);
};


#endif //ROTATIONS_TRIADMETHOD_HPP
