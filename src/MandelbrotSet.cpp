#include "MandelbrotSet.h"
#include <cmath>

MandelbrotSet::MandelbrotSet() 
	: ComplexFractal() {
}

MandelbrotSet::MandelbrotSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y)
	: ComplexFractal(height, width, min_x, max_x, min_y, max_y) {
}

MandelbrotSet::~MandelbrotSet() {
}

void MandelbrotSet::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double &y1) const {
	x1 = (x0 * x0) - (y0 * y0) + a;
	y1 = (2 * x0 * y0) + b;
}

int MandelbrotSet::calculatePlaneEscapeCount(const double& a, const double& b) const {
	//uses calculateNextPoint to find the escape count for the point at a,b
	//the first iteration from x,y = 0,0 to x,y=a,b doesn't count as an iteration
	int count;
	double y = 0;
	double x = 0;
	double x1, y1;
	int maxCount = getMaxNumber();
	calculateNextPoint(x, y, a, b, x1, y1);
	x = x1;
	y = y1;
	for(count = 0; count <= maxCount; count ++) {
		if(count == maxCount) {
			return count;
		} else if(sqrt((x*x) + (y*y)) <= 2) {
			calculateNextPoint(x, y, a, b, x1, y1);
			x = x1;
			y = y1;
		} else {
			return count;
		}
	}
	return count;
}

int MandelbrotSet::calculateNumber(const int& row, const int& column) const {
	//uses other methods to find the plane coordinate of the pixel set at row,column
	//and calcualte the escape count
	//return the count or -1 if index invalid
	double a = 0; //set to 0
	double b = 0;
	calculatePlaneCoordinatesFromPixelCoordinates(row, column, a, b);
	//a and b are just x and y
	int iterations = calculatePlaneEscapeCount(a, b);
	if(indexValid(row, column)) {
		return iterations;
	} else {
		return -1;
	}
}

MandelbrotPower::MandelbrotPower() 
	: MandelbrotSet(), dPower(2.0) {
}

MandelbrotPower::~MandelbrotPower() {
}
double MandelbrotPower::getPower() const {
	return dPower;
}

void MandelbrotPower::setPower(const double& power) {
	dPower = power;
}

void MandelbrotPower::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double &y1) const{
	//apply formulas
	//x' = x1 y' = y1 x =x0 y= y0 a and b are original point
	double r = std::sqrt( x0*x0 + y0*y0);
	double theta = std::atan2(y0, x0);
	x1 = std::pow(r, dPower) * std::cos(dPower * theta) + a;
	y1 = std::pow(r, dPower) * std::sin(dPower * theta) + b;
}

BurningShip::BurningShip()
	: MandelbrotSet() {
}

BurningShip::~BurningShip() {
}

void BurningShip::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double &y1) const {
	x1 = -(x0 * x0 - y0 * y0 - a);
	y1 = std::abs(2 * x0 * y0) + b;
}

Tricorn::Tricorn()
	: MandelbrotSet() {
}

Tricorn::~Tricorn() {
}

void Tricorn::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double &y1) const {
	x1 = x0 * x0 - y0 * y0 + a;
	y1 = -2 * x0 * y0 + b;
}
