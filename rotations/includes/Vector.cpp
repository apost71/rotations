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

