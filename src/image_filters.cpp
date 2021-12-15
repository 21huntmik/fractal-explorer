#include "image_menu.h"


//to use operator functions do something like this:
	// lhs + rhs;
	//the compiler and linker will know the types of both sides and apply the operator functions if applicable

void plusEquals(ActionData& action_data) {
	//Modifies input image 1 by adding input image 2 to it
	action_data.getInputImage1() += action_data.getInputImage2();
}

void minusEquals(ActionData& action_data) {
	//modifies input image 1 by subtracting input image 2 from it
	action_data.getInputImage1() -= action_data.getInputImage2();
}

void timesEquals(ActionData& action_data) {
	//modifies input image 1 by multiplying it by the double obtained by calling getDouble with a prompt of "Factor? "
	double factor = getDouble(action_data, "Factor? ");
	action_data.getInputImage1() *= factor;
}

void timesEqualsPPM(ActionData& action_data) {
	//uses *= to multiply input image 1 by input image 2
	action_data.getInputImage1() *= action_data.getInputImage2();
}

void divideEquals(ActionData& action_data) {
	//modifies input image 1 by dividing it by the double obtained by calling getDouble() with a prompt of "Factor? "
	double factor = getDouble(action_data, "Factor? ");
	action_data.getInputImage1() /= factor;
}

void plus(ActionData& action_data) {
	//sets output image to be the sum of input image 1 and 2
	//use copyImage(ActionData& action_data) -> sets output image to inputImage1
	action_data.getOutputImage() = action_data.getInputImage1() + action_data.getInputImage2();
}

void minus(ActionData& action_data) {
	//sets output image to be the difference of input image 1 and 2
	action_data.getOutputImage() = action_data.getInputImage1() - action_data.getInputImage2();
}

void times(ActionData& action_data) {
	//sets output image to input image 1 times the double obtained by calling getDouble() with a prompt of "Factor? "
	action_data.getOutputImage() = action_data.getInputImage1() * getDouble(action_data, "Factor? ");
}

void divide(ActionData& action_data) {
	//sets output image to input image 1 divided by the double obtained by calling getDouble() with a prompt of "Factor? "
	action_data.getOutputImage() = action_data.getInputImage1() / getDouble(action_data, "Factor? ");
}

void grayFromRed(ActionData& action_data) {
	PPM red;
	action_data.getInputImage1().grayFromRed(red);
	action_data.getOutputImage() = red;
}

void grayFromGreen(ActionData& action_data) {
	PPM green;
	action_data.getInputImage1().grayFromGreen(green);
	action_data.getOutputImage() = green;
}

void grayFromBlue(ActionData& action_data) {
	PPM blue;
	action_data.getInputImage1().grayFromBlue(blue);
	action_data.getOutputImage() = blue;
}

void grayFromLinearColorimetric(ActionData& action_data) {
	PPM color;
	action_data.getInputImage1().grayFromLinearColorimetric(color);
	action_data.getOutputImage() = color;
}

void orangeFilter(ActionData& action_data) {
	PPM orange;
	action_data.getInputImage1().orangeFilter(orange);
	action_data.getOutputImage() = orange;
}

void blendImages(ActionData& action_data) {
	//ask for Ratio?
	//set the output image to the result of adding input image *  ratio to input image 2 * (1.-ratio)
	PPM blended;
	double ratio = getDouble(action_data, "Ratio? ");
	blended = action_data.getInputImage1() * ratio + action_data.getInputImage2() * (1.0 - ratio);
	action_data.getOutputImage() = blended;
}
