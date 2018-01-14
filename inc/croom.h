#pragma once

#include "cobject.h"
#include "ctile.h"
#include "cstring.h"

#include <vector>

class WorldCell;

class Room : public Object
{
public:
    Room();
     ~Room();

    void setCells(int width, int height, WorldCell* cells);

    WorldCell* getCells() const { return m_cells; }

    void setName(const String& name);

    int getWidth() const { return m_width; }

    int getHeight() const { return m_height; }

private:
    String m_name;
    WorldCell* m_cells;
    int m_width;
    int m_height;
};

typedef std::shared_ptr<Room> RoomSharedPtr;
typedef std::vector<RoomSharedPtr> RoomSharedPtrs;
