#include "matrix.hpp"

// matrix class constructor
Matrix::Matrix(int h, int w): _height(h), _width(w) {
    _values = new float*[h];
    for (int i=0; i < h; i++)
        _values[i] = new float[w];
}

// matrix copy constructor
Matrix::Matrix(const Matrix& m): Matrix(m._height, m._width) {
    for (int r=0; r < m._height; r++)
        for (int c=0; c < m._width; c++){
            _values[r][c] = m._values[r][c];
        }
}

// prints an matrix
void Matrix::print() {
    for (int r=0; r < _height; r++) {
        for (int c=0; c < _width; c++) {
            std::cout << _values[r][c] << '\t';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// computes the outer product Gaussian elimination
// of an NxN matrix
void Matrix::gausianOP() {
    assert(_height == _width); // must be a square matrix
    int n = _height;
    
    for (int k = 0; k < n-1; k++){
        for (int z = k+1; z < n; z++){
            _values[z][k] = _values[z][k]/_values[k][k];
        }
        for (int j = k+1; j < n; j++){
            for (int i = k+1; i < n; i++){
                _values[i][j] = _values[i][j] - _values[i][k]*_values[k][j];
            }
        }
    }
}