#pragma once

#include "cobject.h"
#include "cworldcell.h"
#include "croom.h"

#include <vector>


class World : public Object
{
public:
    World();

    void addOnTop(int x, int y, const RoomSharedPtr& room);

    int getHeightAt(int x, int y, int z) const;

    Object* getRoom(int x, int y, int z) const;

    int getWidth() const { return m_width; }

    int getHeight() const { return m_height; }

    virtual void draw(Camera* c, Renderer* r) override;

private:
    RoomSharedPtrs m_rooms;
    WorldCells m_cells;
    int m_width;
    int m_height;
};

typedef std::shared_ptr<World> WorldSharedPtr;
