#include "ctile.h"
#include "ccolors.h"

Tile::Tile()
    : m_fg(Colors::INVALID())
    , m_bg(Colors::INVALID())
    , m_value(CHAR_T('x'))
    , m_height(0)
{
}

Tile::Tile(const Color& fg, const Color& bg, Char value, int height)
    : m_fg(fg)
    , m_bg(bg)
    , m_value(value)
    , m_height(height)
{
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

void Tile::setValue(Char ch)
{
    m_value = ch;
}

Char Tile::getValue() const
{
    return m_value;
}
