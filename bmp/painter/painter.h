#pragma once
#include "../writer/image.h"

#include <map>

class Painter
{
	std::vector<std::unique_ptr<Image>> m_font;

	Color m_color;
	Image& m_image;

public:
	Painter(Image&);
	~Painter();

	void setColor(const Color&);

	void drawImageByStringCode(int x, int y, const std::string& value);
	void drawHorizontalLine(int row);
	void drawHorizontalLine(int row, int start, int end);
	void drawVerticalLine(int column);
	void drawVerticalLine(int column, int start, int end);
	void drawPixel(int x, int y);
	void drawCircle(int x, int y, int radius);

private:
	void initFont();
	void draw(int x, int y, char c);
	void drawImage(int x, int y, size_t index);
};

