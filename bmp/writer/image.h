#pragma once
#include "color.h"
#include "../pointer.h"

#include <string>
#include <vector>

class Image
{
	typedef std::vector<Pointer<Color> > Row;
	typedef std::vector<Row> ColorMap;


	int m_width;
	int m_height;

	ColorMap m_color_map;

public:
	Image(int w, int h);
	Image(const std::string&);
	~Image();

	int width() const;
	int height() const;
	
	void setPixel(int, int, const Color&);
	Color getPixel(int, int);

	void fill(const Color&);
	bool save(const std::string&);

private:
	void loadFromFile(const std::string&);
	void writeToFile(void*, size_t, size_t, FILE*);
	void readFromFile(void*, size_t, size_t, FILE*);
};

