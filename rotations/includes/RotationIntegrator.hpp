//
// Created by Alex Post on 3/18/20.
//

#ifndef ROTATIONS_ROTATIONINTEGRATOR_HPP
#define ROTATIONS_ROTATIONINTEGRATOR_HPP

#include "Matrix.hpp"

template <typename T>
class RotationIntegrator {
private:
    T obj;
public:
    RotationIntegrator(T obj);
    RotationIntegrator(const RotationIntegrator &o) = default;
    ~RotationIntegrator() = default;
    T integrate(const std::function<Matrix(double)> &w, double duration, double step);
};

template<typename T>
RotationIntegrator<T>::RotationIntegrator(T obj): obj(obj) {}

template<typename T>
T RotationIntegrator<T>::integrate(const std::function<Matrix(double)> &w, double duration, double step) {
    T result(obj);
    for (double i = 0; i <= duration; i += step) {
        result.update(w(i), step);
    }
    return result;
}


#endif //ROTATIONS_ROTATIONINTEGRATOR_HPP
