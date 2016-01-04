#include "ctile.h"

Tile::Tile()
  : m_style(ColorStyle::NORMAL)
  , m_fg(Color::INVALID)
  , m_bg(Color::INVALID)
  , m_value('x')
{
}

Tile::Tile(ColorStyle style, Color fg, Color bg, char value)
  : m_style(style)
  , m_fg(fg)
  , m_bg(bg)
  , m_value(value)
{
}

const ColorStyle& Tile::getStyle() const
{
  return m_style;
}
  
const Color& Tile::getForeground() const
{
  return m_fg;
}

const Color& Tile::getBackground() const
{
  return m_bg;
}

char Tile::getValue() const
{
  return m_value;
}


