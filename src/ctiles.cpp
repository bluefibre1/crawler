#include "ctiles.h"


const Tile Tiles::EMPTY(ColorStyle::DIM, Color::BLACK, Color::BLACK, ' ');
const Tile Tiles::WATER(ColorStyle::BRIGHT, Color::BLUE, Color::BLUE, '~');
const Tile Tiles::SAND(ColorStyle::DIM, Color::YELLOW, Color::YELLOW, '.');
const Tile Tiles::GRASS(ColorStyle::DIM, Color::GREEN, Color::GREEN,',' );
const Tile Tiles::MOUNTAIN(ColorStyle::DIM, Color::WHITE, Color::WHITE, 'X');
const Tile Tiles::CLOUDS(ColorStyle::BRIGHT, Color::WHITE, Color::WHITE, 'o');
const Tile Tiles::ICE_MOUNTAIN(ColorStyle::DIM, Color::WHITE, Color::WHITE, 'A');
