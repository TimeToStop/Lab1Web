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

void Painter::drawImageByStringCode(int x, int y, const std::string& value)
{
	const int w = m_font[0]->width();

	for (char c : value)
	{
		draw(x, y, c);
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
		throw std::exception("Bad image code");
	}
}

void Painter::drawImage(int x, int y, size_t index)
{
	const std::unique_ptr<Image>& img = m_font[index];

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
	m_font.push_back(std::make_unique<Image>("font/0.bmp"));
	m_font.push_back(std::make_unique<Image>("font/1.bmp"));
	m_font.push_back(std::make_unique<Image>("font/2.bmp"));
	m_font.push_back(std::make_unique<Image>("font/3.bmp"));
	m_font.push_back(std::make_unique<Image>("font/4.bmp"));
	m_font.push_back(std::make_unique<Image>("font/5.bmp"));
	m_font.push_back(std::make_unique<Image>("font/6.bmp"));
	m_font.push_back(std::make_unique<Image>("font/7.bmp"));
	m_font.push_back(std::make_unique<Image>("font/8.bmp"));
	m_font.push_back(std::make_unique<Image>("font/9.bmp"));
	m_font.push_back(std::make_unique<Image>("font/dot.bmp"));
	m_font.push_back(std::make_unique<Image>("font/minus.bmp"));
	m_font.push_back(std::make_unique<Image>("font/error.bmp"));

	for (const auto& e : m_font)
	{
		if (e->width() == 0)
		{
			throw std::exception("Cannot read all fonts images");
		}
	}
}