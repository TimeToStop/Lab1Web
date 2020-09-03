#include <iostream>

#include "painter/painter.h"

int size = 240;
int half_size = (size >> 1);
int step = size / 6;

void drawGrid(Painter& painter);
void drawGraph(Painter& painter);

void drawRect(Painter& painter);
void drawSemiCircle(Painter& painter);
void drawTriangle(Painter& painter);

int main()
{
	Color white(0x66);
	Image img(size, size);
	Painter painter(img);
	img.fill(white);
	drawGraph(painter);
	drawGrid(painter);
	img.save("test.bmp");
	return 0;
}

void drawGrid(Painter& painter)
{
	painter.setColor(Color(0));

	painter.drawHorizontalLine(half_size);
	painter.drawVerticalLine(half_size);

	for (int i = step; i < size; i += step)
	{
		painter.drawHorizontalLine(i, half_size - 5, half_size + 5);
	}

	for (int i = step; i < size; i += step)
	{
		painter.drawVerticalLine(i, half_size - 5, half_size + 5);
	}
}

void drawGraph(Painter& painter)
{
	painter.setColor(Color(0, 0, 0xFF));

	drawRect(painter);
	drawSemiCircle(painter);
	drawTriangle(painter);
}

void drawRect(Painter& painter)
{
	for (int i = step; i < half_size; i += 1)
	{
		for (int j = half_size; j < (step << 2); j++)
		{
			painter.drawPixel(i, j);
		}
	}
}

void drawSemiCircle(Painter& painter)
{
	for (int i = 0; i <= step; i++)
	{
		int j_max = (int)floor(sqrt(static_cast<double>(step) * step - static_cast<double>(i) * i));

		for (int j = 0; j <= j_max; j++)
		{
			painter.drawPixel(half_size + i, half_size + j);
		}
	}
}

void drawTriangle(Painter& painter)
{
	int dest = half_size + (step << 1);
	float k = 0.5, b = step >> 1;

	for (int i = half_size; i < dest; i++)
	{
		int min_y = (int)floor(static_cast<double>(i) * k + b);

		for (int j = min_y; j <= half_size; j++)
		{
			painter.drawPixel(i, j);
		}
	}
}
