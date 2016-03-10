#include "corner.hpp"

// this uses the smallest height and calculates
// the width based on the ratio of the reference
// rectangle's height to its width
Corners Corners::findDest() {
	int width;
	int height = _nw._y - _sw._y;
	int temp_height = _ne._y - _se._y;

	if (temp_height < height)
		height = temp_height;

	width = int_round(height * h2w_ratio);

	Corner sw = Corner(0,0);
 	Corner nw = Corner(0, height);
 	Corner ne = Corner(width, height);
 	Corner se = Corner(width, 0);

	return Corners(sw, nw, ne, se);
}

void Point::print() {
	std::cout << "x: " << _x << " y: " << _y << std::endl;
}

void Corners::print() {
	std::cout << "sw: "; _sw.print();
	std::cout << "nw: "; _nw.print();
	std::cout << "ne: "; _ne.print();
	std::cout << "se: "; _se.print();
	std::cout << std::endl;
}

int* Corners::xArray() {
	return new int[4] {_sw._x, _nw._x, _ne._x, _se._x};
}

int* Corners::yArray() {
	return new int[4] {_sw._y, _nw._y, _ne._y, _se._y};
}