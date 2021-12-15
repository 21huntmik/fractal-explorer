//this file must implement all of the methods of the PPM class declared in PPM.h
#include "PPM.h"
#include "image_menu.h"
#include <iostream>
#include <vector>

PPM::PPM()
	:Image(), maximum_color_value(1) {
}

PPM::PPM(const int& height, const int& width)
	:Image(height, width), maximum_color_value(1) {
}

int PPM::getMaxColorValue() const {
	return maximum_color_value;
}

bool PPM::valueValid(const int& value) const {
	//checks if value is a legal color value for this image. legal means at least 0 and no more than max_color_value. returns true if legal false if it's not.
	if(value >= 0 and value <= maximum_color_value) {
		return true;
	} else {
		return false;
	}
}

void PPM::setMaxColorValue(const int& max_color_value) {
	//change the maximum color value of the PPM. only values 1-255 inclusive are accepted. if the value is invalid... make no changes
	if(max_color_value > 0 and max_color_value <= 255) {
		maximum_color_value = max_color_value;
	}
}

void PPM::setChannel(const int& row, const int& column, const int& channel, const int& value) {
	//if value is valid (use valueValid()) then call Image::setChannel() passing in the correct parameters. if values is not valid, do nothing
	bool validity = valueValid(value);
	if(validity == true) {
		Image::setChannel(row, column, channel, value);
	}
}

void PPM::setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue) {
	//set all three channels to the specified pixel. should use setChannel to do the work
	//RGB
	//R = 0
	//G = 1
	//B = 2
	setChannel(row, column, 0, red);
	setChannel(row, column, 1, green);
	setChannel(row, column, 2, blue);
}

void PPM::writeStream(std::ostream& os) const {
	int height = Image::getHeight();
	int width = Image::getWidth();	
	os << "P6 "<< width << " " << height << " "  << maximum_color_value << "\n";
	int height_counter;
	int width_counter;
	for(height_counter = 0; height_counter < height; height_counter ++) {
		for(width_counter = 0; width_counter < width; width_counter ++) {
			int i;
			for(i = 0; i < 3; i ++) {
				int c = Image::getChannel(height_counter, width_counter, i);
				unsigned char v = c;
				os.write((char*) &v, 1);
			}
		}
	}
}

void PPM::readStream(std::istream& is) {
	int height;
	int width;
	int height_counter;
	int width_counter;
	int max_color;
	unsigned char v;
	std::string hi;
	is >> hi >> width >> height >> max_color;
	Image::setHeight(height);
	Image::setWidth(width);
	setMaxColorValue(max_color);
	is.read((char*)&v, 1);
	for(height_counter = 0; height_counter < height; height_counter ++) {
		for(width_counter = 0; width_counter < width; width_counter ++) {
			int i;
			for(i = 0; i < 3; i ++) {
				is.read((char*) &v, 1);
				Image::setChannel(height_counter, width_counter, i, v);
			}
		}
	}
}

bool PPM::operator==(const PPM& rhs) const {
	int pixelsThis = getHeight() * getWidth();
	int pixelsThat = rhs.getHeight() * rhs.getWidth();
	if(pixelsThis == pixelsThat) {
		return true;
	} else {
		return false;
	}
}

bool PPM::operator!=(const PPM& rhs) const {
	int pixelsThis = getHeight() * getWidth();
	int pixelsThat = rhs.getHeight() * rhs.getWidth();
	if(pixelsThis != pixelsThat) {
		return true;
	} else {
		return false;
	}
}

bool PPM::operator<(const PPM& rhs) const {
	int pixelsThis = getHeight() * getWidth();
	int pixelsThat = rhs.getHeight() * rhs.getWidth();
	if(pixelsThis < pixelsThat) {
		return true;
	} else {
		return false;
	}
}

bool PPM::operator<=(const PPM& rhs) const {

	int pixelsThis = getHeight() * getWidth();
	int pixelsThat = rhs.getHeight() * rhs.getWidth();
	if(pixelsThis <= pixelsThat) {
		return true;
	} else {
		return false;
	}
}

bool PPM::operator>(const PPM& rhs) const {
	int pixelsThis = getHeight() * getWidth();
	int pixelsThat = rhs.getHeight() * rhs.getWidth();
	if(pixelsThis > pixelsThat) {
		return true;
	} else {
		return false;
	}
}

bool PPM::operator>=(const PPM& rhs) const {
	int pixelsThis = getHeight() * getWidth();
	int pixelsThat = rhs.getHeight() * rhs.getWidth();
	if(pixelsThis >= pixelsThat) {
		return true;
	} else {
		return false;
	}
}

PPM& PPM::operator+=(const PPM& rhs) {
	int image_height = getHeight();
	int image_width = getWidth();
	
	int row_counter;
	int column_counter;

	for(row_counter = 0; row_counter < image_height; row_counter++) {
		for(column_counter = 0; column_counter < image_width; column_counter++) {
			int thisRPixel = this->getChannel(row_counter, column_counter, 0);
			int thisGPixel = this->getChannel(row_counter, column_counter, 1);
			int thisBPixel = this->getChannel(row_counter, column_counter, 2);
			
			int rhsRPixel = rhs.getChannel(row_counter, column_counter, 0);
			int rhsGPixel = rhs.getChannel(row_counter, column_counter, 1);
			int rhsBPixel = rhs.getChannel(row_counter, column_counter, 2);

			int max = this->getMaxColorValue();

			int newRPixel = thisRPixel + rhsRPixel;

			if(newRPixel > max) {
				newRPixel = max;
			}
			if(newRPixel < 0) {
				newRPixel = 0;
			}
				
			int newGPixel = thisGPixel + rhsGPixel;
			
			if(newGPixel > max) {
				newGPixel = max;
			}
			if(newGPixel < 0) {
				newGPixel = 0;
			}

			int newBPixel = thisBPixel + rhsBPixel;

			if(newBPixel > max) {
				newBPixel = max;
			}
			if(newBPixel < 0) {
				newBPixel = 0;
			}

			this->setPixel(row_counter, column_counter, newRPixel, newGPixel, newBPixel);
		}
	}
		
	return *this;
}

PPM& PPM::operator-=(const PPM& rhs) {
	int image_height = this->getHeight();
	int image_width = this->getWidth();

	int row_counter;
	int column_counter;

	for(row_counter = 0; row_counter < image_height; row_counter++) {
		for(column_counter = 0; column_counter < image_width; column_counter++) {
			int thisRPixel = this->getChannel(row_counter, column_counter, 0);
			int rhsRPixel = rhs.getChannel(row_counter, column_counter, 0);
			int thisGPixel = this->getChannel(row_counter, column_counter, 1);
			int rhsGPixel = rhs.getChannel(row_counter, column_counter, 1);
			int thisBPixel = this->getChannel(row_counter, column_counter, 2);
			int rhsBPixel = rhs.getChannel(row_counter, column_counter, 2);

			int max = this->getMaxColorValue();

			int newRPixel = thisRPixel - rhsRPixel;
			int newGPixel = thisGPixel - rhsGPixel;
			int newBPixel = thisBPixel - rhsBPixel;

			if(newRPixel > max) {
				newRPixel = max;
			}
			if(newRPixel < 0) {
				newRPixel = 0;
			}

			if(newGPixel > max) {
				newGPixel = max;
			}
			if(newGPixel < 0) {
				newGPixel = 0;
			}

			if(newBPixel > max) {
				newBPixel = max;
			}
			if(newBPixel < 0) {
				newBPixel = 0;
			}

			this->setPixel(row_counter, column_counter, newRPixel, newGPixel, newBPixel);
		}
	}			
	
	return *this;
}

PPM& PPM::operator*=(const PPM& rhs) {
	int image_height = getHeight();
	int image_width = getWidth();

	int row_counter, column_counter;

	for(row_counter = 0; row_counter < image_height; row_counter++) {
		for(column_counter = 0; column_counter < image_width; column_counter++) {
			int thisR = this->getChannel(row_counter, column_counter, 0);
			int thisG = this->getChannel(row_counter, column_counter, 1);
			int thisB = this->getChannel(row_counter, column_counter, 2);
		
			int max = this->getMaxColorValue();

			int thatR = rhs.getChannel(row_counter, column_counter, 0);
			int thatG = rhs.getChannel(row_counter, column_counter, 1);
			int thatB = rhs.getChannel(row_counter, column_counter, 2);
		
			int newR = thisR * thatR;
			int newG = thisG * thatG;
			int newB = thisB * thatB;
			
			if(newR > max) {
				newR = max;
			}
			if(newR < 0) {
				newR = 0;
			}
			if(newG > max) {
				newG = max;
			}
			if(newG < 0) {
				newG = 0;
			}
			if(newB > max) {
				newB = max;
			}
			if(newB < 0) {
				newB = 0;
			}
			this->setPixel(row_counter, column_counter, newR, newG, newB);
		}
	}
	return *this;
}

PPM& PPM::operator*=(const double& rhs) {
	int image_height = getHeight();
	int image_width = getWidth();
	
	int row_counter;
	int column_counter;

	for(row_counter = 0; row_counter < image_height; row_counter++) {
		for(column_counter = 0; column_counter < image_width; column_counter++) {
			int thisR = this->getChannel(row_counter, column_counter, 0);
			int thisG = this->getChannel(row_counter, column_counter, 1);
			int thisB = this->getChannel(row_counter, column_counter, 2);
	
			int max = this->getMaxColorValue();
		
			int newR = thisR * rhs;
			int newG = thisG * rhs;
			int newB = thisB * rhs;
			
			if(newR > max) {
				newR = max;
			}
			if(newR < 0) {
				newR = 0;
			} 
			if(newG > max) {
				newG = max;
			}
			if(newG < 0) {
				newG = 0;
			}
			if(newB > max) {
				newB = max;
			}
			if(newB < 0) {
				newB = 0;
			}
			
			this->setPixel(row_counter, column_counter, newR, newG, newB);
		}
	} 
	return *this;
}

PPM& PPM::operator/=(const double& rhs) {
	int image_height = getHeight();
	int image_width = getWidth();
	
	int row_counter;
	int column_counter;

	for(row_counter = 0; row_counter < image_height; row_counter++) {
		for(column_counter = 0; column_counter < image_width; column_counter++) {
			int thisR = this->getChannel(row_counter, column_counter, 0);
			int thisG = this->getChannel(row_counter, column_counter, 1);
			int thisB = this->getChannel(row_counter, column_counter, 2);
			
			int max = this->getMaxColorValue();
		
			int newR = thisR / rhs;
			int newG = thisG / rhs;
			int newB = thisB / rhs;
			
			if(newR > max) {
				newR = max;
			}
			if(newR < 0) {
				newR = 0;
			}
			if(newG > max) {
				newG = max;
			}
			if(newG < 0) {
				newG = 0;
			}
			if(newB > max) { 
				newB = max;
			}
			if(newB < 0) {
				newB = 0;
			}

			this->setPixel(row_counter, column_counter, newR, newG, newB);
		}
	}
	return *this;
}

PPM PPM::operator+(const PPM& rhs) const{
	PPM newPPM;
	int image_height = getHeight();
	int image_width = getWidth();
	int max = getMaxColorValue();

	newPPM.setHeight(image_height);
	newPPM.setWidth(image_width);
	newPPM.setMaxColorValue(max);

	int row_counter;
	int column_counter;

	for(row_counter = 0; row_counter < image_height; row_counter++) {
		for(column_counter = 0; column_counter < image_width; column_counter++) {
			int thisR = getChannel(row_counter, column_counter, 0);
			int thisG = getChannel(row_counter, column_counter, 1);
			int thisB = getChannel(row_counter, column_counter, 2);
			
			int rhsR = rhs.getChannel(row_counter, column_counter, 0);
			int rhsG = rhs.getChannel(row_counter, column_counter, 1);
			int rhsB = rhs.getChannel(row_counter, column_counter, 2);

			int newR = thisR + rhsR;
			int newG = thisG + rhsG;
			int newB = thisB + rhsB;
			
			if(newR > max) {
				newR = max;
			}
			if(newG > max) {
				newG = max;
			}
			if(newB > max) {
				newB = max;
			}
	
			newPPM.setPixel(row_counter, column_counter, newR, newG, newB);
		}
	}		
	return newPPM;
}

PPM PPM::operator-(const PPM& rhs) const {
	PPM newPPM;
	int image_height = getHeight();
	int image_width = getWidth();
	int max = getMaxColorValue();
		
	newPPM.setHeight(image_height);
	newPPM.setWidth(image_width);
	newPPM.setMaxColorValue(max);
	
	int row_counter;
	int column_counter;

	for(row_counter = 0; row_counter < image_height; row_counter++) {
		for(column_counter = 0; column_counter < image_width; column_counter++) {
			int thisR = getChannel(row_counter, column_counter, 0);
			int thisG = getChannel(row_counter, column_counter, 1);
			int thisB = getChannel(row_counter, column_counter, 2);
		
			int rhsR = rhs.getChannel(row_counter, column_counter, 0);
			int rhsG = rhs.getChannel(row_counter, column_counter, 1);
			int rhsB = rhs.getChannel(row_counter, column_counter, 2);

			int newR = thisR - rhsR;
			int newG = thisG - rhsG;
			int newB = thisB - rhsB;

			if(newR < 0) {
				newR = 0;
			}
			if(newG < 0) {
				newG = 0;
			}
			if(newB < 0) {
				newB = 0;
			}

			newPPM.setPixel(row_counter, column_counter, newR, newG, newB);
		}
	}

	return newPPM;
}

PPM PPM::operator*(const double& rhs) const {
	PPM newPPM;
	int thisHeight = getHeight();
	int thisWidth = getWidth();
	int max = getMaxColorValue();

	newPPM.setHeight(thisHeight);
	newPPM.setWidth(thisWidth);
	newPPM.setMaxColorValue(max);

	int row_counter;
	int column_counter;

	for(row_counter = 0; row_counter < thisHeight; row_counter++) {
		for(column_counter = 0; column_counter < thisWidth; column_counter++) {
			int thisR = getChannel(row_counter, column_counter, 0);
			int thisG = getChannel(row_counter, column_counter, 1);
			int thisB = getChannel(row_counter, column_counter, 2);
			
			int newR = thisR * rhs;
			int newG = thisG * rhs;
			int newB = thisB * rhs;

			if(newR > max) {
				newR = max;
			}
			if(newR < 0) {
				newR = 0;
			}
			if(newG > max) {
				newG = max;
			}
			if(newG < 0) {
				newG = 0;
			}
			if(newB > max) {
				newB = max;
			}
			if(newB < 0) {
				newB = 0;
			}

			newPPM.setPixel(row_counter, column_counter, newR, newG, newB);
		}
	}
	
	return newPPM;
}

PPM PPM::operator/(const double& rhs) const {
	PPM newPPM;
	int image_height = getHeight();
	int image_width = getWidth();
	int max = getMaxColorValue();
	
	newPPM.setHeight(image_height);
	newPPM.setWidth(image_width);
	newPPM.setMaxColorValue(max);

	int row_counter;
	int column_counter;

	for(row_counter = 0; row_counter < image_height; row_counter++) {
		for(column_counter = 0; column_counter < image_width; column_counter++) {
			int thisR = getChannel(row_counter, column_counter, 0);
			int thisG = getChannel(row_counter, column_counter, 1);
			int thisB = getChannel(row_counter, column_counter, 2);
	
			int newR = thisR / rhs;
			int newG = thisG / rhs;
			int newB = thisB / rhs;

			if(newR > max) {
				newR = max;
			}
			if(newR < 0) {
				newR = 0;
			}
			if(newG > max) {
				newG = max;
			}
			if(newG < 0) {
				newG = 0;
			}
			if(newB > max) {
				newB = max;
			}
			if(newB < 0) {
				newB = 0;
			}

			newPPM.setPixel(row_counter, column_counter, newR, newG, newB);
		}
	}
	return newPPM;
}

void PPM::grayFromChannel(PPM& dst, const int& src_channel) const {
	int image_height = getHeight();
	int image_width = getWidth();
	int max = getMaxColorValue();
	
	dst.setHeight(image_height);
	dst.setWidth(image_width);
	dst.setMaxColorValue(max);

	int row_counter;
	int column_counter;

	for(row_counter = 0; row_counter < image_height; row_counter++) {
		for(column_counter = 0; column_counter < image_width; column_counter++) {
			int channelValue = getChannel(row_counter, column_counter, src_channel);
			dst.setPixel(row_counter, column_counter, channelValue, channelValue, channelValue);
		}
	}
}

void PPM::grayFromRed(PPM& dst) const {
	grayFromChannel(dst, 0);
}

void PPM::grayFromGreen(PPM& dst) const {
	grayFromChannel(dst, 1);
}

void PPM::grayFromBlue(PPM& dst) const {
	grayFromChannel(dst, 2);
}

double PPM::linearColorimetricPixelValue(const int& row, const int& column) const {
	//function -> 0.2126*r + 0.7152*g + 0.0722*b
	int R = getChannel(row, column, 0);
	int G = getChannel(row, column, 1);
	int B = getChannel(row, column, 2);
	
	double colorimetricValue = (0.2126 * R) + (0.7152 * G) + (0.0722 * B);

	return colorimetricValue;
}

void PPM::grayFromLinearColorimetric(PPM& dst) const {
	int image_height = getHeight();
	int image_width = getWidth();
	int max = getMaxColorValue();

	int row_counter;
	int column_counter;
	
	dst.setHeight(image_height);
	dst.setWidth(image_width);
	dst.setMaxColorValue(max);
	
	for(row_counter = 0; row_counter < image_height; row_counter++) {
		for(column_counter = 0; column_counter < image_width; column_counter++) {
			double colorimetricValue = linearColorimetricPixelValue(row_counter, column_counter);
			dst.setPixel(row_counter, column_counter, colorimetricValue, colorimetricValue, colorimetricValue);
		}
	}
}

void PPM::orangeFilter(PPM& dst) const {
	int image_height = getHeight();
	int image_width = getWidth();
	int max = getMaxColorValue();

	int row_counter;
	int column_counter;

	dst.setHeight(image_height);
	dst.setWidth(image_width);
	dst.setMaxColorValue(max);

	for(row_counter = 0; row_counter < image_height; row_counter++) {
		for(column_counter = 0; column_counter < image_width; column_counter++) {
			int R = getChannel(row_counter, column_counter, 0);
			int G = getChannel(row_counter, column_counter, 1);
			int B = getChannel(row_counter, column_counter, 2);

			int newR = (2*((2*R)+G))/3;
			int newG = (2*((2*R)+G))/6;
			int newB = B/2;
			
			if(newR > max) {
				newR = max;
			}
			if(newR < 0) {
				newR = 0;
			}
			if(newG > max) {
				newG = max;
			}
			if(newG < 0) {
				newG = 0;
			}
			if(newB > max) {
				newB = max;
			}
			if(newB < 0) {
				newB = 0;
			} 

			dst.setPixel(row_counter, column_counter, newR, newG, newB);
		}
	}
}
