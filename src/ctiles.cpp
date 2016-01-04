#include "ctiles.h"


const Tile Tiles::EMPTY(ColorStyle::BRIGHT, Color::WHITE, Color::BLACK, ' ');
const Tile Tiles::WATER(ColorStyle::BRIGHT, Color::BLUE, Color::BLUE, ' ');
const Tile Tiles::GRASS(ColorStyle::NORMAL, Color::GREEN, Color::BLACK, '#');
const Tile Tiles::EARTH(ColorStyle::DIM, Color::YELLOW, Color::BLACK, '#');
const Tile Tiles::ROCK(ColorStyle::DIM, Color::WHITE, Color::BLACK, 'o');
const Tile Tiles::MOUNTAIN(ColorStyle::DIM, Color::WHITE, Color::BLACK, 'O');
const Tile Tiles::ICE_ROCK(ColorStyle::BRIGHT, Color::CYAN, Color::BLACK, 'o');
const Tile Tiles::ICE_MOUNTAIN(ColorStyle::BRIGHT, Color::WHITE, Color::BLACK, 'A');
