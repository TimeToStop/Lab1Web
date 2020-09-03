#include "image.h"

#include <windows.h>
#include <fstream>

Image::Image(int w, int h):
    m_width(w),
    m_height(h),
    m_color_map(new Color*[h])
{
    if ((m_width & 0b11) != 0)
    {
        delete[] m_color_map;
        throw std::exception("Width of page must be multiple of four");
    }

    for (int i = 0; i < m_height; i++)
    {
        m_color_map[i] = new Color[w];
    }
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
    std::ofstream file(file_path, std::ios::out | std::ios::binary);

    if (file.is_open())
    {
        BITMAPFILEHEADER tWBFH;
        memset(&tWBFH, 0, sizeof(BITMAPFILEHEADER));
        tWBFH.bfType = 0x4d42;
        tWBFH.bfSize = 14 + 40 + (m_width * m_height * 3);
        tWBFH.bfReserved1 = 0;
        tWBFH.bfReserved2 = 0;
        tWBFH.bfOffBits = 14 + 40;

        BITMAPINFOHEADER tW2BH;
        memset(&tW2BH, 0, 40);
        tW2BH.biSize = 40;
        tW2BH.biWidth = m_width;
        tW2BH.biHeight = m_height;
        tW2BH.biPlanes = 1;
        tW2BH.biBitCount = 24;
        tW2BH.biCompression = 0;


        file.write((char*)&tWBFH, sizeof(BITMAPFILEHEADER));
        file.write((char*)&tW2BH, sizeof(BITMAPINFOHEADER));
        
        char color_data[3] = { 0 };

        for (int i = m_height - 1; i >= 0; i--)
        {
            for (int j = 0; j < m_width; j++)
            {
                color_data[0] = m_color_map[i][j].b();
                color_data[1] = m_color_map[i][j].g();
                color_data[2] = m_color_map[i][j].r();

                file.write(color_data, sizeof(color_data));

                if (!file.good())
                {
                    return false;
                }
            }
        }

        return true;
    }

    return false;
}
