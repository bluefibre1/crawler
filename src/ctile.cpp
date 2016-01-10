#include "ctile.h"
#include "ccolors.h"

Tile::Tile()
    : m_style(ColorStyle::NORMAL)
    , m_fg(Colors::INVALID())
    , m_bg(Colors::INVALID())
    , m_value('x')
{
}

Tile::Tile(ColorStyle style, const Color& fg, const Color& bg, char value)
    : m_style(style)
    , m_fg(fg)
    , m_bg(bg)
    , m_value(value)
{
}

void Tile::setStyle(ColorStyle style)
{
    m_style = style;
}

const ColorStyle& Tile::getStyle() const
{
    return m_style;
}

void Tile::setForeground(Color color)
{
    m_fg = color;
}

const Color& Tile::getForeground() const
{
    return m_fg;
}

void Tile::setBackground(Color color)
{
    m_bg = color;
}

const Color& Tile::getBackground() const
{
    return m_bg;
}

void Tile::setValue(char ch)
{
    m_value = ch;
}

char Tile::getValue() const
{
    return m_value;
}
