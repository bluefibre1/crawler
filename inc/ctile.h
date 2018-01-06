#pragma once

#include "ccolor.h"
#include "cstring.h"

#include <vector>

class Tile
{
public:
    Tile();
    Tile(const Color& fg, const Color& bg, Char value);

    void setForeground(Color color);

    const Color& getForeground() const;

    void setBackground(Color color);

    const Color& getBackground() const;

    void setValue(Char ch);

    Char getValue() const;

private:
    Color m_fg;
    Color m_bg;
    Char m_value;
};

typedef std::vector<const Tile*> TilePtrs;
typedef std::vector<TilePtrs> TilePtrSurface;
