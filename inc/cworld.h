#pragma once

#include "cobject.h"
#include "ctile.h"

#include <vector>

class World : public Object
{
public:
    World();
    virtual ~World();

    void generate(int size);

    int getHeightAt(int x, int y);

    int getWidth() const { return m_width; }

    int getHeight() const { return m_height; }

    virtual void draw(Renderer* r) override;

private:
    void generateHeights(int size, float roughness, float height);
    float averageSquare(int x, int y, int stride, int size, int* array);
    float averageDiamond(int x, int y, int stride, int size, int* array);

    int m_width;
    int m_height;
    const Tile** m_tiles;
    int* m_heights;
};

typedef std::shared_ptr<World> WorldSharedPtr;
