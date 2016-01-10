#pragma once

#include "ccolor.h"

class Tile
{
public:
    Tile();
    Tile(ColorStyle style, const Color& fg, const Color& bg, char value);

    void setStyle(ColorStyle style);

    const ColorStyle& getStyle() const;

    void setForeground(Color color);

    const Color& getForeground() const;

    void setBackground(Color color);

    const Color& getBackground() const;

    void setValue(char ch);

    char getValue() const;

private:
    ColorStyle m_style;
    Color m_fg;
    Color m_bg;
    char m_value;
};
