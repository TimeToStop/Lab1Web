#pragma once
#include "../writer/image.h"
#include <stdexcept>
#include <map>

class Painter
{
	Pointer<Image> m_error;
	std::map<char, Pointer<Image> > m_font;

	Color m_color;
	Image& m_image;

public:
	Painter(Image&);
	~Painter();

	void setColor(const Color&);

	void drawFloatString(int x, int y, std::string& value);
	void drawError(int x, int y);

	void drawHorizontalLine(int row);
	void drawHorizontalLine(int row, int start, int end);

	void drawVerticalLine(int column);
	void drawVerticalLine(int column, int start, int end);

	void drawPixel(int x, int y);
	void drawCircle(int x, int y, int radius);

private:
	void readFontImages();
	void drawImage(int x, int y, Image* index);
};

