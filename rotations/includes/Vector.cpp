//
// Created by Alex Post on 2/25/20.
//

#include "Vector.hpp"
#include <iostream>
#include <cmath>


Vector::Vector(int length) {
    this->length = length;
    this->m_data = new double[length];
    for (int i = 0; i < length; i ++) {
        this->m_data[i] = 0;
    }
}

Vector::Vector(const std::initializer_list<double> &d) {
    this->length = d.size();
    this->m_data = new double[this->length];
    int i = 0;
    for (auto &element: d) {
        m_data[i] = element;
        i ++;
    }
}

Vector::~Vector() {
    delete this->m_data;
}

Vector::Vector(const Vector &o) {
    this->length = o.length;
    this->m_data = new double[o.length];
    for (int i = 0; i < length; i ++) {
        this->m_data[i] = o.m_data[i];
    }
}

Vector& Vector::operator=(const Vector &o) {
    this->length = o.length;
    this->m_data = new double[o.length];
    for (int i = 0; i < length; i ++) {
        this->m_data[i] = o.m_data[i];
    }
    return *this;
}

int Vector::getLength() {
    return length;
}

double& Vector::operator[](int i) {
    return m_data[i];
}

double Vector::norm() {
    double sum = 0;
    for (int i = 0; i < length; i ++) {
        sum += pow(m_data[i], 2);
    }
    return sqrt(sum);
}

bool operator==(const Vector &lhs, const Vector &rhs) {
    if (lhs.length != rhs.length) {
        return false;
    }
    for (int i = 0; i < lhs.length; i ++ ){
        if (abs(lhs.m_data[i] - rhs.m_data[i]) >= std::numeric_limits<double>::epsilon()) {
            return false;
        }
    }
    return true;
}

void Vector::normalize() {
    double mag = this->norm();
    for (int i = 0; i < length; i ++) {
        this->m_data[i] = this->m_data[i] / mag;
    }
}

std::ostream &operator<<(std::ostream &os, Vector &v) {
    os << "[";
    for (int i = 0; i < v.getLength() - 1; i++) {
        os << v[i] << ", ";
    }
    os << v[v.getLength() - 1] << "]";
    return os;
}

double Vector::dot(Vector &v) {
    assert(this->length == v.length);

    double sum = 0;
    for (int i = 0; i < this->length; i++) {
        sum += (*this)[i] * v[i];
    }
    return sum;
}

Vector &operator*(double d, Vector &v) {
    auto result = new Vector(v.length);

    for (int i = 0; i < v.length; i ++) {
        (*result)[i] = d * v[i];
    }

    return *result;
}

Vector &operator+(Vector &v1, Vector &v2) {
    assert(v1.length == v2.length);
    auto result = new Vector(v1.length);

    for (int i = 0; i < v1.length; i ++) {
        (*result)[i] = v1[i] + v2[i];
    }
    return *result;
}

Vector Vector::cross(Vector &v) {
    if (this->length != 3 || v.length != 3) {
        throw std::string("Unimplemented exception");
    }
    auto result = new Vector(v.length);

    (*result)[0] = (*this)[1] * v[2] - (*this)[2] * v[1];
    (*result)[1] = (*this)[2] * v[0] - (*this)[0] * v[2];
    (*result)[2] = (*this)[0] * v[1] - (*this)[1] * v[0];

    return *result;
}

Vector &operator-(Vector &v1, Vector &v2) {
    assert(v1.length == v2.length);
    auto result = new Vector(v1.length);

    for (int i = 0; i < v1.length; i ++) {
        (*result)[i] = v1[i] - v2[i];
    }
    return *result;
}

int Vector::maxIndex() {
    int maxIndex = 0;
    for (int i = 0; i < this->length; i ++) {
        if ((*this)[i] > (*this)[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

double Vector::maxValue() {
    double maxValue = (*this)[0];
    for (int i = 0; i < this->length; i ++) {
        if ((*this)[i] > maxValue) {
            maxValue = i;
        }
    }
    return maxValue;
}

