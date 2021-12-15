#include "JuliaSet.h"
#include <cmath>

JuliaSet::JuliaSet()
	: ComplexFractal(), mA(-0.650492), mB(-0.478235) {
	setMaxNumber(255);
}

JuliaSet::JuliaSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b)
	: ComplexFractal(height, width, min_x, max_x, min_y, max_y), mA(a), mB(b) {
	setMaxNumber(255);
}

JuliaSet::~JuliaSet() {
}

double JuliaSet::getA() const {
	return mA;
}

double JuliaSet::getB() const {
	return mB;
}

void JuliaSet::setParameters(const double& a, const double& b) {
	if(a > 2 || a < -2 || b > 2 || b < -2) {
		return;
	} else {
		mA = a;
		mB = b;
	}
}

void JuliaSet::calculateNextPoint(const double x0, const double y0, double& x1, double &y1) const {
	x1 = (x0 * x0) - (y0 * y0) + mA;
	y1 = (2 * x0 * y0) + mB;
}

int JuliaSet::calculatePlaneEscapeCount(const double& x0, const double& y0) const {
	int count;
	double y = y0;
	double x = x0;
	int maxCount = getMaxNumber();
	for(count = 0; count <= maxCount; count++) {
		if(count == maxCount) {
			return count;
		} else if(sqrt((x*x) + (y*y)) <= 2) {
			calculateNextPoint(x, y, x, y);
		} else {
			return count;
		}
	}
	return count;
	//sqrt(x*x + y*y) > 2
}

int JuliaSet::calculateNumber(const int& row, const int& column) const {
	double x, y;
	if(indexValid(row, column)) {
		calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
		return calculatePlaneEscapeCount(x, y);
	} else {
		return -1;
	}
}

JuliaSetFour::JuliaSetFour() 
	: JuliaSet() {
}

JuliaSetFour::~JuliaSetFour() {
}

void JuliaSetFour::calculateNextPoint(const double x0, const double y0, double& x1, double &y1) const {
	//calculations HERE
	x1 = (x0*x0*x0*x0) - (6 * (x0*x0) * (y0*y0)) + (y0*y0*y0*y0) + getA();
	y1 = 4 * (x0*x0*x0) * y0 - 4 * (y0*y0*y0) * x0 + getB();
}

Julia5::Julia5()
	: JuliaSet() {
}

Julia5::~Julia5() {
}

void Julia5::calculateNextPoint(const double x0, const double y0, double& x1, double& y1) {
	double r = std::sqrt(x0 * x0 + y0 * y0);
	double theta = std::atan2(y0, x0);
	double exp = std::pow(r, 5);
	x1 = 2 * exp * std::cos(5 * theta) + getA();
	y1 = 2 * exp * std::sin(5 * theta) + getB();
}	
