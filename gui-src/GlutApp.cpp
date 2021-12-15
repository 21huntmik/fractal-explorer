#include "GlutApp.h"
#include "glut_app.h"
#include "image_menu.h"
#include <GL/glut.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>

GlutApp::GlutApp(int height, int width)
  : mHeight(height), mWidth(width), mActionData(mInputStream, mOutputStream), mMinX(-2.0), mMaxX(2.0), mMinY(-2.0), mMaxY(2.0), mInteractionMode(IM_FRACTAL), mFractalMode(M_MANDELBROT), mMaxNumber(200), mColor1(245, 227, 66), mColor2(242, 0, 145), mColor3(182, 117, 217), mColor4(109, 232, 177), mNumColor(32), mICounter(1), IWasPushed(1), mImageNumber(1), mHSVColor(false) {
  configureMenu(mMenuData);
  mActionData.setGrid(new ComplexFractal);
  setColorTable();
  createFractal();
}

void GlutApp::setSize(int height, int width) {
  mHeight = height;
  mWidth = width;
}

int GlutApp::getHeight() const {
  return mHeight;
}
int GlutApp::getWidth() const {
  return mWidth;
}

void GlutApp::display() {
  if(mInteractionMode == IM_FRACTAL) {
    PPM& p = mActionData.getOutputImage();
    double max = static_cast<double>(p.getMaxColorValue());
    double r, g, b;
    int row, column;
    glBegin( GL_POINTS );
    for(row = 0; row < p.getHeight(); row++) {
      for(column = 0; column < p.getWidth(); column++) {
        r = p.getChannel(row, column, 0) / max;
        g = p.getChannel(row, column, 1) / max;
        b = p.getChannel(row, column, 2) / max;
        glColor3d(r, g, b);
        glVertex2i(column, p.getHeight()-row-1); 
      }
    }
    glEnd( );
  } else if(mInteractionMode == IM_COLORTABLE) {
    displayColorTable();
  } else if(mInteractionMode == IM_COLOR1) {
    displayColorTable();
  } else if(mInteractionMode == IM_COLOR2) {
    displayColorTable();
  } else if(mInteractionMode == IM_COLOR3) {
    displayColorTable();
  } else if(mInteractionMode == IM_COLOR4) {
    displayColorTable();
  } else if(mInteractionMode == IM_COLORPICKER) {
    glShadeModel(GL_SMOOTH);
    glBegin(GL_QUADS); 
    glColor3f(1.0,1.0,1.0); 
    glVertex2i(0, 0); 
    glColor3f(0.0,0.0,1.0); 
    glVertex2i(700, 0); 
    glColor3f(0.0,1.0,0.0); 
    glVertex2i(700, 500); 
    glColor3f(1.0,0.0,0.0); 
    glVertex2i(0, 500); 
    glEnd();
  }
  displayInstructions();
}

void GlutApp::setIValue() {
	if(mICounter == 0) {
		mICounter = 1;
	} else if(mICounter == 1) {
		mICounter = 0;
	}
	IWasPushed = 0;
}

void GlutApp::displayInstructions() {
  glColor3d(0, 0, 0);
  drawText(2, 490, "Instructions [push i]:");
  if(mICounter == 0 && IWasPushed == 0) {
    glColor3d(0, 0, 0);
    drawText(2, 475, "J/j -> Julia Set Fractal");
    drawText(2, 460, "M/m -> Mandelbrot Fractal");
    drawText(2, 445, "C/c -> Complex Fractal");
    drawText(2, 430, "T -> Display Color Table");
    drawText(2, 415, "t -> Display Fractal");
    drawText(2, 400, ">/. -> Increase Table Color");
    drawText(2, 385, "</, -> Decrease Table Color");
    drawText(2, 370, "b -> Mandelbrot Fractal Mode");
    drawText(2, 355, "n -> Julia Fractal Mode");
    drawText(2, 340, "F -> Complex Fractal Mode");
    drawText(2, 325, "z/Z -> Zoom In & Out");
    drawText(2, 310, "Arrow Keys -> Move Plane Boundary");
    drawText(2, 295, "R -> Reset Plane Boundary");
    drawText(2, 280, "+/= -> Increase Grid Maximum Number");
    drawText(2, 265, "- -> Decrease Grid Maximum Number");
    drawText(2, 250, "1 -> Display Color Picker");
    drawText(15, 235, "Once within the Color Picker, click to set random colors");
    drawText(2, 220, "! -> Select Random Color Scheme");
    drawText(2, 205, "q/esc -> Quit");
  } 
}

int GlutApp::getICounter() {
	return mICounter;
}

void GlutApp::selectJulia() {
	mOutputStream.clear();
	mOutputStream.str("");
	mInputStream.clear();
	mInputStream.str("");
	takeAction("julia", mMenuData, mActionData);
}

void GlutApp::selectMandelbrot() {
	mOutputStream.clear();
	mOutputStream.str("");
	mInputStream.clear();
	mInputStream.str("");
	takeAction("mandelbrot", mMenuData, mActionData);
}

void GlutApp::selectMandelbrotPower() {
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	takeAction("mandelbrot-power", mMenuData, mActionData);
}

void GlutApp::selectBurningShip() {
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	takeAction("burning-ship", mMenuData, mActionData);
}

void GlutApp::selectTricorn() {
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	takeAction("tricorn", mMenuData, mActionData);
}

void GlutApp::selectJulia4() {
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	takeAction("julia-four", mMenuData, mActionData);
}

void GlutApp::selectJulia5() {
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	takeAction("julia5", mMenuData, mActionData);
}

void GlutApp::selectComplexFractal() {
	mOutputStream.clear();
	mOutputStream.str("");
	mInputStream.clear();
	mInputStream.str("");
	takeAction("complex-fractal", mMenuData, mActionData);
}

void GlutApp::configureGrid(int max) {
	mOutputStream.clear();
	mOutputStream.str("");
	mInputStream.clear();
	mInputStream.str("");
	{
		std::stringstream tmp;
		tmp << mHeight << " " << mWidth << " " << max;
		mInputStream.str(tmp.str());
	}
	takeAction("grid", mMenuData, mActionData);
}

void GlutApp::juliaParameters(double a, double b) {
	mOutputStream.clear();
	mOutputStream.str("");
	mInputStream.clear();
	mInputStream.str("");
	{
		std::stringstream tmp;
		tmp << a << " " << b;
		mInputStream.str(tmp.str());
	}
	takeAction("julia-parameters", mMenuData, mActionData);
}

void GlutApp::mandelbrotPowerParameters(double a) {
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	{
		std::stringstream tmp;
		tmp << a;
		mInputStream.str(tmp.str());
	}
	takeAction("set-mandelbrot-power", mMenuData, mActionData);
}

void GlutApp::fractalPlaneSize(double x_min, double x_max, double y_min, double y_max) {
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	{
		std::stringstream tmp;
		tmp << x_min << " " << x_max << " " << y_min << " " << y_max;
		mInputStream.str(tmp.str());
	}
	takeAction("fractal-plane-size", mMenuData, mActionData);
}

void GlutApp::fractalCalculate() {
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	takeAction("fractal-calculate", mMenuData, mActionData);
}

void GlutApp::gridApplyColorTable() {
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	{
		std::stringstream tmp;
		tmp << 100;
		mInputStream.str(tmp.str());
	}
	takeAction("set-color-table-size", mMenuData, mActionData);
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	{
		std::stringstream tmp;
		tmp << 0 << " " << 252 << " " << 227 << " " << 3 << " " << 25 << " " << 189 << " " << 217 << " " << 180;
		mInputStream.str(tmp.str());
	}
	takeAction("set-color-gradient", mMenuData, mActionData);
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	{
		std::stringstream tmp;
		tmp << 25 << " " << 189 << " " << 217 << " " << 180 << " " << 50 << " " << 39 << " " << 156 << " " << 124;
		mInputStream.str(tmp.str());
	}
	takeAction("set-color-gradient", mMenuData, mActionData);
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	{
		std::stringstream tmp;
		tmp << 50 << " " << 39 << " " << 156 << " " << 124 << " " << 75 << " " << 204 << " " << 150 << " " << 255;
		mInputStream.str(tmp.str());
	}
	takeAction("set-color-gradient", mMenuData, mActionData);
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	{
		std::stringstream tmp;
		tmp << 75 << " " << 204 << " " << 150 << " " << 255 << " " << 99 << " " << 255 << " " << 79 << " " << 214;
		mInputStream.str(tmp.str());
	}
	takeAction("set-color-gradient", mMenuData, mActionData);
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");	
	takeAction("grid-apply-color-table", mMenuData, mActionData);
}

void GlutApp::gridApplyColorTable2() {
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	takeAction("grid-apply-color-table", mMenuData, mActionData);	
}

void GlutApp::createJulia() {
	selectJulia();
	configureGrid(200);
	juliaParameters(-0.4, 0.6);
	fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
	fractalCalculate();
	gridApplyColorTable();
}

void GlutApp::createJulia2() {
	selectJulia();
	configureGrid(200);
	juliaParameters(0.285, 0.01);
	fractalPlaneSize(-1.0, 1.0, -1.0, 1.0);
	fractalCalculate();
	gridApplyColorTable();
}

void GlutApp::createMandelbrot() {
	selectMandelbrot();
	configureGrid(200);
	fractalPlaneSize(-4, 4, -4, 4);
	fractalCalculate();
	gridApplyColorTable();
}

void GlutApp::createMandelbrot2() {
	selectMandelbrotPower();
	configureGrid(200);
	mandelbrotPowerParameters(8);
	fractalPlaneSize(-5.5, 5.5, -5.5, 5.5);
	fractalCalculate();
	gridApplyColorTable();
}

void GlutApp::createBurningShip() {
	selectBurningShip();
	configureGrid(200);
	fractalPlaneSize(-2, 2, -2, 2);
	fractalCalculate();
	gridApplyColorTable();
}

void GlutApp::createTricorn() {
	selectTricorn();
	configureGrid(200);
	fractalPlaneSize(-2, 2, -2, 2);
	fractalCalculate();
	gridApplyColorTable();
}

void GlutApp::createJulia4() {
	selectJulia4();
	configureGrid(200);
	fractalPlaneSize(-2, 2, -2, 2);
	fractalCalculate();
	gridApplyColorTable();
}

void GlutApp::createJulia5() {
	selectJulia5();
	configureGrid(400);
	fractalPlaneSize(-5, 5, -5, 5);
	fractalCalculate();
	gridApplyColorTable();
}

void GlutApp::createComplexFractal() {
	selectComplexFractal();
	configureGrid(5000);
	fractalPlaneSize(-2.0, 2.0, -2.0, 2.0);
	fractalCalculate();
	gridApplyColorTable();
}

void GlutApp::createComplexFractal2() {
	selectComplexFractal();
	configureGrid(1000);
	fractalPlaneSize(-7.0, 7.0, -7.0, 7.0);
	fractalCalculate();
	gridApplyColorTable();
}

void GlutApp::displayColorTable() {
	//for each row in the display, do the same thing
	// for each column in the display, calculate the index into the color table using:
		//i = column * color_table_size / width_of_display
	//use the i-th color from mActionData's color table 
	//prepare each color channel (RGB) for OpenGL by dividing by 255.0
	//then use glColor3d(red, green, blue); to set the color
	//finally draw the screen pixel using glVertex2i(column, row);
	PPM& p = mActionData.getOutputImage();
	glBegin( GL_POINTS );
	int row, column;
	for(row = 0; row < p.getHeight(); row++) {
		for(column = 0; column < p.getWidth(); column++) {
			int index = column * mNumColor / mWidth; //what do you use for the width?
			Color color = mActionData.getTable()[index];
			double GLRed = color.getRed() / 255.0;
			double GLGreen = color.getGreen() / 255.0;
			double GLBlue = color.getBlue() / 255.0;
			glColor3d(GLRed, GLGreen, GLBlue);
			glVertex2i(column, row);			
		}
	}
	glEnd();
}

void GlutApp::setRGB(int x, int y) {
	if(mInteractionMode == IM_COLORPICKER) {
		//mColorIterations
		glFlush();
		glFinish();
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		std::cout << x << " " << y << std::endl;
		unsigned char dataRed[4];
		unsigned char dataGreen[4];
		unsigned char dataBlue[4];
		glReadBuffer(GL_BACK);
		glReadPixels(x, y, 1, 1, GL_RED, GL_FLOAT, dataRed);
		glReadPixels(x, y, 1, 1, GL_GREEN, GL_FLOAT, dataGreen);
		glReadPixels(x, y, 1, 1, GL_BLUE, GL_FLOAT, dataBlue);
		double doubleRed = *dataRed;
		double doubleGreen = *dataGreen;
		double doubleBlue = *dataBlue;
		std::cout << doubleRed << " " << dataRed << std::endl;
		std::cout << doubleGreen << " " << dataGreen << std::endl;
		std::cout << doubleBlue << " " << dataBlue << std::endl;
		if(mColorIterations == 0) {
			mColor1.setRed(doubleRed);
			mColor1.setGreen(doubleGreen);
			mColor1.setBlue(doubleBlue);
			iterate();
		} else if(mColorIterations == 1) {
			mColor2.setRed(doubleRed);
			mColor2.setGreen(doubleGreen);
			mColor2.setBlue(doubleBlue);	
			iterate();
		} else if(mColorIterations == 2) {
			mColor3.setRed(doubleRed);
			mColor3.setGreen(doubleGreen);
			mColor3.setBlue(doubleBlue);
			iterate();
		} else if(mColorIterations == 3) {
			mColor4.setRed(doubleRed);
			mColor4.setGreen(doubleGreen);
			mColor4.setBlue(doubleBlue);
			iterate();
		}
		setColorTable();
		fractalCalculate();
	}
}

void GlutApp::iterate() {
	if(mColorIterations < 3) {
		mColorIterations += 1;
	} else if(mColorIterations == 3) {
		mColorIterations = 0;
	}
}

int GlutApp::checkColorPicker() {
	if(mInteractionMode == IM_COLORPICKER) {
		return 1;
	} else {
		return 0;
	}
}	
					
void GlutApp::setInteractionMode(InteractionMode mode) {
	mInteractionMode = mode;
}

void GlutApp::selectColorScheme() {
	if(loopColors < 4) {
		loopColors += 1;
	} else if(loopColors == 4) {
		loopColors = 0;
	}

	if(loopColors == 0) {
		//one color scheme
		mColor1.setRed(245);
		mColor1.setGreen(227);
		mColor1.setBlue(66);
		mColor2.setRed(242);
		mColor2.setGreen(0);
		mColor2.setBlue(145);
		mColor3.setRed(182);
		mColor3.setGreen(117);
		mColor3.setBlue(217);
		mColor4.setRed(109);
		mColor4.setGreen(232);
		mColor4.setBlue(177);
		setColorTable();
		fractalCalculate();
	} else if(loopColors == 1) {
		//another
		mColor1.setRed(57);
		mColor1.setGreen(17);
		mColor1.setBlue(150);
		mColor2.setRed(20);
		mColor2.setGreen(97);
		mColor2.setBlue(94);
		mColor3.setRed(99);
		mColor3.setGreen(214);
		mColor3.setBlue(210);
		mColor4.setRed(22);
		mColor4.setGreen(242);
		mColor4.setBlue(235);
		setColorTable();
		fractalCalculate();
	} else if(loopColors == 2) {
		//another
		mColor1.setRed(36);
		mColor1.setGreen(224);
		mColor1.setBlue(70);
		mColor2.setRed(94);
		mColor2.setGreen(39);
		mColor2.setBlue(47);	
		mColor3.setRed(1);
		mColor3.setGreen(59);
		mColor3.setBlue(12);
		mColor4.setRed(235);
		mColor4.setGreen(66);
		mColor4.setBlue(91);
		setColorTable();
		fractalCalculate();
	} else if(loopColors == 3) {
		//last one
		mColor1.setRed(129);
		mColor1.setGreen(149);
		mColor1.setBlue(179);
		mColor2.setRed(247);
		mColor2.setGreen(64);
		mColor2.setBlue(80);
		mColor3.setRed(172);
		mColor3.setGreen(174);
		mColor3.setBlue(176);
		mColor4.setRed(95);
		mColor4.setGreen(96);
		mColor4.setBlue(97);
		setColorTable();
		fractalCalculate();
	} else if(loopColors == 4) {
		mColor1.setRed(244);
		mColor1.setGreen(164);
		mColor1.setBlue(252);
		mColor2.setRed(138);
		mColor2.setGreen(186);
		mColor2.setBlue(132);
		mColor3.setRed(160);
		mColor3.setGreen(157);
		mColor3.setBlue(161);
		mColor4.setRed(193);
		mColor4.setGreen(98);
		mColor4.setBlue(204);
		setColorTable();
		fractalCalculate();
	}
}

void GlutApp::setColorTable() {
	//use set-color-table-size and set-color-gradient to configure the color table using mNumColor, mColor1, and mColor2
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	{
		std::stringstream tmp;
		tmp << mNumColor;
		mInputStream.str(tmp.str());
	}
	takeAction("set-color-table-size", mMenuData, mActionData);
	if(mHSVColor == false) {
		int mColor1Red = mColor1.getRed();
		int mColor1Green = mColor1.getGreen();
		int mColor1Blue = mColor1.getBlue();
		int mColor2Red = mColor2.getRed();
		int mColor2Green = mColor2.getGreen();
		int mColor2Blue = mColor2.getBlue();
		int mColor3Red = mColor3.getRed();
		int mColor3Green = mColor3.getGreen();
		int mColor3Blue = mColor3.getBlue();
		int mColor4Red = mColor4.getRed();
		int mColor4Green = mColor4.getGreen();
		int mColor4Blue = mColor4.getBlue();
		int stopOne = mNumColor / 3;
		int stopTwo = stopOne * 2;
		int stopThree = mNumColor - 1;
		takeAction("set-color-gradient", mMenuData, mActionData);
		makeGradientEasier(0, mColor1Red, mColor1Green, mColor1Blue, stopOne, mColor2Red, mColor2Green, mColor2Blue);
		makeGradientEasier(stopOne, mColor2Red, mColor2Green, mColor2Blue, stopTwo, mColor3Red, mColor3Green, mColor3Blue);
		makeGradientEasier(stopTwo, mColor3Red, mColor3Green, mColor3Blue, stopThree, mColor4Red, mColor4Green, mColor4Blue);
		std::cout << "normal" << std::endl;
	} else if(mHSVColor == true) {
		double h1, s1, v1, h2, s2, v2, h3, s3, v3, h4, s4, v4;
		mColor1.getHSV(h1, s1, v1);
		mColor2.getHSV(h2, s2, v2);
		mColor3.getHSV(h3, s3, v3);
		mColor4.getHSV(h4, s4, v4);
		mOutputStream.clear();
		mInputStream.clear();
		mOutputStream.str("");
		mInputStream.str("");
		{
			std::stringstream tmp;
			tmp << 0 << " " << h1 << " " << s1 << " " << v1 << " " << mNumColor -1 << " " << h2 << " " << s2 << " " << v2;
			mInputStream.str(tmp.str());
		}
		takeAction("set-hsv-gradient", mMenuData, mActionData);
		std::cout << "hsv" << std::endl;
	}		
}

void GlutApp::toggleHSVColor() {
	if(mHSVColor == false) {
		mHSVColor = true;
	} else if(mHSVColor == true) {
		mHSVColor = false;
	}
	setColorTable();
	gridApplyColorTable();
}

void GlutApp::randomColor1() {
	//get random numbers for RGB values and set the new values
	std::srand(std::time(0));
	int newRed = 1+ (std::rand() % 255);
	int newGreen = 1 + (std::rand() % 255);
	int newBlue = 1 + (std::rand() % 255);
	mColor1.setRed(newRed);
	mColor1.setGreen(newGreen);
	mColor1.setBlue(newBlue);
	setColorTable();
	fractalCalculate();
}

void GlutApp::swapColorPositionsRight() {
	int newRed1 = mColor2.getRed();
	int newGreen1 = mColor2.getGreen();
	int newBlue1 = mColor2.getBlue();
	int newRed2 = mColor3.getRed();
	int newGreen2 = mColor3.getGreen();
	int newBlue2 = mColor3.getBlue();
	int newRed3 = mColor4.getRed();
	int newGreen3 = mColor4.getGreen();
	int newBlue3 = mColor4.getBlue();
	int newRed4 = mColor1.getRed();
	int newGreen4 = mColor1.getGreen();
	int newBlue4 = mColor1.getBlue();
	mColor1.setRed(newRed1);
	mColor1.setGreen(newGreen1);
	mColor1.setBlue(newBlue1);
	mColor2.setRed(newRed2);
	mColor2.setGreen(newGreen2);
	mColor2.setBlue(newBlue2);
	mColor3.setRed(newRed3);
	mColor3.setGreen(newGreen3);
	mColor3.setBlue(newBlue3);
	mColor4.setRed(newRed4);
	mColor4.setGreen(newGreen4);
	mColor4.setBlue(newBlue4);
	setColorTable();
	fractalCalculate();
}

void GlutApp::swapColorPositionsLeft() {
	int newRed1 = mColor4.getRed();
	int newGreen1 = mColor4.getGreen();
	int newBlue1 = mColor4.getBlue();
	int newRed2 = mColor1.getRed();
	int newGreen2 = mColor1.getGreen();
	int newBlue2 = mColor1.getBlue();
	int newRed3 = mColor2.getRed();
	int newGreen3 = mColor2.getGreen();
	int newBlue3 = mColor2.getBlue();
	int newRed4 = mColor3.getRed();
	int newGreen4 = mColor3.getGreen();
	int newBlue4 = mColor3.getBlue();
	mColor1.setRed(newRed1);
	mColor1.setGreen(newGreen1);
	mColor1.setBlue(newBlue1);
	mColor2.setRed(newRed2);
	mColor2.setGreen(newGreen2);
	mColor2.setBlue(newBlue2);
	mColor3.setRed(newRed3);
	mColor3.setGreen(newGreen3);
	mColor3.setBlue(newBlue3);
	mColor4.setRed(newRed4);
	mColor4.setGreen(newGreen4);
	mColor4.setBlue(newBlue4);
	setColorTable();
	fractalCalculate();
}
	

void GlutApp::makeGradientEasier(int start, int r1, int g1, int b1, int end, int r2, int g2, int b2) {
	mOutputStream.clear();
	mInputStream.clear();
	mOutputStream.str("");
	mInputStream.str("");
	{
		std::stringstream tmp;
		tmp << start << " " << r1 << " " << g1 << " " << b1 << " " << end << " " << r2 << " " << g2 << " " << b2;
		mInputStream.str(tmp.str());
	}
	takeAction("set-color-gradient", mMenuData, mActionData);
}

void GlutApp::decreaseColorTableSize() {
	//if the number of colors is more than 10, decrease the number of colors by dividing it by 1.1
	//then use setColorTable() and gridApplyColorTable() to update the output image
	if(mNumColor > 10) {
		mNumColor = mNumColor / 1.1;
	}
	setColorTable();
	gridApplyColorTable2();
}

void GlutApp::increaseColorTableSize() {
	//if the number of colors is less than 1024 increase the number of colors by multiplying by 1.1
	//then use setColorTable() and gridApplyColorTable() to update the output image
	if(mNumColor < 1024) {
		mNumColor = mNumColor * 1.1;
	}
	setColorTable();
	gridApplyColorTable2();
}

void GlutApp::zoomIn() {
	//decrease the size of the view window to 0.9 the size. 
	//calculate dx as (1.0 - 0.9)*(mMaxX - mMinX) / 2.0
	//add dx to mMinX and subtract it from mMaxX
	//do similar for the y dimension
	double dx = (1.0 - 0.9) * (mMaxX - mMinX) / 2.0;
	mMinX += dx;
	mMaxX -= dx;
	double dy = (1.0 - 0.9) * (mMaxY - mMinY) / 2.0;
	mMinY += dy;
	mMaxY -= dy;
}

void GlutApp::zoomOut() {
	//increase the size of the view window to 1.1 the size
	//calculate dx as (1.0 - 0.9)*(mMaxX - mMinX) / 2.0
	//subtract dx from mMinX and add it to mMaxX
	//do similar for the y dimension
	//only do this if it will not cause any of the plane values to go past -2.0 or 2.0
	double dx = (1.0 - 0.9) * (mMaxX - mMinX) / 2.0;
	double dy = (1.0 - 0.9) * (mMaxY - mMinY) / 2.0;
	if((mMinX - dx) >= -2.0 && (mMaxX + dx) <= 2.0 && (mMinY - dy) >= -2.0 && (mMaxY + dy) <= 2.0) {
		mMinX -= dx;
		mMaxX += dx;
		mMinY -= dy;
		mMaxY += dy;
	}
}

void GlutApp::moveLeft() {
	//move the view port to the left by the fraction 0.05
	//calculate dx as (1.0 -0.9)*(mMaxX - mMinX) / 2.0
	//then subtract dx from mMinX and mMaxX
	double dx = (1.0 - 0.9) * (mMaxX - mMinX) / 2.0;
	mMinX = mMinX - dx;
	mMaxX = mMaxX - dx;
}

void GlutApp::moveRight() {
	//move the view port to the right by the fraction 0.05
	//similar to moveLeft() except add mMinX to mMaxX
	double dx = (1.0 - 0.9) * (mMaxX - mMinX) / 2.0;
	mMinX = mMinX + dx;
	mMaxX = mMaxX + dx;
}

void GlutApp::moveDown() {
	//like moveLeft() but for the y dimension
	double dy = (1.0 - 0.9) * (mMaxY - mMinY) / 2.0;
	mMinY = mMinY - dy;
	mMaxY = mMaxY - dy;
}

void GlutApp::moveUp() {
	//like moveRight but for the y dimension
	double dy = (1.0 - 0.9) * (mMaxY - mMinY) / 2.0;
	mMinY = mMinY + dy;
	mMaxY = mMaxY + dy;
}

void GlutApp::setFractalMode(FractalMode mode) {
	mFractalMode = mode;
}

void GlutApp::increaseMaxNumber() {
	//if the mMaxNumber is less than 2048, increase it by multiplying by 1.1
	if(mMaxNumber < 2048) {
		mMaxNumber = mMaxNumber * 1.1;
	}
}

void GlutApp::decreaseMaxNumber() {
	//if the mMaxNumber is greater than 11 decrease it by dividing it by 1.1
	if(mMaxNumber > 11) {
		mMaxNumber = mMaxNumber / 1.1;
	}
}

void GlutApp::setAB(int x, int y) {
	//if the mFractalMode is M_MANDELBROT and the mActionData grid is ComplexFractal
		//set mA to mMinX + x * delta_x
		//and similar for b and y
	//delta_x is obtained from the dynamically cast ComplexFractal pointer with getDeltaX()
	//I NEED THE DYNAMIC CAST FOR THIS FUNCTION, COME BACK LATER
	ComplexFractal *p1 = dynamic_cast<ComplexFractal *>(&mActionData.getGrid());
	if(mFractalMode == M_MANDELBROT && p1 != 0) {
		mA = mMinX + x * p1->getDeltaX();
		mB = mMinY + y * p1->getDeltaY();
	}
}

void GlutApp::resetPlane() {
	mMinX = -2.0;
	mMaxX = 2.0;
	mMinY = -2.0;
	mMaxY = 2.0;
}

void GlutApp::createFractal() {
	//uses mFractalMode to choose whether to selectMandelbrot(), selectJulia(), or selectComplexFractal()
	//for Julia, also call juliaParameters()
	//call configureGrid(), fractalPlaneSize(), fractalCalculate(), and gridApplyColorTable()
	//to calculate the output image
	//make sure to use the data members for parameters to these functions!!
	if(mFractalMode == M_MANDELBROT) {
		selectMandelbrot();
	} else if(mFractalMode == M_JULIA) {
		selectJulia();
		juliaParameters(mA, mB);
	} else if(mFractalMode == M_COMPLEX) {
		selectComplexFractal();
	}
	configureGrid(mMaxNumber);
	fractalPlaneSize(mMinX, mMaxX, mMinY, mMaxY);
	fractalCalculate();
	gridApplyColorTable2();
}

void GlutApp::drawText(double x, double y, const char *string) {
	void *font = GLUT_BITMAP_HELVETICA_10;
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	int len, i;
	glRasterPos2d(x, y);
	len = (int)strlen(string);
	for(i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
	glDisable(GL_BLEND);
}

void GlutApp::increaseChannel(Color& color, int channel) {
	//color is the color to change and channel is 0,1,2
	//add 10 to the current value of the channel
	//if result > 255, set to 255
	//call setColorTable(); and gridApplyColorTable();
	int colorToChange = color.getChannel(channel);
	if(colorToChange + 10 >= 255) {
		color.setChannel(channel, 255);
	} else {
		color.setChannel(channel, colorToChange + 10);
	}
	setColorTable();
	gridApplyColorTable2();
}

void GlutApp::decreaseChannel(Color& color, int channel) {
	int colorToChange = color.getChannel(channel);
	if(colorToChange - 10 <= 0) {
		color.setChannel(channel, 0);
	} else {
		color.setChannel(channel, colorToChange - 10);
	}
	setColorTable();
	gridApplyColorTable2();
}

Color& GlutApp::fetchColor() {
	if(mInteractionMode == IM_COLOR1) {
		return mColor1;
	} else if(mInteractionMode == IM_COLOR2) {
		return mColor2;
	} else if(mInteractionMode == IM_COLOR3) {
		return mColor3;
	} else {
		return mColor4;
	}
}

void GlutApp::increaseRed() {
	// calls increase channel(fetchColor(), 0);
	increaseChannel(fetchColor(), 0);
}

void GlutApp::decreaseRed() {
	decreaseChannel(fetchColor(), 0);
}

void GlutApp::increaseGreen() {
	increaseChannel(fetchColor(), 1);
}

void GlutApp::decreaseGreen() {
	decreaseChannel(fetchColor(), 1);
}

void GlutApp::increaseBlue() {
	increaseChannel(fetchColor(), 2);
}

void GlutApp::decreaseBlue() {
	decreaseChannel(fetchColor(), 2);
}

void GlutApp::writeImage() {
	//prepare the input and output streams for a call to takeAction()
	//the input stream should contain the filename (image- mImageNumber).ppm
	//use action "write"
	//increment mImageNumber
	mInputStream.clear();
	mOutputStream.clear();
	mInputStream.str("");
	mOutputStream.str("");
	{
		std::stringstream tmp;
		tmp << "image-" << mImageNumber << ".ppm";
		mInputStream.str(tmp.str());
	}
	takeAction("write", mMenuData, mActionData);
	mImageNumber += 1;
}

void GlutApp::zoomInAndMove(int x, int y) {
	//let dx = absolute value (x - (width/2)) 
	//let dy = absolute value (y -(height/2))
	//if dx > dy...
		//if x < width/2, move left
		//if x > width/2, move right
	//if dy > dx
		//if y > height/2, move up
		//if < height/2, move down

	int dx = abs( x - (mWidth/2) );
	int dy = abs( y - (mHeight/2) );
	if(dx > dy) {
		if(x < (mWidth/2)) {
			zoomIn();
			moveLeft();
		} else if(x > (mWidth/2)) {
			zoomIn();
			moveRight();
		}
	} else if(dx < dy) {
		if(y < (mHeight/2)) {
			zoomIn();
			moveDown();
		} else if(y > (mHeight/2)) {
			zoomIn();
			moveUp();
		}
	}	
}
