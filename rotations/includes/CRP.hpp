//
// Created by Alex Post on 3/18/20.
//

#ifndef ROTATIONS_CRP_HPP
#define ROTATIONS_CRP_HPP

#include "Vector.hpp"
#include "Matrix.hpp"
#include "RotationParameters.hpp"
#include "Quaternion.hpp"

class CRP: public RotationParameters {
private:
    Vector* q = nullptr;
public:
    CRP() = default;
    CRP(Vector &v);
    CRP(Quaternion &q);
    CRP(const std::initializer_list<double> &list);
    CRP(const CRP &o);
    ~CRP();
    CRP& operator=(const CRP &o);

    Matrix B();
    Matrix toDCM() override;
    Vector& getQVector();
    static CRP fromDCM(Matrix &dcm);
    CRP integrate(const std::function<Matrix(double)> &w, double duration, double step);

    friend std::ostream& operator<<(std::ostream &os, CRP &e);
    friend bool operator==(const CRP &lhs, const CRP&rhs);
    friend CRP operator+(CRP &lhs, CRP &rhs);
    friend CRP operator+(CRP &lhs, RotationParameters &rhs);
    friend CRP operator-(CRP &lhs, CRP &rhs);
    friend CRP operator-(CRP &lhs, RotationParameters &rhs);
};

#endif //ROTATIONS_CRP_HPP
