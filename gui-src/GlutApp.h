#ifndef _GLUTAPP_H_
#define _GLUTAPP_H_

#include "ActionData.h"
#include "MenuData.h"
#include <sstream>

enum InteractionMode { IM_FRACTAL, IM_COLORTABLE, IM_COLORPICKER, IM_COLOR1, IM_COLOR2, IM_COLOR3, IM_COLOR4 };
enum FractalMode { M_MANDELBROT, M_JULIA, M_COMPLEX };

class GlutApp {
public:
	GlutApp(int height, int width);
	void setSize(int height, int width);
	int getHeight() const;
	int getWidth() const;
	void display();
	void setIValue();
	void displayInstructions();
	int getICounter();
	void selectJulia();
	void selectMandelbrot();
	void selectMandelbrotPower();
	void selectTricorn();
	void selectJulia4();
	void selectJulia5();
	void selectComplexFractal();
	void selectBurningShip();
	void configureGrid(int max);	
	void juliaParameters(double a, double b);
	void mandelbrotPowerParameters(double a);
	void fractalPlaneSize(double min_x, double max_x, double min_y, double max_y);
	void fractalCalculate();
	void gridApplyColorTable();
	void gridApplyColorTable2();
	void createJulia();
	void createJulia2();
	void createMandelbrot();
	void createMandelbrot2();
	void createBurningShip();
	void createTricorn();
	void createJulia4();
	void createJulia5();
	void createComplexFractal();
	void createComplexFractal2();
	void displayColorTable();
	void setRGB(int x, int y);
	void iterate();
	void setInteractionMode(InteractionMode mode);
	int checkColorPicker();
	void selectColorScheme();
	void setColorTable();
	void swapColorPositionsLeft();
	void swapColorPositionsRight();
	void makeGradientEasier(int start, int r1, int g1, int b1, int end, int r2, int g2, int b2);
	void decreaseColorTableSize();
	void increaseColorTableSize();
	void zoomIn();
	void randomColor1();
	void zoomOut();
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveUp();
	void setFractalMode(FractalMode mode);
	void increaseMaxNumber();
	void decreaseMaxNumber();
	void setAB(int x, int y);
	void resetPlane();
	void createFractal();
	void drawText(double x, double y, const char *string);
	Color& fetchColor();
	void increaseChannel(Color& color, int channel);
	void decreaseChannel(Color& color, int channel);
	void increaseRed();
	void decreaseRed();
	void increaseGreen();
	void decreaseGreen();
	void increaseBlue();
	void decreaseBlue();
	void writeImage();
	void zoomInAndMove(int x, int y);
	void toggleHSVColor();

protected:
	int mHeight, mWidth;
	std::stringstream mInputStream;
	std::stringstream mOutputStream;
	ActionData mActionData;
	MenuData mMenuData;
	double mMinX, mMaxX, mMinY, mMaxY;
	double mA, mB;
	InteractionMode mInteractionMode;
	FractalMode mFractalMode;
	int mMaxNumber;
	Color mColor1;
	Color mColor2;
	Color mColor3;
	Color mColor4;
	int mNumColor;
	int loopColors;
	int mColorIterations;
	int mICounter;
	int IWasPushed;
	int mImageNumber;
	bool mHSVColor;
};

#endif /* _GLUTAPP_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
