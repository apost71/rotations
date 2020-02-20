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

class Matrix {
private:
    double** m_data;
    int m_cols;
    int m_rows;
    
public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix &o);
    ~Matrix();
    
    Matrix multiply(Matrix o);
    Matrix transpose() ;
    int getRows() const;
    int getColumns() const;
    void print();
    void insert(int row, int column, double value);
    double get(int row, int col);
    double &operator()(int row, int col);
    double det();
    static double getDeterminant(Matrix &m);
    friend Matrix operator*(Matrix &m1, Matrix &m2);
    friend Matrix operator*(double d, Matrix &m);
    friend std::ostream& operator<<(std::ostream& os, Matrix &m);
};
#endif /* Matrix_hpp */
