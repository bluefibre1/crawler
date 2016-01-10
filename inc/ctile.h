#pragma once

#include "ccolor.h"

class Tile
{
public:
    Tile();
    Tile(const Color& fg, const Color& bg, char value);

    void setForeground(Color color);

    const Color& getForeground() const;

    void setBackground(Color color);

    const Color& getBackground() const;

    void setValue(char ch);

    char getValue() const;

private:
    Color m_fg;
    Color m_bg;
    char m_value;
};
