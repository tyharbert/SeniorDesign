#ifndef CORNER_HPP
#define CORNER_HPP

#include <iostream>

// these are based on the reference rectangle
// ratio from height to width
const double h2w_ratio = 17.0/21.0; 

struct Corner {
	int _x;
	int _y;

	Corner(): _x(0), _y(0) { }
	Corner(int c[2]): _x(c[0]), _y(c[1]) { }
	Corner(int x, int y): _x(x), _y(y) { }
};

struct Corners {
	Corner _sw;
	Corner _nw;
	Corner _ne;
	Corner _se;

	Corners() { }
	Corners(Corner sw, Corner nw, Corner ne, Corner se): _sw(sw), _nw(nw), _ne(ne), _se(se) { }
	Corners(int c[4][2]): _sw(c[0]), _nw(c[1]), _ne(c[2]), _se(c[3]) { }
	Corners findDest();
	int* xArray();
	int* yArray();
	void print();
};

#endif