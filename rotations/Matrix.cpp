//
//  Matrix.cpp
//  rotations
//
//  Created by Alex Post on 1/26/20.
//  Copyright © 2020 Alex Post. All rights reserved.
//

#include "Matrix.hpp"
#include <iostream>

Matrix::Matrix(): Matrix(3, 3) {}

Matrix::Matrix(int rows, int cols): m_rows(rows), m_cols(cols){
    m_data = new double*[rows];
    for (int i = 0; i < rows; i ++) {
        m_data[i] = new double[cols];
        for (int j = 0; j < cols; j ++) {
            m_data[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix &o) {
    this->m_rows = o.m_rows;
    this->m_cols = o.m_cols;
    this->m_data = o.m_data;
}

Matrix::~Matrix() {}

Matrix* Matrix::multiply(Matrix &o) {
    Matrix* result = new Matrix(m_rows, o.m_cols);
    for (int i = 0; i < m_rows; i ++) {
        for (int j = 0; j < o.m_cols; j ++) {
            double* sum = new double(0);
            for (int k = 0; k < m_cols; k ++) {
                *sum += this->m_data[i][k] * o.m_data[k][j];
            }
            result->insert(i, j, *sum);
        }
    }
    return result;
}

Matrix* Matrix::transpose() {
    for (int i = 0; i < m_rows; i ++ ) {
        for (int j = i + 1; j < m_cols; j ++) {
            // potential for a memory leak here I think
            double cur = m_data[i][j];
            this->m_data[i][j] = this->m_data[j][i];
            m_data[j][i] = cur;
        }
    }
    return this;
}

void Matrix::insert(int row, int column, double value) {
    m_data[row][column] = value;
}


double* &Matrix::operator[](int i) {
    return m_data[i];
}

int Matrix::getRows() const {
    return m_rows;
}

int Matrix::getColumns() const {
    return m_cols;
}

void Matrix::print() {
    for (int i = 0; i < m_rows; i ++) {
        for (int j = 0; j < m_cols; j++) {
            std::cout << m_data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

double Matrix::get(int row, int col) {
    return m_data[row][col];
}
