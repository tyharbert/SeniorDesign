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

	// TODO: currently truncates to integer, may want to round??
	width = height * h2w_ratio;

	Corner sw = Corner(0,0);
 	Corner nw = Corner(0, height);
 	Corner ne = Corner(width, height);
 	Corner se = Corner(width, 0);

	return Corners(sw, nw, ne, se);
}

void Corners::print() {
	std::cout << "sw: x: " << _sw._x << " y: " << _sw._y << std::endl;
	std::cout << "nw: x: " << _nw._x << " y: " << _nw._y << std::endl;
	std::cout << "ne: x: " << _ne._x << " y: " << _ne._y << std::endl;
	std::cout << "se: x: " << _se._x << " y: " << _se._y << std::endl << std::endl;
}

int* Corners::xArray() {
	return new int[4] {_sw._x, _nw._x, _ne._x, _se._x};
}

int* Corners::yArray() {
	return new int[4] {_sw._y, _nw._y, _ne._y, _se._y};
}