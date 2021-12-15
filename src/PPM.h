//DO NOT IMPLEMENT THE FUNCTIONS ON THIS FILE. THIS IS JUST THE INSTRUCTIONS FOR REFERENCE AND UNDERSTANDING :)

//this file must include the declaration of the PPM class
//the PPM class must inherit from the Image class from the previous assignment
//the PPM class must have an integer data member to store the maximum color value (255 for RGB)

//CLASS INHERITANCE
#ifndef _PPM_H_
#define _PPM_H_

#include "Image.h"
#include <iostream>

class PPM: public Image {
public:
	PPM();
	PPM(const int& height, const int& width);

	int getMaxColorValue() const;
	bool valueValid(const int& value) const;
	void setMaxColorValue(const int& max_color_value);
	void setChannel(const int& row, const int& column, const int& channel, const int& value);
	void setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue);
	void writeStream(std::ostream& os) const;
	void readStream(std::istream& is);

	bool operator==(const PPM& rhs) const;
	bool operator!=(const PPM& rhs) const;
	bool operator<(const PPM& rhs) const;
	bool operator<=(const PPM& rhs) const;
	bool operator>(const PPM& rhs) const;
	bool operator>=(const PPM& rhs) const;

	PPM& operator+=(const PPM& rhs);
	PPM& operator-=(const PPM& rhs);
	PPM& operator*=(const double& rhs);
	PPM& operator*=(const PPM& rhs);
	PPM& operator/=(const double& rhs);
	
	PPM operator+(const PPM& rhs) const;
	PPM operator-(const PPM& rhs) const;
	PPM operator*(const double& rhs) const;
	PPM operator/(const double& rhs) const;
	
	void grayFromChannel(PPM& dst, const int& src_channel) const;
	void grayFromRed(PPM& dst) const;
	void grayFromGreen(PPM& dst) const;
	void grayFromBlue(PPM& dst) const;
	double linearColorimetricPixelValue(const int& row, const int& column) const;
	void grayFromLinearColorimetric(PPM& dst) const;

	void orangeFilter(PPM& dst) const;

private:
	int maximum_color_value;
};

#endif /* _PPM_H_ */
/* Local Variables: */
/* mode:c++ */
/* End: */
