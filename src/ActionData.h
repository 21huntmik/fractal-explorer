#ifndef _ACTIONDATA_H_
#define _ACTIONDATA_H_

#include <iostream>
#include <vector>

#include "PPM.h"
#include "NumberGrid.h"
#include "ColorTable.h"

class ActionData {
public:
	std::istream& main_is;

	std::ostream& main_os;

	bool done;	

	ActionData(std::istream& is, std::ostream& os);

	std::istream& getIS();

	std::ostream& getOS();

	PPM& getInputImage1();

	PPM& getInputImage2();

	PPM& getOutputImage();

	bool getDone() const;

	void setDone();

	~ActionData();

	NumberGrid& getGrid();

	void setGrid(NumberGrid *grid);

	ColorTable& getTable();

private:
	ColorTable tableOfColors;
	PPM ppmImageOne;
	PPM ppmImageTwo;
	PPM ppmImage;
	NumberGrid *NumberGridPointer;
};

#endif /* _ACTIONDATA_H_ */
/* Local Variables: */
/* mode: c++ */
/* End: */
