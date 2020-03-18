//
//  Matrix.hpp
//  rotations
//
//  Created by Alex Post on 1/26/20.
//  Copyright © 2020 Alex Post. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <iostream>
#include "Vector.hpp"

class Matrix {
private:
    Vector* m_data;
    int m_cols = 0;
    int m_rows = 0;
    
public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(Vector &v);
    Matrix(const std::initializer_list<Vector> &list);
    Matrix(const std::initializer_list<std::initializer_list<double>> &list);
    Matrix(const Matrix &o);
    ~Matrix();
    
    Matrix multiply(const Matrix &o);
    Matrix transpose() ;
    [[nodiscard]] int getRows() const;
    [[nodiscard]] int getColumns() const;
    void insert(int row, int column, double value);
    double get(int row, int col);
    double &operator()(int row, int col);
    double det();
    double trace();
    std::pair<int, int> max();
    std::pair<int, int> min();
    static double getDeterminant(Matrix &m);
    friend Matrix operator*(Matrix &m1, Matrix &m2);
    friend Matrix operator*(double d, Matrix &m);
    friend Matrix operator/(Matrix &m, double d);
    friend std::ostream& operator<<(std::ostream& os, Matrix &m);
    friend bool operator==(const Matrix &m1, const Matrix &m2);
    Matrix& operator=(const Matrix &o);
};
#endif /* Matrix_hpp */
