#pragma once

typedef unsigned char byte;

class Color
{
	byte m_r;
	byte m_g;
	byte m_b;
	byte m_alpha;

public:
	Color();
	Color(byte v);
	Color(byte r, byte g, byte b, byte a = 255);
	Color(const Color&);
	Color(Color&&) noexcept;
	~Color();

	void setR(byte);
	void setG(byte);
	void setB(byte);
	void setAlpha(byte);

	byte r() const;
	byte g() const;
	byte b() const;
	byte alpha() const;

	Color& operator=(const Color& other);
};

