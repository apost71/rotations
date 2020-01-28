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
    
    Matrix* multiply(Matrix &o);
    Matrix* transpose() ;
    double* &operator[](int i);
    int getRows() const;
    int getColumns() const;
    void print();
    void insert(int row, int column, double value);
    double get(int row, int col);
};

#endif /* Matrix_hpp */
