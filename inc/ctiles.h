#pragma once

#include "ctile.h"
#include "cstring.h"

class Tiles
{
public:

    static const Tile& EMPTY();
    static const Tile& WATER();
    static const Tile& SAND();
    static const Tile& GRASS();
    static const Tile& MOUNTAIN();
    static const Tile& CLOUDS();
    static const Tile& ICE_MOUNTAIN();

    static const Tile& WALL();
    static const Tile& GROUND();
    static const Tile& TABLE();

    static void convert(const Strings& tiles, TilePtrSurface* surface);

};
