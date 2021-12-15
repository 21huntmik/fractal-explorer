#include <vector>
#include <iostream>
#include "Image.h"

Image::Image()
	: height(0), width(0) {
}

Image::Image(const int& height_in, const int& width_in)
	: height(height_in), width(width_in) {
	//sets width and height
	//data vector should be resized to fit the width and the height
	int vector_len = width_in * height_in * 3;
	channel_vector.resize(vector_len);
}

int Image::getHeight() const {
	//returns height
	return height;
}

int Image::getWidth() const {
	//returns the width
	return width;
}

bool Image::indexValid(const int& row, const int& column, const int& channel) const {
	//checks if row, column, and channel are within legal limits
	//do i need to use getHeight and getWidth to check to make sure that the row and column are valid? Do I need to make sure the channel is 0, 1, or 2? 
	//This is my problem function :)
	if(channel_vector.size() > 0 && height > row && row >= 0 && width > column && column >= 0 && channel < 3 && channel >= 0) {
		return true;
	}
	return false;
	//return true or false
}

int Image::index(const int& row, const int& column, const int& channel) const {
	//returns the index into the data vector for the location specified by row, column, and channel
	return ((row * width * 3 + column * 3) + channel);
}

int Image::getChannel(const int& row, const int& column, const int& channel) const {
	//returns int representation of the value in the data vecotr at the location of the specified by row, column, and channel
	//uses the index method
	//returns -1 if the row, column or channel is not valid
	//uses indexValid to check
	if(indexValid(row, column, channel)) {
		int index_location = index(row, column, channel);
		int returnME = channel_vector[index_location];
		return returnME;
	} else {
		return -1;
	}
}
//hi

void Image::setHeight(const int& mheight) {
	//change the height of the image
	//the state of any new or existing pixels after this is undetermined
	//only non-negative ints are acceptable
	//if it's negative, make no changes
	//if a change is made, don't forget to resize the vector
	if(mheight >= 0) {
		height = mheight;
		int resize_int = width * height * 3;	
		channel_vector.resize(resize_int);
	}
}

void Image::setWidth(const int& mwidth) {
	//change the value of the location specified by row, column, and channel
	//only store if the ints are valid--Use indexValid
	//if any are not valid, make no changes
	//uses the index method to calculate the location
	if(mwidth >= 0) {
		width = mwidth;
		int resize_int = width * height * 3;
		channel_vector.resize(resize_int);
	}
}

void Image::setChannel(const int& row, const int& column, const int& channel, const int& value) {
	//Chang the value of the location specified by row, column, and channel
	//only store if location is valid (use indexValid)
	//use index to calculate the location
	//change the value to value... imagine that
	if(indexValid(row, column, channel)) {
		channel_vector[index(row, column, channel)] = value;
	}
}
