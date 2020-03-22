//
// Created by Alex Post on 3/21/20.
//

#ifndef ROTATIONS_DAVENPORTQ_HPP
#define ROTATIONS_DAVENPORTQ_HPP


#include <math/Vector.hpp>
#include <array>
#include <math/Matrix.hpp>

class DavenportQ {
private:
    Vector* b;
    Vector* n;
    double* w;
    int n_items;
public:
    DavenportQ(Vector b[], Vector n[], double w[], int n_items);
    DavenportQ(const DavenportQ &o);
    ~DavenportQ();

    Matrix solve();
};


#endif //ROTATIONS_DAVENPORTQ_HPP
