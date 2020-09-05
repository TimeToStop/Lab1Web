#include "painter.h"
#include "../filesystem.h"

#include <math.h>
#include <iostream>

Painter::Painter(Image& img):
	m_image(img)
{
	readFontImages();
}

Painter::~Painter()
{
}

void Painter::setColor(const Color& color)
{
	m_color = color;
}

void Painter::drawFloatString(int x, int y, std::string& value)
{
	for (std::string::iterator sym = value.begin(); sym != value.end(); ++sym)
	{
		std::map<char, Pointer<Image>>::iterator it = m_font.find(*sym);

		if (it != m_font.end())
		{
			Image* img = it->second.get();
			drawImage(x, y, it->second.get());
			x += img->width();
		}
	}
}
void Painter::drawError(int x, int y)
{
	for (int i = 0; i < m_error->width(); i++)
	{
		for (int j = 0; j < m_error->height(); j++)
		{
			Color c = m_error->getPixel(i, j);

			if (c.r() == 0 && c.g() == 0 && c.b() == 0)
			{
				m_image.setPixel(i, j, m_color);
			}
		}
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

void Painter::drawImage(int x, int y, Image* img)
{
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

void Painter::readFontImages()
{ 
	m_font.insert({ '0', new Image("font/0.bmp") });
	m_font.insert({ '1', new Image("font/1.bmp") });
	m_font.insert({ '2', new Image("font/2.bmp") });
	m_font.insert({ '3', new Image("font/3.bmp") });
	m_font.insert({ '4', new Image("font/4.bmp") });
	m_font.insert({ '5', new Image("font/5.bmp") });
	m_font.insert({ '6', new Image("font/6.bmp") });
	m_font.insert({ '7', new Image("font/7.bmp") });
	m_font.insert({ '8', new Image("font/8.bmp") });
	m_font.insert({ '9', new Image("font/9.bmp") });
	m_font.insert({ '.', new Image("font/dot.bmp") });
	m_font.insert({ '-', new Image("font/minus.bmp") });

	for (std::map<char, Pointer<Image>>::iterator it = m_font.begin(); it != m_font.end(); ++it)
	{
		if (it->second->width() == 0)
		{
			throw std::runtime_error("Cannot read font image.");
		}
	}

	m_error = new Image("font/error.bmp");

	if (m_error->width() == 0)
	{
		throw std::runtime_error("Cannot read: font/error.bmp");
	}
}
