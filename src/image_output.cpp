#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ios>
#include "Image.h"
#include "image_menu.h"
#include "PPM.h"
#include "ActionData.h"
#include "MenuData.h"

void drawAsciiImage(ActionData& action_data) {
	//Ok, so I need a way to look at the pixel... groups of 3 within the vector
	//	Go back to the loop code... is there a way to go every 3?
	//	Once you can look at 3 at a time, add them up and divide by 765
	//	That will give you the strength
	//	make sure it is in a double
	//	once you figure out a strength... assign a character to the pixel (3)
	//	Display each row as a line of text
	//	display all rows
	//
	//Lots of loops and if statements?? I have no idea... I am brain dead :)
	


	//trying this again with a less dead brain :)
 	//jk it's still dead. I'll come back later
	
	//I am back
	
	int height = action_data.getOutputImage().getHeight();
	int width = action_data.getOutputImage().getWidth();

	std::vector<std::string> image_output;

	int height_counter;
	for(height_counter = 0; height_counter < height; height_counter ++) {
		int column_counter;
		for(column_counter = 0; column_counter < width; column_counter ++) {
			int R = action_data.getOutputImage().getChannel(height_counter, column_counter, 0);
			int G = action_data.getOutputImage().getChannel(height_counter, column_counter, 1);
			int B = action_data.getOutputImage().getChannel(height_counter, column_counter, 2);
			double RGB = (R + G + B) / 765.0;
			if(RGB >= 1.0) {
				image_output.push_back("@");
			} else if(RGB >= 0.9) {
				image_output.push_back("#");
			} else if(RGB >= 0.8) {
				image_output.push_back("%");
			} else if(RGB >= 0.7) {
				image_output.push_back("*");
			} else if(RGB >= 0.6) {
				image_output.push_back("|");
			} else if(RGB >= 0.5) {
				image_output.push_back("+");
			} else if(RGB >= 0.4) {
				image_output.push_back(";");
			} else if(RGB >= 0.3) {
				image_output.push_back("~");
			} else if(RGB >= 0.2) {
				image_output.push_back("-");
			} else if(RGB >= 0.1) {
				image_output.push_back(".");
			} else {
				image_output.push_back(" ");
			}
		}
	}

	//display each row as lines. display all lines.
	//for each row (height) print all columns (width)
	int i;
	int j;
	for(i = 0; i < height; i ++) { //this goes through each row
		for(j = 0; j < width; j++) { //for each row, this goes through each column
			int pinpoint = (i * width) + j;
			std::string output = image_output[pinpoint];
			action_data.getOS() << output;
		}
		action_data.getOS() << "\n";
	}
}

//UPDATE

void writeUserImage(ActionData& action_data) {
	//uses getString to ask the user for "Output filename? ". opens the output file in binary mode, writes the PPM object to the file's stream (use writeStream) and then close the file stream.
	//open in binary mode
	//write the PPM object to file stream (using writeStream)
	//close file stream
	

	//use the following example:
	std::string filename;
	filename = getString(action_data, "Output filename? ");
	std::ofstream data_file(filename, std::ios::binary);
	action_data.getOutputImage().writeStream(data_file);
	data_file.close();
}

void copyImage(ActionData& action_data) {
	action_data.getOutputImage() = action_data.getInputImage1();
}

void readUserImage1(ActionData& action_data) {
	std::string name = getString(action_data, "Input filename? ");
	std::ifstream file;
	//if it doesn't open right, output "'<name>' could not be opened."
	file.open(name, std::ifstream::in);
	if(file.fail()) {
		action_data.getOS() << "'" << name << "' could not be opened.";
		file.close();
		return;
	}
	action_data.getInputImage1().readStream(file);
	file.close();
}

void readUserImage2(ActionData& action_data) {
	std::string name = getString(action_data, "Input filename? ");
	std::ifstream file;
	file.open(name, std::ifstream::in);
	if(file.fail()) {
		action_data.getOS() << "'" << name << "' could not be opened.";
		file.close();
		return;
	}
	action_data.getInputImage2().readStream(file);
	file.close();
}

void copyImage1ToImage2(ActionData& action_data) {
	action_data.getInputImage2() = action_data.getInputImage1();
}

void copyImage2ToImage1(ActionData& action_data) {
	action_data.getInputImage1() = action_data.getInputImage2();
}
