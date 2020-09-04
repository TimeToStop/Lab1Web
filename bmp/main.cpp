#include <iostream>

#include "painter/painter.h"

// Image Info
const int size = 240;

int y_rad_dataX = 119;

int y_plus_radY = 26;
int y_plus_radHalfY = 69;
int y_minus_radHalfY = 154;
int y_minus_radY = 198;

int x_rad_dataY = 100;

int x_minus_radX = 15;
int x_minus_radHalfX = 58;
int x_plus_radHalfX = 149;
int x_plus_radX = 192;


void make_image(float x, float y, float r);

bool valid(const char*);
std::string value(float);

int main(int argc, char* argv[])
{
	if (argc == 4)
	{
		std::string x(argv[1]), y(argv[2]), r(argv[3]);

		if (valid(argv[1]) && valid(argv[2]) && valid(argv[3]))
		{
			float xf = std::stof(x);
			float yf = std::stof(y);
			float rf = std::stof(r);

			if (rf < 0)
			{
				std::cout << "Bad input: negative radius" << std::endl;
				return -3;
			}

			make_image(xf, yf, rf);
		}
		else
		{
			std::cout << "Bad input: not a float number" << std::endl;
			return -2;
		}
	}
	else
	{
		std::cout << "Bad input, expected: x y r" << std::endl;
		return -1;
	}

	return 0;
}

void make_image(float x, float y, float r)
{
	// Init image
	Image img("coord.bmp");
	Painter painter(img);

	// Draw Radius

	std::string rad = value(r);
	std::string half_rad = value(r/2);

	std::string m_rad = value(-r);
	std::string m_half_rad = value(-r / 2);
	

	painter.drawImageByStringCode(x_minus_radX,		x_rad_dataY, m_rad);
	painter.drawImageByStringCode(x_minus_radHalfX,	x_rad_dataY, m_half_rad);
	painter.drawImageByStringCode(x_plus_radHalfX,	x_rad_dataY, half_rad);
	painter.drawImageByStringCode(x_plus_radX,		x_rad_dataY, rad);


	painter.drawImageByStringCode(y_rad_dataX, y_minus_radY, m_rad);
	painter.drawImageByStringCode(y_rad_dataX, y_minus_radHalfY, m_half_rad);
	painter.drawImageByStringCode(y_rad_dataX, y_plus_radHalfY, half_rad);
	painter.drawImageByStringCode(y_rad_dataX, y_plus_radY, rad);


	// Draw circle
	const float mult = 85.f/r;

	int px_x = 116 + (int)ceil(x * mult);
	int px_y = 116 - (int)ceil(y * mult);

	painter.setColor(Color(0xFF, 0, 0));

	if (px_x >= 0 && px_x < size && px_y >= 0 && px_y < size)
	{
		painter.drawCircle(px_x, px_y, 2);
	}
	else
	{
		painter.drawImageByStringCode(10, 10, "e");
	}
	 
	img.save("res.bmp");
}

bool valid(const char* str)
{
	bool has_dot = false;

	if (*str == '-')
	{
		str++;
	}

	for (const char* it = str; *it != 0; it++)
	{
		if (*it == ',' || *it == '.')
		{
			if (has_dot)
			{
				return false;
			}
			else
			{
				has_dot = true;
			}
		}
		else if (!('0' <= *it && *it <= '9'))
		{
			return false;
		}
	}

	return true;
}

std::string value(float value)
{
	int count_minus = 0;
	std::string s = std::to_string(value);

	if (s.size() >= 3)
	{
		return std::string(s.begin(), s.begin() + 3 + (int)(s[0] == '-'));
	}
	else if (s.size() == 2)
	{
		return std::string(s.begin(), s.begin() + 1);
	}
	else
	{
		return std::string("0.0");
	}
}

