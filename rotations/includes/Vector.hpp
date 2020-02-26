//
// Created by Alex Post on 2/25/20.
//

#ifndef ROTATIONS_VECTOR_HPP
#define ROTATIONS_VECTOR_HPP


#include <memory>

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

};

#endif //ROTATIONS_VECTOR_HPP
