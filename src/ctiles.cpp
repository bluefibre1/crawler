#include "ctiles.h"
#include "ccolors.h"

#include <map>

const Tile& Tiles::EMPTY() { static Tile t(Colors::BLACK(), Colors::BLACK(), ' '); return t; }
const Tile& Tiles::WATER() { static Tile t(Colors::BLUE(), Colors::BLUE(), '~'); return t; }
const Tile& Tiles::SAND() { static Tile t(Colors::YELLOW(), Colors::SANDYELLOW(), '.'); return t; }
const Tile& Tiles::GRASS() { static Tile t(Colors::DARK_GREEN(), Colors::GREEN(), ','); return t; }
const Tile& Tiles::MOUNTAIN() { static Tile t(Colors::GREY(), Colors::LIGHT_GREY(), 'X'); return t; }
const Tile& Tiles::CLOUDS() { static Tile t(Colors::LIGHT_BLUE(), Colors::WHITE(), 'o'); return t; }
const Tile& Tiles::ICE_MOUNTAIN() { static Tile t(Colors::WHITE(), Colors::ICY_BLUE(), 'A'); return t; }

const Tile& Tiles::WALL() { static Tile t(Colors::GREY(), Colors::BLACK(), '#'); return t; }
const Tile& Tiles::GROUND() { static Tile t(Colors::WHITE(), Colors::BLACK(), '.'); return t; }
const Tile& Tiles::TABLE() { static Tile t(Colors::BROWN(), Colors::BLACK(), '-'); return t; }


void Tiles::convert(const Strings& tiles, TilePtrSurface* surface)
{
    if (!surface)
    {
        return;
    }

    typedef std::map<char, const Tile*> TileMap;
    static TileMap templates;
    if (templates.empty())
    {
        templates.insert(TileMap::value_type('#', &Tiles::WALL()));
        templates.insert(TileMap::value_type('.', &Tiles::GROUND()));
        templates.insert(TileMap::value_type('-', &Tiles::TABLE()));
    }

    surface->resize(tiles.size());
    int rowCounter = 0;
    std::for_each(
        tiles.begin(), tiles.end(), [&surface, &rowCounter] (const String& row)
        {
            TilePtrs& tiles = (*surface)[rowCounter];
            tiles.resize(row.size());

            int n = row.size();
            for (int i = 0; i < n; i++)
            {
                char c = row[i];
                auto t = templates.find(c);
                if (t != templates.end())
                {
                    tiles[i] = (*t).second;
                }
            }

            rowCounter++;
        });

}
