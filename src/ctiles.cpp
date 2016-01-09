#include "ctiles.h"


const Tile Tiles::EMPTY(ColorStyle::DIM, Color::RED, Color::BLACK, 'X');
const Tile Tiles::WATER(ColorStyle::BRIGHT, Color::BLUE, Color::BLUE, ' ');
const Tile Tiles::SAND(ColorStyle::DIM, Color::YELLOW, Color::YELLOW, '.');
const Tile Tiles::GRASS(ColorStyle::DIM, Color::GREEN, Color::GREEN,'\"' );
const Tile Tiles::MOUNTAIN(ColorStyle::DIM, Color::WHITE, Color::WHITE, 'X');
const Tile Tiles::ICE_MOUNTAIN(ColorStyle::BRIGHT, Color::WHITE, Color::WHITE, 'A');
