#include "image.h"

#include "bmp.h"
#include <stdio.h>
#include <cstring>

#include <iostream>

Image::Image(int w, int h) :
    m_width(w),
    m_height(h),
    m_color_map(new Color* [h])
{
    if ((m_width & 4) != 0)
    {
        delete[] m_color_map;
        exit(-1);
    }

    int i = 0;

    try
    {
        for (; i < m_height; i++)
        {
            m_color_map[i] = new Color[w];
        }
    }
    catch (const std::bad_alloc& e)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            delete m_color_map[j];
        }

        delete[] m_color_map;

        exit(-1);
    }
}

Image::Image(const std::string& file_name):
    m_width(0),
    m_height(0),
    m_color_map(0)
{
    init(file_name); 
}

Image::~Image()
{
    for (int i = 0; i < m_height; i++)
    {
        delete[] m_color_map[i];
    }

    delete[] m_color_map;
}

int Image::width() const
{
    return m_width;
}

int Image::height() const
{
    return m_height;
}

void Image::fill(const Color& color)
{
    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height; j++)
        {
            m_color_map[j][i] = color;
        }
    }
}

void Image::setPixel(int i, int j, const Color& color)
{
    if (i >= 0 && i < m_width && j >= 0 && j < m_height)
    {
        m_color_map[j][i] = color;
    }
}

Color Image::getPixel(int i, int j)
{
    if (i >= 0 && i < m_width && j >= 0 && j < m_height)
    {
        return m_color_map[j][i];
    }

    return Color();
}

bool Image::save(const std::string& file_path)
{
    FILE* f = fopen(file_path.c_str(), "wb");

    if (f != 0)
    {
	BMP bmp;
	memset(&bmp, 0, sizeof(BMP));

	bmp.header = 0x4d42;
	bmp.size = sizeof(BMP) + (m_width * m_height * 3);
	bmp.offset = sizeof(BMP);
	bmp.sizeOfBitMap = 40;
	bmp.width = m_width;
	bmp.height = m_height;
	bmp.planes = 1;
	bmp.bpp = 24;

        fwrite(&bmp, sizeof(BMP), 1, f);

        std::cout << "Start write image data (w, h):" << width() << " " << height() << std::endl;
        
        char color_data[3] = { 0 };

        for (int i = m_height - 1; i >= 0; i--)
        {
            for (int j = 0; j < m_width; j++)
            {
                color_data[0] = m_color_map[i][j].b();
                color_data[1] = m_color_map[i][j].g();
                color_data[2] = m_color_map[i][j].r();

                fwrite(color_data, 3 *sizeof(char), 1, f);
            }
        }

        return true;
    }

    return false;
}

void Image::init(const std::string& str)
{
    FILE* f = fopen(str.c_str(), "rb");

    if (f != 0)
    {
	    BMP bmp = {0};

        fread(&bmp, sizeof(BMP), 1, f);

        int w = bmp.width, h = bmp.height, c = bmp.bpp >> 3;
        
        if (c == 3)
        {
            int size = w * h * c;
            byte* data = new byte[size];
            fread(data, sizeof(byte), size, f);
            
            m_width = w;
            m_height = h;
            m_color_map = new Color*[h];

            for (int i = 0; i < h; i++)
            {
                m_color_map[i] = new Color[w];

                for (int j = 0; j < w; j++)
                {
                    int index = c * ((h - i - 1) * w + j);
                    m_color_map[i][j] = Color(data[index + 2], data[index + 1], data[index]);
                }
            }

            delete[] data;
        }
    }
}
