#include "color.h"

#include <utility>

Color::Color():
    m_r(0),
    m_g(0),
    m_b(0),
    m_alpha(255)
{
}

Color::Color(byte v) :
    m_r(v),
    m_g(v),
    m_b(v),
    m_alpha(255)
{
}

Color::Color(byte r, byte g, byte b, byte a):
    m_r(r),
    m_g(g),
    m_b(b),
    m_alpha(255)
{
}

Color::Color(const Color& other):
    m_r(other.m_r),
    m_g(other.m_g),
    m_b(other.m_b),
    m_alpha(other.m_alpha)
{
}

Color::Color(Color&& other) noexcept:
    m_r(std::move(other.m_r)),
    m_g(std::move(other.m_g)),
    m_b(std::move(other.m_b)),
    m_alpha(std::move(other.m_alpha))
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

void Color::setAlpha(byte alpha)
{
    m_alpha = alpha;
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

byte Color::alpha() const
{
    return m_alpha;
}

Color& Color::operator=(const Color& other)
{
    m_r = other.m_r;
    m_g = other.m_g;
    m_b = other.m_b;
    m_alpha = other.m_alpha;

    return *this;
}