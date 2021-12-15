#include <vector>
#include <iostream>
#include <string>
#include "image_menu.h"
#include <cmath>
#include "MandelbrotSet.h"
#include "JuliaSet.h"

void diagonalQuadPattern(ActionData& action_data) {
	int image_height = getInteger(action_data, "Image height? ");
	int image_width = getInteger(action_data, "Image width? ");

	action_data.getInputImage1().setHeight(image_height);
	action_data.getInputImage1().setWidth(image_width);
	action_data.getInputImage1().setMaxColorValue(255);

	int row_counter;
	int column_counter;
	
	int row_half = image_height / 2;
	int column_half = image_width / 2;
	for(row_counter = 0; row_counter < image_height; row_counter ++) {
		for(column_counter = 0; column_counter < image_width; column_counter ++) {
			if(row_counter < row_half) {
				action_data.getInputImage1().setChannel(row_counter, column_counter, 0, 0);
			} 
			if(row_counter >= row_half) {
				action_data.getInputImage1().setChannel(row_counter, column_counter, 0, 255);
			} 
			if(column_counter < column_half) {
				action_data.getInputImage1().setChannel(row_counter, column_counter, 2, 0);
			}
			if(column_counter >= column_half) {
				action_data.getInputImage1().setChannel(row_counter, column_counter, 2, 255);
			}

			action_data.getInputImage1().setChannel(row_counter, column_counter, 1, ((2 * row_counter + 2 * column_counter) % 256));
			
		}
	}

}

void simpleSquaresPattern(ActionData& action_data) {
	int image_size = getInteger(action_data, "Image size? ");

	action_data.getInputImage1().setHeight(image_size);
	action_data.getInputImage1().setWidth(image_size);

	int image_height = image_size;
	int image_width = image_size;

	int row_half = image_size / 2;
	int column_half = image_size / 2;
	
	int row_counter;
	int column_counter;
	for(row_counter = 0; row_counter < image_height; row_counter ++) {
		for(column_counter = 0; column_counter < image_width; column_counter ++) {
			if(row_counter < row_half) {
				action_data.getInputImage1().setChannel(row_counter, column_counter, 0, 127);
			}
			if(row_counter >= row_half) {
				action_data.getInputImage1().setChannel(row_counter, column_counter, 0, 255);
			}
			if(column_counter < column_half) {
				action_data.getInputImage1().setChannel(row_counter, column_counter, 1, 0);
			}
			if(column_counter >= column_half) {
				action_data.getInputImage1().setChannel(row_counter, column_counter, 1, 255);
			}
			action_data.getInputImage1().setChannel(row_counter, column_counter, 2, 255);
		}
	}
}
	//top half red = 127
	//bottom half red = 255
	//left half green = 0
	//right half green = 255
	//blue = 255

//UPDATE

void stripedDiagonalPattern(ActionData& action_data) {
	int image_height = getInteger(action_data, "Image height? ");
	int image_width = getInteger(action_data, "Image width? ");

	action_data.getInputImage1().setHeight(image_height);
	action_data.getInputImage1().setWidth(image_width);

	int row_counter;
	int column_counter;

	int maximum_color = (image_height + image_width) / 3;
	if(maximum_color > 255) {
		maximum_color = 255;
	}

	action_data.getInputImage1().setMaxColorValue(maximum_color);

	int row_half = image_height / 2;
	for(row_counter = 0; row_counter < image_height; row_counter ++) {
		for(column_counter = 0; column_counter < image_width; column_counter ++) {
			action_data.getInputImage1().setChannel(row_counter, column_counter, 0, 0);
			if(row_counter >= row_half && (row_counter%3) != 0) {
				action_data.getInputImage1().setChannel(row_counter, column_counter, 0, maximum_color);
			}
			action_data.getInputImage1().setChannel(row_counter, column_counter, 1, ((row_counter + image_width - column_counter - 1) % (1 + maximum_color)));
			if(column_counter < row_counter) {
				action_data.getInputImage1().setChannel(row_counter, column_counter, 2, 0);
			} else {
				action_data.getInputImage1().setChannel(row_counter, column_counter, 2, maximum_color);
			}
		}
	}
}

void setSize(ActionData& action_data) {
	int height = getInteger(action_data, "Height? ");
	int width = getInteger(action_data, "Width? ");

	action_data.getInputImage1().setWidth(width);
	action_data.getInputImage1().setHeight(height);
}

void setMaxColorValue(ActionData& action_data) {
	int maxColor = getInteger(action_data, "Max color value? ");

	action_data.getInputImage1().setMaxColorValue(maxColor);
}

void setChannel(ActionData& action_data) {
	int row = getInteger(action_data, "Row? ");
	int column = getInteger(action_data, "Column? ");
	int channel = getInteger(action_data, "Channel? ");
	int value = getInteger(action_data, "Value? ");

	action_data.getInputImage1().setChannel(row, column, channel, value);
}

void setPixel(ActionData& action_data) {
	int row = getInteger(action_data, "Row? ");
	int column = getInteger(action_data, "Column? ");
	int red = getInteger(action_data, "Red? ");
	int green = getInteger(action_data, "Green? ");
	int blue = getInteger(action_data, "Blue? ");

	action_data.getInputImage1().setPixel(row, column, red, green, blue);
}

void clearAll(ActionData& action_data) {
	for(int column_counter = 0; column_counter < action_data.getInputImage1().getWidth(); column_counter ++) {
		for(int row_counter = 0; row_counter < action_data.getInputImage1().getHeight(); row_counter ++) {
			action_data.getInputImage1().setPixel(row_counter, column_counter, 0, 0, 0);
		}
	}
}

void drawCircle(ActionData& action_data) {
	int center_row = getInteger(action_data, "Center Row? ");
	int center_column = getInteger(action_data, "Center Column? ");
	int radius = getInteger(action_data, "Radius? ");
	int red = getInteger(action_data, "Red? ");
	int green = getInteger(action_data, "Green? ");
	int blue = getInteger(action_data, "Blue? ");
	
	int image_height = action_data.getInputImage1().getHeight();
	int image_width = action_data.getInputImage1().getWidth();

	int row_counter;
	int column_counter;

	for(row_counter = 0; row_counter < image_height; row_counter++) {
		for(column_counter = 0; column_counter < image_width; column_counter++) {
			if(radius >= (std::sqrt((row_counter-center_row)*(row_counter-center_row)+(column_counter-center_column)*(column_counter-center_column)))) {
				action_data.getInputImage1().setPixel(row_counter, column_counter, red, green, blue);
			}
		}
	}
}

void drawBox(ActionData& action_data) {
	int top_row = getInteger(action_data, "Top Row? ");
	int left_column = getInteger(action_data, "Left Column? ");
	int bottom_row = getInteger(action_data, "Bottom Row? ");
	int right_column = getInteger(action_data, "Right Column? ");
	int red = getInteger(action_data, "Red? ");
	int green = getInteger(action_data, "Green? ");
	int blue = getInteger(action_data, "Blue? ");
	
	int row_counter;
	int column_counter;

	for(row_counter = top_row; row_counter <= bottom_row; row_counter++) {
		for(column_counter = left_column; column_counter <= right_column; column_counter++) {
			action_data.getInputImage1().setPixel(row_counter, column_counter, red, green, blue);
		}
	}
}

void drawSquare(ActionData& action_data) {
	int row = getInteger(action_data, "Row? ");
	int column = getInteger(action_data, "Column? ");
	int size = getInteger(action_data, "Size? ");
	int r = getInteger(action_data, "Red? ");
	int g = getInteger(action_data, "Green? ");
	int b = getInteger(action_data, "Blue? ");
	
	int row_counter;
	int column_counter;

	for(row_counter = row - (size/2); row_counter <= row + (size/2); row_counter++) {
		for(column_counter = (column - (size/2)); column_counter <= (column + (size/2)); column_counter++) {
			action_data.getInputImage1().setPixel(row_counter, column_counter, r, g, b);
		}
	}
}

void configureGrid(ActionData& action_data) {
	int height = getInteger(action_data, "Grid Height? ");
	int width = getInteger(action_data, "Grid Width? ");
	int maxValue = getInteger(action_data, "Grid Max Value? ");
	action_data.getGrid().setGridSize(height, width);
	action_data.getGrid().setMaxNumber(maxValue);
	
}

void setGrid(ActionData& action_data) {
	int row = getInteger(action_data, "Grid Row? ");
	int column = getInteger(action_data, "Grid Column? ");
	int gridValue = getInteger(action_data, "Grid Value? ");
	action_data.getGrid().setNumber(row, column, gridValue);
}

void applyGrid(ActionData& action_data) {
	//configure the output image using the number grid
	action_data.getGrid().setPPM(action_data.getOutputImage());
}

void setColorTableSize(ActionData& action_data) {
	//asks the user for size?  then applies it to the color table
	int size = getInteger(action_data, "Size? ");
	action_data.getTable().setNumberOfColors(size);
}

void setColor(ActionData& action_data) {
	//asks the user for position, r, g, b
	//uses them to set a color at the specified position in the color table
	int position = getInteger(action_data, "Position? ");
	int R = getInteger(action_data, "Red? ");
	int G = getInteger(action_data, "Green? ");
	int B = getInteger(action_data, "Blue? ");
	Color color(R, G, B);
	action_data.getTable()[position] = color;
}

void setRandomColor(ActionData& action_data) {
	//asks for position and then uses setRandomColor() to set a randome color at the position in the color table 
	//uses 255 for the maximum color value
	int position = getInteger(action_data, "Position? ");
	action_data.getTable().setRandomColor(255, position);
}

void setColorGradient(ActionData& action_data) {
	//asks the user for first position first red first green first blue
	//second position second red second green second blue
	//uses them to insertGradient() in the color table
	int firstPosition = getInteger(action_data, "First position? ");
	int firstR = getInteger(action_data, "First red? ");
	int firstG = getInteger(action_data, "First green? ");
	int firstB = getInteger(action_data, "First blue? ");
	int secondPosition = getInteger(action_data, "Second position? ");
	int secondR = getInteger(action_data, "Second red? ");
	int secondG = getInteger(action_data, "Second green? ");
	int secondB = getInteger(action_data, "Second blue? ");
	Color color1(firstR, firstG, firstB);
	Color color2(secondR, secondG, secondB);
	action_data.getTable().insertGradient(color1, color2, firstPosition, secondPosition);
}

void setHueSaturationValueGradient(ActionData& action_data) {
	//ask for info
	//create a pair of colors (set from HSV values)
	//insert the hsv gradient into action_data's color table
	int firstPosition = getInteger(action_data, "First position? ");
	double firstHue = getDouble(action_data, "First hue? ");
	double firstSaturation = getDouble(action_data, "First saturation? ");
	double firstValue = getDouble(action_data, "First value? ");
	int secondPosition = getInteger(action_data, "Second position? ");
	double secondHue = getDouble(action_data, "Second hue? ");
	double secondSaturation = getDouble(action_data, "Second saturation? ");
	double secondValue = getDouble(action_data, "Second value? ");
	Color color1;
	Color color2;
	color1.setFromHSV(firstHue, firstSaturation, firstValue);
	color2.setFromHSV(secondHue, secondSaturation, secondValue);
	action_data.getTable().insertHueSaturationValueGradient(color1, color2, firstPosition, secondPosition);
}

void setInvertedColorGradient(ActionData& action_data) {
	//will set an inverted gradient in the color table using insertInvertedGradient()
	//prompt for positions and rgb
	int firstPosition = getInteger(action_data, "First position? ");
	int R = getInteger(action_data, "First red? ");
	int G = getInteger(action_data, "First green? ");
	int B = getInteger(action_data, "First blue? ");
	int secondPosition = getInteger(action_data, "Second position? ");
	Color color1(R, G, B);
	action_data.getTable().insertInvertedGradient(color1, firstPosition, secondPosition);
}

void applyGridColorTable(ActionData& action_data) {
	//uses the new setPPM method to set the output image ppm using color table
	//this is not a replacement for applyGrid, this is in addition to that one
	ColorTable colorTable = action_data.getTable();
	action_data.getGrid().setPPM(action_data.getOutputImage(), colorTable);
}

void setFractalPlaneSize(ActionData& action_data) {
	double min_x = getDouble(action_data, "Min X? ");
	double max_x = getDouble(action_data, "Max X? ");
	double min_y = getDouble(action_data, "Min Y? ");
	double max_y = getDouble(action_data, "Max Y? ");
	//set the plane size
	//only do this if the grid is actually a ComplexFractal object
	//otherwise, gives message "Not a ComplexFractal object. Can't set plane size."
	ComplexFractal *p1 = dynamic_cast<ComplexFractal *>(&action_data.getGrid());
	
	if(p1 != 0) {
		p1->setPlaneSize(min_x, max_x, min_y, max_y);
	} else {
		action_data.getOS() << "Not a ComplexFractal object. Can't set plane size.";
	}
}

void calculateFractal(ActionData& action_data) {
	//calculates all numbers for the grid stored in action_data
	action_data.getGrid().calculateAllNumbers();
}

void calculateFractalSingleThread(ActionData& action_data) {
	action_data.getGrid().NumberGrid::calculateAllNumbers();
}

void setJuliaParameters(ActionData& action_data) {
	JuliaSet *p1 = dynamic_cast<JuliaSet *>(&action_data.getGrid());
	if(p1 != 0) {
		double pA = getDouble(action_data, "Parameter a? ");
		double pB = getDouble(action_data, "Parameter b? ");
		p1->setParameters(pA, pB);
	} else {
		action_data.getOS() << "Not a JuliaSet object. Can't set parameters." << std::endl;
	}
}
void setMandelbrotPower(ActionData& action_data) {
	MandelbrotPower *p1 = dynamic_cast<MandelbrotPower *>(&action_data.getGrid());
	if(p1 != 0) {
		double power = getDouble(action_data, "Power? ");
		p1->setPower(power);
	} else {
		action_data.getOS() << "Not a MandelbrotPower object. Can't set power." << std::endl;
	}
}

void zoomPlane(ActionData& action_data) {
	//prompt for Zoom Factor?
	//only does stuff if the grid is a ComplexFractal pointer
	//otherwise sends a message to the actionData output string 
		//Not a ComplexFractal object. Can't zoom plane.
	ComplexFractal *p1 = dynamic_cast<ComplexFractal *>(&action_data.getGrid());
	if(p1 != 0) {
		int factor = getInteger(action_data, "Zoom Factor? ");
		p1->zoomPlane(factor);
	} else {
		action_data.getOS() << "Not a ComplexFractal object. Can't zoom plane." << std::endl;
	}
}
