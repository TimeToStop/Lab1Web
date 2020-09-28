#include "image.h"

#include "bmp.h"
#include "../filesystem.h"

#include <stdio.h>
#include <cstring>
#include <iostream>
#include <stdexcept>

Image::Image(int w, int h) :
    m_width(w),
    m_height(h),
    m_color_map(m_height)
{
    if ((m_width & 3) != 0)
    {
        throw std::runtime_error("Width of image must be multiply of 4");
    }
    else
    {
        try
        {
            for (ColorMap::iterator it = m_color_map.begin();
                it != m_color_map.end(); ++it)
            {
                *it = Row(m_width);

                for (Row::iterator _it = it->begin(); _it != it->end(); ++_it)
                {
                    *_it = Pointer<Color>(new Color(0));
                }
            }
        }
        catch (const std::bad_alloc& e)
        {
            throw std::runtime_error("Image too big: out of memory");
        }
    }
}

Image::Image(const std::string& file_name):
    m_width(0),
    m_height(0),
    m_color_map()
{
    loadFromFile(FileSystem::fullPath(file_name));
}

Image::~Image()
{
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
            m_color_map[j][i] = new Color(color);
        }
    }
}

void Image::setPixel(int i, int j, const Color& color)
{
    if (i >= 0 && i < m_width && j >= 0 && j < m_height)
    {
        m_color_map[j][i] = new Color(color);
    }
}

Color Image::getPixel(int i, int j)
{
    if (i >= 0 && i < m_width && j >= 0 && j < m_height)
    {
        return *m_color_map[j][i];
    }
    else
    {
        throw std::out_of_range("Required pixel does not exists");
    }
}

bool Image::save(const std::string& file_path)
{
    FILE* out_file = fopen(FileSystem::fullPath(file_path).c_str(), "wb");

    if (out_file != NULL)
    {
        BMP bmp;
        memset(&bmp, 0, sizeof(BMP));

        bmp.header          = 0x4d42;
        bmp.sizeOfFile      = sizeof(BMP) + (m_width * m_height * 3);
        bmp.offset          = sizeof(BMP);
        bmp.sizeOfBitMap    = 40;
        bmp.width           = m_width;
        bmp.height          = m_height;
        bmp.planes          = 1;
        bmp.bpp             = 24;

        writeToFile(&bmp, sizeof(BMP), 1, out_file);

        char color_data[3] = { 0 };

        for (int i = m_height - 1; i >= 0; i--)
        {
            for (int j = 0; j < m_width; j++)
            {
                color_data[0] = m_color_map[i][j]->b();
                color_data[1] = m_color_map[i][j]->g();
                color_data[2] = m_color_map[i][j]->r();

                writeToFile(color_data, sizeof(color_data), 1, out_file);
            }
        }
        
        fclose(out_file);
        return true;
    }
    else
    {
        throw std::runtime_error("Cannot open file: " + file_path);
    }

    return false;
}

void Image::loadFromFile(const std::string& file_path)
{
    FILE* in_file = fopen(file_path.c_str(), "rb");

    if (in_file != 0)
    {
	    BMP bmp = { 0 };
        readFromFile(&bmp, sizeof(BMP), 1, in_file);

        int w = bmp.width, h = bmp.height, bytespp = bmp.bpp >> 3;
        
        if (bytespp == 3)
        {
            int size = w * h * bytespp;
            std::vector<byte> data(size);
            readFromFile(&data[0], sizeof(byte), size, in_file);
            
            m_width = w;
            m_height = h;
            
            m_color_map = ColorMap(m_height);

            for (int i = 0; i < h; i++)
            {
                m_color_map[i] = Row(m_width);

                for (int j = 0; j < w; j++)
                {
                    int index = bytespp * ((h - i - 1) * w + j);
                    m_color_map[i][j] = Pointer<Color>(new Color(data[index + 2], 
                                                                 data[index + 1], 
                                                                 data[index    ]));
                }
            }
        }
        else
        {
            throw std::runtime_error("Bad number of bits per pixel: should be 24 in file " + file_path);
        }
    }
    else
    {
        throw std::runtime_error("Cannot open file: " + file_path);
    }
}

void Image::writeToFile(void* data, size_t size_of_element, size_t count, FILE* stream)
{
    size_t result = fwrite(data, size_of_element, count, stream);

    if (result != count)
    {
        throw std::runtime_error("File writing error: ");
    }
}

void Image::readFromFile(void* data, size_t size_of_element, size_t count, FILE* stream)
{
    size_t result = fread(data, size_of_element, count, stream);

    if (result != count)
    {
        throw std::runtime_error("File writing error: ");
    }
}

