#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <vector>

class Image {
public:
	//stores height, width, channel
	Image(); //default constructor
	Image(const int& height, const int& width);
	int getHeight() const;
	int getWidth() const;
	bool indexValid(const int& row, const int& column, const int& channel) const;
	int index(const int& row, const int& column, const int& channel) const;
	int getChannel(const int& row, const int& column, const int& channel) const;
	void setHeight(const int& height);
	void setWidth(const int& width);
	void setChannel(const int& row, const int& column, const int& channel, const int& value);
	
private:
	int height;
	int width;
	std::vector<int> channel_vector;
};

#endif /* _IMAGE_H_ */
/* Local Variables */
/* mode: c++ */
/* End: */
