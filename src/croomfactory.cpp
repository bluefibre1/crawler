#include "croomfactory.h"
#include "ctiles.h"
#include "cworld.h"
#include "cmath.h"

#include <assert.h>
#include <math.h>

class RoomFactoryImpl
{
public:
    static WorldCell* generateGround(int size);
    static void generateHeights(int size, WorldCell* cells, float roughness, float height);
    static float averageSquare(int size, WorldCell* cells, int x, int y, int stride);
    static float averageDiamond(int size, WorldCell* cells, int x, int y, int stride);
};

WorldCell* RoomFactoryImpl::generateGround(int size)
{
    assert(Math::isPowerOf2(size));

    int width = size+1;
    int height = size+1;
    int n = width * height;
    WorldCell* cells = new WorldCell[n];

    generateHeights(size, cells, 0.7f, 2000.0f);

    const Tile* templates[] =
        {
            &Tiles::WATER(),
            &Tiles::WATER(),
            &Tiles::WATER(),
            &Tiles::SAND(),
            &Tiles::GRASS(),
            &Tiles::GRASS(),
            &Tiles::GRASS(),
            &Tiles::GRASS(),
            &Tiles::GRASS(),
            &Tiles::MOUNTAIN(),
            &Tiles::MOUNTAIN(),
            &Tiles::MOUNTAIN(),
            &Tiles::MOUNTAIN(),
            &Tiles::CLOUDS(),
            &Tiles::ICE_MOUNTAIN(),
            &Tiles::ICE_MOUNTAIN(),
        };

    int numTemplates = sizeof(templates) / sizeof(Tile*);

    int maxHeight = INT_MIN;
    int minHeight = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        int h = cells[i].getZ();
        if (h > maxHeight)
        {
            maxHeight = h;
        }

        if (h < minHeight)
        {
            minHeight = h;
        }
    }

    int deltaHeight = maxHeight - minHeight;
    for (int i = 0; i < n; i++)
    {
        int templateIndex = deltaHeight != 0 ? (cells[i].getZ() - minHeight) * (numTemplates) / deltaHeight : 0;
        if (templateIndex >= numTemplates)
        {
            templateIndex = numTemplates-1;
        }

        cells[i].setTile(templates[templateIndex]);
        cells[i].setZ(0);
    }
    return cells;
}

void RoomFactoryImpl::generateHeights(int size, WorldCell* cells, float roughness, float height)
{
    float ratio = (float)pow(2.0, -roughness);
    float scale = height * ratio;
    int verticeSize = size + 1;
    int stride = size / 2;
    int n = verticeSize * verticeSize;

    // Init four corners.
    cells[0].setZ(0);
    cells[size].setZ(0);
    cells[size * verticeSize].setZ(0);
    cells[size * verticeSize+size].setZ(0);

    while (stride > 0)
    {
        for (int i = stride; i < size;  i += stride)
        {
            for (int j = stride; j < size; j += stride)
            {
                assert(i * verticeSize + j < n);
                cells[i * verticeSize + j].setZ(
                    (int)(scale * Math::wrapRandom() * 0.5f +
                          averageSquare(verticeSize, cells, i, j, stride)));
                j += stride;
            }
            i += stride;
        }

        int oddLine = 0;
        for (int i = 0; i < size; i += stride)
        {
            oddLine = (oddLine == 0);
            for (int j = 0; j < size; j += stride)
            {
                if ((oddLine) && j == 0)
                {
                    j += stride;
                }

                int index = i * verticeSize + j;
                assert(index < n);
                cells[index].setZ(
                    (int)(scale * Math::wrapRandom() * 0.5f +
                          averageDiamond(verticeSize, cells, i, j, stride)));

                if (i==0)
                {
                    assert(size*verticeSize < n);
                    cells[(size*verticeSize) + j].setZ(cells[index].getZ());
                }
                if (j==0)
                {
                    assert((i*verticeSize)+size < n);
                    cells[(i*verticeSize) + size].setZ(cells[index].getZ());
                }

                j+=stride;
            }
        }

        scale *= ratio;
        stride >>= 1;
    }
}

float RoomFactoryImpl::averageSquare(int size, WorldCell* cells, int x, int y, int stride)
{
    return ((float) (cells[((x-stride)*size) + y-stride].getZ() +
                     cells[((x-stride)*size) + y+stride].getZ() +
                     cells[((x+stride)*size) + y-stride].getZ() +
                     cells[((x+stride)*size) + y+stride].getZ()) * 0.25f);
}

float RoomFactoryImpl::averageDiamond(int size, WorldCell* cells, int x, int y, int stride)
{
    if (x == 0)
    {
        return ((float) (cells[(x*size) + y-stride].getZ() +
                         cells[(x*size) + y+stride].getZ() +
                         cells[((size-1-stride)*size) + y].getZ() +
                         cells[((x+stride)*size) + y].getZ()) * 0.25f);
    }
    else if (x == size-1)
    {
        return ((float) (cells[(x*size) + y-stride].getZ() +
                         cells[(x*size) + y+stride].getZ() +
                         cells[((x-stride)*size) + y].getZ() +
                         cells[((0+stride)*size) + y].getZ()) * 0.25f);
    }
    else if (y == 0)
    {
        return ((float) (cells[((x-stride)*size) + y].getZ() +
                         cells[((x+stride)*size) + y].getZ() +
                         cells[(x*size) + y+stride].getZ() +
                         cells[(x*size) + size-1-stride].getZ()) * 0.25f);
    }
    else if (y == size-1)
    {
        return ((float) (cells[((x-stride)*size) + y].getZ() +
                         cells[((x+stride)*size) + y].getZ() +
                         cells[(x*size) + y-stride].getZ() +
                         cells[(x*size) + 0+stride].getZ()) * 0.25f);
    }
    else
    {
        return ((float) (cells[((x-stride)*size) + y].getZ() +
                         cells[((x+stride)*size) + y].getZ() +
                         cells[(x*size) + y-stride].getZ() +
                         cells[(x*size) + y+stride].getZ()) * 0.25f);
    }
}

////////////////////////////////////////////////////////////////////////////////

RoomSharedPtr RoomFactory::create(const RoomTemplateSharedPtr& t)
{
    RoomSharedPtr r(new Room());
    r->setName(t->getName());

    static bool init = false;
    static TilePtrs tiles;
    if (!init)
    {
        init = true;
        tiles.resize(256);
        tiles['#'] = &Tiles::WALL();
        tiles['.'] = &Tiles::GROUND();
        tiles['-'] = &Tiles::TABLE();
        tiles['|'] = &Tiles::DOOR();
        tiles['_'] = &Tiles::STAIR_LOW();
        tiles['='] = &Tiles::STAIR_HIGH();
    }

    size_t height = 0;
    size_t width = 0;
    for (auto& layer : t->getLayers())
    {
        if (height < layer.size())
        {
            height = layer.size();
        }

        for (auto& row : layer)
        {
            if (width < row.size())
            {
                width = row.size();
            }
        }
    }

    size_t layerSize = width*height;
    size_t totalSize = layerSize*t->getLayers().size();
    assert(totalSize > 0);
    WorldCell* cells = new WorldCell[totalSize];
    int currentHeight = 0;
    int maxLayerHeight = 0;
    size_t z = 0;
    for (auto& layer : t->getLayers())
    {
        maxLayerHeight = 0;
        size_t y = 0;
        for (auto& row : layer)
        {
            size_t x = 0;
            for (auto& c : row)
            {
                assert(c < (Char)tiles.size());
                int i = x + y * width + z * layerSize;
                WorldCell& cell = cells[i];
                cell.setRoom(r.get());

                const Tile* tile = tiles[c];
                cell.setTile(tile);
                cell.setZ(currentHeight);

                if (tile && maxLayerHeight < tile->getHeight())
                {
                    maxLayerHeight = tile->getHeight();
                }
                x++;
            }
            y++;
        }

        if (z > 0)
        {
            for (size_t y = 0; y < height; ++y)
            {
                for (size_t x = 0; x < width; ++x)
                {
                    int i = x + y * width + z * layerSize;
                    WorldCell& over = cells[i];
                    if (over.getTile())
                    {
                        WorldCell& under = cells[i - layerSize];
                        over.setUnder(&under);
                    }
                }
            }
        }

        currentHeight += maxLayerHeight;
        z++;
    }
    r->setCells(width, height, cells);

    return r;
}

RoomSharedPtr RoomFactory::createLandscape(const String& name, int size)
{
    RoomSharedPtr r(new Room());
    r->setName(name);

    r->setCells(size, size, RoomFactoryImpl::generateGround(size));

    return r;
}
