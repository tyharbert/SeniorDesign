#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cassert>
#include <iostream>

class Matrix {
private:
    float** _values;
    int _height;
    int _width;
    
public:
    Matrix(int, int);
    Matrix(const Matrix& m);
    Matrix(int n): Matrix(n, n) { }
    void gausianOP();
    void print();
};

#endif