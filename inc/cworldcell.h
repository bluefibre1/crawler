#pragma once

#include "ctile.h"
#include "cobject.h"

#include <vector>

class WorldCell
{
public:
    WorldCell();

    void setUnder(WorldCell* under);
    WorldCell* getTop();
    WorldCell* getOver() const { return m_over; }
    WorldCell* getUnder() const { return m_under; }
    WorldCell* getBottom();

    void setTile(const Tile* tile) { m_tile = tile; }
    const Tile* getTile() const { return m_tile; }

    void setZ(int z) { m_z = z; }
    int getZ() const { return m_z; }

    int getSmook() const;

    void setRoom(Object* room) { m_room = room; }
    Object* getRoom() const { return m_room; }

private:
    Object* m_room;
    WorldCell* m_over;
    WorldCell* m_under;
    const Tile* m_tile;
    int m_z;
};

typedef std::vector<WorldCell*> WorldCells;
