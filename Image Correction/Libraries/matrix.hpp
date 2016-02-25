#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <iostream>

#include "corner.hpp"

class Matrix {
private:
    float** _values;
    int _height;
    int _width;
    
public:
    Matrix(int, int);
    Matrix(const Matrix& m);
    Matrix(int n): Matrix(n, n) { }
    Matrix(Corners, Corners);
    ~Matrix();
    void gausianOP();
    void print();
};

#endif