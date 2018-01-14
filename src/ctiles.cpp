#include "ctiles.h"
#include "ccolors.h"

const Tile& Tiles::EMPTY() { static Tile t(Colors::BLACK(), Colors::BLACK(), ' ', 0); return t; }
const Tile& Tiles::WATER() { static Tile t(Colors::BLUE(), Colors::BLUE(), '~', 1); return t; }
const Tile& Tiles::SAND() { static Tile t(Colors::YELLOW(), Colors::SAND_YELLOW(), '.', 1); return t; }
const Tile& Tiles::GRASS() { static Tile t(Colors::DARK_GREEN(), Colors::GREEN(), ',', 1); return t; }
const Tile& Tiles::MOUNTAIN() { static Tile t(Colors::GREY(), Colors::LIGHT_GREY(), 'X', 1); return t; }
const Tile& Tiles::CLOUDS() { static Tile t(Colors::LIGHT_BLUE(), Colors::WHITE(), 'o', 1); return t; }
const Tile& Tiles::ICE_MOUNTAIN() { static Tile t(Colors::WHITE(), Colors::ICY_BLUE(), 'A', 1); return t; }

const Tile& Tiles::WALL() { static Tile t(Colors::GREY(), Colors::WHITE(), CHAR_T('#'), 2); return t; }
const Tile& Tiles::GROUND() { static Tile t(Colors::WHITE(), Colors::BLACK(), CHAR_T('.'), 0); return t; }
const Tile& Tiles::TABLE() { static Tile t(Colors::BROWN(), Colors::BLACK(), CHAR_T('-'), 2); return t; }
const Tile& Tiles::DOOR() { static Tile t(Colors::BROWN(), Colors::BLACK(), CHAR_T('|'), 0); return t; }
const Tile& Tiles::STAIR_LOW() { static Tile t(Colors::BROWN(), Colors::BLACK(), CHAR_T('_'), 1); return t; }
const Tile& Tiles::STAIR_HIGH() { static Tile t(Colors::BROWN(), Colors::BLACK(), CHAR_T('='), 2); return t; }
