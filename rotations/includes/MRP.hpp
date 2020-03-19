//
// Created by Alex Post on 3/18/20.
//

#ifndef ROTATIONS_MRP_HPP
#define ROTATIONS_MRP_HPP


#include "RotationParameters.hpp"
#include "Quaternion.hpp"
#include "CRP.hpp"

class MRP: public RotationParameters {
private:
    Vector* q = nullptr;
public:
    MRP() = default;
    MRP(Vector &v);
    MRP(Quaternion &q);
    MRP(PRV &p);
    MRP(const std::initializer_list<double> &list);
    MRP(const MRP &o);
    ~MRP();
    MRP& operator=(const MRP &o);

    Matrix B();
    Matrix toDCM() override;
    Vector& getQVector();
    Quaternion toQuaternion();
    CRP toCRP();
    void update(Matrix Bi, double step);
    static MRP fromDCM(Matrix &dcm);

    friend std::ostream& operator<<(std::ostream &os, MRP &e);
    friend bool operator==(const MRP &lhs, const MRP&rhs);
    friend MRP operator+(MRP &lhs, MRP &rhs);
    friend MRP operator+(MRP &lhs, RotationParameters &rhs);
    friend MRP operator-(MRP &lhs, MRP &rhs);
    friend MRP operator-(MRP &lhs, RotationParameters &rhs);
};


#endif //ROTATIONS_MRP_HPP
