#include <vector>
#include <cstdlib>
#include <cmath>
#include "ColorTable.h"

Color::Color()
	:R(0), G(0), B(0) {
}

Color::Color(const int& red, const int& green, const int& blue)
	:R(red), G(green), B(blue) {
}

int Color::getRed() const {
	return R;
}

int Color::getGreen() const {
	return G;
}

int Color::getBlue() const {
	return B;
}

int Color::getChannel(const int& channel) const {
	if(channel == 0) {
		return getRed();
	} else if(channel == 1) {
		return getGreen();
	} else if(channel == 2) {
		return getBlue();
	} else {
		return -1;
	}
}

void Color::setRed(const int& value) {
	if(value >= 0) {
		R = value;
	}
}

void Color::setGreen(const int& value) {
	if(value >= 0) {
		G = value;
	}
}

void Color::setBlue(const int& value) {
	if(value >= 0) {
		B = value;
	}
}

void Color::setChannel(const int& channel, const int& value) {
	if(value >= 0) {
		if(channel == 0) {
			setRed(value);
		} else if(channel == 1) {
			setGreen(value);
		} else if(channel == 2) {
			setBlue(value);
		}
	}
}

void Color::invert(const int& max_color_value) {
	if(max_color_value < R || max_color_value < G || max_color_value < B) {
		return;
	} else {
		R = max_color_value - R;
		G = max_color_value - G;
		B = max_color_value - B;
	}
}

bool Color::operator==(const Color& rhs) const {
	int thisR = getRed();
	int thisG = getGreen();
	int thisB = getBlue();
	int rhsR = rhs.getRed();
	int rhsG = rhs.getGreen();
	int rhsB = rhs.getBlue();

	if(thisR == rhsR && thisG == rhsG && thisB == rhsB) {
		return true;
	} else {
		return false;
	}
}

void Color::setFromHSV(const double& hue, const double& saturation, const double& value) {
	double red, green, blue;
	HSV_to_RGB(hue, saturation, value, red, green, blue);
	setRed(red);
	setGreen(green);
	setBlue(blue);
}

void Color::getHSV(double& hue, double& saturation, double& value) const {
	double red = getRed();
	double green = getGreen();
	double blue = getBlue();
	RGB_to_HSV(red, green, blue, hue, saturation, value);
}

std::ostream& operator<<(std::ostream& os, const Color& color) {
	int R = color.getRed();
	int G = color.getGreen();
	int B = color.getBlue();
	os << R << ":" << G << ":" << B;
	return os;
}

ColorTable::ColorTable(const int& num_color) {
	setNumberOfColors(num_color);

}

int ColorTable::getNumberOfColors() const {
	return Colors.size();
}

void ColorTable::setNumberOfColors(const int& num_color) {
	Colors.resize(num_color);
}

const Color& ColorTable::operator[](const int& i) const {
	
	int size = Colors.size();	

	if(i >= 0 && i < size) {
		return Colors[i];
	} else {
		static Color ec(-1, -1, -1);
		static Color c(-1, -1, -1);
		c = ec;
		return c;
	}
}

Color& ColorTable::operator[](const int& i) {
	
	int size = Colors.size();

	if(i >= 0 && i < size) {
		return Colors[i];
	} else {
		static Color ec(-1, -1, -1);
		static Color c(-1, -1, -1);
		c = ec;
		return c;
	}
} 

void ColorTable::setRandomColor(const int& max_color_value, const int& position) {
	int r, g, b;
	int size = getNumberOfColors();
	if(position < 0 || position >= size || max_color_value < 0) {
		return;
	} else {
		r = std::rand() % (max_color_value + 1);
		g = std::rand() % (max_color_value + 1);
		b = std::rand() % (max_color_value + 1);
	}
	Colors[position].setRed(r);
	Colors[position].setGreen(g);
	Colors[position].setBlue(b);
}	

double ColorTable::gradientSlope(const double y1, const double y2, const double x1, const double x2) const {
	double slope = ((double)y2 - y1) / ((double)x2 - x1);
	return slope;
}

double ColorTable::gradientValue(const double y1, const double x1, const double slope, const double x) const {
	double yValue = (slope * (x - x1)) + y1;
	return yValue;
}

void ColorTable::insertHueSaturationValueGradient(const Color& color1, const Color& color2, const int& position1, const int& position2) {
	if(position2 > position1 && position2 >= 0 && position2 < getNumberOfColors() && position1 >= 0 && position1 < getNumberOfColors()) {
		double hue1, saturation1, value1, hue2, saturation2, value2;
		color1.getHSV(hue1, saturation1, value1);
		color2.getHSV(hue2, saturation2, value2);
		int i;
		for(i = position1; i < position2; i++) {
			double hueSlope = gradientSlope(hue1, hue2, position1, position2);
			double hueValue = gradientValue(hue1, position1, hueSlope, i); 
			double saturationSlope = gradientSlope(saturation1, saturation2, position1, position2);	
			double saturationValue = gradientValue(saturation1, position1, saturationSlope, i);
			double valueSlope = gradientSlope(value1, value2, position1, position2);
			double valueValue = gradientValue(value1, position1, valueSlope, i);
			Colors[i].setFromHSV(hueValue, saturationValue, valueValue);
		}
	Colors[position1] = color1;
	Colors[position2] = color2;
	}
			
}

void ColorTable::insertGradient(const Color& color1, const Color& color2, const int& position1, const int& position2){ 
	if(position2 > position1 && position2 >= 0 && position2 < getNumberOfColors() && position1 >= 0 && position1 < getNumberOfColors()) {
		int i;
		for(i = position1; i < position2; i++) {
			double redSlope = gradientSlope(color1.getRed(), color2.getRed(), position1, position2);
			int redValue = gradientValue(color1.getRed(), position1, redSlope, i);
			double greenSlope = gradientSlope(color1.getGreen(), color2.getGreen(), position1, position2);
			int greenValue = gradientValue(color1.getGreen(), position1, greenSlope, i);
			double blueSlope = gradientSlope(color1.getBlue(), color2.getBlue(), position1, position2);
			int blueValue = gradientValue(color1.getBlue(), position1, blueSlope, i);
			Colors[i].setRed(redValue);
			Colors[i].setGreen(greenValue);
			Colors[i].setBlue(blueValue);
		}
	Colors[position1] = color1;
	Colors[position2] = color2;
	}	
}

void ColorTable::insertInvertedGradient(const Color& color1, const int& position1, const int& position2) {
	//creates the second color by inverting a copy of color1 with a max_color_value of 255
	//calls insertGradient() to do the rest of the work
	Color color2 = color1;
	color2.invert(255);
	insertGradient(color1, color2, position1, position2);
}

int ColorTable::getMaxChannelValue() const {
	int i;
	int maxChannelValue = 0;
	int maxSize = getNumberOfColors();
	for(i = 0; i < maxSize; i ++) {
		if(Colors[i].getRed() > maxChannelValue) {
			maxChannelValue = Colors[i].getRed();
		} if(Colors[i].getGreen() > maxChannelValue) {
			maxChannelValue = Colors[i].getGreen();
		} if(Colors[i].getBlue() > maxChannelValue) {
			maxChannelValue = Colors[i].getBlue();
		}
	}
	return maxChannelValue;		
}

void HSV_to_RGB(const double& hue, const double& saturation, const double& value, double& red, double &green, double& blue) {
  /* Convert Hue, Saturation, Value to Red, Green, Blue
   * Implementation of algorithm from:
   * https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
   *
   * Inputs and ranges:
   * 0.0 <= hue <= 360.0
   * 0.0 <= saturation <= 1.0
   * 0.0 <= value <= 1.0
   *
   * Outputs and ranges:
   * 0.0 <= red <= 255.0
   * 0.0 <= green <= 255.0
   * 0.0 <= blue <= 255.0
   */
  if(hue < 0.0 || hue > 360.0 || saturation < 0.0 || saturation > 1.0 || value < 0.0 || value > 1.0) {
    red = green = blue = 0.0;
    std::cerr << "HSV_to_RGB() input parameters out of range." << std::endl
              << " hue: " << hue  << std::endl
              << " saturation: " << saturation << std::endl
              << " value: " << value << std::endl;
    return;
  }

  // chroma selects the strength of the "primary" color of the current area of the wheel
  double chroma = value * saturation;
  // hue2 selects which 60-degree wedge of the color wheel we are in
  double hue2 = hue / 60.0;
  // x selects the strength of the "secondary" color of the current area of the wheel
  double x = chroma * ( 1 - std::abs( std::fmod( hue2, 2 ) - 1 ) );
  if( hue2 >= 0 && hue2 < 1 ) {
    red = chroma;
    green = x;
    blue = 0.0;
  } else if( hue2 >= 1 && hue2 < 2 ) {
    red = x;
    green = chroma;
    blue = 0.0;
  } else if( hue2 >= 2 && hue2 < 3 ) {
    red = 0.0;
    green = chroma;
    blue = x;
  } else if( hue2 >= 3 && hue2 < 4 ) {
    red = 0.0;
    green = x;
    blue = chroma;
  } else if( hue2 >= 4 && hue2 < 5 ) {
    red = x;
    green = 0.0;
    blue = chroma;
  } else if( hue2 >= 5 && hue2 <= 6 ) {
    red = chroma;
    green = 0.0;
    blue = x;
  } else {
    red = 0;
    green = 0;
    blue = 0;
  }

  // m scales all color channels to obtain the overall brightness.
  double m = value - chroma;
  red = 255.0*( red + m );
  green = 255.0*( green + m );
  blue = 255.0*( blue + m );
}

void RGB_to_HSV(const double& red0, const double &green0, const double& blue0, double& hue, double& saturation, double& value) {
  /* Red, Green, Blue to Convert Hue, Saturation, Value
   * Implementation of algorithm from:
   * https://en.wikipedia.org/wiki/HSL_and_HSV#From_RGB
   *
   * Inputs and ranges:
   * 0.0 <= red <= 255.0
   * 0.0 <= green <= 255.0
   * 0.0 <= blue <= 255.0
   *
   * Outputs and ranges:
   * 0.0 <= hue <= 360.0
   * 0.0 <= saturation <= 1.0
   * 0.0 <= value <= 1.0
   */
  if(red0 < 0.0 || red0 > 255.0 || green0 < 0.0 || green0 > 255.0 || blue0 < 0.0 || blue0 > 255.0) {
    hue = saturation = value = 0.0;
    std::cerr << "RGB_to_HSV() input parameters out of range." << std::endl
              << " red: " << red0  << std::endl
              << " green: " << green0 << std::endl
              << " blue: " << blue0 << std::endl;
    return;
  }

  double red   = red0 / 255.0;
  double green = green0 / 255.0;
  double blue  = blue0 / 255.0;

  // x_max helps identify the primary hue
  double x_max = red;
  if(green > x_max) { x_max = green; }
  if(blue > x_max) { x_max = blue; }
  value = x_max;

  double x_min = red;
  if(green < x_min) { x_min = green; }
  if(blue < x_min) { x_min = blue; }

  double chroma = x_max - x_min;

  if(chroma == 0) {
    hue = 0;
  } else if(value == red) {
    hue = 60.0 * (0 + (green - blue)/chroma);
  } else if(value == green) {
    hue = 60.0 * (2 + (blue - red)/chroma);
  } else if(value == blue) {
    hue = 60.0 * (4 + (red - green)/chroma);
  } else {
    hue = -720.0;
  }
  if(hue < 0.0) {
    hue += 360.0;
  }

  if(value == 0.0) {
    saturation = 0.0;
  } else {
    saturation = chroma/value;
  }

}

//??
