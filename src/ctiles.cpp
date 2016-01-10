#include "ctiles.h"
#include "ccolors.h"

const Tile Tiles::EMPTY(Colors::BLACK(), Colors::BLACK(), ' ');
const Tile Tiles::WATER(Colors::BLUE(), Colors::BLUE(), '~');
const Tile Tiles::SAND(Colors::YELLOW(), Colors::YELLOW(), '.');
const Tile Tiles::GRASS(Colors::DARK_GREEN(), Colors::GREEN(), ',');
const Tile Tiles::MOUNTAIN(Colors::WHITE(), Colors::WHITE(), 'X');
const Tile Tiles::CLOUDS(Colors::WHITE(), Colors::WHITE(), 'o');
const Tile Tiles::ICE_MOUNTAIN(Colors::WHITE(), Colors::WHITE(), 'A');
