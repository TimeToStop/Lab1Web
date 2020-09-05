#include "color.h"

#include <utility>

Color::Color():
    m_r(0),
    m_g(0),
    m_b(0)
{
}

Color::Color(byte v) :
    m_r(v),
    m_g(v),
    m_b(v)
{
}

Color::Color(byte r, byte g, byte b):
    m_r(r),
    m_g(g),
    m_b(b)
{
}

Color::Color(const Color& other):
    m_r(other.m_r),
    m_g(other.m_g),
    m_b(other.m_b)
{
}

Color::~Color()
{
}

void Color::setR(byte r)
{
    m_r = r;
}

void Color::setG(byte g)
{
    m_g = g;
}

void Color::setB(byte b)
{
    m_b = b;
}

byte Color::r() const
{
    return m_r;
}

byte Color::g() const
{
    return m_g;
}

byte Color::b() const
{
    return m_b;
}

Color& Color::operator=(const Color& other)
{
    m_r = other.m_r;
    m_g = other.m_g;
    m_b = other.m_b;

    return *this;
}
