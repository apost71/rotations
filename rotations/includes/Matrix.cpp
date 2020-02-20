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
    this->m_data = new double*[m_rows];
    for (int i = 0; i < m_rows; i ++) {
        m_data[i] = new double[m_cols];
        for (int j = 0; j < m_cols; j ++) {
            m_data[i][j] = o.m_data[i][j];
        }
    }
}

Matrix::~Matrix() {
    if (m_data) {
        for (int i = 0; i < m_rows; i++) {
            delete[] m_data[i];
        }
        delete[] m_data;
    } else {
        std::cout << "Data not initialized" << std::endl;
    }
}

Matrix Matrix::multiply(Matrix o) {
    Matrix* result = new Matrix(m_rows, o.m_cols);
    for (int i = 0; i < m_rows; i ++) {
        for (int j = 0; j < o.m_cols; j ++) {
            auto sum = new double(0);
            for (int k = 0; k < m_cols; k ++) {
                *sum += this->m_data[i][k] * o.m_data[k][j];
            }
            result->insert(i, j, *sum);
        }
    }
    return *result;
}

Matrix Matrix::transpose() {
    for (int i = 0; i < m_rows; i ++ ) {
        for (int j = i + 1; j < m_cols; j ++) {
            // potential for a memory leak here I think
            double cur = m_data[i][j];
            this->m_data[i][j] = this->m_data[j][i];
            m_data[j][i] = cur;
        }
    }
    return *this;
}

void Matrix::insert(int row, int column, double value) {
    m_data[row][column] = value;
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

double& Matrix::operator()(int row, int col){
    assert(col >= 0 && col < m_cols);
    assert(row >= 0 && row < m_rows);

    return m_data[row][col];
}

double Matrix::det() {
    return getDeterminant(*this);
}

// Get determinant of n-dimensional matrix using laplace expansion
double Matrix::getDeterminant(Matrix &m) {
    if (m.m_cols == 2 && m.m_rows == 2) {
        return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
    }
    else {
        double d = 0.0;
        for (int i = 0; i < m.m_cols; i ++){
            auto subMatrix = Matrix(m.m_rows - 1, m.m_cols - 1);
            for (int j = 1; j < m.m_rows; j ++) {
                for (int k = 0; k < m.m_cols; k ++) {
                    int col_idx = k;
                    if (k == i) {
                        continue;
                    } else if (k > i) {
                        col_idx = k - 1;
                    }
                    subMatrix(j - 1, col_idx) = m(j, k);
                }
            }
            if (i % 2 == 0) {
                d += m(0, i) * getDeterminant(subMatrix);
            } else {
                d -= m(0, i) * getDeterminant(subMatrix);
            }
        }
        return d;
    }
}



std::ostream& operator<<(std::ostream& os, Matrix &m){
    os << "[" << std::endl;
    for (int i = 0; i < m.getRows(); i ++) {
        os << "  [";
        for (int j = 0; j < m.getColumns(); j ++) {
            os << m(i, j);
            if (j < m.getColumns() - 1) {
                os << ", ";
            }
        }
        os << "]" << std::endl;
    }
    os << "]";
    return os;
}

Matrix operator*(Matrix &m1, Matrix &m2) {
    if (m2.m_rows != m1.m_cols) {
        throw std::runtime_error("Matrices dimensions must be compatible");
    }

    Matrix result = Matrix(m1.m_rows, m2.m_cols);
    for (int i = 0; i < m1.m_rows; i ++) {
        for (int j = 0; j < m2.m_cols; j ++) {
            auto sum = new double(0);
            for (int k = 0; k < m1.m_cols; k ++) {
                *sum += m1.m_data[i][k] * m2.m_data[k][j];
            }

            result(i, j) = *sum;
        }
    }
    return result;
}

Matrix operator*(double d, Matrix &m) {
    Matrix result = Matrix(m.m_rows, m.m_cols);
    for (int i = 0; i < m.m_rows; i++) {
        for (int j = 0; j < m.m_cols; j++) {
            result(i, j) = d * m(i, j);
        }
    }
    return result;
}