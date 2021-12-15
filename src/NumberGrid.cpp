#include <vector>
#include "NumberGrid.h"

NumberGrid::NumberGrid()
	:gridHeight(300), gridWidth(400), gridMaxColor(255) {
	//set the grid to 0's
	int vector_len = gridHeight * gridWidth;
	int i;
	gridNumbers.resize(vector_len);
	for(i = 0; i < vector_len; i++) {
		gridNumbers[i] = 0;
	}
}

NumberGrid::NumberGrid(const int& height, const int& width) 
	:gridHeight(height), gridWidth(width), gridMaxColor(255) {
	//set the grid to 0's (fill it with 0's)
	int vector_len = gridHeight * gridWidth;
	int i;
	gridNumbers.resize(vector_len);
	for(i = 0; i < vector_len; i++) {
		gridNumbers[i] = 0;
	}
}

NumberGrid::~NumberGrid() {
	//I don't think that this is right. I don't know how to do destructors
	//this stays empty. It just needs to exist :)
}

int NumberGrid::getHeight() const {
	return gridHeight;
}

int NumberGrid::getWidth() const {
	return gridWidth;
}

int NumberGrid::getMaxNumber() const {
	return gridMaxColor;
}

void NumberGrid::setGridSize(const int& height, const int& width) {
	if(height >= 2 && width >= 2) {
		gridHeight = height;
		gridWidth = width;
		int vector_len = gridHeight * gridWidth;
		gridNumbers.resize(vector_len);
	} 
	
}

void NumberGrid::setMaxNumber(const int& number) {
	if(number >= 0) {
		gridMaxColor = number;
	}
}

const std::vector<int>& NumberGrid::getNumbers() const {
	return gridNumbers;
}

int NumberGrid::index(const int& row, const int& column) const {
	int index = row * gridWidth + column;
	return index;
}

bool NumberGrid::indexValid(const int& row, const int& column) const {
	if(row < gridHeight && column < gridWidth && row >= 0 && column >= 0) {
		return true;
	} else {
		return false;
	}
}

bool NumberGrid::numberValid(const int& number) const {
	if(number >= 0 && number <= gridMaxColor) {
		return true;
	} else {
		return false;
	}
}

int NumberGrid::getNumber(const int& row, const int& column) const {
	if(indexValid(row, column)) {
		int indexValue = index(row, column);
		return gridNumbers[indexValue];
	} else {
		return -1;
	}
}

void NumberGrid::setNumber(const int& row, const int& column, const int& number) {
	if(indexValid(row, column) && numberValid(number)) {
		int indexValue = index(row, column);
		gridNumbers[indexValue] = number;
	}
}

void NumberGrid::setPPM(PPM& ppm) const {
	ppm.setHeight(gridHeight);
	ppm.setWidth(gridWidth);
	ppm.setMaxColorValue(63);

	int row_counter, column_counter;
	
	for(row_counter = 0; row_counter < gridHeight; row_counter ++) {
		for(column_counter = 0; column_counter < gridWidth; column_counter++) {
			int value = gridNumbers[index(row_counter, column_counter)];
			if(value == 0) {
				ppm.setPixel(row_counter, column_counter, 0, 0, 0);
			} else if(value == gridMaxColor) {
				ppm.setPixel(row_counter, column_counter, 63, 31, 31);
			} else if((value % 8) == 0) {
				ppm.setPixel(row_counter, column_counter, 63, 63, 63);
			} else if((value % 8) == 1) {
				ppm.setPixel(row_counter, column_counter, 63, 31, 31);
			} else if((value % 8) == 2) {
				ppm.setPixel(row_counter, column_counter, 63, 63, 31);
			} else if((value % 8) == 3) {
				ppm.setPixel(row_counter, column_counter, 31, 63, 31);
			} else if((value % 8) == 4) {
				ppm.setPixel(row_counter, column_counter, 0, 0, 0);
			} else if((value % 8) == 5) {
				ppm.setPixel(row_counter, column_counter, 31, 63, 63);
			} else if((value % 8) == 6) {
				ppm.setPixel(row_counter, column_counter, 31, 31, 63);
			} else if((value % 8) == 7) {
				ppm.setPixel(row_counter, column_counter, 63, 31, 63);
			}
		}
	}
}

void NumberGrid::setPPM(PPM& ppm, const ColorTable& colors) {
	if(colors.getNumberOfColors() >= 2) {
		ppm.setHeight(gridHeight);
		ppm.setWidth(gridWidth);
		ppm.setMaxColorValue(colors.getMaxChannelValue());

		int row_counter, column_counter;
		int size = colors.getNumberOfColors();

		for(row_counter = 0; row_counter < gridHeight; row_counter++) {
			for(column_counter = 0; column_counter < gridWidth; column_counter++) {
				int value = getNumber(row_counter, column_counter);

				if(value == gridMaxColor) {
					ppm.setPixel(row_counter, column_counter, colors[size -1].getRed(), colors[size -1].getGreen(), colors[size -1].getBlue());
				} else {
					int index =  value % colors.getNumberOfColors();
					ppm.setPixel(row_counter, column_counter, colors[index].getRed(), colors[index].getGreen(), colors[index].getBlue());
			
				}
			}
		}
	}
}

//virtual void NumberGrid::setGridSize(const int& height, const int& width) {
//	if(height >= 2 && width >= 2) {
//		gridHeight = height;
//		gridWidth = width;
//		int vector_len = gridHeight * gridWidth;
//		gridNumbers.resize(vector_len);
//	}
//}

void NumberGrid::calculateAllNumbers() {
	//for every row, column pair... call calculateNumber to get a number
	//call setNumber to store it
	int row_counter, column_counter;	
	for(row_counter = 0; row_counter < gridHeight; row_counter++) {
		for(column_counter = 0; column_counter < gridWidth; column_counter++) {
			if(indexValid(row_counter, column_counter)) {
				int num = calculateNumber(row_counter, column_counter);
				setNumber(row_counter, column_counter, num);
			}
		}
	}
}

ManhattanNumbers::ManhattanNumbers() 
	: NumberGrid(600, 800) {
}

ManhattanNumbers::ManhattanNumbers(const int& height, const int& width)
	: NumberGrid(height, width) {
}

ManhattanNumbers::~ManhattanNumbers() {
}

int ManhattanNumbers::calculateNumber(const int& row, const int& column) const {
	int x1 = getHeight() / 2;
	int y1 = getWidth() / 2;
	int distance = std::abs(row - x1) + std::abs(column - y1);
	return distance;
}
