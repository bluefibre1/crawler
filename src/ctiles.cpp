#include "ctiles.h"
#include "ccolors.h"

const Tile Tiles::EMPTY(ColorStyle::DIM, Colors::BLACK(), Colors::BLACK(), ' ');
const Tile Tiles::WATER(ColorStyle::BRIGHT, Colors::BLUE(), Colors::BLUE(), '~');
const Tile Tiles::SAND(ColorStyle::DIM, Colors::YELLOW(), Colors::YELLOW(), '.');
const Tile Tiles::GRASS(ColorStyle::DIM, Colors::DARK_GREEN(), Colors::GREEN(), ',');
const Tile Tiles::MOUNTAIN(ColorStyle::DIM, Colors::WHITE(), Colors::WHITE(), 'X');
const Tile Tiles::CLOUDS(ColorStyle::BRIGHT, Colors::WHITE(), Colors::WHITE(), 'o');
const Tile Tiles::ICE_MOUNTAIN(ColorStyle::DIM, Colors::WHITE(), Colors::WHITE(), 'A');
