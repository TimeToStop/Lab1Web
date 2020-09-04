#include "painter.h"

#include <math.h>

Painter::Painter(Image& img):
	m_image(img)
{
	initFont();
}

Painter::~Painter()
{
	for (size_t i = 0; i < m_font.size(); i++)
	{
		delete m_font[i];
	}
}

void Painter::setColor(const Color& color)
{
	m_color = color;
}

void Painter::drawImageByStringCode(int x, int y, const std::string& value)
{
	const int w = m_font[0]->width();

	for (size_t i = 0; i < value.size(); i++)
	{
		draw(x, y, value[i]);
		x += w;
	}
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
			m_image.setPixel(x + i, y + j, m_color);
			m_image.setPixel(x + i, y - j, m_color);
			m_image.setPixel(x - i, y + j, m_color);
			m_image.setPixel(x - i, y - j, m_color);
		}
	}
}

void Painter::draw(int x, int y, char c)
{
	if ('0' <= c && c <= '9')
	{
		drawImage(x, y, c - '0');
	}
	else if (c == ',' || c == '.')
	{
		drawImage(x, y, 10);
	}
	else if (c == '-')
	{
		drawImage(x, y, 11);
	}
	else if (c == 'e')
	{
		drawImage(x, y, 12);
	}
	else
	{
		throw std::runtime_error("Bad image code");
	}
}

void Painter::drawImage(int x, int y, size_t index)
{
	Image* img = m_font[index];

	for (int i = 0; i < img->height(); i++)
	{
		for (int j = 0; j < img->width(); j++)
		{
			Color c = img->getPixel(j, i);

			if (c.r() == 0 && c.b() == 0 && c.g() ==0)
			{
				drawPixel(x + j, y + i);
			}
		}
	}
}

void Painter::initFont()
{ 
	m_font.push_back(new Image("font/0.bmp"));
	m_font.push_back(new Image("font/1.bmp"));
	m_font.push_back(new Image("font/2.bmp"));
	m_font.push_back(new Image("font/3.bmp"));
	m_font.push_back(new Image("font/4.bmp"));
	m_font.push_back(new Image("font/5.bmp"));
	m_font.push_back(new Image("font/6.bmp"));
	m_font.push_back(new Image("font/7.bmp"));
	m_font.push_back(new Image("font/8.bmp"));
	m_font.push_back(new Image("font/9.bmp"));
	m_font.push_back(new Image("font/dot.bmp"));
	m_font.push_back(new Image("font/minus.bmp"));
	m_font.push_back(new Image("font/error.bmp"));

	for (size_t i = 0; i < m_font.size(); i++)
	{
		if (m_font[i]->width() == 0)
		{
			throw std::runtime_error("Cannot read all fonts images");
		}
	}
}
