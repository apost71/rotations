//
// Created by Alex Post on 2/25/20.
//

#ifndef ROTATIONS_VECTOR_HPP
#define ROTATIONS_VECTOR_HPP


#include <memory>
#include <iostream>

class Vector {
private:
    double* m_data;
    int length;
public:
    Vector():Vector(0){};
    Vector(int length);
    Vector(const std::initializer_list<double> &d);
    Vector(const Vector &o);
    ~Vector();
    Vector& operator=(const Vector &o);

    int getLength();
    double& operator[](int i);
    double norm();
    void normalize();
    double dot(Vector &v);
    Vector power(int pow);
    Vector cross(Vector &v);
    int maxIndex();
    double maxValue();

    friend bool operator==(const Vector &lhs, const Vector &rhs);
    friend std::ostream& operator<<(std::ostream &os, Vector &v);
    friend Vector& operator*(double d, Vector &v);
    friend Vector& operator+(Vector &v1, Vector &v2);
    friend Vector& operator-(Vector &v1, Vector &v2);
    friend Vector& operator/(Vector &v, double d);

};

#endif //ROTATIONS_VECTOR_HPP
