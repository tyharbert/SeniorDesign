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

	width = int_round(height * (rr_width_cm/rr_height_cm));

	Corner sw = Corner(0,0);
 	Corner nw = Corner(0, height);
 	Corner ne = Corner(width, height);
 	Corner se = Corner(width, 0);

	return Corners(sw, nw, ne, se);
}

// returns true if the point passed in falls between the
// bounds of the corners
bool Corners::inBounds(Point p) const {
	assert(_nw._x == _sw._x && _ne._x == _se._x && _nw._y == _ne._y && _sw._y == _se._y); // only check for rectangular corners
	if (_nw._x <= p._x && p._x <= _ne._x)
		if (_sw._y <= p._y && p._y <= _nw._y)
			return true;
	return false;
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

Corners getCornerInput() {
	int corners[4][2];
	int value;

	for (int i = 0; i < 8; i++) {
		std::cout << "Enter ";
		if (i/2 == 0)
			std::cout << "SW ";
		else if (i/2 == 1)
			std::cout << "NW ";
		else if (i/2 == 2)
			std::cout << "NE ";
		else if (i/2 == 3)
			std::cout << "SE ";

		if (i%2 == 0)
			std::cout << "X:" << std::endl;
		else if (i%2 == 1)
			std::cout << "Y:" << std::endl;

		std::cin >> value;
		corners[i/2][i%2] = value;
	}

	return Corners(corners);
}
