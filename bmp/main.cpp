#include <iostream>

#include <math.h>
#include <sstream>

#include "painter/painter.h"
#include "writer/bmp.h"


// Image Info
const int size = 240;



const int y_rad_dataX			= 119;

const int y_plus_radY			= 26;
const int y_plus_radHalfY		= 69;
const int y_minus_radHalfY		= 154;
const int y_minus_radY			= 198;



const int x_rad_dataY			= 100;

const int x_minus_radX			= 15;
const int x_minus_radHalfX		= 58;
const int x_plus_radHalfX		= 149;
const int x_plus_radX			= 192;


void make_image(float x, float y, float r);

bool		valid	(const char*);
std::string value	(float);
float		floatVal(const std::string&);
std::string toString(float);

int main(int argc, char* argv[])
{
	if (argc == 4)
	{
		std::string x(argv[1]), y(argv[2]), r(argv[3]);

		if (valid(argv[1]) && valid(argv[2]) && valid(argv[3]))
		{
			float xf = floatVal(x);
			float yf = floatVal(y);
			float rf = floatVal(r);

			if (rf < 0)
			{
				std::cout << "Bad input: negative radius" << std::endl;
				return -3;
			}
			
			try 
			{
				make_image(xf, yf, rf);
			}
			catch (const std::runtime_error& e)
			{
				std::cout << e.what() << std::endl;
				return -4;
			}
			catch (const std::out_of_range& e)
			{
				std::cout << "Critacal error: " << std::endl;
				std::cout << e.what() << std::endl;
				return -5;
			}
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
	
	painter.drawFloatString(x_minus_radX,		x_rad_dataY, m_rad);
	painter.drawFloatString(x_minus_radHalfX,	x_rad_dataY, m_half_rad);
	painter.drawFloatString(x_plus_radHalfX,	x_rad_dataY, half_rad);
	painter.drawFloatString(x_plus_radX,		x_rad_dataY, rad);


	painter.drawFloatString(y_rad_dataX, y_minus_radY,		m_rad);
	painter.drawFloatString(y_rad_dataX, y_minus_radHalfY,	m_half_rad);
	painter.drawFloatString(y_rad_dataX, y_plus_radHalfY,	half_rad);
	painter.drawFloatString(y_rad_dataX, y_plus_radY,		rad);

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
		painter.drawError(10, 10);
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
		if (*it == '.')
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
		else if (*it == ',')
		{
			std::cout << "Float separator must be '.'" << std::endl;
			return false;
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
	std::string s = toString(value);

	if (s.size())
	{
		size_t index = 0;

		if (s.find('.') != std::string::npos
			|| s.find(',') != std::string::npos)
		{
			return std::string(s.begin(), s.begin() + 3 + (int)(s[0] == '-'));
		}
		else
		{
			return s + ".0";
		}
	}
	else
	{
		return "0.0";
	}
}

float floatVal(const std::string& s)
{
	int value;
	float r;
	std::stringstream ss;
	ss << s;
	ss >> r;
	return r;
}

std::string toString(float value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}
