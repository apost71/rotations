//
// Created by Alex Post on 2/19/20.
//

#ifndef ROTATIONS_QUATERNION_HPP
#define ROTATIONS_QUATERNION_HPP

#include <map>
#include "RotationParameters.hpp"
#include "PRV.hpp"
#include <math.h>

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

class ShepperdMethod {
private:
    Matrix* m_C;
    std::map<int, std::map<int, std::function<double(Matrix *, double)>>> m_bFunctions = {
            {
                    0, {
                               {0, [](Matrix *C, double d) { return d; }},
                               {1, [](Matrix *C, double d) { return (((*C)(1, 2) - (*C)(2, 1)) / 4) / d; }},
                               {2, [](Matrix *C, double d) { return (((*C)(2, 0) - (*C)(0, 2)) / 4) / d; }},
                               {3, [](Matrix *C, double d) { return (((*C)(0, 1) - (*C)(1, 0)) / 4) / d; }},
                       }
            },
            {
                    1, {
                               {0, [](Matrix *C, double d) { return (((*C)(1, 2) - (*C)(2, 1)) / 4) / d; }},
                               {1, [](Matrix *C, double d) { return d; }},
                               {2, [](Matrix *C, double d) { return (((*C)(0, 1) - (*C)(1, 0)) / 4) / d; }},
                               {3, [](Matrix *C, double d) { return (((*C)(2, 0) - (*C)(0, 2)) / 4) / d; }},
                       }
            },
            {
                    2, {
                               {0, [](Matrix *C, double d) { return (((*C)(2, 0) - (*C)(0, 2)) / 4) / d; }},
                               {1, [](Matrix *C, double d) { return (((*C)(0, 1) - (*C)(1, 0)) / 4) / d; }},
                               {2, [](Matrix *C, double d) { return d; }},
                               {3, [](Matrix *C, double d) { return (((*C)(1, 2) - (*C)(2, 1)) / 4) / d; }},
                       }
            },
            {
                    3, {
                               {0, [](Matrix *C, double d) { return (((*C)(0, 1) - (*C)(1, 0)) / 4) / d; }},
                               {1, [](Matrix *C, double d) { return (((*C)(2, 0) - (*C)(0, 2)) / 4) / d; }},
                               {2, [](Matrix *C, double d) { return (((*C)(1, 2) - (*C)(2, 1)) / 4) / d; }},
                               {3, [](Matrix *C, double d) { return sqrt(d); }},
                       }
            }
    };

public:
    explicit ShepperdMethod(Matrix &c): m_C(&c){}
    ShepperdMethod(const ShepperdMethod &o);
    ~ShepperdMethod();

    Matrix solve();
    Matrix bSquares();

};
#endif //ROTATIONS_QUATERNION_HPP
