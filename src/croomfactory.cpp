#include "croomfactory.h"
#include "ctiles.h"

RoomSharedPtr RoomFactory::create(const RoomTemplateSharedPtr& t)
{
    RoomSharedPtr r(new Room());
    r->setName(t->getName());

    TilePtrSurface surface;
    createSurface(t->getSurface(), surface);
    r->setTilePtrSurface(surface);

    return r;
}

void RoomFactory::createSurface(const Strings& surface, TilePtrSurface& out)
{
    static bool init = false;
    static TilePtrs tiles;
    if (!init)
    {
        init = true;
        tiles.resize(256);
        tiles['#'] = &Tiles::WALL();
        tiles['.'] = &Tiles::GROUND();
        tiles['-'] = &Tiles::TABLE();
    }

    int rows = surface.size();
    out.resize(rows);
    for (int i = 0; i < rows; ++i)
    {
        const String& row = surface[i];
        TilePtrs& outRow = out[i];
        int cols = row.size();
        outRow.resize(cols);
        for (int j = 0; j < cols; ++j)
        {
            int c = row[j];
            const Tile* t = tiles[c];
            if (!t)
            {
                t = &Tiles::EMPTY();
            }
            outRow[j] = t;
        }
    }
}
