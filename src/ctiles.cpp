#include "ctiles.h"
#include "ccolors.h"

const Tile Tiles::EMPTY(Colors::BLACK(), Colors::BLACK(), ' ');
const Tile Tiles::WATER(Colors::BLUE(), Colors::BLUE(), '~');
const Tile Tiles::SAND(Colors::YELLOW(), Colors::SANDYELLOW(), '.');
const Tile Tiles::GRASS(Colors::DARK_GREEN(), Colors::GREEN(), ',');
const Tile Tiles::MOUNTAIN(Colors::GREY(), Colors::LIGHT_GREY(), 'X');
const Tile Tiles::CLOUDS(Colors::LIGHT_BLUE(), Colors::WHITE(), 'o');
const Tile Tiles::ICE_MOUNTAIN(Colors::WHITE(), Colors::ICY_BLUE(), 'A');
