#pragma once

#include "ccolor.h"

class Tile
{
 public:
  Tile();
  Tile(ColorStyle style, Color fg, Color bg, char value);

  const ColorStyle& getStyle() const;
  
  const Color& getForeground() const;

  const Color& getBackground() const;

  char getValue() const;
 
 private:
  ColorStyle m_style;
  Color m_fg;
  Color m_bg;  
  char m_value;
};
