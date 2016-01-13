#include "cworld.h"

#include "ctiles.h"
#include "crenderer.h"
#include "cmath.h"

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>

World::World()
    : m_width(0)
    , m_height(0)
    , m_tiles(nullptr)
    , m_heights(nullptr)
{

}

World::~World()
{
    delete [] m_tiles;
    delete [] m_heights;
}

int World::getHeightAt(int x, int y)
{
    int i = x + y * m_width;
    return m_heights[i];
}

void World::generate(int size)
{
    assert(Math::isPowerOf2(size));

    m_width = size+1;
    m_height = size+1;

    int n = m_width * m_height;
    delete [] m_tiles;
    m_tiles = new const Tile*[n];

    generateHeights(size, 0.7f, 2000.0f);

    const Tile* templates[] =
        {
            &Tiles::WATER,
            &Tiles::WATER,
            &Tiles::WATER,
            &Tiles::WATER,
            &Tiles::SAND,
            &Tiles::SAND,
            &Tiles::GRASS,
            &Tiles::GRASS,
            &Tiles::GRASS,
            &Tiles::GRASS,
            &Tiles::MOUNTAIN,
            &Tiles::MOUNTAIN,
            &Tiles::MOUNTAIN,
            &Tiles::CLOUDS,
            &Tiles::ICE_MOUNTAIN
        };

    int numTemplates = sizeof(templates) / sizeof(Tile*);

    int maxHeight = INT_MIN;
    int minHeight = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        int h = m_heights[i];
        if (h > maxHeight)
        {
            maxHeight = h;
        }

        if (h < minHeight)
        {
            minHeight = h;
        }
        //printf("%d ", h);
    }

    int deltaHeight = maxHeight - minHeight;

    //printf("%d\n", deltaHeight);
    //exit(0);

    for (int i = 0; i < n; i++)
    {

        int templateIndex = deltaHeight != 0 ? (m_heights[i] - minHeight) * (numTemplates) / deltaHeight : 0;
        if (templateIndex >= numTemplates)
        {
            templateIndex = numTemplates-1;
        }

        m_tiles[i] = templates[templateIndex];
    }
}

void World::draw(Renderer* r)
{
    int ox = r->getOriginX();
    int oy = r->getOriginY();
    int w = r->getWidth() + ox;
    int h = r->getHeight() + oy;

    for (int y = oy; y < h; y++)
    {
        if (y < 0 || y >= m_height)
        {
            continue;
        }

        for (int x = ox; x < w; x++)
        {
            if (x < 0 || x >= m_width)
            {
                continue;
            }
            int idx = x + y * m_width;
            r->draw(x, y, 0, m_tiles[idx]);
        }
    }
}

void World::generateHeights(int size, float roughness, float height)
{
    float ratio = (float)pow(2.0, -roughness);
    float scale = height * ratio;
    int verticeSize = size + 1;
    int stride = size / 2;
    int n = verticeSize * verticeSize;
    delete [] m_heights;
    m_heights = new int[n];

    // Init four corners.
    m_heights[0] = 0;
    m_heights[size] = 0;
    m_heights[size * verticeSize] = 0;
    m_heights[size * verticeSize+size] = 0;

    while (stride > 0)
    {
        for (int i = stride; i < size;  i += stride)
        {
            for (int j = stride; j < size; j += stride)
            {
                assert(i * verticeSize + j < n);
                m_heights[i * verticeSize + j] = (int)(scale * Math::wrapRandom() * 0.5f +
                                                       averageSquare(i, j, stride, verticeSize, m_heights));
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
                m_heights[index] = (int)(scale * Math::wrapRandom() * 0.5f +
                                         averageDiamond(i, j, stride, verticeSize, m_heights));

                if (i==0)
                {
                    assert(size*verticeSize < n);
                    m_heights[(size*verticeSize) + j] = m_heights[index];
                }
                if (j==0)
                {
                    assert((i*verticeSize)+size < n);
                    m_heights[(i*verticeSize) + size] = m_heights[index];
                }

                j+=stride;
            }
        }

        scale *= ratio;
        stride >>= 1;
    }
}

float World::averageSquare(int x, int y, int stride, int size, int* array)
{
    return ((float) (array[((x-stride)*size) + y-stride] +
                     array[((x-stride)*size) + y+stride] +
                     array[((x+stride)*size) + y-stride] +
                     array[((x+stride)*size) + y+stride]) * 0.25f);
}

float World::averageDiamond(int x, int y, int stride, int size, int* array)
{
    if (x == 0)
    {
        return ((float) (array[(x*size) + y-stride] +
                         array[(x*size) + y+stride] +
                         array[((size-1-stride)*size) + y] +
                         array[((x+stride)*size) + y]) * 0.25f);
    }
    else if (x == size-1)
    {
        return ((float) (array[(x*size) + y-stride] +
                         array[(x*size) + y+stride] +
                         array[((x-stride)*size) + y] +
                         array[((0+stride)*size) + y]) * 0.25f);
    }
    else if (y == 0)
    {
        return ((float) (array[((x-stride)*size) + y] +
                         array[((x+stride)*size) + y] +
                         array[(x*size) + y+stride] +
                         array[(x*size) + size-1-stride]) * 0.25f);
    }
    else if (y == size-1)
    {
        return ((float) (array[((x-stride)*size) + y] +
                         array[((x+stride)*size) + y] +
                         array[(x*size) + y-stride] +
                         array[(x*size) + 0+stride]) * 0.25f);
    }
    else
    {
        return ((float) (array[((x-stride)*size) + y] +
                         array[((x+stride)*size) + y] +
                         array[(x*size) + y-stride] +
                         array[(x*size) + y+stride]) * 0.25f);
    }
}
