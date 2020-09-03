#pragma once
#include "../writer/image.h"

#include <map>

class Painter
{
	std::map<char, std::vector<std::pair<int, int>>> m_font;

	Color m_color;
	Image& m_image;

public:
	Painter(Image&);
	~Painter();

	void setColor(const Color&);

	void drawFloatString(int x, int y, const std::string& value);
	void drawHorizontalLine(int row);
	void drawHorizontalLine(int row, int start, int end);
	void drawVerticalLine(int column);
	void drawVerticalLine(int column, int start, int end);
	void drawPixel(int x, int y);
	void drawCircle(int x, int y, int radius);

private:
	void initFont();
	void drawDigitOrDot(int x, int y, char c);
};

