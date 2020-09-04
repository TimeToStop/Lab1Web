#pragma once

typedef unsigned char byte;

class Color
{
	byte m_r;
	byte m_g;
	byte m_b;

public:
	Color();
	Color(byte v);
	Color(byte r, byte g, byte b, byte a = 255);
	Color(const Color&);
	~Color();

	void setR(byte);
	void setG(byte);
	void setB(byte);

	byte r() const;
	byte g() const;
	byte b() const;

	Color& operator=(const Color& other);
};

