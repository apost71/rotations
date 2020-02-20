//
// Created by Alex Post on 2/19/20.
//

#ifndef ROTATIONS_QUATERNION_HPP
#define ROTATIONS_QUATERNION_HPP

#include "RotationParameters.hpp"
#include "PRV.hpp"

class Quaternion: public RotationParameters {
private:
    Matrix m_b = Matrix(4, 1);
public:
    Quaternion() : Quaternion(0., 0., 0., 0.) {};

    Quaternion(double b0, double b1, double b2, double b3);

    Quaternion(const Quaternion &o);

    ~Quaternion() = default;

    std::unique_ptr<RotationParameters> add(RotationParameters &o) override;

    std::unique_ptr<RotationParameters> subtract(RotationParameters &o) override;

    Matrix toDCM() override;

    std::unique_ptr<RotationParameters> fromDCM(Matrix &dcm) override;

    void printRadians() override;

    void printDegrees() override;

    static Quaternion fromPRV(PRV &p);

    friend std::ostream& operator>>(std::ostream& os, Quaternion &q);

    void normalize();

    double length();
};
#endif //ROTATIONS_QUATERNION_HPP
