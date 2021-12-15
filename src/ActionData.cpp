#include "ActionData.h"
#include <iostream>
#include <vector>
#include "NumberGrid.h"
#include "ColorTable.h"

ActionData::ActionData(std::istream& is, std::ostream& os) 
	: main_is(is), main_os(os), tableOfColors(0){
	done = false;
	NumberGridPointer = 0;
	tableOfColors.setNumberOfColors(16);
	Color color1(0, 255, 0);
	Color color2(255, 0, 255);
	tableOfColors.insertGradient(color1, color2, 0, 15);
}

std::istream& ActionData::getIS() {
	return main_is;
}

std::ostream& ActionData::getOS() {
	return main_os;
}

PPM& ActionData::getInputImage1() {
	return ppmImageOne;
}

PPM& ActionData::getInputImage2() {
	return ppmImageTwo;
}

PPM& ActionData::getOutputImage() {
	return ppmImage;
}

bool ActionData::getDone() const {
	return done;
}

void ActionData::setDone() {
	done = true;
}

ActionData::~ActionData() {
	if(NumberGridPointer != 0) {
		delete NumberGridPointer;
		NumberGridPointer = 0;
	}
}

NumberGrid& ActionData::getGrid() {
	return *NumberGridPointer;
	
}

void ActionData::setGrid(NumberGrid *grid) {
	if(NumberGridPointer != 0) {
		delete NumberGridPointer;
		NumberGridPointer = 0;
	}
	NumberGridPointer = grid;
}

ColorTable& ActionData::getTable() {
	return tableOfColors;
}
