#include "ccolor.h"
#include "ccolors.h"

Color::Color()
    : m_color(Colors::WHITE().getValue())
{

}

Color::Color(int c)
    : m_color(c)
{

}

bool Color::operator==(const Color& c) const
{
    return c.m_color == m_color;
}

bool Color::operator!=(const Color& c) const
{
    return c.m_color != m_color;
}
