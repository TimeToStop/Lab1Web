#include "painter.h"

Painter::Painter(Image& img):
	m_image(img)
{
	initFont();
}

Painter::~Painter()
{
}

void Painter::setColor(const Color& color)
{
	m_color = color;
}

void Painter::drawFloatString(int x, int y, const std::string& value)
{
}

void Painter::drawHorizontalLine(int row)
{
	if (row >= 0 && row < m_image.height())
	{
		for (int i = 0; i < m_image.width(); i++)
		{
			m_image.setPixel(i, row, m_color);
		}
	}
}

void Painter::drawHorizontalLine(int row, int start, int end)
{
	if (row >= 0 && row < m_image.height())
	{
		for (int i = start; i < end; i++)
		{
			m_image.setPixel(i, row, m_color);
		}
	}
}

void Painter::drawVerticalLine(int column)
{
	if (column >= 0 && column < m_image.width())
	{
		for (int i = 0; i < m_image.height(); i++)
		{
			m_image.setPixel(column, i, m_color);
		}
	}
}

void Painter::drawVerticalLine(int column, int start, int end)
{
	if (column >= 0 && column < m_image.width())
	{
		for (int i = start; i < end; i++)
		{
			m_image.setPixel(column, i, m_color);
		}
	}
}

void Painter::drawPixel(int x, int y)
{
	if (x >= 0 && x < m_image.width() && y >= 0 && y <= m_image.height())
	{
		m_image.setPixel(x, y, m_color);
	}
}

void Painter::drawCircle(int x, int y, int radius)
{
	for (int i = 0; i <= radius; i++)
	{
		int j_max = (int)floor(sqrt(static_cast<double>(radius) * radius - static_cast<double>(i) * i));

		for (int j = 0; j <= j_max; j++)
		{
			m_image.setPixel(x + i, x + j, m_color);
			m_image.setPixel(x + i, x - j, m_color);
			m_image.setPixel(x - i, x + j, m_color);
			m_image.setPixel(x - i, x - j, m_color);
		}
	}
}

void Painter::drawDigitOrDot(int x, int y, char c)
{
}

void Painter::initFont()
{ 
	m_font.insert({ '0', 
	{ 
		{0, 0},
		{1, 1}
	}});

	m_font.insert({ '1', { {}, {}} });
	m_font.insert({ '2', { {}, {}} });
	m_font.insert({ '3', { {}, {}} });
	m_font.insert({ '4', { {}, {}} });
	m_font.insert({ '5', { {}, {}} });
	m_font.insert({ '6', { {}, {}} });
	m_font.insert({ '7', { {}, {}} });
	m_font.insert({ '8', { {}, {}} });
	m_font.insert({ '9', { {}, {}} });
}