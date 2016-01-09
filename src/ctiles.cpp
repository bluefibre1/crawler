#include "ctiles.h"


const Tile Tiles::EMPTY(ColorStyle::BRIGHT, Color::RED, Color::RED, 'X');
const Tile Tiles::WATER(ColorStyle::BRIGHT, Color::BLUE, Color::BLUE, ' ');
const Tile Tiles::GRASS(ColorStyle::NORMAL, Color::GREEN, Color::GREEN, ' ');
const Tile Tiles::EARTH(ColorStyle::DIM, Color::YELLOW, Color::YELLOW, ' ');
const Tile Tiles::ROCK(ColorStyle::BRIGHT, Color::WHITE, Color::RED, ' ');
const Tile Tiles::MOUNTAIN(ColorStyle::BRIGHT, Color::WHITE, Color::BLACK, ' ');
const Tile Tiles::ICE_ROCK(ColorStyle::BRIGHT, Color::CYAN, Color::CYAN, ' ');
const Tile Tiles::ICE_MOUNTAIN(ColorStyle::BRIGHT, Color::WHITE, Color::WHITE, ' ');
