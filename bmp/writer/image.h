#pragma once
#include <string>

#include "color.h"

#include <memory>
#include <vector>

class Image
{
	int m_width;
	int m_height;

	Color** m_color_map;

public:
	Image(int w, int h);
	~Image();

	int width() const;
	int height() const;

	void fill(const Color&);

	void setPixel(int, int, const Color&);
	Color getPixel(int, int);


	bool save(const std::string&);
};

