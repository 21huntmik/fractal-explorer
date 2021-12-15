#include "ComplexFractal.h"
#include <vector>
#include <cmath>


ComplexFractal::ComplexFractal() 
	: ThreadedGrid(200, 300), mMinX(-1.5), mMinY(-1.0), mMaxX(1.5), mMaxY(1), deltaX(0.01), deltaY(0.01) {
}

ComplexFractal::ComplexFractal(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y)
	: ThreadedGrid(height, width), mMinX(min_x), mMinY(min_y), mMaxX(max_x), mMaxY(max_y) {
	setGridSize(height, width);
}

ComplexFractal::~ComplexFractal() {
}

double ComplexFractal::getMinX() const {
	return mMinX;
}

double ComplexFractal::getMaxX() const {
	return mMaxX;
}

double ComplexFractal::getMinY() const {
	return mMinY;
}

double ComplexFractal::getMaxY() const {
	return mMaxY;
}

void ComplexFractal::setGridSize(const int& height, const int& width) {
	if(height >= 2 && width >= 2) {
		NumberGrid::setGridSize(height, width);
		double delta_y = calculateDeltaY();
		double delta_x = calculateDeltaX();
		setDeltas(delta_x, delta_y);
	}
}

void ComplexFractal::setPlaneSize(const double& min_x, const double& max_x, const double& min_y, const double& max_y) {
	if(min_x >= -2.0 && min_x <= 2.0 && min_y >= -2.0 && min_y <= 2.0 && max_x >= -2.0 && max_x <= 2.0 && max_y <= 2.0 && max_y >= -2.0 && min_x != max_x && min_y != max_y) {
		if(min_x > max_x) {
			mMinX = max_x;
			mMaxX = min_x;
		} else {
			mMinX = min_x;
			mMaxX = max_x;
		}

		if(min_y > max_y) {
			mMinY = max_y;
			mMaxY = min_y;
		} else {
			mMinY = min_y;
			mMaxY = max_y;
		}
		double delta_X = calculateDeltaX();
		double delta_Y = calculateDeltaY();
		setDeltas(delta_X, delta_Y);
	}
}

double ComplexFractal::getDeltaX() const {
	return deltaX;
}

double ComplexFractal::getDeltaY() const {
	return deltaY;
}

void ComplexFractal::setDeltas(const double& delta_x, const double& delta_y) {
	if(delta_x > 0 && delta_y > 0) {
		deltaX = delta_x;
		deltaY = delta_y;
	}
}

double ComplexFractal::calculateDeltaY() const {
	double delta_y = (mMaxY - mMinY) / (NumberGrid::getHeight() - 1);
	return delta_y;
}

double ComplexFractal::calculateDeltaX() const {
	double delta_x = (mMaxX - mMinX) / (NumberGrid::getWidth() -1);
	return delta_x;
}

double ComplexFractal::calculatePlaneXFromPixelColumn(const int& column) const {
	if(column >= NumberGrid::getWidth() || column < 0) {
		return 0.0;
	} else {
		double x = mMinX + column * this->getDeltaX();
		return x;
	}
}

double ComplexFractal::calculatePlaneYFromPixelRow(const int& row) const {
	if(row >= NumberGrid::getHeight() || row < 0) {
		return 0;
	} else {
		double y = mMaxY - row * this->getDeltaY();
		return y;
	}
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double& x, double& y) const {
	if(indexValid(row, column)) {
		y = calculatePlaneYFromPixelRow(row);
		x = calculatePlaneXFromPixelColumn(column);
	} else {
		x = 0;
		y = 0;
	}
}

int ComplexFractal::calculateNumber(const int& row, const int& column) const {
	if(indexValid(row, column)) {
		double x = calculatePlaneXFromPixelColumn(column);
		double y = calculatePlaneYFromPixelRow(row);
		return std::abs(getMaxNumber() * std::sin(10*x) * std::cos(10*y));
	} else {
		return -1;
	}
}

void ComplexFractal::zoomPlane(const double& zoom_factor) {
	//first find the difference by subtracting minimum from the maximum
		//call that current x size
	//desired x size = current x size * zoom factor
	//subtract desired x size from current x size and divide by 2 to find how much to change
	//new minimum x = x change + minimum x
	//new maximum x = x change - maximum x
	//if less than -2, set to -2
	//if greater than 2, set to 2
	//same for y
	//call setPlaneSize(min_x, max_x, min_y, max_y)
	int currentX = mMinX - mMaxX;
	int currentY = mMinY - mMaxY;
	int desiredX = currentX * zoom_factor;
	int desiredY = currentY * zoom_factor;
	int xChange = desiredX - currentX / 2;
	int yChange = desiredY - currentY / 2;
	int newMinX = xChange + mMinX;
	int newMaxX = xChange - mMaxX;
	int newMinY = yChange + mMinY;
	int newMaxY = yChange - mMaxY;
	if(newMinX < -2) {
		newMinX = -2;
	}
	if(newMaxX > 2) {
		newMaxX = 2;
	}
	if(newMinY < -2) {
		newMinY = -2;
	}
	if(newMaxY > 2) {
		newMaxY = 2;
	}
	setPlaneSize(newMinX, newMaxX, newMinY, newMaxY);
}
