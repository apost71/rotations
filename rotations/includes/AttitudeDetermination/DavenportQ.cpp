//
// Created by Alex Post on 3/21/20.
//

#include "DavenportQ.hpp"
#include "Quaternion.hpp"
#include <array>
#include <math/Matrix.hpp>
#include <eigen3/Eigen/Dense>

DavenportQ::DavenportQ(Vector b[], Vector n[], double w[], int n_items) {
    this->b = new Vector[n_items];
    this->n = new Vector[n_items];
    this->w = new double[n_items];
    for (int i = 0; i < n_items; i ++) {
        this->b[i] = b[i];
        this->n[i] = n[i];
        this->w[i] = w[i];
    }
    this->n_items = n_items;
}

DavenportQ::DavenportQ(const DavenportQ &o) {
    this->b = new Vector[o.n_items];
    this->n = new Vector[o.n_items];
    this->w = new double[o.n_items];
    for (int i = 0; i < n_items; i ++) {
        this->b[i] = b[i];
        this->n[i] = n[i];
        this->w[i] = w[i];
    }
    this->n_items = o.n_items;
}

DavenportQ::~DavenportQ() {
//    delete b;
//    delete n;
//    delete w;
}

Matrix DavenportQ::solve() {
    Matrix B(3, 3);
    for (int i = 0; i < n_items; i++) {
        Matrix outer = Matrix::outerProduct(b[i], n[i]);
        std::cout << outer << std::endl;
        B = B + outer;
    }
    Matrix BT = B;
    BT.transpose();
    Matrix S = B + BT;
    double sigma = B.trace();
    Vector Z({
        B(1, 2) - B(2, 1),
        B(2, 0) - B(0, 2),
        B(0, 1) - B(1, 0),
    });
    Matrix sm = Matrix::identity(3, 3);
    Matrix si = sigma * sm;
    Matrix ss = S - si;

    Matrix K({
                     {
                         sigma, Z[0], Z[1], Z[2]
                     },
                     {
                         Z[0], ss(0, 0), ss(0, 1), ss(0, 2)
                     },
                     {
                         Z[1], ss(1, 0), ss(1, 1), ss(1, 2)
                     },
                     {
                         Z[2], ss(2, 0), ss(2, 1), ss(2, 2)
                     }
    });

    Eigen::Matrix4f matK;
    matK <<
         K(0, 0), K(0, 1), K(0, 2), K(0, 3),
            K(1, 0), K(1, 1), K(1, 2), K(1, 3),
            K(2, 0), K(2, 1), K(2, 2), K(2, 3),
            K(3, 0), K(3, 1), K(3, 2), K(3, 3);

    Eigen::EigenSolver<Eigen::Matrix4f> s(matK);
    double maxIndex = 0;
    for (int i = 0; i < s.eigenvalues().size(); i ++) {
        if (s.eigenvalues()(i).real() > s.eigenvalues()(maxIndex).real()) {
            maxIndex = i;
        }
    }
    std::cout << "Max Index: " << maxIndex << " Max Eigenvalue: " << s.eigenvalues()(maxIndex).real() << std::endl;
    Vector maxEigenvector({
        s.eigenvectors()(0, maxIndex).real(),
        s.eigenvectors()(1, maxIndex).real(),
        s.eigenvectors()(2, maxIndex).real(),
        s.eigenvectors()(3, maxIndex).real(),
    });

    Quaternion q = Quaternion(maxEigenvector);
    Matrix dcm = q.toDCM();
    return dcm;
}


