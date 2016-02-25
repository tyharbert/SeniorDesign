#include "matrix.hpp"

// matrix class constructor
Matrix::Matrix(int h, int w): _height(h), _width(w) {
    _values = new float*[h]();
    for (int i=0; i < h; i++)
        _values[i] = new float[w]();
}

// matrix copy constructor
Matrix::Matrix(const Matrix& m): Matrix(m._height, m._width) {
    for (int r=0; r < m._height; r++)
        for (int c=0; c < m._width; c++){
            _values[r][c] = m._values[r][c];
        }
}

// constructor for transformation matrix
Matrix::Matrix(Corners orig, Corners dest): Matrix(8) {
    int row;
    int* ox = orig.xArray();
    int* oy = orig.yArray();
    int* dx = dest.xArray();
    int* dy = dest.yArray();

    for (int i=0; i < 4; i++) {
        _values[i][0] = ox[i];
        _values[i][1] = oy[i];
        _values[i][2] = 1;
    }

    for (int i=0; i < 4; i++) {
        row = i+4;
        _values[row][3] = ox[i];
        _values[row][4] = oy[i];
        _values[row][5] = 1;
    }

    for (int i=0; i < 4; i++) {
        _values[i][6] = -((float)ox[i])*dx[i];
        _values[i][7] = -((float)oy[i])*dx[i];
    }

    for (int i=0; i < 4; i++) {
        row = i+4;
        _values[row][6] = -((float)ox[i])*dy[i];
        _values[row][7] = -((float)oy[i])*dy[i];
    }
}

// matrix destructor
Matrix::~Matrix() {
    for (int i=0; i < _height; i++)
        delete _values[i];
    delete _values;
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